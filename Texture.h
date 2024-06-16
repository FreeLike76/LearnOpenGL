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

	Texture(const char* image, const char* texType, GLuint slot, GLenum format, GLenum pixelType);

	void texUnit(Shader& shader, const char* uniform, GLuint unit);
	void Bind();
	void Unbind();
	void Delete();

private:
	void readImage(const char* image, GLenum format, GLenum pixelType);
};

#endif