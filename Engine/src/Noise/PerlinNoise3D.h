#pragma once
#include "glm/glm.hpp"
#include "glm/gtc/constants.hpp"

#include "Random/Xorshift.h"

namespace Engine {

	struct PerlinNoise3DLayer {
		glm::vec3 offset;
		float scale;
		int smoothness;
	};

	class PerlinNoise3D {
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

		static float dotGridGradient(int ix, int iy, int iz, float x, float y, float z) {
			uint64_t seed = (uint32_t)ix;
			seed = seed << 24;
			seed += (uint32_t)iy;
			seed = seed << 24;
			seed += (uint32_t)iz;

			xorshift.setSeed(seed);
			float r1 = xorshift.nextFloat();
			float r2 = xorshift.nextFloat();

			glm::vec3 gradient;
			gradient.x = cosf(glm::pi<float>() * r1 * 2.0f) * sinf(glm::pi<float>() * r2);
			gradient.y = cosf(glm::pi<float>() * r2);
			gradient.z = sinf(glm::pi<float>() * r1 * 2.0f) * sinf(glm::pi<float>() * r2);

			glm::vec3 distance = glm::vec3(x - ix, y - iy, z - iz);

			return glm::dot(gradient, distance);
		}

		static float value(float x, float y, float z, int smoothness) {
			int x0 = (int)x;
			int x1 = x + 1;
			int y0 = (int)y;
			int y1 = y0 + 1;
			int z0 = (int)z;
			int z1 = z0 + 1;

			float sx = x - (float)x0;
			float sy = y - (float)y0;
			float sz = z - (float)z0;

			float n0, n1, n2, n3, ix0, ix1, iy0, iy1, value;

			n0 = dotGridGradient(x0, y0, z0, x, y, z);
			n1 = dotGridGradient(x1, y0, z0, x, y, z);
			ix0 = interpolate(n0, n1, sx, smoothness);

			n2 = dotGridGradient(x0, y1, z0, x, y, z);
			n3 = dotGridGradient(x1, y1, z0, x, y, z);
			ix1 = interpolate(n2, n3, sx, smoothness);

			iy0 = interpolate(ix0, ix1, sy, smoothness);

			n0 = dotGridGradient(x0, y0, z1, x, y, z);
			n1 = dotGridGradient(x1, y0, z1, x, y, z);
			ix0 = interpolate(n0, n1, sx, smoothness);

			n2 = dotGridGradient(x0, y1, z1, x, y, z);
			n3 = dotGridGradient(x1, y1, z1, x, y, z);
			ix1 = interpolate(n2, n3, sx, smoothness);

			iy1 = interpolate(ix0, ix1, sy, smoothness);

			value = interpolate(iy0, iy1, sz, smoothness);

			return value;
		}
	};
}