#pragma once
#include "NoiseGeneratorDefines.h"
#include "glm/gtc/constants.hpp"
#include "Random/Xorshift.h"
#include "Random/Xorshift64.h"
namespace Engine {
	class NoiseGenerator {
	private:
		//RNG algorithm
		Xorshift rng;
		Xorshift64 rng64;

		glm::ivec3 repeatFrequency = glm::ivec3(1, 1, 1);
		glm::ivec3 repeatOffset = glm::ivec3(0, 0, 0);
		bool noiseRepeatEnabled = false;

	public:
		float Perlin2D(float x, float y, int smoothnessLevel) {
			int x0, y0, x1, y1;
			
			x0 = (int)x;
			x1 = (int)(x + 1);
			y0 = (int)y;
			y1 = (int)(y0 + 1);

			float sx = x - (float)x0;
			float sy = y - (float)y0;

			float n0, n1, n2, n3, ix0, ix1, value;

			n0 = dotGridGradient(x0, y0, x, y);
			n1 = dotGridGradient(x1, y0, x, y);
			ix0 = interpolate(n0, n1, sx, smoothnessLevel);

			n2 = dotGridGradient(x0, y1, x, y);
			n3 = dotGridGradient(x1, y1, x, y);
			ix1 = interpolate(n2, n3, sx, smoothnessLevel);

			value = interpolate(ix0, ix1, sy, smoothnessLevel);

			return glm::clamp<float>(value + 0.5f, 0, 1);
		}

		float Perlin3D(float x, float y, float z, int smoothnessLevel) {
			int x0 = (int)x;
			int x1 = (int)(x + 1);
			int y0 = (int)y;
			int y1 = (int)(y0 + 1);
			int z0 = (int)z;
			int z1 = (int)(z0 + 1);

			float sx = x - (float)x0;
			float sy = y - (float)y0;
			float sz = z - (float)z0;

			float n0, n1, n2, n3, ix0, ix1, iy0, iy1, value;

			n0 = dotGridGradient(x0, y0, z0, x, y, z);
			n1 = dotGridGradient(x1, y0, z0, x, y, z);
			ix0 = interpolate(n0, n1, sx, smoothnessLevel);

			n2 = dotGridGradient(x0, y1, z0, x, y, z);
			n3 = dotGridGradient(x1, y1, z0, x, y, z);
			ix1 = interpolate(n2, n3, sx, smoothnessLevel);

			iy0 = interpolate(ix0, ix1, sy, smoothnessLevel);

			n0 = dotGridGradient(x0, y0, z1, x, y, z);
			n1 = dotGridGradient(x1, y0, z1, x, y, z);
			ix0 = interpolate(n0, n1, sx, smoothnessLevel);

			n2 = dotGridGradient(x0, y1, z1, x, y, z);
			n3 = dotGridGradient(x1, y1, z1, x, y, z);
			ix1 = interpolate(n2, n3, sx, smoothnessLevel);

			iy1 = interpolate(ix0, ix1, sy, smoothnessLevel);

			value = interpolate(iy0, iy1, sz, smoothnessLevel);

			return glm::clamp<float>(value + 0.5f, 0, 1);
		}

		float Worley2D(float x, float y, int smoothnessLevel, bool inverse = false) {
			glm::vec2 origin = glm::vec2(x, y);

			int x0 = (int)x;
			int y0 = (int)y;

			float minDistance = 1;

			for (int y1 = -1; y1 <= 1; y1++) {
				for (int x1 = -1; x1 <= 1; x1++) {
					glm::vec2 point = glm::vec2(x0 + x1, y0 + y1) + randomPoint(x0 + x1, y0 + y1);
					float distance = glm::length(point - origin);

					if (minDistance > distance)
						minDistance = distance;
				}
			}

			float noise = interpolate(0, 1, minDistance, smoothnessLevel);;

			if (inverse)
				noise = 1.0f - noise;

			return noise;
		}

		float Worley3D(float x, float y, float z, int smoothnessLevel, bool inverse = false) {
			glm::vec3 origin = glm::vec3(x, y, z);

			int x0 = (int)x;
			int y0 = (int)y;
			int z0 = (int)z;

			float minDistance = 1;

			for (int z1 = -1; z1 <= 1; z1++) {
				for (int y1 = -1; y1 <= 1; y1++) {
					for (int x1 = -1; x1 <= 1; x1++) {
						glm::vec3 point = glm::vec3(x0 + x1, y0 + y1, z0 + z1) + randomPoint(x0 + x1, y0 + y1, z0 + z1);
						float distance = glm::length(point - origin);

						if (minDistance > distance)
							minDistance = distance;
					}
				}
			}

			float noise = interpolate(0, 1, minDistance, smoothnessLevel);

			if (inverse)
				noise = 1.0f - noise;

			return noise;
		}

