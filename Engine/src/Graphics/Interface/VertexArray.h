#pragma once

#include "VertexBuffer.h"

#ifdef GRAPHICS_API_OPENGL
#include "Graphics/OpenGL/OpenGLVertexArray.h"
#elif GRAPHICS_API_DIRECTX
//TODO Alperen
#endif 

namespace Engine {
	class VertexArray {
	public:
		enum DataType {
			FLOAT, DOUBLE, INT32, UINT32, INT16, UINT16, INT8, UINT8
		};
	private:
#ifdef GRAPHICS_API_OPENGL
		OpenGLVertexArray va;
#elif GRAPHICS_API_DIRECTX
		//TODO Alperen
#endif 

	public:
		VertexArray() {}
		~VertexArray() {}

		void bind() {
#ifdef GRAPHICS_API_OPENGL
			va.bind();
#elif GRAPHICS_API_DIRECTX
			//TODO Alperen
#endif 
		}

		void unbind() {
#ifdef GRAPHICS_API_OPENGL
			va.unbind();
#elif GRAPHICS_API_DIRECTX
			//TODO Alperen
#endif 
		}

		void PushElement(VertexBuffer* vb, int count, DataType type, bool normalized = false) {
#ifdef GRAPHICS_API_OPENGL
			va.PushElement(&(vb->vb), count, (OpenGLVertexArray::DataType)type, normalized);
#elif GRAPHICS_API_DIRECTX
			//TODO Alperen
#endif 
		}
	};
}