#pragma once
#include <utility>
#include "glm/glm.hpp"

namespace Engine {

	class OpenGLFrameBuffer {
	private:
		uint32_t id = -1;
		uint32_t texture_id = -1;
		uint32_t renderbuffer_id = -1;

		uint32_t width, height;
	public:
		OpenGLFrameBuffer(const uint32_t width, const uint32_t height);
		~OpenGLFrameBuffer();

		void resize(const uint32_t width, const uint32_t height);

		uint32_t getWidth();
		uint32_t getHeight();

		void clear(glm::vec3 color = glm::vec3(1,1,1));

		void bind();
		void unbind();

		uint32_t& getID();
		uint32_t& getTextureID();
		uint32_t& getRenderbufferID();
	};

}