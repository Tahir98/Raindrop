#pragma once
#include "glm/glm.hpp"
#include <string>

namespace Engine {
	struct Vertex {
		glm::vec3 position;
		glm::vec3 normal;
		glm::vec3 texCoord;
	};

	enum TextureType {
		DIFFUSE = 0, SPECULAR = 1, NORMAL = 2, AO = 3, METALLIC = 4, ROUGHNESS = 5
	};

	struct TextureDef {
		uint32_t id;
		std::string type;
		std::string path;
		Texture2D* texture = nullptr;
	};
	
}
