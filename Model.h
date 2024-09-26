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
	Model() {};
	Model(std::string filePath);
	~Model();

	std::vector<Mesh> Meshes;
	std::vector<glm::mat4> Transforms;
	std::vector<Texture> Textures;

	void Draw(Shader& shader, Camera& camera);

protected:
	void LoadModel();
	void LoadNode(
		tinygltf::Model& model,
		int nodeIdx,
		const glm::mat4& parentTransform = glm::mat4(1.0f)
	);
	Mesh LoadMesh(
		tinygltf::Model& model,
		int meshId
	);

private:
	std::string filePath;
};

#endif // MODEL_CLASS_H