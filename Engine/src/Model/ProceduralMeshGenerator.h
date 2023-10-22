#pragma once

#include "Mesh.h"

namespace Engine {
	class ProceduralMeshGenerator {
	public:
		enum MeshTypes {
			Cube = 0, Sphere = 1, Cone = 2, Capsule = 3, Torus = 4
		};

	private:


	public:
		static Mesh GenerateCube(float size, bool includeUVs) {
			std::vector<glm::vec3> vertices;

			return;
		}

	};

}
