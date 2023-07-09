#pragma once

#ifdef GRAPHICS_API_OPENGL
#include "Graphics/OpenGL/OpenGLShader.h"
#elif GRAPHICS_API_DIRECTX
//TODO Alperen
#endif 

namespace Engine {
	class Shader {
	private:
#ifdef GRAPHICS_API_OPENGL
		OpenGLShader shader;
#elif GRAPHICS_API_DIRECTX
		//TODO Alperen
#endif 
	public:
		Shader(const std::string filePath) 
#ifdef GRAPHICS_API_OPENGL
			: shader(filePath)
#elif GRAPHICS_API_DIRECTX
			//TODO Alperen
#endif 
		{}
		~Shader() {}

		void bind() {
#ifdef GRAPHICS_API_OPENGL
			shader.bind();
#elif GRAPHICS_API_DIRECTX
			//TODO Alperen
#endif 
		}

		void unbind() {
#ifdef GRAPHICS_API_OPENGL
			shader.unbind();
#elif GRAPHICS_API_DIRECTX
			//TODO Alperen
#endif 
		}

		void SetUniform1f(std::string uname, float v) {
#ifdef GRAPHICS_API_OPENGL
			shader.SetUniform1f(uname, v);
#elif GRAPHICS_API_DIRECTX
			//TODO Alperen
#endif 
		}

		void SetUniform2f(std::string uname, float v1, float v2) {
#ifdef GRAPHICS_API_OPENGL
			shader.SetUniform2f(uname, v1, v2);
#elif GRAPHICS_API_DIRECTX
			//TODO Alperen
#endif 
		}

		void SetUniform2f(std::string uname, glm::vec2 v) {
#ifdef GRAPHICS_API_OPENGL
			shader.SetUniform2f(uname, v.x, v.y);
#elif GRAPHICS_API_DIRECTX
			//TODO Alperen
#endif 
		}

		void SetUniform3f(std::string uname, float v1, float v2, float v3) {
#ifdef GRAPHICS_API_OPENGL
			shader.SetUniform3f(uname, v1, v2, v3);
#elif GRAPHICS_API_DIRECTX
			//TODO Alperen
#endif 
		}

		void SetUniform3f(std::string uname, glm::vec3 v) {
#ifdef GRAPHICS_API_OPENGL
			shader.SetUniform3f(uname, v.x, v.y, v.z);
#elif GRAPHICS_API_DIRECTX
			//TODO Alperen
#endif 
		}

		void SetUniform4f(std::string uname, float v1, float v2, float v3, float v4) {
#ifdef GRAPHICS_API_OPENGL
			shader.SetUniform4f(uname, v1, v2, v3, v4);
#elif GRAPHICS_API_DIRECTX
			//TODO Alperen
#endif
		}

		void SetUniform4f(std::string uname, glm::vec4 v) {
#ifdef GRAPHICS_API_OPENGL
			shader.SetUniform4f(uname, v.x, v.y, v.z, v.w);
#elif GRAPHICS_API_DIRECTX
			//TODO Alperen
#endif
		}

		void SetUniform1i(std::string uname, int32_t v) {
#ifdef GRAPHICS_API_OPENGL
			shader.SetUniform1i(uname, v);
#elif GRAPHICS_API_DIRECTX
			//TODO Alperen
#endif 
		}

		void SetUniform2i(std::string uname, int32_t v1, int32_t v2) {
#ifdef GRAPHICS_API_OPENGL
			shader.SetUniform2i(uname, v1, v2);
#elif GRAPHICS_API_DIRECTX
			//TODO Alperen
#endif
		}

		void SetUniform2i(std::string uname, glm::ivec2 v) {
#ifdef GRAPHICS_API_OPENGL
			shader.SetUniform2i(uname, v.x, v.y);
#elif GRAPHICS_API_DIRECTX
			//TODO Alperen
#endif
		}

		void SetUniform3i(std::string uname, int32_t v1, int32_t v2, int32_t v3) {
#ifdef GRAPHICS_API_OPENGL
			shader.SetUniform3i(uname, v1, v2, v3);
#elif GRAPHICS_API_DIRECTX
			//TODO Alperen
#endif
		}

		void SetUniform3i(std::string uname, glm::ivec3 v) {
#ifdef GRAPHICS_API_OPENGL
			shader.SetUniform3i(uname, v.x, v.y, v.z);
#elif GRAPHICS_API_DIRECTX
			//TODO Alperen
#endif
		}

		void SetUniform4i(std::string uname, int32_t v1, int32_t v2, int32_t v3, int32_t v4) {
#ifdef GRAPHICS_API_OPENGL
			shader.SetUniform4i(uname, v1, v2, v3, v4);
#elif GRAPHICS_API_DIRECTX
			//TODO Alperen
#endif
		}

		void SetUniform4i(std::string uname, glm::ivec4 v) {
#ifdef GRAPHICS_API_OPENGL
			shader.SetUniform4i(uname, v.x, v.y, v.z, v.w);
#elif GRAPHICS_API_DIRECTX
			//TODO Alperen
#endif
		}

