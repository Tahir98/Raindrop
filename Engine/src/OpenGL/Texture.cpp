#include "Texture.h"
#include "stb_image.h"
#include <filesystem>
#include "glad/glad.h"

namespace Engine {
	Texture::Texture(std::string filePath) {
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
		}
		else {
			ENG_LOG_ERROR("Failed to load image: {0}", filePath);
		}
	}

	Texture::~Texture() {
		glDeleteTextures(1, &id);
	}
	void Texture::bind() {
		glBindTexture(GL_TEXTURE_2D, id);
	}

	void Texture::unbind() {
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	void Texture::SetActiveTextureSlot(uint32_t slot) {
		glActiveTexture(GL_TEXTURE0 + slot);
	}

	int32_t Texture::getDimension()
	{
		return dimension;
	}

	int32_t Texture::getWidth()
	{
		return width;
	}
	int32_t Texture::getHeight()
	{
		return height;
	}
	int32_t Texture::getChannels()
	{
		return channels;
	}
}