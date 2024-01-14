#pragma once
#include "Engine.h"

class TextureTest : public Engine::Scene {
private:
	Engine::FrameBuffer* fb = nullptr;

	Engine::VertexBuffer* vb = nullptr;
	Engine::VertexArray va;
	Engine::Shader* shader = nullptr;

	
	Engine::Texture2D* customDataTex = nullptr;
	Engine::Texture2D* imageTex = nullptr;

public:
	TextureTest(std::string name, Engine::Window& window) : Scene(name, window) {
		APP_LOG_INFO("Scene constructor is called, name: {0}, id: {1}", name, id);
	}

	~TextureTest() override {
		APP_LOG_INFO("Scene destructor is called, name: {0}, id: {1}", name, id);
	}

	void OnCreate() override {
		APP_LOG_INFO("Scene OnCreate method is called, name: {0}, id: {1}", name, id);

		fb = new Engine::FrameBuffer(800, 600, Engine::AttachmentType::Texture, Engine::AttachmentType::Texture);

		std::vector<float> vertices = {
			-1,-1,0,	0, 0,
			-1, 1,0,	0, 1,
			 1, 1,0,	1, 1,

			-1,-1,0,	0, 0,
			 1, 1,0,	1, 1,
			 1, -1,0,	1, 0,
		};

		vb = new Engine::VertexBuffer(vertices.data(), sizeof(float) * vertices.size(), GL_STATIC_DRAW);

		va.PushElement(vb, 3, Engine::VertexArray::DataType::FLOAT, false);
		va.PushElement(vb, 2, Engine::VertexArray::DataType::FLOAT, false);

		shader = new Engine::Shader("Shaders/TextureTest.shader");

		int texSize = 256;

		uint8_t* textureData = new uint8_t[texSize * texSize * 3];

		for (int i = 0; i < texSize; i++) {
			for (int j = 0; j < texSize; j++) {
				textureData[(i * texSize + j) * 3 + 0] = (uint8_t)i;
				textureData[(i * texSize + j) * 3 + 1] = (uint8_t)j;
				textureData[(i * texSize + j) * 3 + 2] = (uint8_t)0;
			}
		}

		customDataTex = new Engine::Texture2D(textureData, texSize, texSize, Engine::TextureFormat::RGB8_UNORM);

		delete[] textureData;

		imageTex = new Engine::Texture2D("Textures/rooitou_park.jpg");
	}

	void OnUpdate(float delta) override {
		//APP_LOG_INFO("Scene OnUpdate method is called, name: {0}, id: {1}, delta time: {2}", name, id, delta);

		fb->bind();
		fb->clear();

		va.bind();

		imageTex->bind();
		imageTex->setActiveTextureSlot(0);

		shader->bind();
		shader->SetUniform1i("tex", 0);

		glDrawArrays(GL_TRIANGLES, 0, 6);

		fb->unbind();

		//Frame buffer to screen via ImGui
		ImGui::Begin("Scene");

		ImVec2 PanelSize = ImGui::GetContentRegionAvail();
		glm::vec2 fb_size = { (float)fb->getWidth(),(float)fb->getHeight() };

		if (PanelSize.x != fb_size.x || PanelSize.y != fb_size.y) {
			fb->resize(PanelSize.x, PanelSize.y);
			ImVec2 size = ImGui::GetWindowSize();
		}

		ImGui::Image((ImTextureID)fb->getColorAttachmentID(), PanelSize, ImVec2(0, 1), ImVec2(1, 0));
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
