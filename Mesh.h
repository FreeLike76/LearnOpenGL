#ifndef MESH_CLASS_H
#define MESH_CLASS_H

#include <string>
#include <vector>

#include <glm/glm.hpp>

#include "Vertex.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"
#include "Texture.h"
#include "Camera.h"

class Mesh
{
public:
	std::vector <Entities::Vertex> vertices;
	std::vector <GLuint> indices;
	std::vector <Texture> textures;

	VAO VAO;

	Mesh(
		std::vector <Entities::Vertex> &vertices,
		std::vector <GLuint> &indices,
		std::vector <Texture> &textures
	);
	
	void Draw(Shader& shader, Camera& camera);

protected:
	//VBO VBO;
	//EBO EBO;

	void setupMesh();
};

#endif // MESH_CLASS_H