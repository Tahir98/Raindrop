#include "OpenGLIndexBuffer.h"

namespace Engine {
	OpenGLIndexBuffer::OpenGLIndexBuffer(const uint32_t* indices, uint32_t size, GLenum usage) : size(size) {
		glCreateBuffers(1, &id);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, size * sizeof(uint32_t), indices, usage);

		ENG_LOG_INFO("Index Buffer created, id: {0}", id);
	}

	OpenGLIndexBuffer::~OpenGLIndexBuffer() {
		glDeleteBuffers(1, &id);
		ENG_LOG_INFO("Index Buffer deleted, id: {0}", id);
	}

	void OpenGLIndexBuffer::bind() {
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
	}

	void OpenGLIndexBuffer::unbind() {
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	void OpenGLIndexBuffer::SetData(const uint32_t* indices, uint32_t offset, uint32_t size) {
		if (size > this->size) {
			bind();
			glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, offset, this->size * sizeof(uint32_t), indices);

			ENG_LOG_WARN("Data size is bigger than index buffer size, id: {0}", id);
		}
		else {
			glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, offset, size * sizeof(uint32_t), indices);
		}
	}

	uint32_t OpenGLIndexBuffer::GetBufferSize() {
		return size;
	}
}