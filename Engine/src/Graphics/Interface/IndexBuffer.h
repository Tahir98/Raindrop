#pragma once

#ifdef GRAPHICS_API_OPENGL
#include "Graphics/OpenGL/OpenGLIndexBuffer.h"
#elif GRAPHICS_API_DIRECTX
//TODO Alperen
#endif 

namespace Engine {
	class IndexBuffer {
	public:
		enum DrawType {
			STATIC_DRAW, DYNAMIC_DRAW
		};

	private:
#ifdef GRAPHICS_API_OPENGL
		OpenGLIndexBuffer ib;
#elif GRAPHICS_API_DIRECTX
		//TODO Alperen
#endif 
	public:
		IndexBuffer(const uint32_t* indices, uint32_t size, GLenum usage) 
#ifdef GRAPHICS_API_OPENGL
			: ib(indices, size, usage)
#elif GRAPHICS_API_DIRECTX
			//TODO Alperen
#endif 
		{

		}

		~IndexBuffer() {}

		void bind() {
#ifdef GRAPHICS_API_OPENGL
			ib.bind();
#elif GRAPHICS_API_DIRECTX
			//TODO Alperen
#endif 
		}
		void unbind() {
#ifdef GRAPHICS_API_OPENGL
			ib.unbind();
#elif GRAPHICS_API_DIRECTX
			//TODO Alperen
#endif 
		}

		void SetData(const uint32_t* indices, uint32_t offset, uint32_t size) {
#ifdef GRAPHICS_API_OPENGL
			ib.SetData(indices, offset, size);
#elif GRAPHICS_API_DIRECTX
			//TODO Alperen
#endif 
		}

		uint32_t GetBufferSize() {
#ifdef GRAPHICS_API_OPENGL
			return ib.GetBufferSize();
#elif GRAPHICS_API_DIRECTX
			//TODO Alperen
#endif 
			return 0;
		}
	};
}