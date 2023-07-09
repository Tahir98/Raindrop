#pragma once

#ifdef GRAPHICS_API_OPENGL
#include "Graphics/OpenGL/OpenGLTexture.h"
#elif GRAPHICS_API_DIRECTX
//TODO Alperen
#endif

namespace Engine {
	class Texture {
#ifdef GRAPHICS_API_OPENGL
		OpenGLTexture texture;
#elif GRAPHICS_API_DIRECTX
		//TODO Alperen
#endif
	public:
		Texture(std::string filePath) 
#ifdef GRAPHICS_API_OPENGL
			: texture(filePath)
#elif GRAPHICS_API_DIRECTX
			//TODO Alperen
#endif
		{}
		Texture(int32_t width, int32_t height, int32_t depth, const float* pixels)
#ifdef GRAPHICS_API_OPENGL
			: texture(width, height, depth, pixels)
#elif GRAPHICS_API_DIRECTX
			//TODO Alperen
#endif
		{ }

		~Texture() {}

		void bind() {
#ifdef GRAPHICS_API_OPENGL
			texture.bind();
#elif GRAPHICS_API_DIRECTX
			//TODO Alperen
#endif
		}
		void unbind() {
#ifdef GRAPHICS_API_OPENGL
			texture.unbind();
#elif GRAPHICS_API_DIRECTX
			//TODO Alperen
#endif
		}

		void SetActiveTextureSlot(uint32_t slot) {
#ifdef GRAPHICS_API_OPENGL
			texture.SetActiveTextureSlot(slot);
#elif GRAPHICS_API_DIRECTX
			//TODO Alperen
#endif
		}

		int32_t getDimension() {
#ifdef GRAPHICS_API_OPENGL
			return texture.getDimension();
#elif GRAPHICS_API_DIRECTX
			//TODO Alperen
#endif
			return 0;
		}

		int32_t getWidth() {
#ifdef GRAPHICS_API_OPENGL
			return texture.getWidth();
#elif GRAPHICS_API_DIRECTX
			//TODO Alperen
#endif
			return 0;
		}

		int32_t getHeight() {
#ifdef GRAPHICS_API_OPENGL
			return texture.getHeight();
#elif GRAPHICS_API_DIRECTX
			//TODO Alperen
#endif
			return 0;
		}

		int32_t getDepth() {
#ifdef GRAPHICS_API_OPENGL
			texture.getDepth();
#elif GRAPHICS_API_DIRECTX
			//TODO Alperen
#endif
			return 0;
		}

		int32_t getChannels() {
#ifdef GRAPHICS_API_OPENGL
			return texture.getChannels();
#elif GRAPHICS_API_DIRECTX
			//TODO Alperen
#endif
			return 0;
		}

	};
}