#pragma once
#include <glm/glm.hpp>
#include "Color.h"

namespace Engine {
	//Bling-Phon lighting material
	struct Material {
		glm::vec3 ambient = glm::vec3(0.3f,0.3f, 0.3f);
		glm::vec3 diffuse = glm::vec3(0.5f, 0.5f, 0.5f);;
		glm::vec3 specular = glm::vec3(0.7f, 0.7f, 0.7f);;
		float shininess = 200;
	};

}