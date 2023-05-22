#pragma once
#include "Log.h"
#include <string>
#include <glad/glad.h>

namespace Engine {

	class VertexBuffer {
	private:
		uint32_t id;

		const uint32_t size; //Buffer size in bytes
	public:
		VertexBuffer(const void* data, uint32_t size, GLenum usage) : size(size) {
			glCreateBuffers(1, &id);
			glBindBuffer(GL_ARRAY_BUFFER, id);
			glBufferData(GL_ARRAY_BUFFER, size, data, usage);

			ENG_LOG_INFO("Vertex Buffer created, id: {0}", id);
		}

		~VertexBuffer() {
			glDeleteBuffers(1, &id);
			ENG_LOG_INFO("Vertex Buffer deleted, id: {0}", id);
		}

		void bind() {
			glBindBuffer(GL_ARRAY_BUFFER, id);
		}

		void unmbind() {
			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}

		void SetData(const void* data, uint32_t offset, uint32_t size) {
			if (size > this->size) {
				bind();
				glBufferSubData(GL_ARRAY_BUFFER, offset, this->size, data);

				ENG_LOG_WARN("Data size is bigger than vertex buffer size, id: {0}", id);
			}
			else {
				glBufferSubData(GL_ARRAY_BUFFER, offset, size, data);
			}
		}

		uint32_t GetBufferSize() {
			return size;
		}
	};
}