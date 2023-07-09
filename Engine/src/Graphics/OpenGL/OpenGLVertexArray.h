#pragma once
#include "Log.h"
#include "OpenGLVertexBuffer.h"
#include <string>
#include <vector>

namespace Engine {
	class OpenGLVertexArray {
	public:
		enum DataType {
			FLOAT, DOUBLE, INT32, UINT32, INT16, UINT16, INT8, UINT8
		};
	private:
		uint32_t id;
		OpenGLVertexBuffer* vb = nullptr;

		struct VertexElement {
			int count;
			DataType type;
		};

		std::vector<VertexElement> vertexElements;
	public:
		OpenGLVertexArray();
		~OpenGLVertexArray();

		void bind();
		void unbind();

		void PushElement(OpenGLVertexBuffer* vb, int count, DataType type, bool normalized = false);

	private:
		int GetSize(DataType type);
		GLenum GetGLType(DataType type);
	};
}