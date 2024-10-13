#include "Model.h"
#include <chrono>

namespace Engine {
	Model::Model(std::string path) : filePath(path) {
		auto startTime = std::chrono::system_clock::now();

		shader = new Shader("Shaders/ModelPBR.shader");
		loadModel(path);

		for (int i = 0; i < meshes.size(); i++) {
			meshes[i]->setShader(shader);
		}

		auto endTime = std::chrono::system_clock::now();

		auto loadingTime = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime);
		ENG_LOG_INFO("Model loading time: {0}ms", loadingTime.count());
	}

	Model::~Model() {
		for (int i = 0; i < meshes.size(); i++) {
			delete meshes[i];
		}

		for (int i = 0; i < textures.size(); i++) {
			delete textures[i].texture;
		}
	}

	void Model::draw(Camera& camera, DirectionalLight& light) {
		for (int i = 0; i < meshes.size(); i++) {
			meshes[i]->draw(camera, light);
		}
	}

	void Model::setMaterial(Material material) {
		for (int i = 0; i < meshes.size(); i++) {
			meshes[i]->setMaterial(material);
		}
	}

	void Model::setPosition(glm::vec3 position) {
		this->position = position;

		for (int i = 0; i < meshes.size(); i++) {
			meshes[i]->setPosition(position);
		}
	}

	void Model::setPosition(float x, float y, float z) {
		position = glm::vec3(x, y, z);

		for (int i = 0; i < meshes.size(); i++) {
			meshes[i]->setPosition(position);
		}
	}

	void Model::setScale(glm::vec3 scale) {
		this->scale = scale;

		for (int i = 0; i < meshes.size(); i++) {
			meshes[i]->setScale(scale);
		}
	}

	void Model::setScale(float x, float y, float z) {
		scale = glm::vec3(x, y, z);

		for (int i = 0; i < meshes.size(); i++) {
			meshes[i]->setScale(scale);
		}
	}

	void Model::setRotation(glm::vec3 rotation) {
		this->rotation = rotation;

		for (int i = 0; i < meshes.size(); i++) {
			meshes[i]->setRotation(rotation);
		}
	}

	void Model::setRotation(float x, float y, float z) {
		rotation = glm::vec3(x, y, z);

		for (int i = 0; i < meshes.size(); i++) {
			meshes[i]->setRotation(rotation);
		}
	}

	glm::vec3 Model::getPosition() {
		return position;
	}

	glm::vec3 Model::getScale() {
		return scale;
	}

	glm::vec3 Model::getRotation() {
		return rotation;
	}

	void Model::loadModel(std::string path) {
		Assimp::Importer importer;

		uint32_t flags = aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenNormals;
		const aiScene* scene = importer.ReadFile(path, flags);

		if (!scene) {
			ENG_LOG_ERROR("Failed to load model, path: {0}", path);
		}
		else {
			filePath = path.substr(0, path.find_last_of('/'));

			processNode(scene->mRootNode, scene);

			ENG_LOG_INFO("Model is successfully loaded, path: {0}, mesh count: {1}", path, meshes.size());
		}
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

	Mesh* Model::processMesh(aiMesh* mesh, const aiScene* scene) {
		std::vector<Vertex>* vertices = new std::vector<Vertex>();
		std::vector<uint32_t>* indices = new std::vector<uint32_t>(); 
		std::vector<TextureDef>* mesh_textures = nullptr;

		for (int i = 0; i < mesh->mNumVertices; i++) {
			Vertex vertex;
			vertex.position = glm::vec3(mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z);

			vertex.normal = glm::vec3(mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z);

			if (mesh->mTextureCoords[0]) {
				vertex.texCoord = glm::vec3(mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y, 0);
			}

			vertices->push_back(vertex);
		}

		for (int i = 0; i < mesh->mNumFaces; i++) {
			aiFace face = mesh->mFaces[i];

			for (int j = 0; j < face.mNumIndices; j++) {
				indices->push_back(face.mIndices[j]);
			}
		}

		if (mesh->mMaterialIndex >= 0) {
			aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
			mesh_textures = loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
		}

		return new Mesh(vertices, indices, mesh_textures);
	}

	std::vector<TextureDef>* Model::loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName) {
		std::vector<TextureDef>* mesh_textures = new std::vector<TextureDef>();

		int texCount = mat->GetTextureCount(type);

		for (int i = 0; i < texCount; i++) {
			aiString str;
			mat->GetTexture(type,i, &str);

			bool textureFound = false;
			std::string path = filePath + "/" + std::string(str.C_Str());

			if (texturePaths.find(path) != texturePaths.end()) {
				mesh_textures->push_back(textures[texturePaths[path]]);
				textureFound = true;
				break;
			}	

			if (!textureFound) {
				TextureDef textureDef;
				textureDef.type = getTextureType(typeName);

				TextureFilter filter = TextureFilter::BILINEAR;
				TextureWrapper wrapMode = TextureWrapper::REPEAT;

				textureDef.texture = new Texture2D(path, filter, wrapMode);

				textures.push_back(textureDef);

				ENG_LOG_INFO("Texture full path: {0}", path);
				texturePaths[path] = textures.size() - 1;

				mesh_textures->push_back(textureDef);
			}
		}

		return mesh_textures;
	}
	TextureType Model::getTextureType(std::string typeStr) {
		if (typeStr.compare("texture_diffuse") == 0) {
			return TextureType::DIFFUSE;
		}
	}


}