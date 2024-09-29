#ifndef VBO_CLASS_H
#define VBO_CLASS_H

#include <vector>
#include <glad/glad.h>
#include "Vertex.h"

class VBO
{
public:
	GLuint ID;
	
	VBO(std::vector<Vertex> &vertices);

	void Bind();
	void Unbind();
	void Delete();
};

#endif