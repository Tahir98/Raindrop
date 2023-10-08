#pragma once
#include "Engine.h"
#include <algorithm>
#include <execution>
#include <fstream>
#include <filesystem>

class VolumeRendering : public Engine::Scene {
private:

	Engine::PerspectiveCamera camera;
	bool isRightClicked = false;
	glm::vec2 mousePos{};
	float camSpeed = 3.0;
	float camSensivity = 0.075f;

	Engine::SpherecalSkybox skybox;
	Engine::FrameBuffer fb;

	Engine::VertexBuffer* vb = nullptr;
	Engine::VertexArray va;
	Engine::IndexBuffer* ib = nullptr;
	Engine::Shader* shader = nullptr;

	Engine::Texture* densityTex = nullptr;
	int32_t texSize = 512;
	int32_t subdivision_Size = 8;
	std::vector<glm::vec2> minmaxDensities;

	Bound bound;

	glm::mat4 model;

	float stepCount = 1000;
	float threshold = 0.5f;
	float opacity = 0.6f;

	float frameTime;
	int frameCounter = 0;
	float fps = 165;
	float frameTimeLimit = 0.120f; //ms
	bool vsync = false;

public:
	VolumeRendering(std::string name, Engine::Window& window) : Scene(name, window), camera(70, 16.0f / 9.0f, 0.1f, 100),
		skybox("Textures/rooitou_park.jpg"), fb(800, 600), bound(glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(0.5f, 0.5f, 0.5f)) {
		APP_LOG_INFO("Scene constructor is called, name: {0}, id: {1}", name, id);
	}

	~VolumeRendering() override {
		APP_LOG_INFO("Scene destructor is called, name: {0}, id: {1}", name, id);
	}

	void OnCreate() override {
		APP_LOG_INFO("Scene OnCreate method is called, name: {0}, id: {1}", name, id);

		std::vector<glm::vec3> vertices = {
			glm::vec3(0,0,0),
			glm::vec3(0,1,0),
			glm::vec3(1,1,0),
			glm::vec3(1,0,0),
			glm::vec3(1,0,1),
			glm::vec3(1,1,1),
			glm::vec3(0,1,1),
			glm::vec3(0,0,1)
		};

		for (int i = 0; i < vertices.size(); i++) {
			vertices[i] += glm::vec3(-0.5f, -0.5f, -0.5f);
			vertices[i] *= glm::vec3(1, 1, 1);
		}

		std::vector<uint32_t> indices = {
			0,1,2, 0,2,3,
			3,2,5, 3,5,4,
			4,5,6, 4,6,7,
			7,6,1, 7,1,0,
			7,0,3, 7,3,4,
			1,6,5, 1,5,2
		};

		vb = new Engine::VertexBuffer(vertices.data(), sizeof(glm::vec3) * vertices.size(), GL_STATIC_DRAW);
		va.bind();
		vb->bind();
		va.PushElement(vb, 3, Engine::VertexArray::FLOAT, false);

		ib = new Engine::IndexBuffer(indices.data(), indices.size(), GL_STATIC_DRAW);
		shader = new Engine::Shader("Shaders/VolumeRenderer.shader");

		bound.min = glm::vec3(-0.5f, -0.5f, -0.5f);
		bound.max = glm::vec3(0.5f, 0.5f, 0.5f);
		glm::vec3 boundSize = bound.size();
		glm::vec3 boundCenter = bound.center();

		ENG_LOG_INFO("Bounds size : ({0},{1},{2})", boundSize.x, boundSize.y, boundSize.z);
		ENG_LOG_INFO("Bounds center : ({0},{1},{2}", boundCenter.x, boundCenter.y, boundCenter.z);

		Engine::PerlinNoise3DLayer layer1;
		layer1.offset = glm::vec3(223.3f, 627.7f, 556.3f);
		layer1.scale = 3.2f;
		layer1.smoothness = 2;

		Engine::PerlinNoise3DLayer layer2;
		layer2.offset = glm::vec3(200.3f, 623.7f, 523.3f);
		layer2.scale = 5;
		layer2.smoothness = 2;

		Engine::PerlinNoise3DLayer layer3;
		layer3.offset = glm::vec3(200.3f, 623.7f, 523.3f);
		layer3.scale = 10;
		layer3.smoothness = 2;

		Engine::PerlinNoise3DLayer layer4;
		layer4.offset = glm::vec3(200.3f, 623.7f, 523.3f);
		layer4.scale = 20;
		layer4.smoothness = 2;


		std::vector<Engine::PerlinNoise3DLayer> noiseLayers;
		noiseLayers.push_back(layer1);
		noiseLayers.push_back(layer2);
		noiseLayers.push_back(layer3);
		noiseLayers.push_back(layer4);

		float* densityArray = nullptr;

		if (!std::filesystem::exists("DensityTexture.bin")) {
			densityArray = new float[texSize * texSize * texSize];

			for (int x = 0; x < texSize; x++) {
				for (int y = 0; y < texSize; y++) {
					for (int z = 0; z < texSize; z++) {
						float density = 0;

						glm::vec3 position;
						position.x = bound.min.x + (boundSize.x * x / (float)texSize);
						position.y = bound.min.y + (boundSize.y * y / (float)texSize);
						position.z = bound.min.z + (boundSize.z * z / (float)texSize);

						float densityMultiplier = (bound.center() - position).length() * 2.0f;

						for (int i = 0; i < noiseLayers.size(); i++) {
							glm::vec3 corner = (position * noiseLayers[i].scale + noiseLayers[i].offset);

							density += Engine::PerlinNoise3D::value(corner.x, corner.y, corner.z, noiseLayers[i].smoothness) / (noiseLayers[i].scale * 0.5f);
						}

						densityArray[x + y * texSize + z * texSize * texSize] = density * 12.0f;
					}
				}
			}

			std::fstream filewriter("DensityTexture.bin", std::ios_base::out | std::ios_base::binary);
			filewriter.write(  (char*) & texSize, sizeof(texSize));
			filewriter.write((char*)&texSize, sizeof(texSize));
			filewriter.write((char*)&texSize, sizeof(texSize));


			filewriter.write((char*)densityArray, texSize* texSize* texSize * sizeof(float));

			filewriter.close();
		}
		else {
			std::ifstream file("DensityTexture.bin", std::ios::in | std::ios::binary);

			file.read((char*)&texSize, sizeof(float));
			file.read((char*)&texSize, sizeof(float));
			file.read((char*)&texSize, sizeof(float));

			APP_LOG_INFO("Texsize: {0}", texSize);

			densityArray = new float[texSize * texSize * texSize];

			file.read((char*) densityArray, sizeof(float) * texSize * texSize * texSize);
		}

		densityTex = new Engine::Texture(texSize, texSize, texSize, densityArray);

		delete densityArray;

		camera.setPosition(glm::vec3(0, 0, 2));

	}

