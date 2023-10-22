#include "Texture2D.h"
#include "stb_image.h"

namespace Engine {

	Texture2D::Texture2D(uint32_t width, uint32_t height, TextureFormat format) : width(width), height(height), format(format){
		glGenTextures(1, &id);
		glBindTexture(GL_TEXTURE_2D, id);

		SetTextureFilter(filter);
		SetTextureWrapMode(wrapper);

		bbp = TextureUtility::GetTextureFormatStride(format);

		glTexImage2D(GL_TEXTURE_2D, 0, TextureUtility::GetOpenGLInternalFormat(format), width, height, 0, 
			TextureUtility::GetOpenGLBaseFormat(format), TextureUtility::GetOpenGLPixelDataType(format), nullptr);

		glBindTexture(GL_TEXTURE_2D, 0);

		ENG_LOG_INFO("2D Texture created, id:{0}, width:{1}, height:{2}, bbp:{3}", id, width, height, bbp);
	}

	Texture2D::Texture2D(uint32_t width, uint32_t height, TextureFormat format, TextureFilter filter) : width(width), height(height), format(format), filter(filter) {
		glGenTextures(1, &id);
		glBindTexture(GL_TEXTURE_2D, id);

		SetTextureFilter(filter);
		SetTextureWrapMode(wrapper);

		bbp = TextureUtility::GetTextureFormatStride(format);

		glTexImage2D(GL_TEXTURE_2D, 0, TextureUtility::GetOpenGLInternalFormat(format), width, height, 0,
			TextureUtility::GetOpenGLBaseFormat(format), TextureUtility::GetOpenGLPixelDataType(format), nullptr);

		glBindTexture(GL_TEXTURE_2D, 0);

		ENG_LOG_INFO("2D Texture created, id:{0}, width:{1}, height:{2}, bbp:{3}", id, width, height, bbp);
	}

	Texture2D::Texture2D(uint32_t width, uint32_t height, TextureFormat format, TextureFilter filter, TextureWrapper wrapper) : width(width), height(height), format(format), filter(filter), wrapper(wrapper){
		glGenTextures(1, &id);
		glBindTexture(GL_TEXTURE_2D, id);

		SetTextureFilter(filter);
		SetTextureWrapMode(wrapper);

		bbp = TextureUtility::GetTextureFormatStride(format);

		glTexImage2D(GL_TEXTURE_2D, 0, TextureUtility::GetOpenGLInternalFormat(format), width, height, 0,
			TextureUtility::GetOpenGLBaseFormat(format), TextureUtility::GetOpenGLPixelDataType(format), nullptr);

		glBindTexture(GL_TEXTURE_2D, 0);

		ENG_LOG_INFO("2D Texture created, id:{0}, width:{1}, height:{2}, bbp:{3}", id, width, height, bbp);
	}

	Texture2D::Texture2D(std::string filePath) {

		stbi_set_flip_vertically_on_load(true);

		int w, h, b;
		unsigned char* data = stbi_load(filePath.c_str(), &w, &h, &b, 0);

		if (data) {
			width = w;
			height = h;
			bbp = b * 8;

			if (bbp == 8)
				format = TextureFormat::R8_UNORM;
			else if (bbp == 16)
				format = TextureFormat::RG8_UNORM;
			else if (bbp == 24)
				format = TextureFormat::RGB8_UNORM;
			else if (bbp == 32)
				format = TextureFormat::RGBA8_UNORM;

			glGenTextures(1, &id);
			glBindTexture(GL_TEXTURE_2D, id);

			SetTextureFilter(filter);
			SetTextureWrapMode(wrapper);

			bbp = TextureUtility::GetTextureFormatStride(format);

			glTexImage2D(GL_TEXTURE_2D, 0, TextureUtility::GetOpenGLInternalFormat(format), width, height, 0,
				TextureUtility::GetOpenGLBaseFormat(format), TextureUtility::GetOpenGLPixelDataType(format), data);

			glBindTexture(GL_TEXTURE_2D, 0);

			stbi_image_free(data);

			ENG_LOG_INFO("2D Texture created, id:{0}, width:{1}, height:{2}, bbp:{3}", id, width, height, bbp);
		}
		else {
			ENG_LOG_ERROR("Failed to load texture from file path: {0}", filePath);
		}
	}

