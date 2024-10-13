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
	
		glm::vec3 position = glm::vec3(0, 0, 0);
		glm::vec3 scale = glm::vec3(1, 1, 1);
		glm::vec3 rotation = glm::vec3(0, 0, 0);
	public:
		Model(std::string path);
		~Model();

		void draw(Camera& camera, DirectionalLight& light);
		void setMaterial(Material material);

		void setPosition(glm::vec3 position);
		void setPosition(float x, float y, float z);

		void setScale(glm::vec3 scale);
		void setScale(float x, float y, float z);

		void setRotation(glm::vec3 rotation);
		void setRotation(float x, float y, float z);

		glm::vec3 getPosition();
		glm::vec3 getScale();
		glm::vec3 getRotation();
	private:
		void loadModel(std::string path);
		void processNode(aiNode* node, const aiScene* scene);
		Mesh* processMesh(aiMesh* mesh, const aiScene* scene);
		std::vector<TextureDef>* loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);

		TextureType getTextureType(std::string typeStr);
	};

}