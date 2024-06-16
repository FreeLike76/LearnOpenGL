#include "Texture.h"

Texture::Texture(
	const char* image,
	const char* texType,
	GLuint slot,
	GLenum format,
	GLenum pixelType
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

	readImage(image, format, pixelType);

	// Unbind
	glBindTexture(GL_TEXTURE_2D, 0);
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
	GLenum format,
	GLenum pixelType
) {
	int width, height, nrChannels;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* data = stbi_load(image, &width, &height, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, pixelType, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);
}