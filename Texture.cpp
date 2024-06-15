#include "Texture.h"

Texture::Texture(
	const char* image,
	GLenum texType,
	GLuint slot,
	GLenum format,
	GLenum pixelType
) {
	type = texType;
	glGenTextures(1, &ID);

	this->slot = slot;
	glActiveTexture(GL_TEXTURE0 + this->slot);
	glBindTexture(type, ID);

	// xyz -> str
	glTexParameteri(type, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(type, GL_TEXTURE_WRAP_T, GL_REPEAT);
	
	glTexParameteri(type, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(type, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	readImage(image, format, pixelType);

	// Unbind
	glBindTexture(type, 0);
}

void Texture::texUnit(Shader& shader, const char* uniform, GLuint unit)
{
	GLuint texUni = glGetUniformLocation(shader.ID, uniform);
	shader.Activate();
	glUniform1i(texUni, unit);
}

void Texture::Bind()
{
	glActiveTexture(GL_TEXTURE0 + this->slot);
	glBindTexture(type, ID);
}

void Texture::Unbind()
{
	glBindTexture(type, 0);
}

void Texture::Delete()
{
	glDeleteTextures(1, &ID);
}

void Texture::readImage(const char* image, GLenum format, GLenum pixelType)
{
	int width, height, nrChannels;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* data = stbi_load(image, &width, &height, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(type, 0, format, width, height, 0, format, pixelType, data);
		glGenerateMipmap(type);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);
}