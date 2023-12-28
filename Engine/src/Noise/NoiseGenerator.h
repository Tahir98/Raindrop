#pragma once
#include <glm/glm.hpp>
#include "Random/Xorshift.h"

namespace Engine {
	//Current noise algorithm implementations
	enum NoiseType {
		Perlin2D = 0, Perlin3D = 1, Worley2D = 2, Worley3D = 3
	};

	//How to blend with total value of noise in multilayer noise use cases
	enum LayerBlending {
		Add = 0, Subtruct = 1, Multiply = 2, Divide = 3 
	};

	//Layer struct to generate more natural shapes in 2d and 3d textures
	struct NoiseLayer {
		NoiseType type;
		LayerBlending blending;
		glm::vec3 offset;
		float scale;
		float opacity;
		int smoothnessLevel;
	};



	class NoiseGenerator {
	private:
		//RNG algorithm
		Xorshift rng;

	public:
		float Perlin2D(float x, float y, int smoothnessLevel) {

		}
	};
}