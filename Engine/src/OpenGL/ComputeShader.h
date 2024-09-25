#pragma once
#include "BaseShader.h"

namespace Engine {
	class ComputeShader : public BaseShader {
	private:
		uint32_t cs_id = -1;

	public:
		ComputeShader(const std::string filePath);
		~ComputeShader();

		void DispatchCompute(uint32_t threadGroupX, uint32_t threadGroupY, uint32_t threadGroupZ);
	};

}