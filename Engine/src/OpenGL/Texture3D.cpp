#include "Texture3D.h"

namespace Engine {
	Texture3D::Texture3D(uint32_t width, uint32_t height, uint32_t depth, TextureFormat format) : width(width), height(height), depth(depth), format(format) {
		glCreateTextures(GL_TEXTURE_3D, 1, &id);
		glBindTexture(GL_TEXTURE_3D, id);

		SetTextureFilter(filter);
		SetTextureWrapMode(wrapper);
		
		bbp = TextureUtility::GetTextureFormatStride(format);

		glTexImage3D(GL_TEXTURE_3D, 0, TextureUtility::GetOpenGLInternalFormat(format), width, height, depth, 0,
			TextureUtility::GetOpenGLBaseFormat(format), TextureUtility::GetOpenGLPixelDataType(format), nullptr);

		glBindTexture(GL_TEXTURE_3D, 0);

		ENG_LOG_INFO("3D Texture created, id:{0}, width:{1}, height:{2}, depth{3},  bbp:{4}", id, width, height, depth, bbp);
	}

	Texture3D::Texture3D(uint32_t width, uint32_t height, uint32_t depth, TextureFormat format, TextureFilter filter) : width(width), height(height), depth(depth), format(format), filter(filter) {
		glCreateTextures(GL_TEXTURE_3D, 1, &id);
		glBindTexture(GL_TEXTURE_3D, id);

		SetTextureFilter(filter);
		SetTextureWrapMode(wrapper);

		bbp = TextureUtility::GetTextureFormatStride(format);

		glTexImage3D(GL_TEXTURE_3D, 0, TextureUtility::GetOpenGLInternalFormat(format), width, height, depth, 0,
			TextureUtility::GetOpenGLBaseFormat(format), TextureUtility::GetOpenGLPixelDataType(format), nullptr);

		glBindTexture(GL_TEXTURE_3D, 0);

		ENG_LOG_INFO("3D Texture created, id:{0}, width:{1}, height:{2}, depth{3},  bbp:{4}", id, width, height, depth, bbp);
	}

	Texture3D::Texture3D(uint32_t width, uint32_t height, uint32_t depth, TextureFormat format, TextureFilter filter, TextureWrapper wrapper) : width(width), height(height), depth(depth), format(format), filter(filter), wrapper(wrapper) {
		glCreateTextures(GL_TEXTURE_3D, 1, &id);
		glBindTexture(GL_TEXTURE_3D, id);

		SetTextureFilter(filter);
		SetTextureWrapMode(wrapper);

		bbp = TextureUtility::GetTextureFormatStride(format);

		glTexImage3D(GL_TEXTURE_3D, 0, TextureUtility::GetOpenGLInternalFormat(format), width, height, depth, 0,
			TextureUtility::GetOpenGLBaseFormat(format), TextureUtility::GetOpenGLPixelDataType(format), nullptr);

		glBindTexture(GL_TEXTURE_3D, 0);

		ENG_LOG_INFO("3D Texture created, id:{0}, width:{1}, height:{2}, depth{3},  bbp:{4}", id, width, height, depth, bbp);
	}

	Texture3D::Texture3D(void* data, uint32_t width, uint32_t height, uint32_t depth, TextureFormat format) : width(width), height(height), depth(depth), format(format) {
		if (data) {
			glCreateTextures(GL_TEXTURE_3D, 1, &id);
			glBindTexture(GL_TEXTURE_3D, id);

			SetTextureFilter(filter);
			SetTextureWrapMode(wrapper);

			bbp = TextureUtility::GetTextureFormatStride(format);

			glTexImage3D(GL_TEXTURE_3D, 0, TextureUtility::GetOpenGLInternalFormat(format), width, height, depth, 0,
				TextureUtility::GetOpenGLBaseFormat(format), TextureUtility::GetOpenGLPixelDataType(format), data);

			glBindTexture(GL_TEXTURE_3D, 0);

			ENG_LOG_INFO("3D Texture created, id:{0}, width:{1}, height:{2}, depth{3}, bbp:{4}", id, width, height, depth, bbp);
		}
		else {
			ENG_LOG_ERROR("Texture3D, given data pointer is null");
		}
	}

	Texture3D::Texture3D(void* data, uint32_t width, uint32_t height, uint32_t depth, TextureFormat format, TextureFilter filter) : width(width), height(height), depth(depth), format(format), filter(filter) {
		if (data) {
			glCreateTextures(GL_TEXTURE_3D, 1, &id);
			glBindTexture(GL_TEXTURE_3D, id);

			SetTextureFilter(filter);
			SetTextureWrapMode(wrapper);

			bbp = TextureUtility::GetTextureFormatStride(format);

			glTexImage3D(GL_TEXTURE_3D, 0, TextureUtility::GetOpenGLInternalFormat(format), width, height, depth, 0,
				TextureUtility::GetOpenGLBaseFormat(format), TextureUtility::GetOpenGLPixelDataType(format), data);

			glBindTexture(GL_TEXTURE_3D, 0);

			ENG_LOG_INFO("3D Texture created, id:{0}, width:{1}, height:{2}, depth{3}, bbp:{4}", id, width, height, depth, bbp);
		}
		else {
			ENG_LOG_ERROR("Texture3D, given data pointer is null");
		}
	}

