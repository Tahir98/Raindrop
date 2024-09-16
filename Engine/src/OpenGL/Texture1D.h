#pragma once
#include "Log.h"
#include "glad/glad.h"
#include "TextureUtility.h"

namespace Engine {
	class Texture1D {
	private:
		uint32_t id = 0;

		uint32_t width = 0;
		uint32_t bbp = 0; //Bit per pixel

		TextureFormat format;
		TextureFilter filter = TextureFilter::BILINEAR;
		TextureWrapper wrapper = TextureWrapper::CLAMP;

	public:
		//Empty texture creation 
		Texture1D(uint32_t width, TextureFormat format);
		Texture1D(uint32_t width, TextureFormat format, TextureFilter filter);
		Texture1D(uint32_t width, TextureFormat format, TextureFilter filter, TextureWrapper wrapper);

		//Custom data loading
		Texture1D(void* data, uint32_t width, TextureFormat format);
		Texture1D(void* data, uint32_t width, TextureFormat format, TextureFilter filter);
		Texture1D(void* data, uint32_t width, TextureFormat format, TextureFilter filter, TextureWrapper wrapper);

		~Texture1D();

		void SetData(void* data, uint32_t size, uint32_t startIndex = 0);

		void Resize(uint32_t width);

		void bind();
		void unbind();
		void setActiveTextureSlot(int slot = 0);

		uint32_t getWidth();
		uint32_t getBBP();

		TextureFormat getTextureFormat();
		TextureFilter getTextureFilter();
		TextureWrapper getWrapMode();

	private:
		void SetTextureFilter(TextureFilter filter);
		void SetTextureWrapMode(TextureWrapper wrapper);
	};
}
