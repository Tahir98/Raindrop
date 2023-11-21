#pragma once
#include "Mesh.h"
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <assimp/Importer.hpp>
#include <unordered_map>

namespace Engine {

	class Model {
	private:
		std::vector<Mesh*> meshes;
		std::string filePath;

		std::vector<TextureDef> textures;
		//std::vector<std::string> texturePaths;
		std::unordered_map<std::string, int> texturePaths;

		Shader* shader = nullptr;
	public:
		Model(std::string path);
		~Model();

		void draw(Camera& camera, DirectionalLight& light);
		void setMaterial(Material material);
	private:
		void loadModel(std::string path);
		void processNode(aiNode* node, const aiScene* scene);
		Mesh* processMesh(aiMesh* mesh, const aiScene* scene);
		std::vector<TextureDef>* loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);

		TextureType getTexuteType(std::string typeStr);
	};

}