#pragma once
#include "BaseShader.h"
namespace Engine {
	class Shader : public BaseShader {
	private:
		uint32_t id = -1;

		uint32_t vs_id = -1, fs_id = -1;
		uint32_t gs_id = -1, ts_id = -1;
	
	public:
		Shader(const std::string filePath);
		~Shader();

		void bind();
		void unbind();
	};

}