		void SetUniform1ui(std::string uname, uint32_t v) {
#ifdef GRAPHICS_API_OPENGL
			shader.SetUniform1ui(uname, v);
#elif GRAPHICS_API_DIRECTX
			//TODO Alperen
#endif 
		}

		void SetUniform2ui(std::string uname, uint32_t v1, uint32_t v2) {
#ifdef GRAPHICS_API_OPENGL
			shader.SetUniform2ui(uname, v1, v2);
#elif GRAPHICS_API_DIRECTX
			//TODO Alperen
#endif 
		}

		void SetUniform2ui(std::string uname, glm::uvec2 v) {
#ifdef GRAPHICS_API_OPENGL
			shader.SetUniform2ui(uname, v.x, v.y);
#elif GRAPHICS_API_DIRECTX
			//TODO Alperen
#endif 
		}

		void SetUniform3ui(std::string uname, uint32_t v1, uint32_t v2, uint32_t v3) {
#ifdef GRAPHICS_API_OPENGL
			shader.SetUniform3ui(uname, v1, v2, v3);
#elif GRAPHICS_API_DIRECTX
			//TODO Alperen
#endif 
		}

		void SetUniform3ui(std::string uname, glm::uvec3 v) {
#ifdef GRAPHICS_API_OPENGL
			shader.SetUniform3ui(uname, v.x, v.y, v.z);
#elif GRAPHICS_API_DIRECTX
			//TODO Alperen
#endif 
		}

		void SetUniform4ui(std::string uname, uint32_t v1, uint32_t v2, uint32_t v3, uint32_t v4) {
#ifdef GRAPHICS_API_OPENGL
			shader.SetUniform4ui(uname, v1, v2, v3, v4);
#elif GRAPHICS_API_DIRECTX
			//TODO Alperen
#endif 
		}

		void SetUniform4ui(std::string uname, glm::uvec4 v) {
#ifdef GRAPHICS_API_OPENGL
			shader.SetUniform4ui(uname, v.x, v.y, v.z, v.w);
#elif GRAPHICS_API_DIRECTX
			//TODO Alperen
#endif 
		}

		void SetUniformArray1f(std::string uname, int32_t count, const float* array) {
#ifdef GRAPHICS_API_OPENGL
			shader.SetUniformArray1f(uname, count, array);
#elif GRAPHICS_API_DIRECTX
			//TODO Alperen
#endif 
		}

		void SetUniformArray2f(std::string uname, int32_t count, const float* array) {
#ifdef GRAPHICS_API_OPENGL
			shader.SetUniformArray2f(uname, count, array);
#elif GRAPHICS_API_DIRECTX
			//TODO Alperen
#endif 
		}

		void SetUniformArray2f(std::string uname, int32_t count, const glm::vec2* array) {
#ifdef GRAPHICS_API_OPENGL
			shader.SetUniformArray2f(uname, count, array);
#elif GRAPHICS_API_DIRECTX
			//TODO Alperen
#endif 
		}

		void SetUniformArray3f(std::string uname, int32_t count, const float* array) {
#ifdef GRAPHICS_API_OPENGL
			shader.SetUniformArray3f(uname, count, array);
#elif GRAPHICS_API_DIRECTX
			//TODO Alperen
#endif 
		}

		void SetUniformArray3f(std::string uname, int32_t count, const glm::vec3* array) {
#ifdef GRAPHICS_API_OPENGL
			shader.SetUniformArray3f(uname, count, array);
#elif GRAPHICS_API_DIRECTX
			//TODO Alperen
#endif 
		}

		void SetUniformArray4f(std::string uname, int32_t count, const float* array) {
#ifdef GRAPHICS_API_OPENGL
			shader.SetUniformArray4f(uname, count, array);
#elif GRAPHICS_API_DIRECTX
			//TODO Alperen
#endif 
		}

		void SetUniformArray4f(std::string uname, int32_t count, const glm::vec4* array) {
#ifdef GRAPHICS_API_OPENGL
			shader.SetUniformArray4f(uname, count, array);
#elif GRAPHICS_API_DIRECTX
			//TODO Alperen
#endif 
		}

		void SetUniformArray1i(std::string uname, int32_t count, const int32_t* array) {
#ifdef GRAPHICS_API_OPENGL
			shader.SetUniformArray1i(uname, count, array);
#elif GRAPHICS_API_DIRECTX
			//TODO Alperen
#endif 
		}

		void SetUniformArray2i(std::string uname, int32_t count, const int32_t* array) {
#ifdef GRAPHICS_API_OPENGL
			shader.SetUniformArray2i(uname, count, array);
#elif GRAPHICS_API_DIRECTX
			//TODO Alperen
#endif 
		}

		void SetUniformArray2i(std::string uname, int32_t count, const glm::ivec2* array) {
#ifdef GRAPHICS_API_OPENGL
			shader.SetUniformArray2i(uname, count, array);
#elif GRAPHICS_API_DIRECTX
			//TODO Alperen
#endif 
		}

