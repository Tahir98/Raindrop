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
		IndexBuffer(const uint32_t* indices, uint32_t size, GLenum usage);

		~IndexBuffer();

		void bind();
		void unbind();

		void SetData(const uint32_t* indices, uint32_t offset, uint32_t size);

		uint32_t GetBufferSize();
	};
}