	Texture3D::Texture3D(void* data, uint32_t width, uint32_t height, uint32_t depth, TextureFormat format, TextureFilter filter, TextureWrapper wrapper) : width(width), height(height), depth(depth), format(format), filter(filter), wrapper(wrapper) {
		if (data) {
			glCreateTextures(GL_TEXTURE_3D, 1, &id);
			glBindTexture(GL_TEXTURE_3D, id);

			SetTextureFilter(filter);
			SetTextureWrapMode(wrapper);

			bbp = TextureUtility::GetTextureFormatStride(format);

			glTexImage3D(GL_TEXTURE_3D, 0, TextureUtility::GetOpenGLInternalFormat(format), width, height, depth, 0,
				TextureUtility::GetOpenGLBaseFormat(format), TextureUtility::GetOpenGLPixelDataType(format), data);

			glBindTexture(GL_TEXTURE_3D, 0);

			ENG_LOG_INFO("3D Texture created, id:{0}, width:{1}, height:{2}, depth{3}, bbp:{4}", id, width, height, depth, bbp);
		}
		else {
			ENG_LOG_ERROR("Texture3D, given data pointer is null");
		}
	}

	Texture3D::~Texture3D() {
		if (id != 0) {
			glDeleteTextures(1, &id);

			ENG_LOG_INFO("3D Texture deleted, id:{0}, width:{1}, height:{2}, depth:{3} bbp:{4}", id, width, height, depth, bbp);
		}
	}

	void Texture3D::SetData(void* data, uint32_t size, uint32_t startIndex) {
		if (id != 0) {
			int32_t previouslyBindedTexture;
			glGetIntegerv(GL_TEXTURE_BINDING_3D, &previouslyBindedTexture);

			glBindTexture(GL_TEXTURE_3D, id);

			int32_t xoffset = (startIndex % width);
			int32_t yoffset = (startIndex / width) % height;
			int32_t zoffset = (startIndex / (width * height));

			glTexSubImage3D(GL_TEXTURE_3D, 0, xoffset, yoffset, zoffset, width, height, depth, TextureUtility::GetOpenGLBaseFormat(format), TextureUtility::GetOpenGLPixelDataType(format), data);

			glBindTexture(GL_TEXTURE_3D, (uint32_t)previouslyBindedTexture);
		}
	}

	void Texture3D::SetData(void* data, uint32_t size, uint32_t xoffset, uint32_t yoffset, uint32_t zoffset) {
		if (id != 0) {
			int32_t previouslyBindedTexture;
			glGetIntegerv(GL_TEXTURE_BINDING_3D, &previouslyBindedTexture);

			glBindTexture(GL_TEXTURE_3D, id);

			glTexSubImage3D(GL_TEXTURE_3D, 0, xoffset, yoffset, zoffset, width, height, depth, TextureUtility::GetOpenGLBaseFormat(format), TextureUtility::GetOpenGLPixelDataType(format), data);

			glBindTexture(GL_TEXTURE_3D, (uint32_t)previouslyBindedTexture);
		}
	}

	void Texture3D::Resize(uint32_t width, uint32_t height, uint32_t depth) {
		this->width = width;
		this->height = height;
		this->depth = depth;

		bind();

		glTexImage3D(GL_TEXTURE_3D, 0, TextureUtility::GetOpenGLInternalFormat(format), width, height, depth, 0,
			TextureUtility::GetOpenGLBaseFormat(format), TextureUtility::GetOpenGLPixelDataType(format), nullptr);
	}

	void Texture3D::bind() {
		glBindTexture(GL_TEXTURE_3D, id);
	}

	void Texture3D::unbind() {
		glBindTexture(GL_TEXTURE_3D, 0);
	}

	void Texture3D::setActiveTextureSlot(int slot) {
		glActiveTexture(GL_TEXTURE0 + slot);
	}

	uint32_t Texture3D::getID() {
		return id;
	}

	uint32_t Texture3D::getWidth() {
		return width;
	}

	uint32_t Texture3D::getHeight() {
		return height;
	}

	uint32_t Texture3D::getDepth() {
		return depth;
	}

	uint32_t Texture3D::getBBP() {
		return bbp;
	}

	TextureFormat Texture3D::getTextureFormat() {
		return format;
	}

	TextureFilter Texture3D::getTextureFilter() {
		return filter;
	}

	TextureWrapper Texture3D::getWrapMode() {
		return wrapper;
	}

	void Texture3D::SetTextureFilter(TextureFilter filter) {
		this->filter = filter;

		if (id != 0) {
			int32_t previouslyBindedTexture;
			glGetIntegerv(GL_TEXTURE_BINDING_3D, &previouslyBindedTexture);

			glBindTexture(GL_TEXTURE_3D, id);

			switch (filter) {
			case TextureFilter::POINT:
				glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
				glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
				break;
			case TextureFilter::BILINEAR:
				glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
				break;
			case TextureFilter::TRILINEAR:
				glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
				break;
			}

			glBindTexture(GL_TEXTURE_3D, (uint32_t)previouslyBindedTexture);
		}
	}

	void Texture3D::SetTextureWrapMode(TextureWrapper wrapper) {
		this->wrapper = wrapper;

		if (id != 0) {
			int32_t previouslyBindedTexture;
			glGetIntegerv(GL_TEXTURE_BINDING_3D, &previouslyBindedTexture);

			glBindTexture(GL_TEXTURE_3D, id);

			switch (wrapper)
			{
			case Engine::CLAMP:
				glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
				glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
				glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
				break;
			case Engine::MIRROR:
				glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
				glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
				glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_R, GL_MIRRORED_REPEAT);
				break;
			case Engine::REPEAT:
				glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_S, GL_REPEAT);
				glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_T, GL_REPEAT);
				glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_R, GL_REPEAT);
				break;
			}

			glBindTexture(GL_TEXTURE_3D, (uint32_t)previouslyBindedTexture);
		}
	}

}