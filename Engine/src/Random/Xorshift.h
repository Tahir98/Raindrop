#pragma once
#include "Random.h"
#include <chrono>

class Xorshift : public Random {
private:
	uint32_t a = 11;//shift counts
	uint32_t b = 19;//shift counts
	uint32_t c = 8;	//shift counts

	uint32_t x, y, z, w; // random seeds (4 * 32 bits) will be produce 2^128 - 1(exculuding 0 bits) period pseudorandom numbers 

public:
	Xorshift(bool useTimeAsSeed = true) {
		if (useTimeAsSeed) {
			std::chrono::steady_clock::time_point now = std::chrono::high_resolution_clock::now();

			auto time = now.time_since_epoch();
			auto time_cast = std::chrono::duration_cast<std::chrono::nanoseconds>(time);
			uint64_t seed = time_cast.count();

			w = (uint32_t)seed;
			z = (uint32_t)(seed >> 32);

			time = now.time_since_epoch();
			time_cast = std::chrono::duration_cast<std::chrono::microseconds>(time);
			seed = time.count();

			y = (uint32_t)seed;
			x = (uint32_t)(seed >> 32);
		}
		else {
			uint64_t seed = 123456789987654321;
			w = (uint32_t)seed;
			z = (uint32_t)(seed >> 32);

			seed = 987654321123456789;
			y = (uint32_t)seed;
			x = (uint32_t)(seed >> 32);
		}
	}

	Xorshift(const uint32_t seed) {
		x = seed;
		y = 181243323UL * (x ^ (x >> 30)) + 1;
		z = 181243323UL * (y ^ (y >> 30)) + 2;
		w = 181243323UL * (z ^ (z >> 30)) + 3;
	}

	Xorshift(const uint32_t x, const uint32_t y, const uint32_t z, const uint32_t w): x(x), y(y), z(z), w(w) {
	}

	Xorshift(const uint64_t xy, uint64_t zw) {
		x = xy >> 32;
		y = (uint32_t)xy;
		
		z = zw >> 32;
		w = (uint32_t)zw;
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

	void setSeed(uint32_t seed) override {
		x = seed;
		y = 181243323UL * (x ^ (x >> 30)) + 1;
		z = 181243323UL * (y ^ (y >> 30)) + 2;
		w = 181243323UL * (z ^ (z >> 30)) + 3;
	}

	//set initial values
	void setSeed(const uint32_t x, const uint32_t y, const uint32_t z, const uint32_t w) {
		this->x = x;
		this->y = y;
		this->z = z;
		this->w = w;
	}

	//set initial values
	void setSeed(const uint64_t xy, const uint64_t zw) {
		x = xy >> 32;
		y = (uint32_t)xy;

		z = zw >> 32;
		w = (uint32_t)zw;
	}

	//It returns random 32bit unsigned integer
	uint32_t nextUInt() override {
		uint32_t temp = x ^ (x << a);
		x = y;
		y = z;
		z = w;
		w = (w ^ (w >> b)) ^ (temp ^ (temp >> c));

		return w;
	}

	//It returns random 32bit unsigned integer, range[min,max]
	uint32_t nextUInt(const uint32_t min, const uint32_t max ) override {
		if (min >= max) {
			ENG_LOG_ERROR("Error, Xorshift: min is bigger or equal than max");
			return 0;
		}

		uint32_t temp = x ^ (x << a);
		x = y;
		y = z;
		z = w;
		w = (w ^ (w >> b)) ^ (temp >> c);

		uint32_t diff = max - min + 1;

		return min + w % diff;
	}
};