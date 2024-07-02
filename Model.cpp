#include "Model.h"

#include <stdexcept>

template <typename T>
std::vector<T> LoadBufferData(
	tinygltf::Model& model,
	tinygltf::Accessor& accessor
) {
	std::vector<T> data;
	const tinygltf::BufferView bufferView = model.bufferViews[accessor.bufferView];
	const tinygltf::Buffer& buffer = model.buffers[bufferView.buffer];
	
	const size_t count = accessor.count;
	const size_t offset = bufferView.byteOffset + accessor.byteOffset;
	const size_t stride = accessor.ByteStride(bufferView);
	const size_t componentSize = sizeof(T);

	data.resize(count);

	/*
	for (size_t i = 0; i < count; i++)
	{
		const T* ptr = reinterpret_cast<const T*>(&buffer.data[offset + i * stride]);
		data.push_back(*ptr);
	}
	*/

	if (stride == componentSize)
		std::memcpy(data.data(), &buffer.data[offset], count * componentSize);
	else
		for (size_t i = 0; i < count; i++)
			std::memcpy(&data[i], &buffer.data[offset + i * stride], componentSize);

	return data;
}

std::vector<Texture> LoadTextures(tinygltf::Model& model)
{
	// Load all gltf images as textures
	std::vector<Texture> images;
	for (const tinygltf::Image& gltfImage : model.images)
	{
		Texture image(
			gltfImage.image.data(),
			gltfImage.width,
			gltfImage.height,
			gltfImage.component,
			"diffuse",
			0
		);
		images.push_back(image);
	}

	// Go over gltf textures and create references vector
	std::vector<Texture> textureReferences;
	for (const tinygltf::Texture& gltfTexture : model.textures)
	{
		const tinygltf::Image& gltfImage = model.images[gltfTexture.source];
		textureReferences.push_back(images[gltfTexture.source]);
	}

	return textureReferences;
}

Model::Model(std::string filePath)
{
	this->filePath = filePath;
	this->LoadModel();
}

Model::~Model()
{
	Meshes.clear();
	Textures.clear();
}

void Model::LoadModel()
{
	tinygltf::Model model;
	{
		tinygltf::TinyGLTF loader;
		std::string err;
		std::string warn;

		bool ret = loader.LoadASCIIFromFile(&model, &err, &warn, this->filePath);
		if (!warn.empty())
			std::cout << "[Model:LoadModel] Warn: " << warn << std::endl;
		if (!err.empty())
			std::cout << "[Model:LoadModel] Err: " << err << std::endl;
		if (!ret)
		{
			std::cout << "[Model:LoadModel] Failed to load model: " << this->filePath << std::endl;
			return;
		}
		std::cout << "[Model:LoadModel] Loaded model: " << this->filePath << std::endl;
	}
	
	Textures.clear();
	Textures = LoadTextures(model);
	
	// TODO: Recursive function for nodes
	Meshes.clear();
	for (size_t nodeId = 0; nodeId < model.nodes.size(); nodeId++)
	{
		const tinygltf::Node node = model.nodes[nodeId];
		if (node.mesh == -1) continue;

		Mesh mesh = LoadMesh(model, node.mesh);
		Meshes.push_back(mesh);
	}
}

Mesh Model::LoadMesh(
	tinygltf::Model& model,
	int meshId
) {
	const tinygltf::Mesh gltfMesh = model.meshes[meshId];

	// TODO: Multiple primitives
	const tinygltf::Primitive primitive = gltfMesh.primitives[0];

	// TODO: Error handling if necessary

	// Position
	int positionAccessorId = primitive.attributes.at("POSITION");
	tinygltf::Accessor positionAccessor = model.accessors[positionAccessorId];
	std::vector<glm::vec3> position = LoadBufferData<glm::vec3>(model, positionAccessor);

	// Normal
	int normalAccessorId = primitive.attributes.at("NORMAL");
	tinygltf::Accessor normalAccessor = model.accessors[normalAccessorId];
	std::vector<glm::vec3> normal = LoadBufferData<glm::vec3>(model, normalAccessor);

	// UV
	int uvAccessorId = primitive.attributes.at("TEXCOORD_0");
	tinygltf::Accessor uvAccessor = model.accessors[uvAccessorId];
	std::vector<glm::vec2> uv = LoadBufferData<glm::vec2>(model, uvAccessor);

	// Indices
	// TODO: Non-triangular indices
	int indicesAccessorId = primitive.indices;
	tinygltf::Accessor indicesAccessor = model.accessors[indicesAccessorId];
	std::vector<GLuint> indices = LoadBufferData<GLuint>(model, indicesAccessor);

	// Create vectices
	std::vector<Vertex> vertices;
	vertices.reserve(position.size());
	for (size_t i = 0; i < position.size(); i++)
	{
		Vertex vertex{
			position[i],
			normal[i],
			glm::vec3(1.0f, 1.0f, 1.0f),
			uv[i]
		};
		vertices.push_back(vertex);
	}

	Mesh mesh(vertices, indices, Textures);
	return mesh;
}