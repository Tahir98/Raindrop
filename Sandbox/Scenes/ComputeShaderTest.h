#pragma once
#include "Engine.h"

class ComputeShaderTest : public Engine::Scene {
private:
	Engine::FrameBuffer* fb = nullptr;
	Engine::ComputeShader* computeShader = nullptr;

	//Engine::Texture2D* imageTex = nullptr;

	Engine::Texture2D* customTex = nullptr;

	Engine::NoiseGeneratorGPU noiseGenerator;
	Engine::NoiseLayer layer, tempLayer;

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

		computeShader = new Engine::ComputeShader("Shaders/TestCompute.comp");

		//imageTex = new Engine::Texture2D("Textures/rooitou_park.jpg");

		customTex = new Engine::Texture2D(1024,1024, Engine::RGBA8_UNORM);

		layer.type = Engine::NoiseType::Perlin2D;
		layer.offset = glm::vec3(125.34, 46.66, 520.87);
		layer.scale = 2.0f;

		tempLayer = layer;

		glfwSwapInterval(1);
	}

	void OnUpdate(float delta) override {
		//APP_LOG_INFO("Scene OnUpdate method is called, name: {0}, id: {1}, delta time: {2}", name, id, delta);

		fb->bind();
		fb->clear();

		noiseGenerator.GenerateNoise(*customTex, layer);
		DrawImGui(delta);

		fb->unbind();

		//Frame buffer to screen via ImGui
		ImGui::Begin("Scene");

		ImVec2 PanelSize = ImGui::GetContentRegionAvail();
		glm::vec2 tex_size = { (float)customTex->getWidth(),(float)customTex->getHeight() };

		if (PanelSize.x != tex_size.x || PanelSize.y != tex_size.y) {
			uint32_t size = glm::min(PanelSize.x, PanelSize.y);
			customTex->Resize(size, size);
		}

		ImGui::Image((ImTextureID)customTex->getID(), ImVec2(customTex->getWidth(), customTex->getHeight()), ImVec2(0, 1), ImVec2(1, 0));
		ImGui::End();
	}

	void DrawImGui(float delta) {
		ImGui::Begin("Settings");
		ImGui::Text("Frame time: %.1f, Fps: %.2f", (delta * 1000.0f), 1.0f / delta);
		ImGui::Separator();

		ImGui::NewLine();



		const char* noise_types[] = { "Perlin2D", "Perlin3D", "Worley2D", "Worley3D", "Inverse Worley2D", "Inverse Worley3D" };
		int chosen_type = layer.type;
		const char* current_type = noise_types[chosen_type];

		if (ImGui::BeginCombo("Noise Type", current_type)) {
			for (int i = 0; i < IM_ARRAYSIZE(noise_types); i++) {
				bool is_selected = (chosen_type == i);

				if (ImGui::Selectable(noise_types[i], is_selected)) {
					chosen_type = i;
					layer.type = (Engine::NoiseType)i;
				}

				if (is_selected)
					ImGui::SetItemDefaultFocus();
			}

			ImGui::EndCombo();
		}

		ImGui::DragFloat3("offset", glm::value_ptr(layer.offset), 0.01, -1000, 1000);
		ImGui::SliderInt("Octave count", &layer.octaveCount, 1, 6);
		ImGui::DragInt("scale", &layer.scale, 0.1f, 0, 512);
		ImGui::SliderFloat("opacity", &layer.opacity, 0, 1);
		ImGui::SliderFloat("coverage", &layer.coverage, 0, 1);
		ImGui::SliderInt("Smoothness Level", &layer.smoothnessLevel, 0, 2);

		layer.normalizedScale = (float)layer.scale / customTex->getWidth();

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
