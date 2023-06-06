#include "VertexArray.h"

namespace Engine {
	VertexArray::VertexArray() {
		glGenVertexArrays(1, &id);
		ENG_LOG_INFO("Vertex array created, id: {0}", id);
	}
	VertexArray::~VertexArray() {
		glDeleteVertexArrays(1, &id);
		ENG_LOG_INFO("Vertex array deleted, id: {0}", id);
	}

	void VertexArray::bind() {
		glBindVertexArray(id);
	}

	void VertexArray::unbind() {
		glBindVertexArray(0);
	}

	void VertexArray::PushElement(VertexBuffer* vb, int count, DataType type, bool normalized) {
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

	int VertexArray::GetSize(DataType type) {
		switch (type) {
		case Engine::VertexArray::FLOAT:
			return 4;
			break;
		case Engine::VertexArray::DOUBLE:
			return 8;
			break;
		case Engine::VertexArray::INT32:
			return 4;
			break;
		case Engine::VertexArray::UINT32:
			return 4;
			break;
		case Engine::VertexArray::INT16:
			return 2;
			break;
		case Engine::VertexArray::UINT16:
			return 2;
			break;
		case Engine::VertexArray::INT8:
			return 1;
			break;
		case Engine::VertexArray::UINT8:
			return 1;
			break;
		}

		return 0;
	}

	GLenum VertexArray::GetGLType(DataType type) {
		switch (type) {
		case Engine::VertexArray::FLOAT:
			return GL_FLOAT;
			break;
		case Engine::VertexArray::DOUBLE:
			return GL_DOUBLE;
			break;
		case Engine::VertexArray::INT32:
			return GL_INT;
			break;
		case Engine::VertexArray::UINT32:
			return GL_UNSIGNED_INT;
			break;
		case Engine::VertexArray::INT16:
			return GL_SHORT;
			break;
		case Engine::VertexArray::UINT16:
			return GL_UNSIGNED_SHORT;
			break;
		case Engine::VertexArray::INT8:
			return GL_BYTE;
			break;
		case Engine::VertexArray::UINT8:
			return GL_UNSIGNED_BYTE;
			break;
		}

		return GL_FLOAT;
	}
}