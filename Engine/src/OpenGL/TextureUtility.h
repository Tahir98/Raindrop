#pragma once

namespace Engine {
	enum TextureFormat {
		R8_UNORM = 0,
		RG8_UNORM = 1,
		RGB8_UNORM = 2,
		RGBA8_UNORM = 3,

		R16_UNORM = 4,
		RG16_UNORM = 5,
		RGB16_UNORM = 6,
		RGBA16_UNORM = 7,

		R8_SNORM = 8,
		RG8_SNORM = 9,
		RGB8_SNORM = 10,
		RGBA8_SNORM = 11,

		R16_SNORM = 12,
		RG16_SNORM = 13,
		RGB16_SNORM = 14,
		RGBA16_SNORM = 15,

		R16_Float = 16,
		RG16_Float = 17,
		RGB16_Float = 18,
		RGBA16_Float = 19,

		R32_Float = 20,
		RG32_Float = 21,
		RGB32_Float = 22,
		RGBA32_Float = 23,

		R8_INT = 24,
		RG8_INT = 25,
		RGB8_INT = 26,
		RGBA8_INT = 27,

		R16_INT = 28,
		RG16_INT = 29,
		RGB16_INT = 30,
		RGBA16_INT = 31,

		R32_INT = 32,
		RG32_INT = 33,
		RGB32_INT = 34,
		RGBA32_INT = 35,

		R8_UINT = 36,
		RG8_UINT = 37,
		RGB8_UINT = 38,
		RGBA8_UINT = 39,

		R16_UINT = 40,
		RG16_UINT = 41,
		RGB16_UINT = 42,
		RGBA16_UINT = 43,

		R32_UINT = 44,
		RG32_UINT = 45,
		RGB32_UINT = 46,
		RGBA32_UINT = 47,

		//TODO Compressed, depth and stencil formats can be added in the future
	};

	enum TextureFilter {
		POINT, BILINEAR, TRILINEAR
	};

	enum TextureWrapper {
		CLAMP, MIRROR, REPEAT
	};

	class TextureUtility {
	public:
		static int32_t GetOpenGLInternalFormat(TextureFormat format) {
			switch (format)
			{
			case Engine::R8_UNORM:
				return GL_R8;
			case Engine::RG8_UNORM:
				return GL_RG8;
			case Engine::RGB8_UNORM:
				return GL_RGB8;
			case Engine::RGBA8_UNORM:
				return GL_RGBA8;
			case Engine::R16_UNORM:
				return GL_R16;
			case Engine::RG16_UNORM:
				return GL_RG16;
			case Engine::RGB16_UNORM:
				return GL_RGB16;
			case Engine::RGBA16_UNORM:
				return GL_RGBA16;
			case Engine::R8_SNORM:
				return GL_R8_SNORM;
			case Engine::RG8_SNORM:
				return GL_RG8_SNORM;
			case Engine::RGB8_SNORM:
				GL_RGB8_SNORM;
			case Engine::RGBA8_SNORM:
				GL_RGBA8_SNORM;
			case Engine::R16_SNORM:
				return GL_R16_SNORM;
			case Engine::RG16_SNORM:
				return GL_RG16_SNORM;;
			case Engine::RGB16_SNORM:
				return GL_RGB16_SNORM;
			case Engine::RGBA16_SNORM:
				return GL_RGBA16_SNORM;
			case Engine::R16_Float:
				return GL_R16F;
			case Engine::RG16_Float:
				return GL_RG16F;
			case Engine::RGB16_Float:
				return GL_RGB16F;
			case Engine::RGBA16_Float:
				return GL_RGBA16F;
			case Engine::R32_Float:
				return GL_R32F;
			case Engine::RG32_Float:
				return GL_RG32F;
			case Engine::RGB32_Float:
				return GL_RGB32F;
			case Engine::RGBA32_Float:
				return GL_RGBA32F;
			case Engine::R8_INT:
				return GL_R8I;
			case Engine::RG8_INT:
				return GL_RG8I;
			case Engine::RGB8_INT:
				return GL_RGB8I;
			case Engine::RGBA8_INT:
				return GL_RGBA8I;
			case Engine::R16_INT:
				return GL_R16I;
			case Engine::RG16_INT:
				return GL_RG16I;
			case Engine::RGB16_INT:
				return GL_RGB16I;
			case Engine::RGBA16_INT:
				return GL_RGBA16I;
			case Engine::R32_INT:
				return GL_R32I;
			case Engine::RG32_INT:
				return GL_RG32I;
			case Engine::RGB32_INT:
				return GL_RGB32I;
			case Engine::RGBA32_INT:
				return GL_RGBA32I;
			case Engine::R8_UINT:
				return GL_R8UI;
			case Engine::RG8_UINT:
				return GL_RG8UI;
			case Engine::RGB8_UINT:
				return GL_RGB8UI;
			case Engine::RGBA8_UINT:
				return GL_RGBA8UI;
			case Engine::R16_UINT:
				return GL_R16UI;
			case Engine::RG16_UINT:
				return GL_RG16UI;
			case Engine::RGB16_UINT:
				return GL_RGB16UI;
			case Engine::RGBA16_UINT:
				return GL_RGBA16UI;
			case Engine::R32_UINT:
				return GL_R32UI;
			case Engine::RG32_UINT:
				return GL_RG32UI;
			case Engine::RGB32_UINT:
				return GL_RGB32UI;
			case Engine::RGBA32_UINT:
				return GL_RGBA32UI;
			}

			return GL_ZERO;
		}

