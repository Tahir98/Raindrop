#include "Mesh.h"
#include "glm/gtx/euler_angles.hpp"

namespace Engine {

	Engine::Mesh::Mesh(std::vector<Vertex>& vertices, std::vector<uint32_t>& indices, std::vector<TextureDef>& textureDefinitions) : vertices(vertices), indices(indices), textureDefinitions(textureDefinitions){

		SetupMesh();
		UpdateMatrices();
	}

	Mesh::~Mesh() {
		delete vb;
		delete va;
		delete ib;
		delete shader;

		vertices.clear();
		vertices.shrink_to_fit();

		indices.clear();
		indices.shrink_to_fit();

		textureDefinitions.clear();
		textureDefinitions.shrink_to_fit();
	}

	bool Mesh::IsInitialized() {
		return initialized;
	}
	
	void Mesh::draw(Camera& camera, DirectionalLight& light) {
		if (initialized) {
			OpenGLUtility::SetOpenGLState(rendererState);

			va->bind();
			ib->bind();
			shader->bind();

			shader->SetUniformMatrix4x4("model", 1, false, glm::value_ptr(modelMatrix));
			shader->SetUniformMatrix4x4("view", 1, false, glm::value_ptr(camera.getViewMatrix()));
			shader->SetUniformMatrix4x4("projection", 1, false, glm::value_ptr(camera.getProjectionMatrix()));

			shader->SetUniform3f("cameraPos", camera.getPosition());
			shader->SetUniform3f("material.ambient", material.ambient);
			shader->SetUniform3f("material.diffuse", material.diffuse);
			shader->SetUniform3f("material.specular", material.specular);
			shader->SetUniform1f("material.shininess", material.shininess);

			shader->SetUniform3f("light.direction", light.direction);
			shader->SetUniform4f("light.color", light.color);
			shader->SetUniform1f("light.intensity", light.intensity);

			for (int i = 0; i < textureDefinitions.size(); i++) {
				if (textureDefinitions[i].type == "texture_diffuse") {
					textureDefinitions[i].texture->bind();
					textureDefinitions[i].texture->setActiveTextureSlot(0);

					shader->SetUniform1i("diffuseTex", 0);
					break;
				}
			}

			glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_BYTE, 0);
		}
	}
	
	void Mesh::deleteCPUSideData() {
		vertices.clear();
		vertices.shrink_to_fit();

		indices.clear();
		indices.shrink_to_fit();
	}

	void Mesh::setPosition(glm::vec3 position) {
		this->position = position;
		UpdateMatrices();
	}

	void Mesh::setPosition(float x, float y, float z) {
		position = glm::vec3(x, y, z);
		UpdateMatrices();
	}

	void Mesh::setScale(glm::vec3 scale) {
		this->scale = scale;
		UpdateMatrices();
	}

	void Mesh::setScale(float x, float y, float z) {
		scale = glm::vec3(x, y, z);
		UpdateMatrices();
	}

	void Mesh::setRotation(glm::vec3 rotation) {
		this->rotation = rotation;
		UpdateMatrices();
	}

	void Mesh::setRotation(float x, float y, float z) {
		rotation = glm::vec3(x, y, z);
		UpdateMatrices();
	}

	glm::vec3 Mesh::getPosition() {
		return position;
	}

	glm::vec3 Mesh::getScale() {
		return scale;
	}

	glm::vec3 Mesh::getRotation() {
		return rotation;
	}

	glm::mat4x4 Mesh::getModelMatrix() {
		return modelMatrix;
	}

	glm::mat4x4 Mesh::getTranslationMatrix() {
		return translationMatrix;
	}

	glm::mat4x4 Mesh::getScaleMatrix() {
		return scaleMatrix;
	}

	glm::mat4x4 Mesh::getRotationMatrix() {
		return rotationMatrix;
	}

	OpenGLState Mesh::getRendererState() {
		return rendererState;
	}

	void Mesh::setRendererState(OpenGLState state) {
		rendererState = state;
	}

	Material Mesh::getMaterial() {
		return material;
	}

	void Mesh::setMaterial(Material material) {
		this->material = material;
	}

	void Mesh::SetupMesh() {
		vb = new VertexBuffer(vertices.data(), sizeof(Vertex) * vertices.size(), GL_STATIC_DRAW);
		va = new VertexArray();

		va->PushElement(vb, 3, VertexArray::DataType::FLOAT, false);
		va->PushElement(vb, 3, VertexArray::DataType::FLOAT, false);
		va->PushElement(vb, 3, VertexArray::DataType::FLOAT, false);
		
		ib = new IndexBuffer(indices.data(), sizeof(uint32_t) * indices.size(), GL_STATIC_DRAW);

		shader = new Shader("Shaders/Model.shader");

	}

	void Mesh::UpdateMatrices() {
		translationMatrix = glm::translate(glm::mat4(1.0f), position);
		scaleMatrix = glm::scale(glm::mat4(1.0f), scale);

		glm::vec3 euler = rotation;
		euler.x *= glm::pi<float>() / 180.0f;
		euler.y *= glm::pi<float>() / 180.0f;
		euler.z *= glm::pi<float>() / 180.0f;
		rotationMatrix = glm::eulerAngleXYZ(euler.x, euler.y, euler.z);

		modelMatrix = translationMatrix * rotationMatrix * scaleMatrix;
	}
}