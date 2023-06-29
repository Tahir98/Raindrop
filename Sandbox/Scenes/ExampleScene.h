#pragma once
#include "Engine.h"
#include "glm/ext/matrix_transform.hpp"
#include "glm/ext.hpp"
#include "glm/trigonometric.hpp"

class ExampleScene : public Engine::Scene {
private:
	std::vector<glm::vec3> vertices;
	std::vector<uint32_t> indices;

	Engine::VertexArray va;
	Engine::VertexBuffer* vb = nullptr;
	Engine::IndexBuffer* ib = nullptr;
	Engine::Shader* shader = nullptr;

	glm::mat4 model;
	glm::mat4 view;
	glm::mat4 projection;

	glm::vec3 position;
	glm::vec3 position2;
	glm::vec3 position3;
	glm::vec3 scale;
	glm::vec3 rotation;

	Engine::PerspectiveCamera camera;
	bool isRightClicked = false; 
	glm::vec2 mousePos;
	float camSpeed = 3.0;
	float camSensivity = 0.075f;

public:
	ExampleScene(std::string name, Engine::Window& window) : Scene(name, window), camera(70, 16.0f / 9.0f, 0.1f, 100) {
		APP_LOG_INFO("Scene constructor is called, name: {0}, id: {1}", name, id);
	}

	~ExampleScene() override {
		APP_LOG_INFO("Scene destructor is called, name: {0}, id: {1}", name, id);
	}

