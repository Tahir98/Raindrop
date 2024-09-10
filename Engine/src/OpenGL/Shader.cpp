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

		ENG_LOG_INFO("Shader is created, id: {0}", id);
	}

	Shader::~Shader() {
		glDeleteProgram(id);

		ENG_LOG_INFO("Shader is deleted, id: {0}", id);
	}

	void Shader::bind() {
		glUseProgram(id);
	}

	void Shader::unbind() {
		glUseProgram(0);
	}

	bool Shader::isCompute() {
		return cs_id >= 0;
	}

	void Shader::DispatchCompute(uint32_t threadGroupX, uint32_t threadGroupY, uint32_t threadGroupZ) {
		if (isCompute()) {
			bind();
			glDispatchCompute(threadGroupX, threadGroupY, threadGroupZ);

			glMemoryBarrier(GL_ALL_BARRIER_BITS);
		}
	}

	void Shader::SetUniform1f(std::string uname, float v) {

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


	void Shader::SetUniform2f(std::string uname, float v1, float v2) {

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

		glUniform2f(location, v1, v2);
	}

	void Shader::SetUniform2f(std::string uname, glm::vec2 v) {

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

		glUniform2f(location, v.x, v.y);
	}

	void Shader::SetUniform3f(std::string uname, float v1, float v2, float v3) {

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

		glUniform3f(location, v1, v2, v3);
	}

	void Shader::SetUniform3f(std::string uname, glm::vec3 v) {

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

		glUniform3f(location, v.x, v.y, v.z);
	}

	void Shader::SetUniform4f(std::string uname, float v1, float v2, float v3, float v4) {

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

		glUniform4f(location, v1, v2, v3, v4);
	}

	void Shader::SetUniform4f(std::string uname, glm::vec4 v) {

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

		glUniform4f(location, v.x, v.y, v.z, v.w);
	}

	void Shader::SetUniform1i(std::string uname, int32_t v) {
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

		glUniform1i(location, v);
	}

	void Shader::SetUniform2i(std::string uname, int32_t v1, int32_t v2) {
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

		glUniform2i(location, v1, v2);
	}

	void Shader::SetUniform2i(std::string uname, glm::ivec2 v) {
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

		glUniform2i(location, v.x, v.y);
	}

	void Shader::SetUniform3i(std::string uname, int32_t v1, int32_t v2, int32_t v3) {
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

		glUniform3i(location, v1, v2, v3);
	}

	void Shader::SetUniform3i(std::string uname, glm::ivec3 v) {
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

		glUniform3i(location, v.x, v.y, v.z);
	}

	void Shader::SetUniform4i(std::string uname, int32_t v1, int32_t v2, int32_t v3, int32_t v4) {
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

		glUniform4i(location, v1, v2, v3, v4);
	}

	void Shader::SetUniform4i(std::string uname, glm::ivec4 v) {
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

		glUniform4i(location, v.x, v.y, v.z, v.w);
	}

	void Shader::SetUniform1ui(std::string uname, uint32_t v) {
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

		glUniform1ui(location, v);
	}

	void Shader::SetUniform2ui(std::string uname, uint32_t v1, uint32_t v2) {
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

		glUniform2ui(location, v1, v2);
	}

	void Shader::SetUniform2ui(std::string uname, glm::uvec2 v) {
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

		glUniform2ui(location, v.x, v.y);
	}

	void Shader::SetUniform3ui(std::string uname, uint32_t v1, uint32_t v2, uint32_t v3) {
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

		glUniform3ui(location, v1, v2, v3);
	}

	void Shader::SetUniform3ui(std::string uname, glm::uvec3 v) {
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

		glUniform3ui(location, v.x, v.y, v.z);
	}

	void Shader::SetUniform4ui(std::string uname, uint32_t v1, uint32_t v2, uint32_t v3, uint32_t v4) {
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

		glUniform4ui(location, v1, v2, v3, v4);
	}

	void Shader::SetUniform4ui(std::string uname, glm::uvec4 v) {
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

		glUniform4ui(location, v.x, v.y, v.z, v.w);
	}

	void Shader::SetUniformArray1f(std::string uname, int32_t count, const float* array) {
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

		glUniform1fv(location, count, array);
	}

	void Shader::SetUniformArray2f(std::string uname, int32_t count, const float* array) {
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

		glUniform2fv(location, count, array);
	}

	void Shader::SetUniformArray2f(std::string uname, int32_t count, const glm::vec2* array) {
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

		glUniform1fv(location, count, reinterpret_cast<const float*>(array));
	}

	void Shader::SetUniformArray3f(std::string uname, int32_t count, const float* array) {
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

		glUniform3fv(location, count, array);
	}

	void Shader::SetUniformArray3f(std::string uname, int32_t count, const glm::vec3* array) {
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

		glUniform3fv(location, count, reinterpret_cast<const float*>(array));
	}

	void Shader::SetUniformArray4f(std::string uname, int32_t count, const float* array) {
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

		glUniform1fv(location, count, array);
	}

	void Shader::SetUniformArray4f(std::string uname, int32_t count, const glm::vec4* array) {
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

		glUniform4fv(location, count, reinterpret_cast<const float*>(array));
	}

	void Shader::SetUniformArray1i(std::string uname, int32_t count, const int32_t* array){
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

		glUniform1iv(location, count, array);
	}

	void Shader::SetUniformArray2i(std::string uname, int32_t count, const int32_t* array) {
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

		glUniform2iv(location, count, array);
	}

	void Shader::SetUniformArray2i(std::string uname, int32_t count, const glm::ivec2* array) {
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

		glUniform2iv(location, count, reinterpret_cast<const int32_t*> (array));
	}

	void Shader::SetUniformArray3i(std::string uname, int32_t count, const int32_t* array){
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

		glUniform3iv(location, count, array);
	}

	void Shader::SetUniformArray3i(std::string uname, int32_t count, const glm::ivec3* array) {
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

		glUniform3iv(location, count, reinterpret_cast<const int32_t*> (array));
	}

	void Shader::SetUniformArray4i(std::string uname, int32_t count, const int32_t* array) {
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

		glUniform4iv(location, count, array);
	}

	void Shader::SetUniformArray4i(std::string uname, int32_t count, const glm::ivec4* array) {
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

		glUniform4iv(location, count, reinterpret_cast<const int32_t*> (array));
	}

	void Shader::SetUniformArray1ui(std::string uname, int32_t count, const uint32_t* array) {
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

		glUniform1uiv(location, count, array);
	}

	void Shader::SetUniformArray2ui(std::string uname, int32_t count, const uint32_t* array) {
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

		glUniform2uiv(location, count, array);
	}

	void Shader::SetUniformArray2ui(std::string uname, int32_t count, const glm::uvec2* array) {
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

		glUniform2uiv(location, count, reinterpret_cast<const uint32_t*> (array));
	}

	void Shader::SetUniformArray3ui(std::string uname, int32_t count, const uint32_t* array) {
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

		glUniform3uiv(location, count, array);
	}

	void Shader::SetUniformArray3ui(std::string uname, int32_t count, const glm::uvec3* array) {
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

		glUniform3uiv(location, count, reinterpret_cast<const uint32_t*> (array));
	}

	void Shader::SetUniformArray4ui(std::string uname, int32_t count, const uint32_t* array) {
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

		glUniform4uiv(location, count, array);
	}

	void Shader::SetUniformArray4ui(std::string uname, int32_t count, const glm::uvec4* array) {
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

		glUniform4uiv(location, count, reinterpret_cast<const uint32_t*> (array));
	}

	void Shader::SetUniformMatrix2x2(std::string uname, int32_t count, bool transpose, const float* array) {
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

		glUniformMatrix2fv(location, count, transpose, array);
	}

	void Shader::SetUniformMatrix2x2(std::string uname, int32_t count, bool transpose, const glm::mat2* array) {
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

		glUniformMatrix2fv(location, count, transpose, reinterpret_cast<const float*> (array));
	}

	void Shader::SetUniformMatrix3x3(std::string uname, int32_t count, bool transpose, const float* array) {
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

		glUniformMatrix3fv(location, count, transpose, array);
	}

	void Shader::SetUniformMatrix3x3(std::string uname, int32_t count, bool transpose, const glm::mat3* array) {
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

		glUniformMatrix3fv(location, count, transpose, reinterpret_cast<const float*> (array));
	}

	void Shader::SetUniformMatrix4x4(std::string uname, int32_t count, bool transpose, const float* array) {
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

		glUniformMatrix4fv(location, count, transpose, array);
	}

	void Shader::SetUniformMatrix4x4(std::string uname, int32_t count, bool transpose, const glm::mat4* array) {
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

		glUniformMatrix4fv(location, count, transpose, reinterpret_cast<const float*> (array));
	}

	bool Shader::InShaderTypeList(ShaderType type) {
		for (int i = 0; i < shaderTypes.size(); i++)
			if (type == shaderTypes[i])
				return true;

		return false;
	}
}