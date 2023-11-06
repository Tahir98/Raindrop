#pragma once
#include "Mesh.h"
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <assimp/Importer.hpp>

namespace Engine {

	class Model {
	private:
		std::vector<Mesh*> meshes;
		std::string filePath;

		std::vector<TextureDef> loadedTextures;
	public:
		Model(std::string path);
		~Model();

		void draw(Camera& camera, DirectionalLight& light);
	private:
		void loadModel(std::string path);
		void processNode(aiNode* node, const aiScene* scene);
		Mesh* processMesh(aiMesh* mesh, const aiScene* scene);
		std::vector<TextureDef> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);
	};

}