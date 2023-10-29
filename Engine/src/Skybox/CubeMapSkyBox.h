#pragma once
#include "Log.h"
#include "glad/glad.h"
#include "stb_image.h"

#include "OpenGL/VertexArray.h"
#include "OpenGL/VertexBuffer.h"
#include "OpenGL/IndexBuffer.h"
#include "OpenGL/Shader.h"
#include "OpenGL/OpenGLUtility.h"

#include "Camera/Camera.h"



namespace Engine {
	class CubeMapSkybox {
	private:
		uint32_t textureID = -1;

		VertexBuffer* vb = nullptr;
		VertexArray* va = nullptr;
		IndexBuffer* ib = nullptr;
		Shader* shader = nullptr;

		OpenGLState renderState;
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

			std::vector<glm::vec3> vertices = {
				glm::vec3(0,0,0),
				glm::vec3(0,1,0),
				glm::vec3(1,1,0),
				glm::vec3(1,0,0),
				glm::vec3(1,0,1),
				glm::vec3(1,1,1),
				glm::vec3(0,1,1),
				glm::vec3(0,0,1)
			};

			for (int i = 0; i < vertices.size(); i++) {
				vertices[i] += glm::vec3(-0.5f, -0.5f, -0.5f);
			}

			std::vector<uint32_t> indices = {
				0,1,2, 0,2,3,
				3,2,5, 3,5,4,
				4,5,6, 4,6,7,
				7,6,1, 7,1,0,
				7,0,3, 7,3,4,
				1,6,5, 1,5,2
			};

			vb = new VertexBuffer(vertices.data(), sizeof(glm::vec3) * vertices.size(), GL_STATIC_DRAW);
			va = new VertexArray();

			va->PushElement(vb, 3, VertexArray::FLOAT, false);

			ib = new IndexBuffer(indices.data(), sizeof(uint32_t) * indices.size(), GL_STATIC_DRAW);

			shader = new Shader("Shaders/cubemap.shader");
		}

		~CubeMapSkybox() {
			glDeleteTextures(1, &textureID);

			delete vb;
			delete va;
			delete ib;
			delete shader;
		}

		void draw(Camera& camera) {
			va->bind();
			ib->bind();
			shader->bind();

			glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);
			glActiveTexture(GL_TEXTURE0);

			shader->SetUniformMatrix4x4("view", 1, false, glm::value_ptr(camera.getViewMatrix()));
			shader->SetUniformMatrix4x4("projection", 1, false, glm::value_ptr(camera.getProjectionMatrix()));

			shader->SetUniform1i("cubemap", 0);

			OpenGLUtility::SetOpenGLState(renderState);

			glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
		}
	};
}
