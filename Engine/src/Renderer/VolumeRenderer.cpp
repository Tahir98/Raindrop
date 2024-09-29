#include "VolumeRenderer.h"
#include "Input/InputHandler.h"
#include "imgui.h"
#include <execution>

namespace Engine {
	VolumeRenderer::VolumeRenderer() {
		rendererState.cullingEnabled = true;
		rendererState.cullMode = CullFront;
		rendererState.blendingEnabled = true;
		rendererState.depthTestEnabled = false;

		lineRenderer.setColor(Colors::Yellow);
	}

	VolumeRenderer::~VolumeRenderer() {
		delete vb;
		delete va;
		delete ib;
		delete shader;

		delete shapeTexture;
		delete detailTexture;
		delete noiseTex;
	}

	bool VolumeRenderer::init() {

		glm::vec2 origin = glm::vec2(-1, -1);
	
		float dist = 2.0f / splitCount;

		for (int y = 0; y < splitCount + 1; y++) {
			for (int x = 0; x < splitCount + 1; x++) {
				vertices.push_back(glm::vec3(origin.x + dist * x, origin.y + dist * y, 0));
			}
		}


		for (int y = 0; y < splitCount; y++) {
			for (int x = 0; x < splitCount; x++) {
				indices.push_back(x + y * (splitCount + 1));
				indices.push_back(x + 1 + (y + 1) * (splitCount + 1));
				indices.push_back(x + 1 + y * (splitCount + 1));

				indices.push_back(x + y * (splitCount + 1));
				indices.push_back(x + (y + 1) * (splitCount + 1));
				indices.push_back(x + 1 + (y + 1) * (splitCount + 1));
			}
		}

		//OpenGL objects creation
		vb = new VertexBuffer(vertices.data(), vertices.size() * sizeof(glm::vec3), GL_STATIC_DRAW);

		va = new VertexArray();
		va->PushElement(vb, 3, VertexArray::DataType::FLOAT, false);

		ib = new IndexBuffer(indices.data(), indices.size() * sizeof(uint32_t), GL_STATIC_DRAW);

		shader = new Shader("Shaders/VolumeRenderer.shader");

		AddDefaultNoiseLayers();

		if(computeDataOnGPU)
			GenerateVolumeDataGPU();
		else 
			GenerateVolumeData();

		std::vector<uint8_t> noiseData;
		Xorshift rng((uint32_t)2356);

		for (int y = 0; y < 64; y++) {
			for (int x = 0; x < 64; x++) {
				noiseData.push_back((uint8_t)(rng.nextFloat() * 255.0f));
			}
		}

		noiseTex = new Texture2D(noiseData.data(), 64, 64, TextureFormat::R8_UNORM, TextureFilter::POINT, TextureWrapper::REPEAT);

		return true;
	}

	void VolumeRenderer::dispose() {

	}

	void VolumeRenderer::update(float delta) {
		//ENG_LOG_INFO("Delta time: {0}", delta);

		shapeTexturePositionOffset += shapeTextureMovementSpeed * delta;
		detailTexturePositionOffset += detailTextureMovementSpeed * delta;
	}

