#pragma once
#include "Engine.h"

class ComputeShaderTest : public Engine::Scene {
private:
	Engine::FrameBuffer* fb = nullptr;
	Engine::Shader* computeShader = nullptr;

	//Engine::Texture2D* imageTex = nullptr;

	Engine::Texture2D* customTex = nullptr;

	Engine::NoiseGeneratorGPU noiseGenerator;

public:
	ComputeShaderTest(std::string name, Engine::Window& window) : Scene(name, window) {
		APP_LOG_INFO("Scene constructor is called, name: {0}, id: {1}", name, id);
	}

	~ComputeShaderTest() override {
		APP_LOG_INFO("Scene destructor is called, name: {0}, id: {1}", name, id);
	}

	void OnCreate() override {
		APP_LOG_INFO("Scene OnCreate method is called, name: {0}, id: {1}", name, id);

		fb = new Engine::FrameBuffer(800, 600, Engine::AttachmentType::Texture, Engine::AttachmentType::Texture);

		computeShader = new Engine::Shader("Shaders/TestCompute.comp");

		//imageTex = new Engine::Texture2D("Textures/rooitou_park.jpg");

		customTex = new Engine::Texture2D(1024,1024, Engine::RGBA8_UNORM);

		Engine::NoiseLayer layer;
		layer.type = Engine::NoiseType::Perlin2D;
		layer.offset = glm::vec3(125.34, 46.66, 520.87);
		layer.scale = 8.0f;
		layer.normalizedScale = (float)layer.scale / customTex->getWidth();

		noiseGenerator.GenerateNoise(*customTex, layer);
	}

	void OnUpdate(float delta) override {
		//APP_LOG_INFO("Scene OnUpdate method is called, name: {0}, id: {1}, delta time: {2}", name, id, delta);

		fb->bind();
		fb->clear();

		fb->unbind();

		//Frame buffer to screen via ImGui
		ImGui::Begin("Scene");

		ImVec2 PanelSize = ImGui::GetContentRegionAvail();
		glm::vec2 fb_size = { (float)fb->getWidth(),(float)fb->getHeight() };

		if (PanelSize.x != fb_size.x || PanelSize.y != fb_size.y) {
			fb->resize(PanelSize.x, PanelSize.y);
			ImVec2 size = ImGui::GetWindowSize();
		}

		ImGui::Image((ImTextureID)customTex->getID(), PanelSize, ImVec2(0, 1), ImVec2(1, 0));
		ImGui::End();
	}

	void OnSuspend() override {
		APP_LOG_INFO("Scene OnSuspend method is called, name: {0}, id: {1}", name, id);
	}

	void OnResume() override {
		APP_LOG_INFO("Scene OnResume method is called, name: {0}, id: {1}", name, id);
	}

	void OnDestroy() override {
		APP_LOG_INFO("Scene OnDestroy method is called, name: {0}, id: {1}", name, id);

		delete fb;
	}
};
