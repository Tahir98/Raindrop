#pragma once
#include <cmath>
#include "Log.h"
#include "BitConverter.h"

class MersenneTwister64 {
private:
	const unsigned int N = 312; //Size of state vector
	const unsigned int M = 156; //Half size
	uint64_t* sv = nullptr; // State Vector
	unsigned int index; // Index of the element in the state vector
public:

	MersenneTwister64(bool useTimeAsSeed = true) {
		sv = new uint64_t[N]{ 0 };
		index = 0;

		if (useTimeAsSeed) {
			std::chrono::steady_clock::time_point now = std::chrono::high_resolution_clock::now();

			auto time = now.time_since_epoch();
			auto time_cast = std::chrono::duration_cast<std::chrono::nanoseconds>(time);
			sv[0] = time_cast.count();
		}
		else
			sv[0] = 42;

		//initialize the state vector array
		for (unsigned int i = 1; i < N; i++) {
			sv[i] = (uint64_t)6364136223846793005 * (sv[i - 1] ^ (sv[i - 1] >> 62)) + i;
		}

		twist();
	}

	MersenneTwister64 (const uint64_t seed) {
		sv = new uint64_t[N]{ 0 };
		index = 0;
		sv[0] = seed;

		//initialize the state vector array
		for (unsigned int i = 1; i < N; i++) {
			sv[i] = (uint64_t)6364136223846793005 * (sv[i - 1] ^ (sv[i - 1] >> 62)) + i;
		}

		twist();
	}

	~MersenneTwister64() {
		delete sv;
	}

	// Reseeding
	void setSeed(const uint64_t seed) {
		sv[0] = seed;
		index = 0;

		//initialize the state vector array
		for (unsigned int i = 1; i < N; i++) {
			sv[i] = (uint64_t)6364136223846793005 * (sv[i - 1] ^ (sv[i - 1] >> 62)) + i;
		}

		twist();
	}

	// It returns 64 bit unsigned integer
	uint64_t nextUInt64() {
		if (index >= N)
			twist();

		uint64_t y = sv[index++];

		//tempering
		y ^= y >> 29;
		y ^= (y << 17) & 0x71D67FFFEDA60000;
		y ^= (y << 37) & 0xFFF7EEE000000000;
		y ^= y >> 43;

		return y;
	}

	// It returns 64 bit unsigned integer, range[min,max]
	uint64_t nextUInt64(const uint64_t min, const uint64_t max) {
		if (min >= max) {
			ENG_LOG_ERROR("Mersenne twister: Max must be bigger than min");
			return 0;
		}

		if (index >= N)
			twist();

		uint64_t y = sv[index++];

		//tempering
		y ^= y >> 29;
		y ^= (y << 17) & 0x71D67FFFEDA60000;
		y ^= (y << 37) & 0xFFF7EEE000000000;
		y ^= y >> 43;

		uint64_t diff = max - min + 1;

		y = min + y % diff;

		return y;
	}

	// It returns 64 bit integer
	int64_t  nextInt64() {
		uint64_t  random = nextUInt64();
		return (int64_t)random;
	}

	// It returns 64 bit integer, range[min,max]
	int64_t  nextInt64(const int64_t min, const int64_t max) {
		if (min >= max) {
			ENG_LOG_ERROR("Mersenne twister: Max must be bigger than min");
			return 0;
		}

		uint64_t  random = nextUInt64();
		int64_t diff = max - min + 1;
		random = min + random % diff;

		return (int64_t)random;
	}

	// It returns 32 bit floating point, range[0,1)
	float nextFloat() {
		uint64_t random = nextUInt64();
		uint32_t r = (uint32_t)random;

		return BitConverter::Ran32Flt1(r);
	}

	// It returns 64 bit floating point, range[0,1)
	long double nextDouble() {
		uint64_t random = nextUInt64();
		uint32_t random1 = (uint32_t)random;
		uint32_t random2 = (uint32_t)(random >> 32);

		return BitConverter::Ran32Dbl1((int32_t)random1, (int32_t)random2);
	}

private:
	//It generates the next N values for tempering
	void twist() {

		const unsigned int FirstHalf = N - M;

		//APP_LOG_INFO("UPPER_MASK: {0}",((1 << 31) - 1) ^ 0xFFFFFFFF);
		const uint64_t UPPER_MASK = 0x80000000;

		//APP_LOG_INFO("LOWER_MASK: {0}",((1 << 31) - 1));
		const uint64_t LOWER_MASK = 0x7fffffff;
		const uint64_t MATRIX_A = 0xB5026F5AA96619E9;

		unsigned int i = 0;

		for (; i < FirstHalf; i++) {
			uint64_t bits = (sv[i] & UPPER_MASK) | (sv[i + 1] & LOWER_MASK);
			sv[i] = sv[M + i] ^ (bits >> 1) ^ ((bits & 1) * MATRIX_A);
		}

		for (; i < N - 1; i++) {
			uint64_t bits = (sv[i] & UPPER_MASK) | (sv[i + 1] & LOWER_MASK);
			sv[i] = sv[i - FirstHalf] ^ (bits >> 1) ^ ((bits & 1) * MATRIX_A);
		}

		uint64_t bits = (sv[i] & UPPER_MASK) | (sv[i + 1] & LOWER_MASK);
		sv[i] = sv[M - 1] ^ (bits >> 1) ^ ((bits & 1) * MATRIX_A);

		index = 0;
	}
};