#pragma once

#ifdef GRAPHICS_API_OPENGL
#include "Graphics/OpenGL/OpenGLVertexBuffer.h"
#elif GRAPHICS_API_DIRECTX
//TODO Alperen
#endif 

namespace Engine {
	class VertexBuffer {
	public:
		enum DrawType {
			STATIC_DRAW, DYNAMIC_DRAW
		};

	private:
	#ifdef GRAPHICS_API_OPENGL
		friend class VertexArray;
		OpenGLVertexBuffer vb;
	#elif GRAPHICS_API_DIRECTX
		//TODO Alperen
	#endif 
	public:
		VertexBuffer(const void* data, uint32_t size, GLenum usage) 
#ifdef GRAPHICS_API_OPENGL
			: vb(data, size, usage)
#elif GRAPHICS_API_DIRECTX
			//TODO Alperen
#endif 
		{

		}

		~VertexBuffer() {

		}

		void bind() {
#ifdef GRAPHICS_API_OPENGL
			vb.bind();
#elif GRAPHICS_API_DIRECTX
			//TODO Alperen
#endif 
		}
		void unbind() {
#ifdef GRAPHICS_API_OPENGL
			vb.unbind();
#elif GRAPHICS_API_DIRECTX
			//TODO Alperen
#endif 
		}

		void SetData(const void* data, uint32_t offset, uint32_t size) {
#ifdef GRAPHICS_API_OPENGL
			vb.SetData(data, offset, size);
#elif GRAPHICS_API_DIRECTX
			//TODO Alperen
#endif 
		}

		uint32_t GetBufferSize() {
#ifdef GRAPHICS_API_OPENGL
			return vb.GetBufferSize();
#elif GRAPHICS_API_DIRECTX
			//TODO Alperen
#endif 
			return 0;
		}
	};
}