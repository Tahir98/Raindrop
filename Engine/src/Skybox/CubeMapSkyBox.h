#pragma once
#include "Log.h"
#include "glad/glad.h"
#include "stb_image.h"
#include "Camera/Camera.h"

namespace Engine {
	class CubeMapSkybox {
	private:
		uint32_t textureID = -1;

	public:
		CubeMapSkybox(std::string filePath) {
			glGenTextures(1, &textureID);
			glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

			int32_t width, height, channels;
			uint8_t* data = nullptr;

			std::vector<std::string> texture_faces = {
				filePath + "/right.jpg",
				filePath + "/left.jpg",
				filePath + "/top.jpg",
				filePath + "/bottom.jpg",
				filePath + "/front.jpg",
				filePath + "/back.jpg"
			};

			for (int i = 0; i < texture_faces.size(); i++) {
				data = stbi_load(texture_faces[i].c_str(), &width, &height, &channels, 0);

				if (data) {
					glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

					stbi_image_free(data);
				}
				else {
					ENG_LOG_ERROR("Faile to load cube map, path: {0}", filePath);
					break;
				}
			}

			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
		}

		~CubeMapSkybox() {

		}

		void draw(Camera& camera) {
			camera.get
		}
	};
}
