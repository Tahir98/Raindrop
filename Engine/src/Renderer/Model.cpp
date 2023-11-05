#include "Model.h"

namespace Engine {
	Model::Model(std::string path) : filePath(path) {
		loadModel(path);
	}

	Model::~Model() {
	}

	void Model::draw(Camera& camera, DirectionalLight& light) {
		for (int i = 0; i < meshes.size(); i++) {
			meshes[i].draw(camera, light);
		}
	}

	void Model::loadModel(std::string path) {
		Assimp::Importer importer;

		uint32_t flags = aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenNormals;
		const aiScene* scene = importer.ReadFile(path, flags);

		if (!scene) {
			ENG_LOG_ERROR("Failed to load model, path: {0}", path);
		}

		filePath = path.substr(0, path.find_last_of('/'));

		processNode(scene->mRootNode, scene);

		ENG_LOG_INFO("Model is successfully loaded, path: {0}, mesh count: {1}", path, meshes.size());
	}

	void Model::processNode(aiNode* node, const aiScene* scene) {

		for (int i = 0; i < node->mNumMeshes; i++) {
			aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
			meshes.push_back(processMesh(mesh, scene));
		}

		for (int i = 0; i < node->mNumChildren; i++) {
			processNode(node->mChildren[i], scene);
		}
	}

	Mesh Model::processMesh(aiMesh* mesh, const aiScene* scene) {
		std::vector<Vertex> vertices;
		std::vector<uint32_t> indices;
		std::vector<TextureDef> textureDefinitions;
		std::vector<Texture2D> textures;

		for (int i = 0; i < mesh->mNumVertices; i++) {
			Vertex vertex;
			vertex.position = glm::vec3(mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z);

			vertex.normal = glm::vec3(mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z);

			if (mesh->mTextureCoords[0]) {
				vertex.texCoord = glm::vec3(mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y, 0);
			}

			vertices.push_back(vertex);
		}

		for (int i = 0; i < mesh->mNumFaces; i++) {
			aiFace face = mesh->mFaces[i];

			for (int j = 0; j < face.mNumIndices; j++) {
				indices.push_back(face.mIndices[j]);
			}
		}

		if (mesh->mMaterialIndex >= 0) {
			aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
			loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
		}

		return Mesh(vertices, indices, textureDefinitions);
	}

	std::vector<TextureDef> Model::loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName) {
		std::vector<TextureDef> textures;

		for (int i = 0; i < mat->GetTextureCount(type); i++) {
			aiString str;
			mat->GetTexture(type,i, &str);
			//ENG_LOG_INFO("Texture path: {0}", str);

			bool skip = false;

			for (int j = 0; j < loadedTextures.size(); j++) {
				if (std::strcmp(loadedTextures[j].path.data(), str.C_Str()) == 0) {
					textures.push_back(loadedTextures[j]);
					skip = true;
					break;
				}
			}

			if (!skip) {
				TextureDef textureDef;
				std::string fullPath = filePath + "/" + std::string(str.C_Str());
				ENG_LOG_INFO("Texture full path: {0}",  fullPath);
				textureDef.texture = new Texture2D(fullPath);
			}

		}

		return textures;
	}
}