#include "Shader.h"
#include <iostream>

namespace Engine {
	Shader::Shader(const std::string filePath) {
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

		ShaderType currentType = ShaderType::None;

		while (std::getline(file, line)) {
			if (line.find("#vertex shader") != std::string::npos) {
				currentType = ShaderType::Vertex;

				if (!InShaderTypeList(currentType)) {
					shaderTypes.push_back(currentType);
				}
			}
			else if (line.find("#fragment shader") != std::string::npos) {
				currentType = ShaderType::Fragment;

				if (!InShaderTypeList(currentType)) {
					shaderTypes.push_back(currentType);
				}
			}
			else if (line.find("#geometry shader") != std::string::npos) {
				currentType = ShaderType::Geometry;

				if (!InShaderTypeList(currentType)) {
					shaderTypes.push_back(currentType);
				}
			}
			else if (line.find("#tessellation shader") != std::string::npos) {
				currentType = ShaderType::Tessellation;

				if (!InShaderTypeList(currentType)) {
					shaderTypes.push_back(currentType);
				}
			}
			else if (line.find("#compute shader") != std::string::npos) {
				ENG_LOG_ERROR("Given standard shader file contains Compute Shader");
				return;
			}
			else {
				switch (currentType)
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
				}
			}
		}

		ShaderVariant* sv = new ShaderVariant();

		sv->id = glCreateProgram();

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

				glAttachShader(sv->id, vs_id);

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

				glAttachShader(sv->id, fs_id);

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

				glAttachShader(sv->id, gs_id);

			}
		}

		glLinkProgram(sv->id);

		glGetProgramiv(sv->id, GL_LINK_STATUS, &success);
		if (!success) {
			int length;
			glGetProgramiv(sv->id, GL_INFO_LOG_LENGTH, &length);
			char* message = (char*)malloc(length);
			glGetProgramInfoLog(sv->id, length, &length, message);

			ENG_LOG_ERROR("FAILED TO LINK SHADER(PROGRAM): {0}", message);
			free(message);
		}

		glValidateProgram(sv->id);

		glGetProgramiv(sv->id, GL_VALIDATE_STATUS, &success);
		if (!success) {
			int length;
			glGetProgramiv(sv->id, GL_INFO_LOG_LENGTH, &length);
			char* message = (char*)malloc(length);
			glGetProgramInfoLog(sv->id, length, &length, message);

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

		shaderVariants.push_back(sv);
		SetCurrentVariantIndex(0);

		ENG_LOG_INFO("Shader is created, variant id: {0}", sv->id);
	}

	Shader::~Shader() {
		for (int32_t i = 0; i < shaderVariants.size(); i++) {
			glDeleteProgram(shaderVariants[i]->id);

			ENG_LOG_INFO("Shader is deleted, variant id: {0}", shaderVariants[i]->id);

			delete shaderVariants[i];
		}
	}

	void Shader::bind() {
		glUseProgram(currentVariant->id);
	}

	void Shader::unbind() {
		glUseProgram(0);
	}
}