#pragma once
#include <glm/glm.hpp>
#include "Color.h"

struct DirectionalLight {
	glm::vec3 direction = glm::vec3(0, -1, 0);
	Color color = PredefinedColor::White;
	float intensity = 1;
};

struct PointList {
	glm::vec3 position;
	float intensity;
};