	void OnCreate() override {
		APP_LOG_INFO("Scene OnCreate method is called, name: {0}, id: {1}", name, id);

		vertices = {
			glm::vec3(0,0,0), glm::vec3(0,0,0),
			glm::vec3(0,1,0), glm::vec3(0,1,0),
			glm::vec3(1,1,0), glm::vec3(1,1,0),
			glm::vec3(1,0,0), glm::vec3(1,0,0),
			glm::vec3(1,0,1), glm::vec3(1,0,1),
			glm::vec3(1,1,1), glm::vec3(1,1,1),
			glm::vec3(0,1,1), glm::vec3(0,1,1),
			glm::vec3(0,0,1), glm::vec3(0,0,1)
		};

		for (int i = 0; i < vertices.size() / 2; i++) {
			vertices[i * 2] += glm::vec3(-0.5f, -0.5f, -0.5f);
			vertices[i * 2] *= glm::vec3(1, 1, -1);
		}

		indices = {
			0,2,1, 0,3,2,
			3,5,2, 3,4,5,
			4,6,5, 4,7,6,
			7,1,6, 7,0,1,
			7,3,0, 7,4,3,
			1,5,6, 1,2,5
		};

		vb = new Engine::VertexBuffer(vertices.data(), sizeof(glm::vec3) * vertices.size(), GL_STATIC_DRAW);
		
		va.bind();
		vb->bind();
		va.PushElement(vb, 3, Engine::VertexArray::FLOAT, false);
		va.PushElement(vb, 3, Engine::VertexArray::FLOAT, false);

		ib = new  Engine::IndexBuffer(indices.data(), sizeof(uint32_t) * indices.size(), GL_STATIC_DRAW);

		shader = new Engine::Shader("Shaders/Basic.shader");

		position = glm::vec3(0, 0, -3.5f);
		position2 = glm::vec3(0, 0.5f, -1.5f);
		position3 = glm::vec3(1.5f, -0.2f, -1.7f);

		scale = glm::vec3(1, 1, 1);
		rotation = glm::vec3(glm::radians(20.0f), 0, 0);

		projection = glm::perspective(glm::radians(45.0f), 16.0f / 9.0f, 0.1f, 100.0f);

		view = glm::mat4(1.0f);

		model = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), scale);

	}

	void OnUpate(float delta) override {
		//APP_LOG_INFO("Scene OnUpdate method is called, name: {0}, id: {1}, delta time: ", name, id, delta);

		inputControl(delta);

		camera.update();

		rotation.y += delta * 1.3f;

		va.bind();
		ib->bind();
		shader->bind();

		shader->SetUniformMatrix4x4("view", 1, false, glm::value_ptr(camera.getViewMatrix()));
		shader->SetUniformMatrix4x4("projection", 1, false, glm::value_ptr(camera.getProjectionMatrix()));

		model = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), scale) * glm::rotate(glm::mat4(1.0f), rotation.x, glm::vec3(1, 0, 0)) * glm::rotate(glm::mat4(1.0f), rotation.y, glm::vec3(0, 1, 0));

		shader->SetUniformMatrix4x4("model", 1, false, glm::value_ptr(model));


		glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);

		model = glm::translate(glm::mat4(1.0f), position2) * glm::scale(glm::mat4(1.0f), scale) * glm::rotate(glm::mat4(1.0f), rotation.x, glm::vec3(1, 0, 0)) * glm::rotate(glm::mat4(1.0f), rotation.y, glm::vec3(0, 1, 0));

		shader->SetUniformMatrix4x4("model", 1, false, glm::value_ptr(model));

		glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);

		model = glm::translate(glm::mat4(1.0f), position3) * glm::scale(glm::mat4(1.0f), scale) * glm::rotate(glm::mat4(1.0f), rotation.x, glm::vec3(1, 0, 0)) * glm::rotate(glm::mat4(1.0f), rotation.y, glm::vec3(0, 1, 0));

		shader->SetUniformMatrix4x4("model", 1, false, glm::value_ptr(model));


		glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
	}

	void inputControl(float delta) {
		if (Engine::InputHandler::Key(KEY_W)) {
			glm::vec3 forward = camera.getForward();

			APP_LOG_INFO("Camera forward: {0},{1},{2}", forward.x, forward.y, forward.z);

			camera.translate(forward * camSpeed * delta);
		}
		if (Engine::InputHandler::Key(KEY_S)) {
			glm::vec3 forward = camera.getForward();

			APP_LOG_INFO("Camera forward: {0},{1},{2}", forward.x, forward.y, forward.z);

			camera.translate(forward * camSpeed * delta * -1.0f);
		}

		if (Engine::InputHandler::Key(KEY_A)) {
			glm::vec3 right = camera.getRight();

			APP_LOG_INFO("Camera right: {0},{1},{2}", right.x, right.y, right.z );

			camera.translate(right * camSpeed * delta * -1.0f);
		}

		if (Engine::InputHandler::Key(KEY_D)) {
			glm::vec3 right = camera.getRight();

			APP_LOG_INFO("Camera right: {0},{1},{2}", right.x, right.y, right.z);

			camera.translate(right * camSpeed * delta);
		}

		if (Engine::InputHandler::Key(KEY_SPACE)) {
			glm::vec3 up = camera.getUp();
			APP_LOG_INFO("Camera up: {0},{1},{2}", up.x, up.y, up.z);

			camera.translate(glm::vec3(0, 1, 0) * camSpeed * delta);
		}
		if (Engine::InputHandler::Key(KEY_LEFT_SHIFT)) {
			glm::vec3 up = camera.getUp();
			APP_LOG_INFO("Camera up: {0},{1},{2}", up.x, up.y, up.z);

			camera.translate(glm::vec3(0, 1, 0) * camSpeed * delta * -1.0f);
		}

		float screenRatio = 1600.0f / window.getWindowProperties().width;

		if (Engine::InputHandler::MouseButtonDown(MOUSE_BUTTON_2)) {
			isRightClicked = true;
			mousePos = Engine::InputHandler::MousePosition();
		}
		else if (isRightClicked && Engine::InputHandler::MouseButton(MOUSE_BUTTON_2)) {
			glm::vec2 mouseCurrentPos = Engine::InputHandler::MousePosition();

			float angleX = (mouseCurrentPos.y - mousePos.y) * camSensivity * screenRatio;
			float angleY = (mouseCurrentPos.x - mousePos.x) * camSensivity * screenRatio;

			camera.rotatePitch(angleX * -1.0f);
			camera.rotateYaw(angleY);

			mousePos = mouseCurrentPos;
		}
		else {
			isRightClicked = false;
		}
	}


	void OnSuspend() override {
		APP_LOG_INFO("Scene OnSuspend method is called, name: {0}, id: {1}", name, id);
	}

	void OnResume() override {
		APP_LOG_INFO("Scene OnResume method is called, name: {0}, id: {1}", name, id);
	}

	void OnDestroy() override {
		APP_LOG_INFO("Scene OnDestroy method is called, name: {0}, id: {1}", name, id);
	}
};