		float Value(glm::vec3 point, NoiseLayer layer) {
			float noise = 0;
			float totalOctaveStrength = 0;

			for (int i = 0; i < layer.octaveCount; i++) {
				float octaveStrength = 1.0f / (pow(2.0f, i + 1.0f)); //1.0, 0.5, 0.25, 0.125,...

				glm::vec3 position = point * layer.normalizedScale / octaveStrength + layer.offset;

				switch (layer.type) {
				case NoiseType::Perlin2D:
					noise += Perlin2D(position.x, position.y, layer.smoothnessLevel) * octaveStrength;
					break;
				case NoiseType::Perlin3D:
					noise += Perlin3D(position.x, position.y, position.z, layer.smoothnessLevel) * octaveStrength;
					break;
				case NoiseType::Worley2D:
					noise += Worley2D(position.x, position.y, layer.smoothnessLevel, false) * octaveStrength;
					break;
				case NoiseType::Worley3D:
					noise += Worley3D(position.x, position.y, position.z, layer.smoothnessLevel, false) * octaveStrength;
					break;
				case NoiseType::InverseWorley2D:
					noise += Worley2D(position.x, position.y, layer.smoothnessLevel, true) * octaveStrength;
					break;
				case NoiseType::InverseWorley3D:
					noise += Worley3D(position.x, position.y, position.z, layer.smoothnessLevel, true) * octaveStrength;
					break;
				}

				totalOctaveStrength += octaveStrength;
			}


			return remap(noise, 0, totalOctaveStrength, 0, 1) * layer.opacity;
		}

		float Value(glm::vec3 point, std::vector<NoiseLayer> layers) {
			float totalNoise = 0;

			for (uint8_t i = 0;i < layers.size(); i++) {
				float noise = 0;
				float totalOctaveStrength = 0;
				
				for (uint8_t j = 0; j < layers[i].octaveCount; j++) {
					float octaveStrength = 1.0f / (pow(2.0f, j + 1.0f)); //1.0, 0.5, 0.25, 0.125,...

					glm::vec3 position = point * layers[i].normalizedScale / octaveStrength + layers[i].offset;

					switch (layers[i].type) {
					case NoiseType::Perlin2D:
						noise += Perlin2D(position.x, position.y, layers[i].smoothnessLevel) * octaveStrength;
						break;
					case NoiseType::Perlin3D:
						noise += Perlin3D(position.x, position.y, position.z, layers[i].smoothnessLevel) * octaveStrength;
						break;
					case NoiseType::Worley2D:
						noise += Worley2D(position.x, position.y, layers[i].smoothnessLevel, false) * octaveStrength;
						break;
					case NoiseType::Worley3D:
						noise += Worley3D(position.x, position.y, position.z, layers[i].smoothnessLevel, false) * octaveStrength;
						break;
					case NoiseType::InverseWorley2D:
						noise += Worley2D(position.x, position.y, layers[i].smoothnessLevel, true) * octaveStrength;
						break;
					case NoiseType::InverseWorley3D:
						noise += Worley3D(position.x, position.y, position.z, layers[i].smoothnessLevel, true) * octaveStrength;
						break;
					}

					totalOctaveStrength += octaveStrength;
				}

				noise = remap(noise, 0, totalOctaveStrength, 0, 1) * layers[i].opacity;
				totalNoise = BlendNoise(totalNoise, noise, layers[i].blend);
			}

			return totalNoise;
		}

		void EnableNoiseRepeat(bool enable) {
			noiseRepeatEnabled = enable;
		}

		void SetNoiseRepeatFrequency(glm::ivec3 repeatFrequency) {
			this->repeatFrequency = repeatFrequency;
		}

		void SetNoiseRepeatOffset(glm::ivec3 repeatOffset) {
			this->repeatOffset = repeatOffset;
		}

	private:
		float BlendNoise(float totalNoise, float noise, LayerBlending blend) {
			float newNoise = 0;

			switch (blend) {
			case Engine::Add:
				newNoise = totalNoise + noise;
				break;
			case Engine::Subtract:
				newNoise = totalNoise - noise;
				break;
			case Engine::Multiply:
				newNoise = totalNoise * noise;
				break;
			case Engine::Divide:
				if(noise != 0)
					newNoise = totalNoise / noise;
				break;
			default:
				newNoise = totalNoise + noise;
				break;
			}

			return newNoise;
		}

