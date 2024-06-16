#include "Mesh.h"

Mesh::Mesh(
	std::vector<Entities::Vertex> &vertices,
	std::vector<GLuint> &indices,
	std::vector<Texture> &textures
) {
	this->vertices = vertices;
	this->indices = indices;
	this->textures = textures;

	setupMesh();
}

void Mesh::Draw(Shader& shader, Camera& camera)
{
	// Bind
	shader.Activate();
	VAO.Bind();

	// Set up textures
	unsigned int numDiffuse = 0;
	unsigned int numSpecular = 0;

	for (unsigned int i = 0; i < textures.size(); i++)
	{
		std::string num;
		std::string type = textures[i].type;

		if (type == "diffuse")
			num = std::to_string(numDiffuse++);
		else if (type == "specular")
			num = std::to_string(numSpecular++);

		textures[i].texUnit(shader, (type + num).c_str(), i);
		textures[i].Bind();
	}

	// Set up view
	glUniform3f(
		glGetUniformLocation(shader.ID, "viewPos"),
		camera.Position.x, camera.Position.y, camera.Position.z
	);
	camera.Matrix(shader, "camMatrix");

	// Draw
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);

	// Unbind
	VAO.Unbind();
}

void Mesh::setupMesh()
{
	VAO.Bind();

	// Create Vertex Buffer Object and Element Buffer Object
	VBO VBO(vertices);
	EBO EBO(indices);

	// Link VBO to VAO
	auto stride = sizeof(vertices[0]);
	VAO.LinkAttrib(VBO, 0, 3, GL_FLOAT, stride, (void*)0);
	VAO.LinkAttrib(VBO, 1, 3, GL_FLOAT, stride, (void*)(3 * sizeof(float)));
	VAO.LinkAttrib(VBO, 2, 3, GL_FLOAT, stride, (void*)(6 * sizeof(float)));
	VAO.LinkAttrib(VBO, 3, 2, GL_FLOAT, stride, (void*)(9 * sizeof(float)));

	// Unbind all to prevent accidentally modifying them
	VAO.Unbind();
	VBO.Unbind();
	EBO.Unbind();
}