		static int32_t GetOpenGLBaseFormat(TextureFormat format) {
			switch (format)
			{
			case Engine::R8_UNORM:
			case Engine::R16_UNORM:
			case Engine::R8_SNORM:
			case Engine::R16_SNORM:
			case Engine::R16_Float:
			case Engine::R32_Float:
			case Engine::R8_INT:
			case Engine::R16_INT:
			case Engine::R32_INT:
			case Engine::R8_UINT:
			case Engine::R16_UINT:
			case Engine::R32_UINT:
				return GL_RED;
			case Engine::RG8_UNORM:
			case Engine::RG16_UNORM:
			case Engine::RG8_SNORM:
			case Engine::RG16_SNORM:
			case Engine::RG16_Float:
			case Engine::RG32_Float:
			case Engine::RG8_INT:
			case Engine::RG16_INT:
			case Engine::RG32_INT:
			case Engine::RG8_UINT:
			case Engine::RG16_UINT:
			case Engine::RG32_UINT:
				return GL_RG;
			case Engine::RGB8_UNORM:
			case Engine::RGB16_UNORM:
			case Engine::RGB8_SNORM:
			case Engine::RGB16_SNORM:
			case Engine::RGB16_Float:
			case Engine::RGB32_Float:
			case Engine::RGB8_INT:
			case Engine::RGB16_INT:
			case Engine::RGB32_INT:
			case Engine::RGB8_UINT:
			case Engine::RGB16_UINT:
			case Engine::RGB32_UINT:
				return GL_RGB;
			case Engine::RGBA8_UNORM:
			case Engine::RGBA16_UNORM:
			case Engine::RGBA8_SNORM:
			case Engine::RGBA16_SNORM:
			case Engine::RGBA16_Float:
			case Engine::RGBA32_Float:
			case Engine::RGBA8_INT:
			case Engine::RGBA16_INT:
			case Engine::RGBA32_INT:
			case Engine::RGBA8_UINT:
			case Engine::RGBA16_UINT:
			case Engine::RGBA32_UINT:
				return GL_RGBA;
			}
			
			return GL_RED;
		}

