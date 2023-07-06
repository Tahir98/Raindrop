#pragma once 
#include "Log.h"

namespace Engine {

	class Texture {
	private:
		uint32_t id;

		int32_t width, height, depth, channels;
		int32_t dimension;
	public:
		enum TextureFormat {

		};

		enum TextureFilter {
			POINT, BILINEAR, TRILINEAR 
		};

		enum TextureWrapper {
			CLAMP, MIRROR
		};

		Texture(std::string filePath);
		Texture(int32_t width, int32_t height, int32_t depth, const float* pixels);
		~Texture();

		void bind();
		void unbind();
		
		void SetActiveTextureSlot(uint32_t slot);

		int32_t getDimension();
		int32_t getWidth();
		int32_t getHeight();
		int32_t getDepth();
		int32_t getChannels();

	};

}