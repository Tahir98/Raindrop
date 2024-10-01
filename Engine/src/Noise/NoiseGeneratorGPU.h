#pragma once
#include "NoiseGeneratorDefines.h"

#include "OpenGL/Shader.h"
#include "OpenGL/Texture2D.h"
#include "OpenGL/Texture3D.h"
#include "OpenGL/ComputeShader.h"

namespace Engine {
	class NoiseGeneratorGPU {
	private:
		glm::ivec3 repeatFrequency = glm::ivec3(1, 1, 1);
		glm::ivec3 repeatOffset = glm::ivec3(0, 0, 0);
		bool noiseRepeatEnabled = false;

		ComputeShader* computeShader;
	public:
		NoiseGeneratorGPU() {
			computeShader = new ComputeShader("Shaders/NoiseGenerator.comp");
		}

		void EnableNoiseRepeat(bool enable) {
			noiseRepeatEnabled = enable;
		}

		void SetNoiseRepeatFrequency(glm::ivec3 repeatFrequency) {
			this->repeatFrequency = repeatFrequency;
		}

		void SetNoiseRepeatOffset(glm::ivec3 repeatOffset) {
			this->repeatOffset = repeatOffset;
		}

		void GenerateNoise2D(Texture2D& noiseTex, const NoiseLayer& layer, int channelIndex) {
			computeShader->EnableKernel("GenerateNoise2D");
			computeShader->bind();
			
			glBindImageTexture(0, noiseTex.getID(), 0, false, 0, GL_READ_WRITE, GL_RGBA8);

			computeShader->SetUniform1i("_NoiseTex2D", 0);
			computeShader->SetUniform1i("_NoiseRepeatEnabled", noiseRepeatEnabled);
			computeShader->SetUniform3i("_RepeatFrequency", repeatFrequency);
			computeShader->SetUniform3i("_RepeatOffset", repeatOffset);

			computeShader->SetUniform1i("_Layer.type", layer.type);
			computeShader->SetUniform1i("_Layer.blend", layer.blend);
			computeShader->SetUniform3f("_Layer.offset", layer.offset);
			computeShader->SetUniform1i("_Layer.octaveCount", layer.octaveCount);
			computeShader->SetUniform1i("_Layer.scale", layer.scale);
			computeShader->SetUniform1f("_Layer.normalizedScale", layer.normalizedScale);
			computeShader->SetUniform1f("_Layer.opacity", layer.opacity);
			computeShader->SetUniform1f("_Layer.coverage", layer.coverage);
			computeShader->SetUniform1i("_Layer.smoothnessLevel", layer.smoothnessLevel);
		
			glm::uvec3 texSize = glm::uvec3(noiseTex.getWidth(), noiseTex.getHeight(), 1);
			computeShader->SetUniform3ui("_TexSize", texSize);
			computeShader->SetUniform1ui("_ChannelIndex", channelIndex);
			computeShader->DispatchCompute(texSize.x / 4, texSize.y / 4, 1);
		}

		void GenerateNoise3D(Texture3D& noiseTex, const NoiseLayer& layer, int channelIndex) {
			computeShader->EnableKernel("GenerateNoise3D");
			computeShader->bind();


			uint32_t format = 0;
			if (noiseTex.getTextureFormat() == TextureFormat::RGBA8_UNORM)
				format = GL_RGBA8;
			else if(noiseTex.getTextureFormat() == TextureFormat::RG8_UNORM)
				format = GL_RG8;
			else if (noiseTex.getTextureFormat() == TextureFormat::R8_UNORM)
				format = GL_R8;

			glBindImageTexture(1, noiseTex.getID(), 0, false, 0, GL_READ_WRITE, format);

			computeShader->SetUniform1i("_NoiseTex3D", 1);
			computeShader->SetUniform1i("_NoiseRepeatEnabled", noiseRepeatEnabled);
			computeShader->SetUniform3i("_RepeatFrequency", repeatFrequency);
			computeShader->SetUniform3i("_RepeatOffset", repeatOffset);

			computeShader->SetUniform1i("_Layer.type", layer.type);
			computeShader->SetUniform1i("_Layer.blend", layer.blend);
			computeShader->SetUniform3f("_Layer.offset", layer.offset);
			computeShader->SetUniform1i("_Layer.octaveCount", layer.octaveCount);
			computeShader->SetUniform1i("_Layer.scale", layer.scale);
			computeShader->SetUniform1f("_Layer.normalizedScale", layer.normalizedScale);
			computeShader->SetUniform1f("_Layer.opacity", layer.opacity);
			computeShader->SetUniform1f("_Layer.coverage", layer.coverage);
			computeShader->SetUniform1i("_Layer.smoothnessLevel", layer.smoothnessLevel);

			glm::uvec3 texSize = glm::uvec3(noiseTex.getWidth(), noiseTex.getHeight(), noiseTex.getDepth());
			computeShader->SetUniform3ui("_TexSize", texSize);
			computeShader->SetUniform1ui("_ChannelIndex", channelIndex);
			computeShader->DispatchCompute(glm::ceil(texSize.x / 4.0f), glm::ceil(texSize.y / 4.0f), glm::ceil(texSize.z / 4.0f));
		}