	void OnUpdate(float delta) override {
		//APP_LOG_INFO("Scene OnUpdate method is called, name: {0}, id: {1}, delta time: {2}", name, id, delta);

		inputControl(delta);

		camera.update();

		fb.bind();
		fb.clear();

		Engine::OpenGLUtility::EnableBlend();
		Engine::OpenGLUtility::SetBlendFunction(Engine::SRC_ALPHA, Engine::ONE_MINUS_SRC_ALPHA);

		Engine::OpenGLUtility::EnableCulling();
		Engine::OpenGLUtility::EnableDepthTest();


		Engine::OpenGLUtility::SetCullMode(Engine::CullBack);
		skybox.draw(camera);

		////////////////////////////////////////////////

		model = glm::mat4(1.0f);

		Engine::OpenGLUtility::SetCullMode(Engine::CullFront);

		shader->bind();
		va.bind();
		ib->bind();
		densityTex->bind();
		densityTex->SetActiveTextureSlot(0);

		shader->SetUniformMatrix4x4("model", 1, false, glm::value_ptr(model));
		shader->SetUniformMatrix4x4("view", 1, false, glm::value_ptr(camera.getViewMatrix()));
		shader->SetUniformMatrix4x4("projection", 1, false, glm::value_ptr(camera.getProjectionMatrix()));

		//shader->SetUniform1i("screenWidth", window.getWindowProperties().width);
		//shader->SetUniform1i("screenHeight", window.getWindowProperties().height);

		//shader->SetUniform3i("texSize", texSize, texSize, texSize);
		shader->SetUniform3f("cameraPos", camera.getPosition());
		shader->SetUniform1i("densityTex", 0);

		shader->SetUniform1f("stepSize", 1.0f / (float)stepCount);
		shader->SetUniform3f("boundMin", bound.min);
		shader->SetUniform3f("boundMax", bound.max);
		shader->SetUniform1f("threshold", threshold);
		shader->SetUniform1f("opacity", opacity);
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

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
		ImGui::Text("Frame time: %.2fms, fps: %.2f", 1000.0f / fps , fps);
		ImGui::NewLine();
		ImGui::Separator();

		ImGui::SliderFloat("Step count", &stepCount, 5, 1000, "%.0f");
		ImGui::SliderFloat("Threshold", &threshold, 0, 1);
		ImGui::SliderFloat("Opacity", &opacity, 0, 1);

		ImGui::End();

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
