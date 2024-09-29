#pragma once
#include "Log.h"
#include "glad/glad.h"
#include <glm/glm.hpp>
#include <string>
#include <fstream>
#include <unordered_map>

namespace Engine {
	class ShaderVariant {
	public:
		uint32_t id = -1;
		std::unordered_map<std::string, int> uniforms;
	};

	class BaseShader {
	public:
		enum ShaderType {
			None = -1, Vertex = 0, Fragment = 1, Geometry = 2, Tessellation = 3, Compute = 4
		};

		bool logUniformErrors = false;

	protected:
		uint32_t currentVariantIndex = 0;
		
		ShaderVariant* currentVariant = nullptr;
		std::vector<ShaderVariant*> shaderVariants;

		std::vector<ShaderType> shaderTypes;

		void SetCurrentVariantIndex(uint32_t index);
	public:
		BaseShader();
		~BaseShader();

		void SetUniform1f(std::string uname, float v);
		void SetUniform2f(std::string uname, float v1, float v2);
		void SetUniform2f(std::string uname, glm::vec2 v);
		void SetUniform3f(std::string uname, float v1, float v2, float v3);
		void SetUniform3f(std::string uname, glm::vec3 v);
		void SetUniform4f(std::string uname, float v1, float v2, float v3, float v4);
		void SetUniform4f(std::string uname, glm::vec4 v);

		void SetUniform1i(std::string uname, int32_t v);
		void SetUniform2i(std::string uname, int32_t v1, int32_t v2);
		void SetUniform2i(std::string uname, glm::ivec2 v);
		void SetUniform3i(std::string uname, int32_t v1, int32_t v2, int32_t v3);
		void SetUniform3i(std::string uname, glm::ivec3 v);
		void SetUniform4i(std::string uname, int32_t v1, int32_t v2, int32_t v3, int32_t v4);
		void SetUniform4i(std::string uname, glm::ivec4 v);

		void SetUniform1ui(std::string uname, uint32_t v);
		void SetUniform2ui(std::string uname, uint32_t v1, uint32_t v2);
		void SetUniform2ui(std::string uname, glm::uvec2 v);
		void SetUniform3ui(std::string uname, uint32_t v1, uint32_t v2, uint32_t v3);
		void SetUniform3ui(std::string uname, glm::uvec3 v);
		void SetUniform4ui(std::string uname, uint32_t v1, uint32_t v2, uint32_t v3, uint32_t v4);
		void SetUniform4ui(std::string uname, glm::uvec4 v);

		void SetUniformArray1f(std::string uname, int32_t count, const float* array);
		void SetUniformArray2f(std::string uname, int32_t count, const float* array);
		void SetUniformArray2f(std::string uname, int32_t count, const glm::vec2* array);
		void SetUniformArray3f(std::string uname, int32_t count, const float* array);
		void SetUniformArray3f(std::string uname, int32_t count, const glm::vec3* array);
		void SetUniformArray4f(std::string uname, int32_t count, const float* array);
		void SetUniformArray4f(std::string uname, int32_t count, const glm::vec4* array);

		void SetUniformArray1i(std::string uname, int32_t count, const int32_t* array);
		void SetUniformArray2i(std::string uname, int32_t count, const int32_t* array);
		void SetUniformArray2i(std::string uname, int32_t count, const glm::ivec2* array);
		void SetUniformArray3i(std::string uname, int32_t count, const int32_t* array);
		void SetUniformArray3i(std::string uname, int32_t count, const glm::ivec3* array);
		void SetUniformArray4i(std::string uname, int32_t count, const int32_t* array);
		void SetUniformArray4i(std::string uname, int32_t count, const glm::ivec4* array);

		void SetUniformArray1ui(std::string uname, int32_t count, const uint32_t* array);
		void SetUniformArray2ui(std::string uname, int32_t count, const uint32_t* array);
		void SetUniformArray2ui(std::string uname, int32_t count, const glm::uvec2* array);
		void SetUniformArray3ui(std::string uname, int32_t count, const uint32_t* array);
		void SetUniformArray3ui(std::string uname, int32_t count, const glm::uvec3* array);
		void SetUniformArray4ui(std::string uname, int32_t count, const uint32_t* array);
		void SetUniformArray4ui(std::string uname, int32_t count, const glm::uvec4* array);

		void SetUniformMatrix2x2(std::string uname, int32_t count, bool transpose, const float* array);
		void SetUniformMatrix2x2(std::string uname, int32_t count, bool transpose, const glm::mat2* array);
		void SetUniformMatrix3x3(std::string uname, int32_t count, bool transpose, const float* array);
		void SetUniformMatrix3x3(std::string uname, int32_t count, bool transpose, const glm::mat3* array);
		void SetUniformMatrix4x4(std::string uname, int32_t count, bool transpose, const float* array);
		void SetUniformMatrix4x4(std::string uname, int32_t count, bool transpose, const glm::mat4* array);

	protected:
		bool InShaderTypeList(ShaderType type);
	};

}