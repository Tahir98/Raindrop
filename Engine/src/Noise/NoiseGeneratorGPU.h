#pragma once
#include "NoiseGeneratorDefines.h"

#include "OpenGL/Shader.h"
#include "OpenGL/Texture2D.h"
#include "OpenGL/Texture3D.h"


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

		void GenerateNoise(Texture2D& noiseTex, NoiseLayer layer) {
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
			computeShader->SetUniform1i("_WriteTo2DTex", (int)true);
			computeShader->SetUniform1ui("_ChannelIndex", 0);
			computeShader->DispatchCompute(texSize.x / 4, texSize.y / 4, 1);
		}
	};
}