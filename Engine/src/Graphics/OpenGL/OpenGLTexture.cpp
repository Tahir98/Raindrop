#include "OpenGLTexture.h"
#include "stb_image.h"
#include <filesystem>
#include "glad/glad.h"

namespace Engine {
	OpenGLTexture::OpenGLTexture(std::string filePath) {
		if (!std::filesystem::exists(filePath)) {
			ENG_LOG_ERROR("Given image file is not found: {0}", filePath);
			return;
		}

		stbi_set_flip_vertically_on_load(true);

		unsigned char* data = stbi_load(filePath.c_str(), &width, &height, &channels, 0);
		
		glGenTextures(1, &id);
		glBindTexture(GL_TEXTURE_2D, id);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		if (data) {
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);

			ENG_LOG_INFO("Texture created; id: {0}, file: {1}, width: {2}, height: {3}", id, filePath, width, height);
		}
		else {
			ENG_LOG_ERROR("Failed to load image: {0}", filePath);
		}

		dimension = 2;
	}

	OpenGLTexture::OpenGLTexture(int32_t width, int32_t height, int32_t depth, const float* pixels) : width(width), height(height), depth(depth){
		glGenTextures(1, &id);
		glBindTexture(GL_TEXTURE_3D, id);

		glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_R, GL_REPEAT);

		glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		if (pixels) {
			glTexImage3D(GL_TEXTURE_3D,0, GL_R32F, width, height, depth, 0, GL_RED, GL_UNSIGNED_INT, pixels);

			ENG_LOG_INFO("Texture created; id: {0} width: {1}, height: {2}, depth", id, width, height, depth);
		}

		dimension = 3;
	}

	OpenGLTexture::~OpenGLTexture() {
		glDeleteTextures(1, &id);
	}
	void OpenGLTexture::bind() {
		if(dimension == 2)
			glBindTexture(GL_TEXTURE_2D, id);
		else if(dimension == 3)
			glBindTexture(GL_TEXTURE_3D, id);
	}

	void OpenGLTexture::unbind() {
		if (dimension == 2)
			glBindTexture(GL_TEXTURE_2D, 0);
		else if (dimension == 3)
			glBindTexture(GL_TEXTURE_3D, 0);
	}

	void OpenGLTexture::SetActiveTextureSlot(uint32_t slot) {
		glActiveTexture(GL_TEXTURE0 + slot);
	}

	int32_t OpenGLTexture::getDimension()
	{
		return dimension;
	}

	int32_t OpenGLTexture::getWidth()
	{
		return width;
	}

	int32_t OpenGLTexture::getHeight()
	{
		return height;
	}

	int32_t OpenGLTexture::getDepth()
	{
		return depth;
	}

	int32_t OpenGLTexture::getChannels()
	{
		return channels;
	}
}