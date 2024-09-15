#pragma once
#include "glm/glm.hpp"

namespace Engine {

	//Current noise algorithm implementations
	static enum NoiseType {
		Perlin2D = 0, Perlin3D = 1, Worley2D = 2, Worley3D = 3, InverseWorley2D = 4, InverseWorley3D = 5
	};

	//How to blend with total value of noise in multilayer noise use cases
	static enum LayerBlending {
		Add = 0, Subtract = 1, Multiply = 2, Divide = 3
	};

	//Layer struct to generate more natural shapes in 2d and 3d textures
	static struct NoiseLayer {
		NoiseType type = NoiseType::Perlin3D;
		LayerBlending blend = LayerBlending::Add;
		glm::vec3 offset = glm::vec3(10, 10, 10);
		int octaveCount = 1;
		int scale = 1;
		float normalizedScale = 1;
		float opacity = 1;
		int smoothnessLevel = 1;
	};
}