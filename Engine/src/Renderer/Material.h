#pragma once
#include <glm/glm.hpp>
#include "Color.h"

namespace Engine {
	//PBR Material
	struct Material {
		Color color = Colors::White;
		float roughness = 0.2f;
		float metallic = 0.0f;
		float specular = 1.0f;
	};

}