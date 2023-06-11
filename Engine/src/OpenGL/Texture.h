#pragma once 
#include "Log.h"

namespace Engine {

	class Texture {
	private:
		uint32_t id;

		int32_t width, height, channels;
		int32_t dimension;
	public:
		Texture(std::string filePath);
		~Texture();

		void bind();
		void unbind();
		
		void SetActiveTextureSlot(uint32_t slot);

		int32_t getWidth();
		int32_t getHeight();
		int32_t getChannels();

	};

}