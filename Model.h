#ifndef MODEL_CLASS_H
#define MODEL_CLASS_H

#include <string>
#include <vector>

#include <stb/stb_image.h>
#include <tinygltf/tiny_gltf.h>
//#include <glm/glm.hpp>

//#include <json/json.h>
//using json = nlohmann::json;

#include "Mesh.h"

class Model
{
public:
	Model(std::string filePath);
	~Model();

	std::vector<Mesh> Meshes;
	std::vector<Texture> Textures;

	void Draw(Shader& shader);

protected:
	void LoadModel();
	Mesh LoadMesh(tinygltf::Model& model, int meshId);

private:
	std::string filePath;
};

#endif // MODEL_CLASS_H