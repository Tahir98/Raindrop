#pragma once
#include "Log.h"
#include "glad/glad.h"
#include <glm/glm.hpp>
#include <string>
#include <fstream>

namespace Engine {
	class Shader {
	public:
		enum ShaderType {
			None = -1, Vertex = 0, Fragment = 1, Geometry = 2, Tessellation = 3, Compute = 4
		};

	private:
		uint32_t id;
		uint32_t vs_id = -1, fs_id = -1;
		uint32_t gs_id = -1, ts_id = -1, cs_id = -1;

		std::vector<ShaderType> shaderTypes;

	public:
		Shader(const std::string filePath) {
			std::ifstream file(filePath);

			if (!file.is_open()) {
				ENG_LOG_ERROR("Given shader file is not found: {0}", filePath);
				return;
			}

			std::string line;

			std::string vs_string = "";
			std::string fs_string = "";
			std::string gs_string = "";
			std::string ts_string = "";
			std::string cs_string = "";
			
			ShaderType currentTpye = ShaderType::None;

			while (std::getline(file, line)) {
				if (line.find("#vertex shader") != std::string::npos) {
					currentTpye = ShaderType::Vertex;
			
					if (!InShaderTypeList(currentTpye)) {
						shaderTypes.push_back(currentTpye);
					}
				}
				else if (line.find("#fragment shader") != std::string::npos) {
					currentTpye = ShaderType::Fragment;

					if (!InShaderTypeList(currentTpye)) {
						shaderTypes.push_back(currentTpye);
					}
				}
				else if (line.find("#geometry shader") != std::string::npos) {
					currentTpye = ShaderType::Geometry;

					if (!InShaderTypeList(currentTpye)) {
						shaderTypes.push_back(currentTpye);
					}
				}
				else if (line.find("#tessalation shader") != std::string::npos) {
					currentTpye = ShaderType::Tessellation;

					if (!InShaderTypeList(currentTpye)) {
						shaderTypes.push_back(currentTpye);
					}
				}
				else if (line.find("#compute shader") != std::string::npos) {
					currentTpye = ShaderType::Compute;

					if (!InShaderTypeList(currentTpye)) {
						shaderTypes.push_back(currentTpye);
					}
				}
				else {
					switch (currentTpye)
					{
					case Vertex:
						vs_string += line + "\n";
						break;
					case Fragment:
						fs_string += line + "\n";
						break;
					case Geometry:
						gs_string += line + "\n";
						break;
					case Tessellation:
						ts_string += line + "\n";
						break;
					case Compute:
						cs_string += line + "\n";
						break;
					}
				}
			}
		}

	private:
		bool InShaderTypeList(ShaderType type) {
			for (int i = 0; i < shaderTypes.size(); i++) 
				if (type == shaderTypes[i]) 
					return true;

			return false;
		}
	};

}