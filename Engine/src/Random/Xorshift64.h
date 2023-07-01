#pragma once

#include <cstdint>
#include <chrono>
#include "Log.h"
#include "BitConverter.h"

class Xorshift64 {
private:
	uint32_t a = 11;//shift counts
	uint32_t b = 19;//shift counts
	uint32_t c = 8;	//shift counts

	uint64_t x, y; // random seeds (2 * 64 bits) will be produce 2^128 - 1(exculuding 0 bits) period pseudorandom numbers 

public:
	Xorshift64(bool useTimeAsSeed = true) {
		if (useTimeAsSeed) {

			std::chrono::steady_clock::time_point now = std::chrono::high_resolution_clock::now();

			auto time = now.time_since_epoch();
			auto time_cast = std::chrono::duration_cast<std::chrono::nanoseconds>(time);
			uint64_t seed = time_cast.count();

			x = seed;
			y =  seed ^ (seed >> 14);
		}
		else {
			x = 123456789987654321;
			y = 987654321123456789;
		}
	}

	Xorshift64(const uint64_t x, uint64_t y) : x(x), y(y) {
	}

	void setShiftingParemeters(const uint32_t a, const uint32_t b, const uint32_t c) {
		if (a == 0 || a > 31)
			ENG_LOG_ERROR("Error, Xorshift, a must be in [1,31], given: {0}", a);
		else
			this->a = a;

		if (b == 0 || b > 31)
			ENG_LOG_ERROR("Error, Xorshift, b must be in [1,31], given: {0}", b);
		else
			this->b = b;

		if (c == 0 || c > 31)
			ENG_LOG_ERROR("Error, Xorshift, c must be in [1,31], given: {0}", a);
		else
			this->c = c;
	}

	//set initial values
	void setSeed(const uint64_t x, const uint64_t y) {
		this->x = x;
		this->y = y;
	}

	void setSeed(const uint64_t x) {
		this->x = x;
		this->y = 6364136223846793005 * (x ^ (x << 62));
	}

	//It returns random 64bit unsigned integer
	uint64_t nextUInt64() {
		uint64_t temp = x ^ (x << a);
		x = y;
		y = (y ^ (y >> b)) ^ (temp ^ (temp >> c));

		return y;
	}

	//It returns random 64bit unsigned integer, range[min,max]
	uint64_t nextUInt64(const uint64_t min, const uint64_t max) {
		if (min >= max) {
			ENG_LOG_ERROR("Error, Xorshift: min is bigger or equal than max");
			return 0;
		}

		uint64_t temp = x ^ (x << a);
		x = y;
		y = (y ^ (y >> b)) ^ (temp ^ (temp >> c));

		uint64_t diff = max - min + 1;

		return min + y % diff;
	}

	//It returns random 64bit signed integer
	int64_t nextInt64() {
		return (int64_t)nextUInt64();
	}

	//It returns random 64bit signed integer, range[min,max]
	int64_t nextInt64(const int64_t min, const int64_t max) {
		if (min >= max) {
			ENG_LOG_ERROR("Error, Xorshift: min is bigger or equal than max");
			return 0;
		}

		uint64_t value = nextUInt64();
		uint64_t diff = max - min + 1;

		return min + value % diff;
	}

	// It returns 32 bit floating point
	float nextFloat() {
		uint32_t random = (uint32_t)nextUInt64();

		return BitConverter::Ran32Flt1(random);
	}

	// It returns 64 bit floating point
	long double nextDouble() {
		int64_t random = nextInt64();
		int32_t random1 = random >> 32;
		int32_t random2 = (uint32_t)random;

		return BitConverter::Ran32Dbl1(random1, random2);
	}
};