		void GenerateNoise2D(Texture2D& noiseTex, const std::vector<NoiseLayer>& layers, int channelIndex) {
			computeShader->EnableKernel("GenerateNoise2DMultiLayer");
			computeShader->bind();

			glBindImageTexture(0, noiseTex.getID(), 0, false, 0, GL_READ_WRITE, GL_RGBA8);

			computeShader->SetUniform1i("_NoiseTex2D", 0);
			computeShader->SetUniform1i("_NoiseRepeatEnabled", noiseRepeatEnabled);
			computeShader->SetUniform3i("_RepeatFrequency", repeatFrequency);
			computeShader->SetUniform3i("_RepeatOffset", repeatOffset);

			for (uint32_t i = 0; i < layers.size() && i < 10; i++) {
				computeShader->SetUniform1i("_Layers[" + std::to_string(i) +  "].type", layers[i].type);
				computeShader->SetUniform1i("_Layers[" + std::to_string(i) +  "].blend", layers[i].blend);
				computeShader->SetUniform3f("_Layers[" + std::to_string(i) + "].offset", layers[i].offset);
				computeShader->SetUniform1i("_Layers[" + std::to_string(i) +  "].octaveCount", layers[i].octaveCount);
				computeShader->SetUniform1i("_Layers[" + std::to_string(i) +  "].scale", layers[i].scale);
				computeShader->SetUniform1f("_Layers[" + std::to_string(i) +  "].normalizedScale", layers[i].normalizedScale);
				computeShader->SetUniform1f("_Layers[" + std::to_string(i) +  "].opacity", layers[i].opacity);
				computeShader->SetUniform1f("_Layers[" + std::to_string(i) +  "].coverage", layers[i].coverage);
				computeShader->SetUniform1i("_Layers[" + std::to_string(i) +  "].smoothnessLevel", layers[i].smoothnessLevel);
			}

			computeShader->SetUniform1ui("_LayerCount", layers.size() <= 10 ? layers.size() : 10);

			glm::uvec3 texSize = glm::uvec3(noiseTex.getWidth(), noiseTex.getHeight(), 1);
			computeShader->SetUniform3ui("_TexSize", texSize);
			computeShader->SetUniform1ui("_ChannelIndex", channelIndex);
			computeShader->DispatchCompute(texSize.x / 4, texSize.y / 4, 1);
		}

		void GenerateNoise3D(Texture3D& noiseTex, const std::vector<NoiseLayer>& layers, int channelIndex) {
			computeShader->EnableKernel("GenerateNoise3DMultiLayer");
			computeShader->bind();

			glBindImageTexture(1, noiseTex.getID(), 0, false, 0, GL_READ_WRITE, GL_RGBA8);

			computeShader->SetUniform1i("_NoiseTex3D", 1);
			computeShader->SetUniform1i("_NoiseRepeatEnabled", noiseRepeatEnabled);
			computeShader->SetUniform3i("_RepeatFrequency", repeatFrequency);
			computeShader->SetUniform3i("_RepeatOffset", repeatOffset);

			for (uint32_t i = 0; i < layers.size() && i < 10; i++) {
				computeShader->SetUniform1i("_Layers[" + std::to_string(i) + "].type", layers[i].type);
				computeShader->SetUniform1i("_Layers[" + std::to_string(i) + "].blend", layers[i].blend);
				computeShader->SetUniform3f("_Layers[" + std::to_string(i) + "].offset", layers[i].offset);
				computeShader->SetUniform1i("_Layers[" + std::to_string(i) + "].octaveCount", layers[i].octaveCount);
				computeShader->SetUniform1i("_Layers[" + std::to_string(i) + "].scale", layers[i].scale);
				computeShader->SetUniform1f("_Layers[" + std::to_string(i) + "].normalizedScale", layers[i].normalizedScale);
				computeShader->SetUniform1f("_Layers[" + std::to_string(i) + "].opacity", layers[i].opacity);
				computeShader->SetUniform1f("_Layers[" + std::to_string(i) + "].coverage", layers[i].coverage);
				computeShader->SetUniform1i("_Layers[" + std::to_string(i) + "].smoothnessLevel", layers[i].smoothnessLevel);
			}

			computeShader->SetUniform1ui("_LayerCount", layers.size() <= 10 ? layers.size() : 10);

			glm::uvec3 texSize = glm::uvec3(noiseTex.getWidth(), noiseTex.getHeight(), noiseTex.getDepth());
			computeShader->SetUniform3ui("_TexSize", texSize);
			computeShader->SetUniform1ui("_ChannelIndex", channelIndex);
			computeShader->DispatchCompute(glm::ceil(texSize.x / 4.0f), glm::ceil(texSize.y / 4.0f), glm::ceil(texSize.z / 4.0f));
		}
	};
}