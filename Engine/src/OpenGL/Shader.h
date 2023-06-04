#pragma once
#include "Log.h"
#include "glad/glad.h"
#include <glm/glm.hpp>
#include <string>
#include <fstream>
#include <unordered_map>

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

		std::unordered_map<std::string, int> uniforms;

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

			id = glCreateProgram();
			int success;

			for (ShaderType type : shaderTypes) {
				if (type == Vertex) {
					vs_id = glCreateShader(GL_VERTEX_SHADER);

					const char* source1 = vs_string.c_str();

					glShaderSource(vs_id, 1, &source1, nullptr);
					glCompileShader(vs_id);

					glGetShaderiv(vs_id, GL_COMPILE_STATUS, &success);
					if (!success) {
						int length;
						glGetShaderiv(vs_id, GL_INFO_LOG_LENGTH, &length);
						char* message = (char*)malloc(length);
						glGetShaderInfoLog(vs_id, length, &length, message);

						ENG_LOG_ERROR("FAILED TO COMPILE VERTEX SHADER: {0}", message);

						free(message);
					}

					glAttachShader(id, vs_id);

				}
				else if (type == Fragment) {
					fs_id = glCreateShader(GL_FRAGMENT_SHADER);

					const char* source2 = fs_string.c_str();

					glShaderSource(fs_id, 1, &source2, nullptr);
					glCompileShader(fs_id);

					glGetShaderiv(fs_id, GL_COMPILE_STATUS, &success);
					if (!success) {
						int length;
						glGetShaderiv(fs_id, GL_INFO_LOG_LENGTH, &length);
						char* message = (char*)malloc(length);
						glGetShaderInfoLog(fs_id, length, &length, message);

						ENG_LOG_ERROR("FAILED TO COMPILE FRAGMENT SHADER: {0}", message);

						free(message);
					}

					glAttachShader(id, fs_id);

				}
				else if (type == Geometry) {
					gs_id = glCreateShader(GL_GEOMETRY_SHADER);

					const char* source3 = gs_string.c_str();

					glShaderSource(gs_id, 1, &source3, nullptr);
					glCompileShader(gs_id);

					glGetShaderiv(gs_id, GL_COMPILE_STATUS, &success);
					if (!success) {
						int length;
						glGetShaderiv(gs_id, GL_INFO_LOG_LENGTH, &length);
						char* message = (char*)malloc(length);
						glGetShaderInfoLog(gs_id, length, &length, message);

						ENG_LOG_ERROR("FAILED TO COMPILE GEOMETRY SHADER: {0}", message);

						free(message);
					}

					glAttachShader(id, gs_id);

				}
				else if (type == Compute) {
					vs_id = glCreateShader(GL_COMPUTE_SHADER);

					const char* source4 = cs_string.c_str();

					glShaderSource(cs_id, 1, &source4, nullptr);
					glCompileShader(cs_id);

					glGetShaderiv(cs_id, GL_COMPILE_STATUS, &success);
					if (!success) {
						int length;
						glGetShaderiv(cs_id, GL_INFO_LOG_LENGTH, &length);
						char* message = (char*)malloc(length);
						glGetShaderInfoLog(cs_id, length, &length, message);

						ENG_LOG_ERROR("FAILED TO COMPILE COMPUTE SHADER: {0}", message);

						free(message);
					}

					glAttachShader(id, cs_id);

				}

			}

			glLinkProgram(id);

			glGetProgramiv(id, GL_LINK_STATUS, &success);
			if (!success) {
				int length;
				glGetProgramiv(id, GL_INFO_LOG_LENGTH, &length);
				char* message = (char*)malloc(length);
				glGetProgramInfoLog(id, length, &length, message);

				ENG_LOG_ERROR("FAILED TO LINK SHADER(PROGRAM): {0}", message);
				free(message);
			}

			glValidateProgram(id);

			glGetProgramiv(id, GL_VALIDATE_STATUS, &success);
			if (!success) {
				int length;
				glGetProgramiv(id, GL_INFO_LOG_LENGTH, &length);
				char* message = (char*)malloc(length);
				glGetProgramInfoLog(id, length, &length, message);

				ENG_LOG_ERROR("FAILED TO VALIDATE SHADER(PROGRAM): {0}", message);
				free(message);
				exit(-1);
			}

			if (vs_id != -1)
				glDeleteShader(vs_id);
			if (fs_id != -1)
				glDeleteShader(fs_id);
			if (gs_id != -1)
				glDeleteShader(gs_id);
			if (cs_id != -1)
				glDeleteShader(cs_id);

		}

		void bind() {
			glUseProgram(id);
		}

		void unbind() {
			glUseProgram(0);
		}

		void SetUniform1f(std::string uname, float v) {

			int location = -1;

			if (uniforms.find(uname) == uniforms.end()) {
				location = glGetUniformLocation(id, uname.c_str());

				if (location >= 0) {
					uniforms[uname] = location;
				}
				else {
					ENG_LOG_ERROR("Uniform location is not found, name: {0}", uname);
					return;
				}
			}
			else {
				location = uniforms[uname];
			}

			glUniform1f(location, v);
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