	void VolumeRenderer::draw(PerspectiveCamera& camera, FrameBuffer& fb) {
		if (InputHandler::Key(KEY_LEFT_CONTROL) && InputHandler::KeyDown(KEY_P)) {
			showPropertiesWindow != showPropertiesWindow;
		}

		OpenGLUtility::SetOpenGLState(rendererState);

		modelMat = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), scale);

		va->bind();
		ib->bind();

		shader->bind();

		shapeTexture->setActiveTextureSlot(0);
		shapeTexture->bind();

		detailTexture->setActiveTextureSlot(1);
		detailTexture->bind();

		noiseTex->setActiveTextureSlot(2);
		noiseTex->bind();

		glActiveTexture(GL_TEXTURE0 + 3);
		glBindTexture(GL_TEXTURE_2D, fb.getDepthAttachmentID());

		shader->SetUniform1i("screenWidth", fb.getWidth());
		shader->SetUniform1i("screenHeight", fb.getHeight());

		shader->SetUniform3f("cameraPos", camera.getPosition());

		shader->SetUniform1i("shapeTex", 0);
		shader->SetUniform1i("detailTex", 1);
		shader->SetUniform1i("noiseTex", 2);
		shader->SetUniform1i("depthTex", 3);

		shader->SetUniform1f("stepSize", stepSize);
		shader->SetUniform3f("boundMin", position - volumeSize / 2.0f);
		shader->SetUniform3f("boundMax", position + volumeSize / 2.0f);

		shader->SetUniform1f("coverage", coverage);
		
		shader->SetUniform1f("zNear", camera.getNearPlaneDistance());
		shader->SetUniform1f("zFar", camera.getFarPlaneDistance());

		shader->SetUniform3f("shapeTexPosOffset", shapeTexturePositionOffset);
		shader->SetUniform3f("detailTexPosOffset", detailTexturePositionOffset);

		shader->SetUniform1f("shapeTexFitSize", shapeTextureFitSize);
		shader->SetUniform1f("detailTexFitSize", detailTextureFitSize);

		shader->SetUniform4f("shapeTexWeights", shapeTextureWeights);
		shader->SetUniform2f("detailTexWeights", detailTextureWeights);

		shader->SetUniform3f("lightDirection", lightDirection);
		shader->SetUniform1i("lightMarchStepCount", lightMarchStepCount);
		shader->SetUniform1f("lightBaseIntensity", lightBaseIntensity);
		shader->SetUniform1f("lightAbsorptionSun", lightAbsorptionSun);
		shader->SetUniform1f("lightAbsorptionCloud", lightAbsorptionCloud);
		shader->SetUniform1f("transmittanceThreshold", transmittanceThreshold);
		shader->SetUniform1f("lightEnergyCoefficient", lightEnergyCoefficient);

		shader->SetUniform1f("falloffDistanceH", falloffDistanceHorizontal);
		shader->SetUniform1f("falloffDistanceV", falloffDistanceVertical);

		shader->SetUniformMatrix4x4("_CameraToWorld", 1, false, glm::value_ptr(glm::inverse(camera.getViewMatrix())));
		shader->SetUniformMatrix4x4("_CameraInverseProjection", 1, false, glm::value_ptr(glm::inverse(camera.getProjectionMatrix())));

		for (int i = 0; i < splitCount * splitCount; i++)
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (const void*)(i * 6));

		if (showPropertiesWindow) {
			DrawPropertiesWindow();
		}

		if (showBoundingBox) {
			DrawBoundingBox(camera);
		}
	}

	void VolumeRenderer::setPosition(glm::vec3 position) {
		this->position = position;
	}

	void VolumeRenderer::setScale(glm::vec3 scale) {
		this->scale = scale;
	}

	void VolumeRenderer::setRotation(glm::vec3 rotation) {
		this->rotation = rotation;
	}

	glm::vec3 VolumeRenderer::getPosition() {
		return position;
	}

	glm::vec3 VolumeRenderer::getScale() {
		return scale;
	}

	glm::vec3 VolumeRenderer::getRotation() {
		return rotation;
	}

	void VolumeRenderer::regenerateVolumeTexture() {

	}

	void VolumeRenderer::setVolumeSize(glm::vec3 volumeSize) {
		this->volumeSize = volumeSize;
	}

	glm::vec3 VolumeRenderer::getVolumeSize() {
		return volumeSize;
	}

	void VolumeRenderer::setShapeTextureFitSize(float size) {
		shapeTextureFitSize = size;
	}

	float VolumeRenderer::getShapeTextureFitSize() {
		return shapeTextureFitSize;
	}

	void VolumeRenderer::setDetailTextureFitSize(float size) {
		detailTextureFitSize = size;
	}

	float VolumeRenderer::getDetailTextureFitSize() {
		return detailTextureFitSize;
	}

	void VolumeRenderer::setStepSize(float stepSize) {
		this->stepSize = stepSize;
	}

	float VolumeRenderer::getStepSize() {
		return stepSize;
	}

	void VolumeRenderer::setLightMarchStepCount(int32_t count) {
		lightMarchStepCount = glm::clamp<int32_t>(count, 1, 50);
	}

	int32_t VolumeRenderer::getLightMarchStepCount() {
		return 0;
	}

	void VolumeRenderer::setLightBaseIntensity(float baseIntensity) {
		lightBaseIntensity = baseIntensity;
	}

	void VolumeRenderer::setLightAbsorptionCoefficient(float absorption) {
		lightAbsorptionCloud = absorption;
	}

	float VolumeRenderer::getLightBaseIntensity() {
		return lightBaseIntensity;
	}

	float VolumeRenderer::getLightAbsorptionCoefficient() {
		return lightAbsorptionSun;
	}

	void VolumeRenderer::setLightDirection(glm::vec3 direction) {
		lightDirection = direction;
	}

	void VolumeRenderer::setScreenSize(glm::vec2 screenSize) {
		this->screenSize = screenSize;
	}

	void VolumeRenderer::DrawPropertiesWindow() {
		ImGui::Begin("Volume Renderer");
		ImGui::Checkbox("Show Bounding Box", &showBoundingBox);
		ImGui::DragFloat3("Position", glm::value_ptr(position), 0.1f);
		//ImGui::Checkbox("Show Properties Window", &showPropertiesWindow);
		ImGui::InputInt("Shape Texture Size", (int*) & shapeTextureSize);
		ImGui::InputInt("Detail Texture Size", (int*)&detailTextureSize);

		ImGui::DragFloat("Shape Texture Fit Size", &shapeTextureFitSize, 10, 10, 20000);
		ImGui::DragFloat("Detail Texture Fit Size", &detailTextureFitSize, 10,10, 10000);

		ImGui::DragFloat3("Volume Size", glm::value_ptr(volumeSize), 100, 0, 64000);
		ImGui::DragFloat3("Shape Texture Speed", glm::value_ptr(shapeTextureMovementSpeed), 0.01f, -100, 100);
		ImGui::DragFloat3("Detail Texture Speed", glm::value_ptr(detailTextureMovementSpeed), 0.01f, -100, 100);

		ImGui::DragFloat4("Shape Texture Weights", glm::value_ptr(shapeTextureWeights), 0.001f,-1, 5);
		ImGui::DragFloat2("Detail Texture Weights", glm::value_ptr(detailTextureWeights), 0.001f, -1, 5);

		ImGui::Text("Shape Texture Position (%.1f,%.1f,%.1f)", shapeTexturePositionOffset.x, shapeTexturePositionOffset.y, shapeTexturePositionOffset.z);
		ImGui::Text("Detail Texture Position (%.1f,%.1f,%.1f)", detailTexturePositionOffset.x, detailTexturePositionOffset.y, detailTexturePositionOffset.z);
		
		if (ImGui::Button("Reset Offset")) {
			shapeTexturePositionOffset = glm::vec3(0, 0, 0);
			detailTexturePositionOffset = glm::vec3(0, 0, 0);
		}

		ImGui::Separator();
		
		ImGui::NewLine();
		ImGui::SliderFloat("Coverage", &coverage, 0, 1);
		ImGui::DragFloat("Step Size", &stepSize, 0.01f, 5, 200);
		ImGui::DragInt("Light March Step Count", &lightMarchStepCount, 0.25f, 1, 50);
		ImGui::SliderFloat("Light Base Intensity", &lightBaseIntensity, 0, 1);
		ImGui::DragFloat("Light Absorption Cloud", &lightAbsorptionCloud, 0.001f, 0, 20);
		ImGui::DragFloat("Light Absorption Sun", &lightAbsorptionSun, 0.001f, 0, 10);
		ImGui::SliderFloat("Transmittance Threshold", &transmittanceThreshold, 0, 1);
		ImGui::DragFloat("Light Energy Coefficient", &lightEnergyCoefficient, 0.01, 0, 10);

		ImGui::DragFloat("Falloff Distance Vertical", &falloffDistanceVertical, 0.1, 0, 1000);
		ImGui::DragFloat("Falloff Distance Horizontal", &falloffDistanceHorizontal, 0.1, 0, 1000);

		ImGui::SliderFloat3("Light Direction", glm::value_ptr(lightDirection), -1, 1);
		ImGui::Separator();

		ImGui::NewLine();

		std::vector<std::string> textureTypes = { "Shape", "Detail" };
		static uint32_t selectedTextureType = 0;

		const char* current_tex_type = textureTypes[selectedTextureType].c_str();

		if (ImGui::BeginCombo("Texture Type", current_tex_type)) {
			for (uint32_t i = 0; i < textureTypes.size(); i++) {
				bool is_selected = (bool)!strcmp(current_tex_type, textureTypes[i].c_str());
				if (ImGui::Selectable(textureTypes[i].c_str(), is_selected)) {
					current_tex_type = textureTypes[i].c_str();
					selectedTextureType = i;
				}

				if (is_selected)
					ImGui::SetItemDefaultFocus();
			}

			ImGui::EndCombo();
		}

		std::vector<std::string> layerNames;
		int layerCount = selectedTextureType == 0 ? 4 : 2;

		for (int i = 0; i < layerCount; i++) {
			layerNames.push_back(std::string("Layer") + std::to_string(i + 1));
		}

		static uint32_t selected_layer = 0;
		static NoiseLayer tempLayer;

		if (selectedTextureType == 1 && selected_layer > 1)
			selected_layer = 1;

		const char* current_name = layerNames[selected_layer].c_str();

		if (ImGui::BeginCombo("Layers", current_name)) {
			for (uint32_t i = 0; i < layerNames.size(); i++) {
				bool is_selected = (bool)!strcmp(current_name, layerNames[i].c_str());
				if (ImGui::Selectable(layerNames[i].c_str(), is_selected)) {
					current_name = layerNames[i].c_str();
					selected_layer = i;
					if(selectedTextureType == 0)
						tempLayer = shapeNoiseLayers[selected_layer];
					else if(selectedTextureType == 1)
						tempLayer = detailNoiseLayers[selected_layer];
				}

				if (is_selected)
					ImGui::SetItemDefaultFocus();
			}

			ImGui::EndCombo();
		}

		std::vector<NoiseLayer>* currentLayer = selectedTextureType == 0 ? &shapeNoiseLayers : &detailNoiseLayers;

		const char* noise_types[] = {"Perin", "Worley", "Inverse Worley"};
		int chosen_type = (*currentLayer)[selected_layer].type / 2;
		const char* current_type = noise_types[chosen_type];

		if (ImGui::BeginCombo("Noise Type", current_type)) {
			for (int i = 0; i < IM_ARRAYSIZE(noise_types); i++) {
				bool is_selected = (chosen_type == i);

				if (ImGui::Selectable(noise_types[i], is_selected)) {
					chosen_type = i;
					(*currentLayer)[selected_layer].type = (NoiseType)(i * 2 + 1);
				}

				if (is_selected)
					ImGui::SetItemDefaultFocus();
			}

			ImGui::EndCombo();
		}

		ImGui::SliderInt("Octave count", &(*currentLayer)[selected_layer].octaveCount, 1, 6);
		ImGui::DragFloat3("offset", glm::value_ptr((*currentLayer)[selected_layer].offset), 0.01, -1000, 1000);
		ImGui::DragInt("scale", &(*currentLayer)[selected_layer].scale, 0.1f, 0, 512);
		ImGui::SliderFloat("opacity", &(*currentLayer)[selected_layer].opacity, -1, 1);

		//if (ImGui::Button("Add Layer")) {
		//	NoiseLayer layers;
		//
		//	noiseLayers.push_back(layers);
		//	selected_layer = noiseLayers.size() - 1;
		//}
		//
		//ImGui::SameLine();
		//if (ImGui::Button("Delete Layer")) {
		//	if (noiseLayers.size() >= 1) {
		//		noiseLayers.erase(noiseLayers.begin() + selected_layer);
		//		if (noiseLayers.size() >= 1) {
		//			if (selected_layer > 0)
		//				selected_layer--;
		//			tempLayer = noiseLayers[selected_layer];
		//		}
		//	}
		//}

		if (ImGui::Button("Regenerate")) {
			if (computeDataOnGPU)
				GenerateVolumeDataGPU();
			else
				GenerateVolumeData();
		}

		ImGui::End();
	}

	void VolumeRenderer::DrawBoundingBox(PerspectiveCamera& camera) {
		lineRenderer.drawBoundingBox(position - volumeSize / 2.0f, position + volumeSize / 2.0f, camera);
	}

	void VolumeRenderer::GenerateVolumeData() {
		ClearData();

		for (int i = 0; i < shapeNoiseLayers.size(); i++) {
			shapeNoiseLayers[i].normalizedScale = (float)shapeNoiseLayers[i].scale / shapeTextureSize;
		}

		for (int i = 0; i < detailNoiseLayers.size(); i++) {
			detailNoiseLayers[i].normalizedScale = (float)detailNoiseLayers[i].scale / detailTextureSize;
		}

		std::vector<uint8_t> volumeData;

		//Shape Texture Generation
		uint32_t stride = shapeNoiseLayers.size();
		uint32_t data_size = shapeTextureSize * shapeTextureSize * shapeTextureSize * stride;

		volumeData.reserve(data_size);

		noiseGenerator.EnableNoiseRepeat(true);

		for (uint32_t i = 0; i < shapeNoiseLayers.size(); i++) {
			noiseGenerator.SetNoiseRepeatFrequency(glm::ivec3(shapeNoiseLayers[i].scale, shapeNoiseLayers[i].scale, shapeNoiseLayers[i].scale));
			noiseGenerator.SetNoiseRepeatOffset(shapeNoiseLayers[i].offset);

			for (uint32_t z = 0; z < shapeTextureSize; z++) {
				uint32_t z_offset = z * shapeTextureSize * shapeTextureSize;
				
				for (uint32_t y = 0; y < shapeTextureSize; y++) {
					uint32_t y_offset = y * shapeTextureSize;

					for (uint32_t x = 0; x < shapeTextureSize; x++) {
						glm::vec3 point = glm::vec3(x, y, z);
						float noise = noiseGenerator.Value(point, shapeNoiseLayers[i]);

						volumeData[(z_offset + y_offset + x) * stride + i] = (uint8_t)(glm::clamp<float>(noise, 0, 1) * 255);
					}
				}
			}
		}

		shapeTexture = new Texture3D(volumeData.data(), shapeTextureSize, shapeTextureSize , shapeTextureSize, 
			TextureFormat::RGBA8_UNORM, TextureFilter::TRILINEAR, TextureWrapper::REPEAT);

		volumeData.clear();
		volumeData.shrink_to_fit();
	
		//Detail Texture Generation
		stride = detailNoiseLayers.size();
		data_size = detailTextureSize * detailTextureSize * detailTextureSize * stride;

		volumeData.reserve(data_size);

		noiseGenerator.EnableNoiseRepeat(true);

		for (uint32_t i = 0; i < detailNoiseLayers.size(); i++) {
			noiseGenerator.SetNoiseRepeatFrequency(glm::ivec3(detailNoiseLayers[i].scale, detailNoiseLayers[i].scale, detailNoiseLayers[i].scale));
			noiseGenerator.SetNoiseRepeatOffset(detailNoiseLayers[i].offset);

			for (uint32_t z = 0; z < detailTextureSize; z++) {
				uint32_t z_offset = z * detailTextureSize * detailTextureSize;

				for (uint32_t y = 0; y < detailTextureSize; y++) {
					uint32_t y_offset = y * detailTextureSize;

					for (uint32_t x = 0; x < detailTextureSize; x++) {
						glm::vec3 point = glm::vec3(x, y, z);
						float noise = noiseGenerator.Value(point, detailNoiseLayers[i]);

						volumeData[(z_offset + y_offset + x) * stride + i] = (uint8_t)(glm::clamp<float>(noise, 0, 1) * 255);
					}
				}
			}
		}

		detailTexture = new Texture3D(volumeData.data(), detailTextureSize, detailTextureSize, detailTextureSize,
			TextureFormat::RG8_UNORM, TextureFilter::TRILINEAR, TextureWrapper::REPEAT);

		volumeData.clear();
		volumeData.shrink_to_fit();
	}

	void VolumeRenderer::GenerateVolumeDataGPU() {
		ClearData();

		//Creating textures
		shapeTexture = new Texture3D(nullptr, shapeTextureSize, shapeTextureSize, shapeTextureSize,
			TextureFormat::RGBA8_UNORM, TextureFilter::TRILINEAR, TextureWrapper::REPEAT);

		detailTexture = new Texture3D(nullptr, detailTextureSize, detailTextureSize, detailTextureSize,
			TextureFormat::RG8_UNORM, TextureFilter::TRILINEAR, TextureWrapper::REPEAT);

		//Normalizing scales
		for (int i = 0; i < shapeNoiseLayers.size(); i++) {
			shapeNoiseLayers[i].normalizedScale = (float)shapeNoiseLayers[i].scale / shapeTextureSize;
		}
		
		for (int i = 0; i < detailNoiseLayers.size(); i++) {
			detailNoiseLayers[i].normalizedScale = (float)detailNoiseLayers[i].scale / detailTextureSize;
		}

		
		//Writing noise data to textures
		noiseGeneratorGPU.EnableNoiseRepeat(false);
		for (uint32_t i = 0; i < shapeNoiseLayers.size(); i++) {
			noiseGeneratorGPU.SetNoiseRepeatFrequency(glm::ivec3(shapeNoiseLayers[i].scale, shapeNoiseLayers[i].scale, shapeNoiseLayers[i].scale));
			noiseGeneratorGPU.SetNoiseRepeatOffset(shapeNoiseLayers[i].offset);

			noiseGeneratorGPU.GenerateNoise3D(*shapeTexture, shapeNoiseLayers[i], i);
		}


		//noiseGenerator.EnableNoiseRepeat(false);
		//for (uint32_t i = 0; i < detailNoiseLayers.size(); i++) {
		//	noiseGeneratorGPU.SetNoiseRepeatFrequency(glm::ivec3(detailNoiseLayers[i].scale, detailNoiseLayers[i].scale, detailNoiseLayers[i].scale));
		//	noiseGeneratorGPU.SetNoiseRepeatOffset(detailNoiseLayers[i].offset);
		//
		//	noiseGeneratorGPU.GenerateNoise3D(*detailTexture, detailNoiseLayers[i], i);
		//}
	}

	void VolumeRenderer::ClearData() {
		delete shapeTexture;
		delete detailTexture;
 	}

	void VolumeRenderer::AddDefaultNoiseLayers() {
		//Shape Noise Layers
		NoiseLayer sLayer1;
		sLayer1.offset = glm::vec3(120.34, 467.66, 53.87);
		sLayer1.scale = 3.0f;

		NoiseLayer sLayer2;
		sLayer2.type = NoiseType::Worley3D;
		sLayer2.offset = glm::vec3(125.34, 46.66, 520.87);
		sLayer2.scale = 8.0f;

		NoiseLayer sLayer3;
		sLayer3.type = NoiseType::Worley3D;
		sLayer3.offset = glm::vec3(125.34, 46.66, 520.87);
		sLayer3.scale = 12.0f;

		NoiseLayer sLayer4;
		sLayer4.type = NoiseType::Worley3D;
		sLayer4.offset = glm::vec3(125.34, 46.66, 520.87);
		sLayer4.scale = 24.0f;

		shapeNoiseLayers.push_back(sLayer1);
		shapeNoiseLayers.push_back(sLayer2);
		shapeNoiseLayers.push_back(sLayer3);
		shapeNoiseLayers.push_back(sLayer4);

		//Detail Noise Layers
		NoiseLayer dLayer1;
		dLayer1.type = NoiseType::Worley3D;
		dLayer1.offset = glm::vec3(120.34, 467.66, 53.87);
		dLayer1.scale = 4.0f;
		dLayer1.octaveCount = 3;

		NoiseLayer dLayer2;
		dLayer2.type = NoiseType::Worley3D;
		dLayer2.offset = glm::vec3(120.34, 467.66, 53.87);
		dLayer2.scale = 6.0f;
		dLayer2.octaveCount = 3;

		detailNoiseLayers.push_back(dLayer1);
		detailNoiseLayers.push_back(dLayer2);
	}

	void VolumeRenderer::UpdateVertexData() {
		vertices.clear();

		vertices = {
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
			vertices[i] *= volumeSize;
		}

		vb->SetData(vertices.data(), 0, sizeof(glm::vec3) * vertices.size());
	}
}