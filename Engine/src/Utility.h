#pragma once
#include "glm/glm.hpp"

struct Bound {
	glm::vec3 min;
	glm::vec3 max;

	Bound(glm::vec3 min, glm::vec3 max) : min(min), max(max) {}

	glm::vec3 size() {
		return glm::vec3(glm::abs(max.x - min.x), glm::abs(max.y - min.y), glm::abs(max.z - min.z));
	}

	glm::vec3 center() {
		return (min + max) / 2.0f;
	}
};