		float dotGridGradient(int ix, int iy, float x, float y) {
			glm::vec2 gradient = randomVector(ix, iy);

			glm::vec2 distance = { x - ix , y - iy };
			return glm::dot(gradient, distance);
		}

		float dotGridGradient(int ix, int iy, int iz, float x, float y, float z) {
			glm::vec3 gradient = randomVector(ix, iy, iz);
			glm::vec3 distance = glm::vec3(x - ix, y - iy, z - iz);

			return glm::dot(gradient, distance);
		}

		float interpolate(float a0, float a1, float w, int smoothness) {
			if (w < 0) w = 0;
			else if (w > 1.0f) w = 1.0f;

			switch (smoothness) {
			case 0:
				return (a1 - a0) * w + a0;
				break;
			case 1:
				return (a1 - a0) * (3.0f - w * 2.0f) * w * w + a0;
				break;
			case 2:
				return (a1 - a0) * ((w * (w * 6.0f - 15.0f) + 10.0f) * w * w * w) + a0;
				break;
			default:
				return (a1 - a0) * ((w * (w * 6.0 - 15.0f) + 10.0f) * w * w * w) + a0;
				break;
			}

			return 0;
		}

		glm::vec2 randomPoint(int x, int y) {
			glm::ivec2 fpos = getFrequencyBasedCoordinate(x, y);

			uint32_t seed = (uint32_t)fpos.x;
			seed = seed << 16;
			seed += (uint32_t)fpos.y;

			rng.setSeed(seed);

			return glm::vec2(rng.nextFloat(), rng.nextFloat());
		}

		glm::vec3 randomPoint(int x, int y, int z) {
			glm::ivec3 fpos = getFrequencyBasedCoordinate(x, y, z);

			uint64_t seed = (uint32_t)fpos.x;
			seed = seed << 24;
			seed += (uint32_t)fpos.y;
			seed = seed << 24;
			seed += (uint32_t)fpos.z;

			rng64.setSeed(seed);

			return glm::vec3(rng64.nextFloat(), rng64.nextFloat(), rng64.nextFloat());
		}

		glm::vec2 randomVector(int x, int y) {
			glm::ivec2 fpos = getFrequencyBasedCoordinate(x, y);

			uint32_t seed = (uint32_t)fpos.x;
			seed = seed << 16;
			seed += (uint32_t)fpos.y;

			rng.setSeed(seed);
			
			float random = rng.nextFloat();

			return glm::vec2(cosf(random * glm::pi<float>()), sinf(random * glm::pi<float>()));
		}

		glm::vec3 randomVector(int x, int y, int z) {
			glm::ivec3 fpos = getFrequencyBasedCoordinate(x, y, z);

			uint64_t seed = (uint32_t)fpos.x;
			seed = seed << 24;
			seed += (uint32_t)fpos.y;
			seed = seed << 24;
			seed += (uint32_t)fpos.z;

			rng64.setSeed(seed);
			float r1 = rng64.nextFloat();
			float r2 = rng64.nextFloat();

			glm::vec3 nvector; //Normalized vector
			nvector.x = cosf(glm::pi<float>() * r1 * 2.0f) * sinf(glm::pi<float>() * r2);
			nvector.y = cosf(glm::pi<float>() * r2);
			nvector.z = sinf(glm::pi<float>() * r1 * 2.0f) * sinf(glm::pi<float>() * r2);

			return nvector;
		}

		glm::ivec2 getFrequencyBasedCoordinate(int x, int y) {
			int fx = x, fy = y;

			if (noiseRepeatEnabled) {
				int intPart = (int)(x / repeatFrequency.x);
				fx = x - intPart * repeatFrequency.x + repeatOffset.x;

				intPart = (int)(y / repeatFrequency.y);
				fy = y - intPart * repeatFrequency.y + repeatOffset.y;
			}

			return glm::ivec2(fx, fy);
		}

		glm::ivec3 getFrequencyBasedCoordinate(int x, int y, int z) {
			int fx = x, fy = y, fz = z;

			if (noiseRepeatEnabled) {
				int intPart = (int)(x / repeatFrequency.x);
				fx = x - intPart * repeatFrequency.x + repeatOffset.x;

				intPart = (int)(y / repeatFrequency.y);
				fy = y - intPart * repeatFrequency.y + repeatOffset.y;

				intPart = (int)(z / repeatFrequency.z);
				fz = z - intPart * repeatFrequency.z + repeatOffset.z;
			}

			return glm::ivec3(fx, fy, fz);
		}

		float remap(float originalValue, float originalMin, float originalMax, float newMin, float newMax) {
			return newMin + (originalValue - originalMin) / (originalMax - originalMin) * (newMax - newMin);
		}
	};
}