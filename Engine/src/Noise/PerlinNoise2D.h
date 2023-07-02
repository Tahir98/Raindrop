#pragma once
#include "glm/glm.hpp"
#include "glm/gtc/constants.hpp"

#include "Random/Xorshift.h"

namespace Engine {
	struct PerlinNoise2DLayer {
		glm::vec2 offset;
		float scale;
		float height;
		int smoothness;
	};

	class PerlinNoise2D {
	private:
		static Xorshift xorshift;
	public:
		static float interpolate(float a0, float a1, float w, int smoothness) {
			if (w < 0) w = 0;
			else if (w > 1.0f) w = 1.0f;

			switch (smoothness) {
			case 0:
				return (a1 - a0) * w + a0;
				break;
			case 1:
				return (a1 - a0) * (3.0 - w * 2.0) * w * w + a0;
				break;
			case 2:
				return (a1 - a0) * ((w * (w * 6.0 - 15.0) + 10.0) * w * w * w) + a0;
				break;
			default:
				return (a1 - a0) * ((w * (w * 6.0 - 15.0) + 10.0) * w * w * w) + a0;
				break;
			}

			return 0;
		}

		static float dotGridGradient(int ix, int iz, float x, float z) {
			uint64_t seed = (uint32_t)ix;
			seed = seed << 32;
			seed += (uint32_t)iz;
			xorshift.setSeed(seed);
			float random = xorshift.nextFloat();

			glm::vec2 gradient;
			gradient.x = cosf(random * glm::pi<float>()); gradient.y = sinf(random * glm::pi<float>());

			glm::vec2 distance = { x - ix , z - iz };
			return glm::dot(gradient, distance);
		}

		static float value(float x, float z, int smoothness) {
			int x0 = (int)x;
			int x1 = x + 1;
			int z0 = (int)z;
			int z1 = z0 + 1;

			float sx = x - (float)x0;
			float sz = z - (float)z0;

			float n0, n1, n2, n3, ix0, ix1, value;

			n0 = dotGridGradient(x0, z0, x, z);
			n1 = dotGridGradient(x1, z0, x, z);
			ix0 = interpolate(n0, n1, sx, smoothness);

			n2 = dotGridGradient(x0, z1, x, z);
			n3 = dotGridGradient(x1, z1, x, z);
			ix1 = interpolate(n2, n3, sx, smoothness);

			value = interpolate(ix0, ix1, sz, smoothness);

			return value;
		}
	};
}