#pragma once

#include "OpenGL/VertexBuffer.h"
#include "OpenGL/VertexArray.h"
#include "OpenGL/IndexBuffer.h"

#include <vector>
#include <glm/glm.hpp>

namespace Engine {
	class Mesh {
		friend class ProceduralMeshGenerator;
	private:
		std::vector<glm::vec3>* positions = nullptr;
		std::vector<glm::vec3>* normals = nullptr;
		std::vector<glm::vec3>* texcoords = nullptr;

		std::vector<uint32_t>* indices = nullptr;

		VertexBuffer* vb = nullptr;
		VertexArray* va = nullptr;
		IndexBuffer* ib = nullptr;

	public:
		Mesh() {};
		Mesh(std::vector<glm::vec3>* positions, std::vector<uint32_t>* indices) 
			: positions(positions), indices(indices) {};
		Mesh(std::vector<glm::vec3>* positions, std::vector<glm::vec3>* normals, std::vector<uint32_t>* indices) 
			: positions(positions), normals(normals), indices(indices){};
		Mesh(std::vector<glm::vec3>* positions, std::vector<glm::vec3>* texcoords, std::vector<uint32_t>* indices)
			: positions(positions), texcoords(texcoords), indices(indices) {};
		Mesh(std::vector<glm::vec3>* positions, std::vector<glm::vec3>* normals, std::vector<glm::vec3>* texcoords, std::vector<uint32_t>* indices) 
			: positions(positions), normals(normals), texcoords(texcoords), indices(indices) {};

		std::vector<glm::vec3>* getPositions() {
			return positions;
		}

		std::vector<glm::vec3>* getNormals() {
			return normals;
		}

		std::vector<glm::vec3>* getTexcoords() {
			return texcoords;
		}

		std::vector<uint32_t>* getIndices() {
			return indices;
		}
	};
}
