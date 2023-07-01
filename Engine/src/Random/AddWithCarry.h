#pragma once
#include "Random.h"
#include <chrono>
#include "Log.h"
#include "BitConverter.h"

class AddWithCarry : public Random {
private:
	uint32_t r, s;
	uint64_t b;
	uint32_t* stateVector = nullptr;
	uint32_t c;

	uint32_t iSeed; // initial seed
	uint32_t index = 0;
public:
	AddWithCarry(bool useTimeAsSeed = true) {
		b = (uint64_t)(std::pow(2,32));
		r = 20;
		s = 11; // r > s
		c = 1; // initial value

		//Add with cary function
		//xi = (xi-s + xi-r + ci) mod b
		//ci+1 = I(xi-s + xi-r + ci >= b)

		uint32_t seed = 1234554321;

		if (useTimeAsSeed) {
			std::chrono::steady_clock::time_point now = std::chrono::high_resolution_clock::now();

			auto time = now.time_since_epoch();
			auto time_cast = std::chrono::duration_cast<std::chrono::nanoseconds>(time);
			seed = (uint32_t)time_cast.count();
		}

		iSeed = seed;

		stateVector = new uint32_t[r];
		stateVector[0] = seed;

		//Filling the initial state vector
		for (uint32_t i = 1; i < r; i++) {
			stateVector[i] = 181243323UL * (stateVector[i - 1] ^ (stateVector[i - 1] >> 30)) + i;
		}
	}

	AddWithCarry(uint32_t seed) {
		b = (uint64_t)(std::pow(2, 32));
		r = 20;
		s = 11; // r > s
		c = 1; // initial value

		//Add with cary function
		//xi = (xi-s + xi-r + ci) mod b
		//ci+1 = I(xi-s + xi-r + ci >= b)

		iSeed = seed;

		stateVector = new uint32_t[r];
		stateVector[0] = seed;

		//Filling the initial state vector
		for (uint32_t i = 1; i < r; i++) {
			stateVector[i] = 181243323UL * (stateVector[i - 1] ^ (stateVector[i - 1] >> 30)) + i;
		}
	}

	AddWithCarry(const uint32_t r, const uint32_t s, const uint32_t c, const uint32_t b,bool useTimeAsSeed = true): r(r),s(s),c(c),b(b) {
		
		//Add with cary function
		//xi = (xi-s + xi-r + ci) mod b
		//ci+1 = I(xi-s + xi-r + ci >= b)

		uint32_t seed = 1234554321;

		if (useTimeAsSeed) {
			std::chrono::steady_clock::time_point now = std::chrono::high_resolution_clock::now();

			auto time = now.time_since_epoch();
			auto time_cast = std::chrono::duration_cast<std::chrono::nanoseconds>(time);
			seed = (uint32_t)time_cast.count();
		}

		iSeed = seed;

		stateVector = new uint32_t[r];
		stateVector[0] = seed;

		//Filling the initial state vector
		for (uint32_t i = 1; i < r; i++) {
			stateVector[i] = 181243323UL * (stateVector[i - 1] ^ (stateVector[i - 1] >> 30)) + i;
		}
	}

	AddWithCarry(const uint32_t r, const uint32_t s, const uint32_t c, const uint32_t b, uint32_t seed) : r(r), s(s), c(c), b(b) {
		//Add with cary function
		//xi = (xi-s + xi-r + ci) mod b
		//ci+1 = I(xi-s + xi-r + ci >= b)

		iSeed = seed;
		stateVector = new uint32_t[r];
		stateVector[0] = seed;

		//Filling the initial state vector
		for (uint32_t i = 1; i < r; i++) {
			stateVector[i] = 181243323UL * (stateVector[i - 1] ^ (stateVector[i - 1] >> 30)) + i;
		}
	}

	~AddWithCarry() {
		delete stateVector;
	}


	//set initial value
	void setSeed(uint32_t seed) override {
		iSeed = seed;
		c = 1;
		stateVector[0] = seed;

		//Filling the initial state vector
		for (uint32_t i = 1; i < r; i++) {
			stateVector[i] = 181243323UL * (stateVector[i - 1] ^ (stateVector[i - 1] >> 30)) + i;
		}

		index = 0;
	}

	void setParameters(const uint32_t r, const uint32_t s, const uint32_t c, const uint32_t b) {
		if (r <= s) {
			ENG_LOG_ERROR("Error, Add Width Carry: r must be bigger than s");
			return;
		}

		if (b < 2) {
			ENG_LOG_ERROR("Error, Add Width Carry: b must be bigger than 2");
			return;
		}

		this->r = r;
		this->s = s;
		this->c = c % 2;
		this->b = b;

		delete stateVector;

		stateVector = new uint32_t[r];
		stateVector[0] = iSeed;

		//Filling the initial state vector
		for (uint32_t i = 1; i < r; i++) {
			stateVector[i] = 181243323UL * (stateVector[i - 1] ^ (stateVector[i - 1] >> 30)) + i;
		}

		index = 0;
	}


	//it returns 32bit unsigned integer
	uint32_t nextUInt() override {
		uint64_t a = (uint64_t)stateVector[(index + r - s) % r] + stateVector[index] + c;
		c = a >= b ? 1 : 0; // next c value 

		uint32_t value = (uint32_t)(a % b);
		
		stateVector[index++] = value;
		if (index >= r)
			index -= r;

		return value;
	}

	//it returns 32bit unsigned integer, range[min,max]
	uint32_t nextUInt(const uint32_t min, const uint32_t max) override { 
		if (min >= max) {
			ENG_LOG_ERROR("Error, Lagged Finonacci Generator: max must be bigger than min [{0},{1}]", min, max);
			return 0;
		}

		uint64_t a = (uint64_t)stateVector[r - s] + stateVector[0] - c;
		c = a >= b ? 1 : 0; // next c value 

		uint32_t value = (uint32_t)(a % b);

		for (uint32_t i = 0; i < r - 1; i++) {
			stateVector[i] = stateVector[i + 1];
		}

		stateVector[r - 1] = value;

		uint32_t diff = max - min + 1;

		return min + value % diff;
	}
};

