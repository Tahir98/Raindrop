#pragma once
#include "Engine.h"
#include <algorithm>
#include <execution>
#include <fstream>
#include <filesystem>

class ModelTest : public Engine::Scene {
private:

	Engine::PerspectiveCamera camera;
	bool isRightClicked = false;
	glm::vec2 mousePos{};
	float camSpeed = 10.0;
	float camSensivity = 0.125f;

	//Engine::SpherecalSkybox skybox;
	Engine::CubeMapSkybox cubemap;
	Engine::FrameBuffer fb;


	float frameTime;
	int frameCounter = 0;
	float fps = 165;
	float frameTimeLimit = 0.120f; //ms
	bool vsync = false;

	DirectionalLight light;
	Engine::Model* sponza = nullptr;
	Engine::Material material;

public:
	ModelTest(std::string name, Engine::Window& window) : Scene(name, window), camera(70, 16.0f / 9.0f, 0.1f, 2000),
		 cubemap("Textures/CubeMap"), fb(800, 600) {
		APP_LOG_INFO("Scene constructor is called, name: {0}, id: {1}", name, id);
	}

	~ModelTest() override {
		APP_LOG_INFO("Scene destructor is called, name: {0}, id: {1}", name, id);
	}

	void OnCreate() override {
		APP_LOG_INFO("Scene OnCreate method is called, name: {0}, id: {1}", name, id);
		sponza = new Engine::Model("Models/Sponza/sponza.obj");
	}

	void OnUpdate(float delta) override {
		//APP_LOG_INFO("Scene OnUpdate method is called, name: {0}, id: {1}, delta time: {2}", name, id, delta);

		inputControl(delta);

		camera.update();

		fb.bind();
		fb.clear();

		sponza->draw(camera, light);
		cubemap.draw(camera);

		////////////////////////////////////////////////
		fb.unbind();

		//Frame buffer to screen via ImGui
		ImGui::Begin("Scene");

		ImVec2 PanelSize = ImGui::GetContentRegionAvail();
		glm::vec2 fb_size = { (float)fb.getWidth(),(float)fb.getHeight() };

		if (PanelSize.x != fb_size.x || PanelSize.y != fb_size.y) {
			fb.resize(PanelSize.x, PanelSize.y);
			ImVec2 size = ImGui::GetWindowSize();
			camera.setAspectRatio((float)PanelSize.x / (float)PanelSize.y);
		}

		ImGui::Image((ImTextureID)fb.getTextureID(), PanelSize, ImVec2(0, 1), ImVec2(1, 0));
		ImGui::End();

		DrawSettingsPanel(delta);
	}

	void inputControl(float delta) {
		if (Engine::InputHandler::Key(KEY_W)) {
			glm::vec3 forward = camera.getForward();

			camera.translate(forward * camSpeed * delta);
		}
		if (Engine::InputHandler::Key(KEY_S)) {
			glm::vec3 forward = camera.getForward();

			camera.translate(forward * camSpeed * delta * -1.0f);
		}

		if (Engine::InputHandler::Key(KEY_A)) {
			glm::vec3 right = camera.getRight();

			camera.translate(right * camSpeed * delta * -1.0f);
		}

		if (Engine::InputHandler::Key(KEY_D)) {
			glm::vec3 right = camera.getRight();

			camera.translate(right * camSpeed * delta);
		}

		if (Engine::InputHandler::Key(KEY_SPACE)) {
			glm::vec3 up = camera.getUp();

			camera.translate(glm::vec3(0, 1, 0) * camSpeed * delta);
		}
		if (Engine::InputHandler::Key(KEY_LEFT_SHIFT)) {
			glm::vec3 up = camera.getUp();

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

	void DrawSettingsPanel(float delta) {
		frameCounter++;
		frameTime += delta;

		if (frameTime >= frameTimeLimit) {
			fps = frameCounter / frameTime;

			frameCounter = 0;
			frameTime = 0;
		}

		ImGui::Begin("Setting");
		ImGui::Checkbox("Vsync", &vsync);
		ImGui::Text("Frame time: %.2fms, fps: %.2f", 1000.0f / fps, fps);
		ImGui::NewLine();
		ImGui::Separator();
		ImGui::Text("Material properties");
		ImGui::ColorEdit4("color", &material.color.x);
		ImGui::SliderFloat("ambient", &material.ambient, 0, 1);
		ImGui::SliderFloat("diffuse", &material.diffuse, 0, 1);
		ImGui::SliderFloat("specular", &material.specular, 0, 1);
		ImGui::SliderFloat("shininess", &material.shininess, 1, 250);

		ImGui::Separator();
		ImGui::NewLine();
		ImGui::Text("Light properties");
		ImGui::SliderFloat3("direction", &light.direction.x, -1, 1);
		ImGui::ColorEdit4("light color", &light.color.x);
		ImGui::SliderFloat("intensity", &light.intensity, 0, 5);

		ImGui::End();

		sponza->setMaterial(material);

		glfwSwapInterval(vsync ? 1 : 0);
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