	Texture2D::Texture2D(std::string filePath, TextureFilter filter) : filter(filter){
		stbi_set_flip_vertically_on_load(true);

		int w, h, b;
		unsigned char* data = stbi_load(filePath.c_str(), &w, &h, &b, 0);

		if (data) {
			width = w;
			height = h;
			bbp = b * 8;

			if (bbp == 8)
				format = TextureFormat::R8_UNORM;
			else if (bbp == 16)
				format = TextureFormat::RG8_UNORM;
			else if (bbp == 24)
				format = TextureFormat::RGB8_UNORM;
			else if (bbp == 32)
				format = TextureFormat::RGBA8_UNORM;

			glGenTextures(1, &id);
			glBindTexture(GL_TEXTURE_2D, id);

			SetTextureFilter(filter);
			SetTextureWrapMode(wrapper);

			bbp = TextureUtility::GetTextureFormatStride(format);

			glTexImage2D(GL_TEXTURE_2D, 0, TextureUtility::GetOpenGLInternalFormat(format), width, height, 0,
				TextureUtility::GetOpenGLBaseFormat(format), TextureUtility::GetOpenGLPixelDataType(format), data);

			glBindTexture(GL_TEXTURE_2D, 0);

			stbi_image_free(data);

			ENG_LOG_INFO("2D Texture created, id:{0}, width:{1}, height:{2}, bbp:{3}", id, width, height, bbp);
		}
		else {
			ENG_LOG_ERROR("Failed to load texture from file path: {0}", filePath);
		}
	}

	Texture2D::Texture2D(std::string filePath, TextureFilter filter, TextureWrapper wrapper) : filter(filter), wrapper(wrapper) {
		stbi_set_flip_vertically_on_load(true);

		int w, h, b;
		unsigned char* data = stbi_load(filePath.c_str(), &w, &h, &b, 0);

		if (data) {
			width = w;
			height = h;
			bbp = b * 8;

			if (bbp == 8)
				format = TextureFormat::R8_UNORM;
			else if (bbp == 16)
				format = TextureFormat::RG8_UNORM;
			else if (bbp == 24)
				format = TextureFormat::RGB8_UNORM;
			else if (bbp == 32)
				format = TextureFormat::RGBA8_UNORM;

			glGenTextures(1, &id);
			glBindTexture(GL_TEXTURE_2D, id);

			SetTextureFilter(filter);
			SetTextureWrapMode(wrapper);

			bbp = TextureUtility::GetTextureFormatStride(format);

			glTexImage2D(GL_TEXTURE_2D, 0, TextureUtility::GetOpenGLInternalFormat(format), width, height, 0,
				TextureUtility::GetOpenGLBaseFormat(format), TextureUtility::GetOpenGLPixelDataType(format), data);

			glBindTexture(GL_TEXTURE_2D, 0);

			stbi_image_free(data);

			ENG_LOG_INFO("2D Texture created, id:{0}, width:{1}, height:{2}, bbp:{3}", id, width, height, bbp);
		}
		else {
			ENG_LOG_ERROR("Failed to load texture from file path: {0}", filePath);
		}
	}

	Texture2D::Texture2D(void* data, uint32_t width, uint32_t height, TextureFormat format) : width(width), height(height), format(format) {
		if (data) {
			glGenTextures(1, &id);
			glBindTexture(GL_TEXTURE_2D, id);

			SetTextureFilter(filter);
			SetTextureWrapMode(wrapper);

			bbp = TextureUtility::GetTextureFormatStride(format);

			glTexImage2D(GL_TEXTURE_2D, 0, TextureUtility::GetOpenGLInternalFormat(format), width, height, 0,
				TextureUtility::GetOpenGLBaseFormat(format), TextureUtility::GetOpenGLPixelDataType(format), data);

			glBindTexture(GL_TEXTURE_2D, 0);

			ENG_LOG_INFO("2D Texture created, id:{0}, width:{1}, height:{2}, bbp:{3}", id, width, height, bbp);
		}
		else {
			ENG_LOG_ERROR("Texture2D, given data pointer is null");
		}
	}

	Texture2D::Texture2D(void* data, uint32_t width, uint32_t height, TextureFormat format, TextureFilter filter) : width(width), height(height), format(format), filter(filter) {
		if (data) {
			glGenTextures(1, &id);
			glBindTexture(GL_TEXTURE_2D, id);

			SetTextureFilter(filter);
			SetTextureWrapMode(wrapper);

			bbp = TextureUtility::GetTextureFormatStride(format);

			glTexImage2D(GL_TEXTURE_2D, 0, TextureUtility::GetOpenGLInternalFormat(format), width, height, 0,
				TextureUtility::GetOpenGLBaseFormat(format), TextureUtility::GetOpenGLPixelDataType(format), data);

			glBindTexture(GL_TEXTURE_2D, 0);

			ENG_LOG_INFO("2D Texture created, id:{0}, width:{1}, height:{2}, bbp:{3}", id, width, height, bbp);
		}
		else {
			ENG_LOG_ERROR("Texture2D, given data pointer is null");
		}
	}

