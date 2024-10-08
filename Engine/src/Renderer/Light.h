#pragma once
#include <glm/glm.hpp>
#include "Color.h"

struct DirectionalLight {
	glm::vec3 direction = glm::vec3(0, -1, 0);
	Color color = Colors::White;
	float intensity = 1;
};

struct PointLight {
	glm::vec3 position;
	float intensity;
};