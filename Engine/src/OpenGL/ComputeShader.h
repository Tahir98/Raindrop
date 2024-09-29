#pragma once
#include "BaseShader.h"

namespace Engine {
	class ComputeShader : public BaseShader {
	private:
		uint32_t cs_id = -1;
		std::vector<std::string> kernelNames;
	public:
		ComputeShader(const std::string filePath);
		~ComputeShader();

		void bind();
		void unbind();

		int GetKernelIndex(std::string kernelName);

		bool EnableKernel(std::string kernelName);
		bool EnableKernel(int kernelIndex);

		void DispatchCompute(uint32_t threadGroupX, uint32_t threadGroupY, uint32_t threadGroupZ);
	};

}