#pragma once
#include "Log.h"
#include "VertexBuffer.h"
#include <string>
#include <vector>

namespace Engine {
	class VertexArray {
	public:
		enum DataType {
			FLOAT, DOUBLE, INT32, UINT32, INT16, UINT16, INT8, UINT8
		};
	private:
		uint32_t id;
		VertexBuffer* vb = nullptr;

		struct VertexElement {
			int count;
			DataType type;
		};

		std::vector<VertexElement> vertexElements;
	public:
		VertexArray() {
			glGenVertexArrays(1, &id);
			ENG_LOG_INFO("Vertex array created, id: {0}", id);
		}
		~VertexArray() {
			glDeleteVertexArrays(1, &id);
			ENG_LOG_INFO("Vertex array deleted, id: {0}", id);
		}

		void bind() {
			glBindVertexArray(id);
		}

		void unbind() {
			glBindVertexArray(0);
		}

		void PushElement(VertexBuffer* vb, int count, DataType type, bool normalized = false) {
			if (this->vb == nullptr && vb != nullptr) {
				this->vb = vb;
			}
			else if(vb != this->vb) {
				ENG_LOG_ERROR("Given vertex buffer is null or not the same as saved in Vertex Array");
				return;
			}

			bind();
			vb->bind();

			if (count > 0) {
				vertexElements.push_back({ count, type });

				int stride = 0;

				for (int i = 0; i < vertexElements.size() && stride > 0; i++) {
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

	private:
		int GetSize(DataType type) {
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

		GLenum GetGLType(DataType type) {
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
	};
}