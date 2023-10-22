#pragma once
#include "Log.h"
#include "glad/glad.h"
#include "TextureUtility.h"

namespace Engine {
	class Texture2D {
	private:
		uint32_t id = 0;

		uint32_t width = 0, height = 0;
		uint32_t bbp = 0; //Bit per pixel

		TextureFormat format;
		TextureFilter filter = TextureFilter::BILINEAR;
		TextureWrapper wrapper = TextureWrapper::CLAMP;

	public:
		//Empty texture creation 
		Texture2D(uint32_t width, uint32_t height, TextureFormat format);
		Texture2D(uint32_t width, uint32_t height, TextureFormat format, TextureFilter filter);
		Texture2D(uint32_t width, uint32_t height, TextureFormat format, TextureFilter filter, TextureWrapper wrapper);

		//Loading data from file
		Texture2D(std::string filePath);
		Texture2D(std::string filePath, TextureFilter filter);
		Texture2D(std::string filePath, TextureFilter filter, TextureWrapper wrapper);
		
		//Custom data loading
		Texture2D(void* data, uint32_t width, uint32_t height, TextureFormat format);
		Texture2D(void* data, uint32_t width, uint32_t height, TextureFormat format, TextureFilter filter);
		Texture2D(void* data, uint32_t width, uint32_t height, TextureFormat format, TextureFilter filter, TextureWrapper wrapper);

		~Texture2D();

		void SetData(void* data, uint32_t size, uint32_t startIndex = 0);
		void SetData(void* data, uint32_t size, uint32_t xoffset = 0, uint32_t yoffset = 0);

		void bind();
		void unbind();
		void setActiveTextureSlot(int slot = 0);

		uint32_t getWidth();
		uint32_t getHeight();

		uint32_t getBBP();

		TextureFormat getTextureFormat();
		TextureFilter getTextureFilter();
		TextureWrapper getWrapMode();

	private:
		void SetTextureFilter(TextureFilter filter);
		void SetTextureWrapMode(TextureWrapper wrapper);
	};


}
