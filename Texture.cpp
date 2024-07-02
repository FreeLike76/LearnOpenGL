#include "Texture.h"

GLenum GetFormat(int nChannels) {
	switch (nChannels)
	{
	case 1: return GL_RED;
	case 3: return GL_RGB;
	case 4: return GL_RGBA;
	default: throw std::invalid_argument("Invalid number of channels");
	}
}

void Texture::setupGLTexture(
	const char* texType,
	GLuint slot
) {
	type = texType;
	glGenTextures(1, &ID);

	this->slot = slot;
	glActiveTexture(GL_TEXTURE0 + this->slot);
	glBindTexture(GL_TEXTURE_2D, ID);

	// xyz -> str
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

Texture::Texture(
	const unsigned char* data,
	int width,
	int height,
	int nChannels,
	const char* texType,
	GLuint slot
) {
	setupGLTexture(texType, slot);
	generateTexture(data, width, height, nChannels);
	glBindTexture(GL_TEXTURE_2D, 0); // Unbind
}

Texture::Texture(
	const char* image,
	const char* texType,
	GLuint slot
) {
	setupGLTexture(texType, slot);
	readImage(image);
	glBindTexture(GL_TEXTURE_2D, 0); // Unbind
}

void Texture::texUnit(
	Shader& shader,
	const char* uniform,
	GLuint unit
) {
	GLuint texUni = glGetUniformLocation(shader.ID, uniform);
	shader.Activate();
	glUniform1i(texUni, unit);
}

void Texture::Bind()
{
	glActiveTexture(GL_TEXTURE0 + this->slot);
	glBindTexture(GL_TEXTURE_2D, ID);
}

void Texture::Unbind()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::Delete()
{
	glDeleteTextures(1, &ID);
}

void Texture::readImage(
	const char* image,
	GLenum pixelType
) {
	// Config
	stbi_set_flip_vertically_on_load(true);
	
	// Load image
	int width, height, nChannels;
	unsigned char* data = stbi_load(image, &width, &height, &nChannels, 0);
	generateTexture(data, width, height, nChannels, pixelType);

	stbi_image_free(data);
}

void Texture::generateTexture(
	const unsigned char* data,
	int width,
	int height,
	int nChannels,
	GLenum pixelType
) {
	if (!data)
	{
		std::cout << "[Texture::generateTexture] No data!" << std::endl;
		return;
	}

	GLenum format = GetFormat(nChannels);
	glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, pixelType, data);
	glGenerateMipmap(GL_TEXTURE_2D);
}