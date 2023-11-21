#pragma once
#include <glm/glm.hpp>
#include "Color.h"

namespace Engine {
	//Bling-Phon lighting material
	struct Material {
		Color color = Colors::White;
		float ambient = 0.3f;
		float diffuse = 0.5f;
		float specular = 0.7f;
		float shininess = 200;
	};

}