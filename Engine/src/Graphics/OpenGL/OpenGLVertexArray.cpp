#include "OpenGLVertexArray.h"

namespace Engine {
	OpenGLVertexArray::OpenGLVertexArray() {
		glGenVertexArrays(1, &id);
		ENG_LOG_INFO("Vertex array created, id: {0}", id);
	}
	OpenGLVertexArray::~OpenGLVertexArray() {
		glDeleteVertexArrays(1, &id);
		ENG_LOG_INFO("Vertex array deleted, id: {0}", id);
	}

	void OpenGLVertexArray::bind() {
		glBindVertexArray(id);
	}

	void OpenGLVertexArray::unbind() {
		glBindVertexArray(0);
	}

	void OpenGLVertexArray::PushElement(OpenGLVertexBuffer* vb, int count, DataType type, bool normalized) {
		if (this->vb == nullptr && vb != nullptr) {
			this->vb = vb;
		}
		else if (vb != this->vb) {
			ENG_LOG_ERROR("Given vertex buffer is null or not the same as saved in Vertex Array");
			return;
		}

		ENG_LOG_INFO("Vertex attrib pushed, id: {0}, count: {1}", id, count);

		vb->bind();
		bind();

		if (count > 0) {
			vertexElements.push_back({ count, type });

			int stride = 0;

			for (int i = 0; i < vertexElements.size(); i++) {
				stride += vertexElements[i].count * GetSize(vertexElements[i].type);
			}

			int offset = 0;
			for (int i = 0; i < vertexElements.size() && stride > 0; i++) {
				glEnableVertexAttribArray(i);
				glVertexAttribPointer(i, vertexElements[i].count, GetGLType(vertexElements[i].type), normalized, stride, (void*)offset);

				offset += vertexElements[i].count * GetSize(vertexElements[i].type);
			}
		}
	}

	int OpenGLVertexArray::GetSize(DataType type) {
		switch (type) {
		case Engine::OpenGLVertexArray::FLOAT:
			return 4;
			break;
		case Engine::OpenGLVertexArray::DOUBLE:
			return 8;
			break;
		case Engine::OpenGLVertexArray::INT32:
			return 4;
			break;
		case Engine::OpenGLVertexArray::UINT32:
			return 4;
			break;
		case Engine::OpenGLVertexArray::INT16:
			return 2;
			break;
		case Engine::OpenGLVertexArray::UINT16:
			return 2;
			break;
		case Engine::OpenGLVertexArray::INT8:
			return 1;
			break;
		case Engine::OpenGLVertexArray::UINT8:
			return 1;
			break;
		}

		return 0;
	}

	GLenum OpenGLVertexArray::GetGLType(DataType type) {
		switch (type) {
		case Engine::OpenGLVertexArray::FLOAT:
			return GL_FLOAT;
			break;
		case Engine::OpenGLVertexArray::DOUBLE:
			return GL_DOUBLE;
			break;
		case Engine::OpenGLVertexArray::INT32:
			return GL_INT;
			break;
		case Engine::OpenGLVertexArray::UINT32:
			return GL_UNSIGNED_INT;
			break;
		case Engine::OpenGLVertexArray::INT16:
			return GL_SHORT;
			break;
		case Engine::OpenGLVertexArray::UINT16:
			return GL_UNSIGNED_SHORT;
			break;
		case Engine::OpenGLVertexArray::INT8:
			return GL_BYTE;
			break;
		case Engine::OpenGLVertexArray::UINT8:
			return GL_UNSIGNED_BYTE;
			break;
		}

		return GL_FLOAT;
	}
}