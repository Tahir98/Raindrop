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
		VertexArray();
		~VertexArray();

		void bind();
		void unbind();

		void PushElement(VertexBuffer* vb, int count, DataType type, bool normalized = false);

	private:
		int GetSize(DataType type);
		GLenum GetGLType(DataType type);
	};
}