		void SetUniformArray3i(std::string uname, int32_t count, const int32_t* array) {
#ifdef GRAPHICS_API_OPENGL
			shader.SetUniformArray3i(uname, count, array);
#elif GRAPHICS_API_DIRECTX
			//TODO Alperen
#endif 
		}

		void SetUniformArray3i(std::string uname, int32_t count, const glm::ivec3* array) {
#ifdef GRAPHICS_API_OPENGL
			shader.SetUniformArray3i(uname, count, array);
#elif GRAPHICS_API_DIRECTX
			//TODO Alperen
#endif 
		}

		void SetUniformArray4i(std::string uname, int32_t count, const int32_t* array) {
#ifdef GRAPHICS_API_OPENGL
			shader.SetUniformArray4i(uname, count, array);
#elif GRAPHICS_API_DIRECTX
			//TODO Alperen
#endif 
		}

		void SetUniformArray4i(std::string uname, int32_t count, const glm::ivec4* array) {
#ifdef GRAPHICS_API_OPENGL
			shader.SetUniformArray4i(uname, count, array);
#elif GRAPHICS_API_DIRECTX
			//TODO Alperen
#endif 
		}

		void SetUniformArray1ui(std::string uname, int32_t count, const uint32_t* array) {
#ifdef GRAPHICS_API_OPENGL
			shader.SetUniformArray1ui(uname, count, array);
#elif GRAPHICS_API_DIRECTX
			//TODO Alperen
#endif 
		}

		void SetUniformArray2ui(std::string uname, int32_t count, const uint32_t* array) {
#ifdef GRAPHICS_API_OPENGL
			shader.SetUniformArray2ui(uname, count, array);
#elif GRAPHICS_API_DIRECTX
			//TODO Alperen
#endif 
		}

		void SetUniformArray2ui(std::string uname, int32_t count, const glm::uvec2* array) {
#ifdef GRAPHICS_API_OPENGL
			shader.SetUniformArray2ui(uname, count, array);
#elif GRAPHICS_API_DIRECTX
			//TODO Alperen
#endif 
		}

		void SetUniformArray3ui(std::string uname, int32_t count, const uint32_t* array) {
#ifdef GRAPHICS_API_OPENGL
			shader.SetUniformArray3ui(uname, count, array);
#elif GRAPHICS_API_DIRECTX
			//TODO Alperen
#endif 
		}

		void SetUniformArray3ui(std::string uname, int32_t count, const glm::uvec3* array) {
#ifdef GRAPHICS_API_OPENGL
			shader.SetUniformArray3ui(uname, count, array);
#elif GRAPHICS_API_DIRECTX
			//TODO Alperen
#endif 
		}

		void SetUniformArray4ui(std::string uname, int32_t count, const uint32_t* array) {
#ifdef GRAPHICS_API_OPENGL
			shader.SetUniformArray4ui(uname, count, array);
#elif GRAPHICS_API_DIRECTX
			//TODO Alperen
#endif 
		}

		void SetUniformArray4ui(std::string uname, int32_t count, const glm::uvec4* array) {
#ifdef GRAPHICS_API_OPENGL
			shader.SetUniformArray4ui(uname, count, array);
#elif GRAPHICS_API_DIRECTX
			//TODO Alperen
#endif 
		}

		void SetUniformMatrix2x2(std::string uname, int32_t count, bool transpose, const float* array) {
#ifdef GRAPHICS_API_OPENGL
			shader.SetUniformMatrix2x2(uname, count, transpose,array);
#elif GRAPHICS_API_DIRECTX
			//TODO Alperen
#endif 
		}

		void SetUniformMatrix2x2(std::string uname, int32_t count, bool transpose, const glm::mat2* array) {
#ifdef GRAPHICS_API_OPENGL
			shader.SetUniformMatrix2x2(uname, count, transpose, array);
#elif GRAPHICS_API_DIRECTX
			//TODO Alperen
#endif
		}

		void SetUniformMatrix3x3(std::string uname, int32_t count, bool transpose, const float* array) {
#ifdef GRAPHICS_API_OPENGL
			shader.SetUniformMatrix3x3(uname, count, transpose, array);
#elif GRAPHICS_API_DIRECTX
			//TODO Alperen
#endif
		}

		void SetUniformMatrix3x3(std::string uname, int32_t count, bool transpose, const glm::mat3* array) {
#ifdef GRAPHICS_API_OPENGL
			shader.SetUniformMatrix3x3(uname, count, transpose, array);
#elif GRAPHICS_API_DIRECTX
			//TODO Alperen
#endif
		}

		void SetUniformMatrix4x4(std::string uname, int32_t count, bool transpose, const float* array) {
#ifdef GRAPHICS_API_OPENGL
			shader.SetUniformMatrix4x4(uname, count, transpose, array);
#elif GRAPHICS_API_DIRECTX
			//TODO Alperen
#endif
		}

		void SetUniformMatrix4x4(std::string uname, int32_t count, bool transpose, const glm::mat4* array) {
#ifdef GRAPHICS_API_OPENGL
			shader.SetUniformMatrix4x4(uname, count, transpose, array);
#elif GRAPHICS_API_DIRECTX
			//TODO Alperen
#endif
		}

	};
}