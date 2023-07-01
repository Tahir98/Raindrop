#pragma once
#include "Random.h"
#include <cmath>
#include <chrono>

class MersenneTwister : public Random {
private:
	const unsigned int N = 624; //Size of state vector
	const unsigned int M = 397; //Half size
	uint32_t* sv = nullptr; // State Vector
	unsigned int index; // Index of the element in the state vector
public:
	MersenneTwister(bool useTimeAsSeed = true) {
		sv = new uint32_t[N]{ 0 };
		index = 0;

		if (useTimeAsSeed) {
			std::chrono::steady_clock::time_point now = std::chrono::high_resolution_clock::now();

			auto time = now.time_since_epoch();
			auto time_cast = std::chrono::duration_cast<std::chrono::nanoseconds>(time);
			sv[0] = (uint32_t)time_cast.count();
		}
		else
			sv[0] = 42;

		//initialize the state vector array
		for (unsigned int i = 1; i < N; i++) {
			sv[i] = 181243323UL * (sv[i - 1] ^ (sv[i - 1] >> 30)) + i;
		}

		twist();
	}

	MersenneTwister(const uint32_t seed) {
		sv = new uint32_t[N]{ 0 };
		index = 0;
		sv[0] = seed;

		//initialize the state vector array
		for (unsigned int i = 1; i < N; i++) {
			sv[i] = 181243323UL * (sv[i - 1] ^ (sv[i - 1] >> 30)) + i;
		}

		twist();
	}

	~MersenneTwister() {
		delete sv;
	}

	// Reseeding
	void setSeed(const uint32_t seed) override {
		sv[0] = seed;
		index = 0;

		for (unsigned int i = 1; i < N; i++) {
			sv[i] = 181243323UL * (sv[i - 1] ^ (sv[i - 1] >> 30)) + i;
		}

		twist();
	}

	// It returns 32 bit unsigned integer
	uint32_t nextUInt() override {
		if (index >= N)
			twist();

		uint32_t y = sv[index++];

		//tempering
		y ^= (y >> 11) & 0xFFFFFFFF;
		y ^= (y << 7) & 0x9d2c5680;
		y ^= (y << 15) & 0xefc60000;
		y ^= y >> 18;

		return y;
	}

	// It returns 32 bit unsigned integer, range[min,max]
	uint32_t nextUInt(const uint32_t min, const uint32_t max) override {
		if (min >= max) {
			ENG_LOG_ERROR("Mersenne twister: Max must be bigger than min");
			return 0;
		}

		if (index >= N)
			twist();

		uint32_t y = sv[index++];

		//tempering
		y ^= y >> 11;
		y ^= (y << 7) & 0x9d2c5680;
		y ^= (y << 15) & 0xefc60000;
		y ^= y >> 18;

		uint32_t diff = max - min + 1;

		y = min + y % diff;

		return y;
	}

private:
	//It generates the next N values for tempering
	void twist() {
		
		const unsigned int FirstHalf = N - M;

		//RAND_LOG_INFO("UPPER_MASK: {0}",((1 << 31) - 1) ^ 0xFFFFFFFF);
		const uint32_t UPPER_MASK = 0x80000000;

		//RAND_LOG_INFO("LOWER_MASK: {0}",((1 << 31) - 1));
		const uint32_t LOWER_MASK = 0x7fffffff;
		const uint32_t MATRIX_A = 0x9908b0df;

		unsigned int i = 0;

		for (; i < FirstHalf;i++) {
			uint32_t bits = (sv[i] & UPPER_MASK) | (sv[i + 1] & LOWER_MASK);
			sv[i] = sv[M + i] ^ (bits >> 1) ^ ((bits & 1) * MATRIX_A);
		}

		for (; i < N - 1; i++) {
			uint32_t bits = (sv[i] & UPPER_MASK) | (sv[i + 1] & LOWER_MASK);
			sv[i] = sv[i - FirstHalf] ^ (bits >> 1) ^ ((bits & 1) * MATRIX_A);
		}

		uint32_t bits = (sv[i] & UPPER_MASK) | (sv[i + 1] & LOWER_MASK);
		sv[i] = sv[M - 1] ^ (bits >> 1) ^ ((bits & 1) * MATRIX_A);

		index = 0;
	}
};