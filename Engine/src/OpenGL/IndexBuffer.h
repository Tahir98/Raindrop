#pragma once
#include "Log.h"
#include <string>
#include <glad/glad.h>

namespace Engine {

	class IndexBuffer {
	private:
		uint32_t id;

		const uint32_t size; //Buffer size in sizeof uint32_t
	public:
		IndexBuffer(const uint32_t* indices, uint32_t size, GLenum usage) : size(size) {
			glCreateBuffers(1, &id);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, size * sizeof(uint32_t), indices, usage);

			ENG_LOG_INFO("Index Buffer created, id: {0}", id);
		}

		~IndexBuffer() {
			glDeleteBuffers(1, &id);
			ENG_LOG_INFO("Index Buffer deleted, id: {0}", id);
		}

		void bind() {
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
		}

		void bind() {
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		}

		void SetData(const uint32_t* indices, uint32_t offset, uint32_t size) {
			if (size > this->size) {
				bind();
				glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, offset, this->size * sizeof(uint32_t), indices);

				ENG_LOG_WARN("Data size is bigger than index buffer size, id: {0}", id);
			}
			else {
				glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, offset, size * sizeof(uint32_t), indices);
			}
		}

		uint32_t GetBufferSize() {
			return size;
		}
	};
}