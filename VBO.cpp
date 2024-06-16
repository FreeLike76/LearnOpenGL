#include "VBO.h"

VBO::VBO(std::vector<Entities::Vertex> &vertices)
{
	ID = -1;
	glGenBuffers(1, &ID);
	glBindBuffer(GL_ARRAY_BUFFER, ID);
	glBufferData(
		GL_ARRAY_BUFFER,
		vertices.size() * sizeof(vertices[0]), // Safe as sizeof vert[0] is evaluated at compile time
		vertices.data(),
		GL_STATIC_DRAW
	);
}

void VBO::Bind()
{
	glBindBuffer(GL_ARRAY_BUFFER, ID);
}

void VBO::Unbind()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VBO::Delete()
{
	glDeleteBuffers(1, &ID);
}