		static int32_t GetTextureFormatStride(TextureFormat format) {
			switch (format)
			{
			case Engine::R8_UNORM:
			case Engine::R8_SNORM:
			case Engine::R8_INT:
			case Engine::R8_UINT:
				return 8;
			case Engine::R16_UNORM:
			case Engine::R16_SNORM:
			case Engine::R16_INT:
			case Engine::R16_UINT:
			case Engine::R16_Float:
				return 16;
			case Engine::R32_INT:
			case Engine::R32_UINT:
			case Engine::R32_Float:
				return 32;

			case Engine::RG8_UNORM:
			case Engine::RG8_SNORM:
			case Engine::RG8_INT:
			case Engine::RG8_UINT:
				return 16;
			case Engine::RG16_UNORM:
			case Engine::RG16_SNORM:
			case Engine::RG16_INT:
			case Engine::RG16_UINT:
			case Engine::RG16_Float:
				return 32;
			case Engine::RG32_INT:
			case Engine::RG32_UINT:
			case Engine::RG32_Float:
				return 64;

			case Engine::RGB8_UNORM:
			case Engine::RGB8_SNORM:
			case Engine::RGB8_INT:
			case Engine::RGB8_UINT:
				return 24;
			case Engine::RGB16_UNORM:
			case Engine::RGB16_SNORM:
			case Engine::RGB16_INT:
			case Engine::RGB16_UINT:
			case Engine::RGB16_Float:
				return 48;
			case Engine::RGB32_INT:
			case Engine::RGB32_UINT:
			case Engine::RGB32_Float:
				return 96;

			case Engine::RGBA8_UNORM:
			case Engine::RGBA8_SNORM:
			case Engine::RGBA8_INT:
			case Engine::RGBA8_UINT:
				return 32;
			case Engine::RGBA16_UNORM:
			case Engine::RGBA16_SNORM:
			case Engine::RGBA16_INT:
			case Engine::RGBA16_UINT:
			case Engine::RGBA16_Float:
				return 64;
			case Engine::RGBA32_INT:
			case Engine::RGBA32_UINT:
			case Engine::RGBA32_Float:
				return 128;
			}
			
			return 0;
		}
		
		static int32_t GetOpenGLPixelDataType(TextureFormat format) {
			switch (format)
			{
			case Engine::R8_UNORM:			
			case Engine::RG8_UNORM:
			case Engine::RGB8_UNORM:
			case Engine::RGBA8_UNORM:
			case Engine::R8_UINT:
			case Engine::RG8_UINT:
			case Engine::RGB8_UINT:
			case Engine::RGBA8_UINT:
				return GL_UNSIGNED_BYTE;

			case Engine::R8_SNORM:
			case Engine::RG8_SNORM:
			case Engine::RGB8_SNORM:
			case Engine::RGBA8_SNORM:
			case Engine::R8_INT:
			case Engine::RG8_INT:
			case Engine::RGB8_INT:
			case Engine::RGBA8_INT:
				return GL_BYTE;

			case Engine::R16_UNORM:
			case Engine::RG16_UNORM:
			case Engine::RGB16_UNORM:
			case Engine::RGBA16_UNORM:
			case Engine::R16_UINT:
			case Engine::RG16_UINT:
			case Engine::RGB16_UINT:
			case Engine::RGBA16_UINT:
				return GL_UNSIGNED_SHORT;

			case Engine::R16_SNORM:
			case Engine::RG16_SNORM:
			case Engine::RGB16_SNORM:
			case Engine::RGBA16_SNORM:
			case Engine::R16_INT:
			case Engine::RG16_INT:
			case Engine::RGB16_INT:
			case Engine::RGBA16_INT:
				return GL_SHORT;

			case Engine::R32_UINT:
			case Engine::RG32_UINT:
			case Engine::RGB32_UINT:
			case Engine::RGBA32_UINT:
				return GL_UNSIGNED_INT;

			case Engine::R32_INT:
			case Engine::RG32_INT:
			case Engine::RGB32_INT:
			case Engine::RGBA32_INT:
				return GL_INT;

			case Engine::R16_Float:
			case Engine::RG16_Float:
			case Engine::RGB16_Float:
			case Engine::RGBA16_Float:
			case Engine::R32_Float:
			case Engine::RG32_Float:
			case Engine::RGB32_Float:
			case Engine::RGBA32_Float:
				return GL_FLOAT;
			default:
				return GL_UNSIGNED_BYTE;
			}
		}

	};
}