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

		Shader* shader;
	public:
		NoiseGeneratorGPU() {
			shader = new Shader("Shaders/NoiseGenerator.comp");
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
			shader->bind();
			
			glBindImageTexture(0, noiseTex.getID(), 0, false, 0, GL_READ_WRITE, GL_RGBA8);

			shader->SetUniform1i("_NoiseTex2D", 0);
			shader->SetUniform1i("_NoiseRepeatEnabled", noiseRepeatEnabled);
			shader->SetUniform3i("_RepeatFrequency", repeatFrequency);
			shader->SetUniform3i("_RepeatOffset", repeatOffset);

			shader->SetUniform1i("_Layer.type", layer.type);
			shader->SetUniform1i("_Layer.blend", layer.blend);
			shader->SetUniform3f("_Layer.offset", layer.offset);
			shader->SetUniform1i("_Layer.octaveCount", layer.octaveCount);
			shader->SetUniform1i("_Layer.scale", layer.scale);
			shader->SetUniform1f("_Layer.normalizedScale", layer.normalizedScale);
			shader->SetUniform1f("_Layer.opacity", layer.opacity);
			shader->SetUniform1i("_Layer.smoothnessLevel", layer.smoothnessLevel);
		
			glm::uvec3 texSize = glm::uvec3(noiseTex.getWidth(), noiseTex.getHeight(), 1);
			shader->SetUniform3ui("_TexSize", texSize);
			shader->SetUniform1i("_WriteTo2DTex", (int)true);
			shader->SetUniform1ui("_ChannelIndex", 0);
			shader->DispatchCompute(texSize.x / 4, texSize.y / 4, 1);
		}
	};
}