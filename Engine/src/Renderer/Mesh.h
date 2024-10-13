#pragma once

#include "OpenGL/VertexBuffer.h"
#include "OpenGL/VertexArray.h"
#include "OpenGL/IndexBuffer.h"
#include "OpenGL/Shader.h"
#include "OpenGL/Texture2D.h"
#include "OpenGL/OpenGLUtility.h"

#include "Camera/Camera.h"

#include <vector>
#include "Primitives.h"
#include "Material.h"
#include "Light.h"

namespace Engine {
	class Mesh {
	private:
		bool initialized = false;
		
		std::vector<Vertex>* vertices;
		std::vector<uint32_t>* indices;
		std::vector<TextureDef>* textures;

		VertexBuffer* vb = nullptr;
		VertexArray* va = nullptr;
		IndexBuffer* ib = nullptr;
		Shader* shader = nullptr;

		OpenGLState rendererState;

		uint32_t vertexCount = 0;
		uint32_t indexCount = 0;

		glm::vec3 position = glm::vec3(0, 0, 0);
		glm::vec3 scale = glm::vec3(1, 1, 1);
		glm::vec3 rotation = glm::vec3(0, 0, 0);

		glm::mat4x4 modelMatrix;
		glm::mat4x4 translationMatrix;
		glm::mat4x4 scaleMatrix;
		glm::mat4x4 rotationMatrix;

		Material material;
	public: 
		Mesh(std::vector<Vertex>* vertices, std::vector<uint32_t>* indices, std::vector<TextureDef>* textures);
		~Mesh();

		bool IsInitialized();
		void draw(Camera& camera, DirectionalLight& light);
		void deleteCPUSideData();

		void setPosition(glm::vec3 position);
		void setPosition(float x, float y, float z);

		void setScale(glm::vec3 scale);
		void setScale(float x, float y, float z);

		void setRotation(glm::vec3 rotation);
		void setRotation(float x, float y, float z);

		glm::vec3 getPosition();
		glm::vec3 getScale();
		glm::vec3 getRotation();

		glm::mat4x4 getModelMatrix();
		glm::mat4x4 getTranslationMatrix();
		glm::mat4x4 getScaleMatrix();
		glm::mat4x4 getRotationMatrix();

		OpenGLState getRendererState();
		void setRendererState(OpenGLState state);

		Material getMaterial();
		void setMaterial(Material material);

		void setShader(Shader* shader);
		Shader* getShader();

	private:
		void SetupMesh();
		void UpdateMatrices();
	};
}