	Texture2D::Texture2D(void* data, uint32_t width, uint32_t height, TextureFormat format, TextureFilter filter, TextureWrapper wrapper) : width(width), height(height), format(format), filter(filter), wrapper(wrapper) {
		if (data) {
			glGenTextures(1, &id);
			glBindTexture(GL_TEXTURE_2D, id);

			SetTextureFilter(filter);
			SetTextureWrapMode(wrapper);

			bbp = TextureUtility::GetTextureFormatStride(format);

			glTexImage2D(GL_TEXTURE_2D, 0, TextureUtility::GetOpenGLInternalFormat(format), width, height, 0,
				TextureUtility::GetOpenGLBaseFormat(format), TextureUtility::GetOpenGLPixelDataType(format), data);

			glBindTexture(GL_TEXTURE_2D, 0);

			ENG_LOG_INFO("2D Texture created, id:{0}, width:{1}, height:{2}, bbp:{3}", id, width, height, bbp);
		}
		else {
			ENG_LOG_ERROR("Texture2D, given data pointer is null");
		}
	}

	Texture2D::~Texture2D() {
		if (id != 0) {
			glDeleteTextures(1, &id);

			ENG_LOG_INFO("2D Texture deleted, id:{0}, width:{1}, height:{2}, bbp:{3}", id, width, height, bbp);
		}
	}

	void Texture2D::SetData(void* data, uint32_t size, uint32_t startIndex) {
		if (id != 0) {
			int32_t previouslyBindedTexture;
			glGetIntegerv(GL_TEXTURE_BINDING_2D, &previouslyBindedTexture);

			glBindTexture(GL_TEXTURE_2D, id);

			int32_t xoffset = (startIndex % width);
			int32_t yoffset = (startIndex / width);

			glTexSubImage2D(GL_TEXTURE_3D, 0, xoffset, yoffset, width, height, TextureUtility::GetOpenGLBaseFormat(format), TextureUtility::GetOpenGLPixelDataType(format), data);

			glBindTexture(GL_TEXTURE_2D, (uint32_t)previouslyBindedTexture);
		}
	}

	void Texture2D::SetData(void* data, uint32_t size, uint32_t xoffset, uint32_t yoffset) {
		if (id != 0) {
			int32_t previouslyBindedTexture;
			glGetIntegerv(GL_TEXTURE_BINDING_2D, &previouslyBindedTexture);

			glBindTexture(GL_TEXTURE_2D, id);

			glTexSubImage2D(GL_TEXTURE_2D, 0, xoffset, yoffset, width, height, TextureUtility::GetOpenGLBaseFormat(format), TextureUtility::GetOpenGLPixelDataType(format), data);

			glBindTexture(GL_TEXTURE_2D, (uint32_t)previouslyBindedTexture);
		}
	}

	void Texture2D::bind() {
		glBindTexture(GL_TEXTURE_2D, id);
	}

	void Texture2D::unbind() {
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	void Texture2D::setActiveTextureSlot(int slot) {
		glActiveTexture(GL_TEXTURE0 + slot);
	}

	uint32_t Texture2D::getWidth() {
		return width;
	}

	uint32_t Texture2D::getHeight() {
		return height;
	}

	uint32_t Texture2D::getBBP() {
		return bbp;
	}

	TextureFormat Texture2D::getTextureFormat() {
		return format;
	}

	TextureFilter Texture2D::getTextureFilter() {
		return filter;
	}

	TextureWrapper Texture2D::getWrapMode() {
		return wrapper;
	}

	void Texture2D::SetTextureFilter(TextureFilter filter) {
		this->filter = filter;

		if (id != 0) {
			int32_t previouslyBindedTexture;
			glGetIntegerv(GL_TEXTURE_BINDING_2D, &previouslyBindedTexture);

			glBindTexture(GL_TEXTURE_2D, id);

			switch (filter) {
			case TextureFilter::POINT:
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
				break;
			case TextureFilter::BILINEAR:
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
				break;
			case TextureFilter::TRILINEAR:
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
				break;
			}

			glBindTexture(GL_TEXTURE_2D, (uint32_t)previouslyBindedTexture);
		}
	}

	void Texture2D::SetTextureWrapMode(TextureWrapper wrapper) {
		this->wrapper = wrapper;

		if (id != 0) {
			int32_t previouslyBindedTexture;
			glGetIntegerv(GL_TEXTURE_BINDING_2D, &previouslyBindedTexture);

			glBindTexture(GL_TEXTURE_2D, id);

			switch (wrapper)
			{
			case Engine::CLAMP:
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
				break;
			case Engine::MIRROR:
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
				break;
			case Engine::REPEAT:
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
				break;
			}

			glBindTexture(GL_TEXTURE_2D, (uint32_t)previouslyBindedTexture);
		}
	}


}