#include "BaseShader.h"
#include <iostream>

namespace Engine {
	BaseShader::BaseShader() {	
	}

	BaseShader::~BaseShader() {
	}

	void BaseShader::bind() {
		glUseProgram(id);
	}

	void BaseShader::unbind() {
		glUseProgram(0);
	}

	void BaseShader::SetUniform1f(std::string uname, float v) {

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


	void BaseShader::SetUniform2f(std::string uname, float v1, float v2) {

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

	void BaseShader::SetUniform2f(std::string uname, glm::vec2 v) {

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

	void BaseShader::SetUniform3f(std::string uname, float v1, float v2, float v3) {

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

	void BaseShader::SetUniform3f(std::string uname, glm::vec3 v) {

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

	void BaseShader::SetUniform4f(std::string uname, float v1, float v2, float v3, float v4) {

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

	void BaseShader::SetUniform4f(std::string uname, glm::vec4 v) {

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

	void BaseShader::SetUniform1i(std::string uname, int32_t v) {
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

	void BaseShader::SetUniform2i(std::string uname, int32_t v1, int32_t v2) {
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

	void BaseShader::SetUniform2i(std::string uname, glm::ivec2 v) {
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

	void BaseShader::SetUniform3i(std::string uname, int32_t v1, int32_t v2, int32_t v3) {
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

	void BaseShader::SetUniform3i(std::string uname, glm::ivec3 v) {
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

	void BaseShader::SetUniform4i(std::string uname, int32_t v1, int32_t v2, int32_t v3, int32_t v4) {
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

	void BaseShader::SetUniform4i(std::string uname, glm::ivec4 v) {
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

	void BaseShader::SetUniform1ui(std::string uname, uint32_t v) {
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

	void BaseShader::SetUniform2ui(std::string uname, uint32_t v1, uint32_t v2) {
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

	void BaseShader::SetUniform2ui(std::string uname, glm::uvec2 v) {
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

	void BaseShader::SetUniform3ui(std::string uname, uint32_t v1, uint32_t v2, uint32_t v3) {
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

	void BaseShader::SetUniform3ui(std::string uname, glm::uvec3 v) {
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

	void BaseShader::SetUniform4ui(std::string uname, uint32_t v1, uint32_t v2, uint32_t v3, uint32_t v4) {
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

	void BaseShader::SetUniform4ui(std::string uname, glm::uvec4 v) {
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

	void BaseShader::SetUniformArray1f(std::string uname, int32_t count, const float* array) {
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

	void BaseShader::SetUniformArray2f(std::string uname, int32_t count, const float* array) {
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

	void BaseShader::SetUniformArray2f(std::string uname, int32_t count, const glm::vec2* array) {
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

	void BaseShader::SetUniformArray3f(std::string uname, int32_t count, const float* array) {
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

	void BaseShader::SetUniformArray3f(std::string uname, int32_t count, const glm::vec3* array) {
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

	void BaseShader::SetUniformArray4f(std::string uname, int32_t count, const float* array) {
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

	void BaseShader::SetUniformArray4f(std::string uname, int32_t count, const glm::vec4* array) {
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

	void BaseShader::SetUniformArray1i(std::string uname, int32_t count, const int32_t* array) {
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

	void BaseShader::SetUniformArray2i(std::string uname, int32_t count, const int32_t* array) {
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

	void BaseShader::SetUniformArray2i(std::string uname, int32_t count, const glm::ivec2* array) {
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

	void BaseShader::SetUniformArray3i(std::string uname, int32_t count, const int32_t* array) {
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

	void BaseShader::SetUniformArray3i(std::string uname, int32_t count, const glm::ivec3* array) {
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

	void BaseShader::SetUniformArray4i(std::string uname, int32_t count, const int32_t* array) {
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

	void BaseShader::SetUniformArray4i(std::string uname, int32_t count, const glm::ivec4* array) {
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

	void BaseShader::SetUniformArray1ui(std::string uname, int32_t count, const uint32_t* array) {
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

	void BaseShader::SetUniformArray2ui(std::string uname, int32_t count, const uint32_t* array) {
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

	void BaseShader::SetUniformArray2ui(std::string uname, int32_t count, const glm::uvec2* array) {
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

	void BaseShader::SetUniformArray3ui(std::string uname, int32_t count, const uint32_t* array) {
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

	void BaseShader::SetUniformArray3ui(std::string uname, int32_t count, const glm::uvec3* array) {
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

	void BaseShader::SetUniformArray4ui(std::string uname, int32_t count, const uint32_t* array) {
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

	void BaseShader::SetUniformArray4ui(std::string uname, int32_t count, const glm::uvec4* array) {
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

	void BaseShader::SetUniformMatrix2x2(std::string uname, int32_t count, bool transpose, const float* array) {
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

	void BaseShader::SetUniformMatrix2x2(std::string uname, int32_t count, bool transpose, const glm::mat2* array) {
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

	void BaseShader::SetUniformMatrix3x3(std::string uname, int32_t count, bool transpose, const float* array) {
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

	void BaseShader::SetUniformMatrix3x3(std::string uname, int32_t count, bool transpose, const glm::mat3* array) {
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

	void BaseShader::SetUniformMatrix4x4(std::string uname, int32_t count, bool transpose, const float* array) {
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

	void BaseShader::SetUniformMatrix4x4(std::string uname, int32_t count, bool transpose, const glm::mat4* array) {
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

	bool BaseShader::InShaderTypeList(ShaderType type) {
		for (int i = 0; i < shaderTypes.size(); i++)
			if (type == shaderTypes[i])
				return true;

		return false;
	}
}