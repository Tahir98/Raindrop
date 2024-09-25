#include "ComputeShader.h"
#include <iostream>

namespace Engine {
	ComputeShader::ComputeShader(const std::string filePath) {
		std::ifstream file(filePath);

		if (!file.is_open()) {
			ENG_LOG_ERROR("Given shader file is not found: {0}", filePath);
			return;
		}

		std::string line;

		std::string cs_string = "";

		while (std::getline(file, line)) {
			if (line.find("#compute shader") == std::string::npos) {
				cs_string += line + "\n";
			}
		}

		id = glCreateProgram();
		int success;

		cs_id = glCreateShader(GL_COMPUTE_SHADER);

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

		glLinkProgram(id);

		glGetProgramiv(id, GL_LINK_STATUS, &success);
		if (!success) {
			int length;
			glGetProgramiv(id, GL_INFO_LOG_LENGTH, &length);
			char* message = (char*)malloc(length);
			glGetProgramInfoLog(id, length, &length, message);

			ENG_LOG_ERROR("FAILED TO LINK COMPUTE SHADER(PROGRAM): {0}", message);
			free(message);
		}

		glValidateProgram(id);

		glGetProgramiv(id, GL_VALIDATE_STATUS, &success);
		if (!success) {
			int length;
			glGetProgramiv(id, GL_INFO_LOG_LENGTH, &length);
			char* message = (char*)malloc(length);
			glGetProgramInfoLog(id, length, &length, message);

			ENG_LOG_ERROR("FAILED TO VALIDATE COMPUTE SHADER(PROGRAM): {0}", message);
			free(message);
			exit(-1);
		}

		if (cs_id != -1)
			glDeleteShader(cs_id);

		ENG_LOG_INFO("Compute Shader is created, id: {0}", id);
	}

	ComputeShader::~ComputeShader() {
		glDeleteProgram(id);

		ENG_LOG_INFO("Comptute Shader is deleted, id: {0}", id);
	}

	void ComputeShader::DispatchCompute(uint32_t threadGroupX, uint32_t threadGroupY, uint32_t threadGroupZ) {
		bind();
		glDispatchCompute(threadGroupX, threadGroupY, threadGroupZ);

		glMemoryBarrier(GL_ALL_BARRIER_BITS);
	}
}