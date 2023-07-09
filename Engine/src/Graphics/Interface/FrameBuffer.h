#pragma once

#ifdef GRAPHICS_API_OPENGL
#include "Graphics/OpenGL/OpenGLFrameBuffer.h"
#elif GRAPHICS_API_DIRECTX
//TODO Alperen
#endif 

namespace Engine {
	class FrameBuffer {
	private:
#ifdef GRAPHICS_API_OPENGL
		OpenGLFrameBuffer fb;
#elif GRAPHICS_API_DIRECTX
		//TODO Alperen
#endif 
	public:
		FrameBuffer(const uint32_t width, const uint32_t height) 
#ifdef GRAPHICS_API_OPENGL
			: fb(width, height)
#elif GRAPHICS_API_DIRECTX
			//TODO Alperen
#endif 
		{}
		~FrameBuffer() {}

		void resize(const uint32_t width, const uint32_t height) {
#ifdef GRAPHICS_API_OPENGL
			fb.resize(width, height);
#elif GRAPHICS_API_DIRECTX
			//TODO Alperen
#endif 
		}

		uint32_t getWidth() {
#ifdef GRAPHICS_API_OPENGL
			return fb.getWidth();
#elif GRAPHICS_API_DIRECTX
			//TODO Alperen
#endif 
			return 0;
		}

		uint32_t getHeight() {
#ifdef GRAPHICS_API_OPENGL
			return fb.getHeight();
#elif GRAPHICS_API_DIRECTX
			//TODO Alperen
#endif 
			return 0;
		}

		void clear(glm::vec3 color = glm::vec3(1, 1, 1)) {
#ifdef GRAPHICS_API_OPENGL
			fb.clear(color);
#elif GRAPHICS_API_DIRECTX
			//TODO Alperen
#endif 
		}

		void bind() {
#ifdef GRAPHICS_API_OPENGL
			fb.bind();
#elif GRAPHICS_API_DIRECTX
			//TODO Alperen
#endif 
		}

		void unbind() {
#ifdef GRAPHICS_API_OPENGL
			fb.unbind();
#elif GRAPHICS_API_DIRECTX
			//TODO Alperen
#endif 
		}

		uint32_t& getID() {
#ifdef GRAPHICS_API_OPENGL
			return fb.getID();
#elif GRAPHICS_API_DIRECTX
			//TODO Alperen
#endif 
		}

		uint32_t& getTextureID() {
#ifdef GRAPHICS_API_OPENGL
			return fb.getTextureID();
#elif GRAPHICS_API_DIRECTX
			//TODO Alperen
#endif 
		}

		uint32_t& getRenderbufferID() {
#ifdef GRAPHICS_API_OPENGL
			return fb.getRenderbufferID();
#elif GRAPHICS_API_DIRECTX
			//TODO Alperen
#endif 
		}
	};
}