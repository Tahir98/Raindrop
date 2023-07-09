#pragma once
#include "Engine.h"

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
	int32_t texSize = 128;

	Bound bound;
	std::vector<Engine::PerlinNoise3DLayer> noiseLayers;

	glm::mat4 model;

	uint32_t stepCount = 200;
	
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
			vertices[i] *= glm::vec3(1, 1, -1);
		}

		std::vector<uint32_t> indices = {
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

		ib = new Engine::IndexBuffer(indices.data(), sizeof(uint32_t) * indices.size(), GL_STATIC_DRAW);
		shader = new Engine::Shader("Shaders/VolumeRenderer.shader");

		glm::vec3 boundSize = bound.size();
		glm::vec3 boundCenter = bound.center();

		Engine::PerlinNoise3DLayer layer1;
		layer1.offset = glm::vec3(0.3f, 6.7f, -5.3f);
		layer1.scale = 3;
		layer1.smoothness = 2;

		noiseLayers.push_back(layer1);

		float* densityArray = new float[texSize * texSize * texSize];

		for (int x = 0; x < texSize; x++) {
			for (int y = 0; y < texSize; y++) {
				for (int z = 0; z < texSize; z++) {
					float density = 0;

					glm::vec3 position;
					position.x = bound.min.x + (boundSize.x * x / (float)texSize);
					position.y = bound.min.y + (boundSize.y * y / (float)texSize);
					position.z = bound.min.z + (boundSize.z * z / (float)texSize);

					for (int i = 0; i < noiseLayers.size(); i++) {
						glm::vec3 corner = (position * noiseLayers[i].scale + noiseLayers[i].offset);

						density += Engine::PerlinNoise3D::value(corner.x, corner.y, corner.z, noiseLayers[i].smoothness);
					}

					densityArray[x + y * texSize + z * texSize * texSize] = density;
				}
			}
		}

		densityTex = new Engine::Texture(texSize, texSize, texSize, densityArray);

		camera.setPosition(glm::vec3(0,0,2));
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

		skybox.draw(camera);

		////////////////////////////////////////////////

		model = glm::mat4(1.0f);

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

		shader->SetUniform1f("stepSize", 1.0f / (float) stepCount);
		shader->SetUniform3f("boundMin", bound.min);
		shader->SetUniform3f("boundMax", bound.min);

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
