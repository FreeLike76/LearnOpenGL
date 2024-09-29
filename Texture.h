#ifndef TEXTURE_CLASS_H
#define TEXTURE_CLASS_H

#include <stdexcept>

#include <glad/glad.h>
#include <stb/stb_image.h>

#include "ShaderClass.h"

//namespace TextureType {
//	enum TextureType
//	{
//		DIFFUSE,
//		SPECULAR
//	};
//	const char* ToString(TextureType type)
//	{
//		switch (type)
//		{
//		case DIFFUSE: return "diffuse";
//		case SPECULAR: return "specular";
//		default: throw std::invalid_argument("Invalid texture type");
//		}
//	}
//}

class Texture
{
public:
	GLuint ID;
	const char* type;
	GLuint slot;

	Texture(const unsigned char* data, int width, int height, int nChannels, const char* texType, GLuint slot);
	Texture(const char* filePath, const char* texType, GLuint slot);

	void texUnit(Shader& shader, const char* uniform, GLuint unit);
	void Bind();
	void Unbind();
	void Delete();

protected:
	void setupGLTexture(const char* texType, GLuint slot);

private:
	void generateTexture(const unsigned char* data, int width, int height, int nChannels, GLenum pixelType = GL_UNSIGNED_BYTE);
	void readImage(const char* filePath, GLenum pixelType = GL_UNSIGNED_BYTE);
};

#endif