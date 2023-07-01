#pragma once
#include "Random.h"
#include <chrono>


//Computation mode
enum class MODE {
	ADD = 0, SUBSTRACT = 1, MULTIPLY = 2, XOR = 3
};

class LaggedFibonacciGenerator : public Random {
private:
	uint32_t j, k;
	uint32_t m;
	uint32_t* stateVector = nullptr;
	uint32_t seed; //Seed value will be used in constructors and setParemeters method
	MODE mode = MODE::MULTIPLY; // Default computation mode
	uint32_t index = 0;
public:
	LaggedFibonacciGenerator(bool useTimeAsSeed = true) {
		j = 124;
		k = 159;
		m = (uint32_t)(std::pow(2,32) - 1);

		uint32_t seed = 1234554321;
		this->seed = seed;

		if (useTimeAsSeed) {
			std::chrono::steady_clock::time_point now = std::chrono::high_resolution_clock::now();

			auto time = now.time_since_epoch();
			auto time_cast = std::chrono::duration_cast<std::chrono::nanoseconds>(time);
			seed = (uint32_t)time_cast.count();
		}

		stateVector = new uint32_t[k];

		//Filing the initial state vector
		for (unsigned int i = 0; i < k; i++) {
			seed = seed * 37;
			stateVector[i] = (seed = seed + 23);
		}
	}

	LaggedFibonacciGenerator(uint32_t j, uint32_t k, uint32_t m, bool useTimeAsSeed = true): j(j), k(k), m(m) {
		uint32_t seed = 1234554321;
		this->seed = seed;
		if (useTimeAsSeed) {
			std::chrono::steady_clock::time_point now = std::chrono::high_resolution_clock::now();

			auto time = now.time_since_epoch();
			auto time_cast = std::chrono::duration_cast<std::chrono::nanoseconds>(time);
			seed = (uint32_t)time_cast.count();
		}

		stateVector = new uint32_t[k];

		//Filing the initial state vector
		for (unsigned int i = 0; i < k; i++) {
			seed = seed * 37;
			stateVector[i] = (seed = seed + 23);
		}
	}

	LaggedFibonacciGenerator(uint32_t seed) : seed(seed){
		j = 124;
		k = 159;
		m = (uint32_t)(std::pow(2, 32) - 1);

		stateVector = new uint32_t[k];

		//Filing the initial state vector
		for (unsigned int i = 0; i < k; i++) {
			seed = seed * 37;
			stateVector[i] = (seed = seed + 23);
		}
	}

	LaggedFibonacciGenerator(uint32_t seed, uint32_t j, uint32_t k, uint32_t m): seed(seed), j(j), k(k), m(m) {
		stateVector = new uint32_t[k];

		//Filing the initial state vector
		for (unsigned int i = 0; i < k; i++) {
			seed = seed * 37;
			stateVector[i] = (seed = seed + 23);
		}
	}

	~LaggedFibonacciGenerator() {
		delete stateVector;
	}


	// 0 < j < k
	void setParemeters(const uint32_t j, const uint32_t k, const uint32_t m) {
		if (j >= k) {
			ENG_LOG_ERROR("Error, Lagged Finonacci Generator: k must be bigger than j [{0},{1}]", j, k);
			return;
		}
		else if (j <= 0) {
			ENG_LOG_ERROR("Error, Lagged Finonacci Generator: j must be bigger than 0, j = {0}]", j);
			return;
		}
		else if (m < 2) {
			ENG_LOG_ERROR("Error, Lagged Finonacci Generator: m must be bigger than 0, m = {0}]", m);
			return;
		}

		delete stateVector;

		this->j = j;
		this->k = k;
		this->m = m;

		stateVector = new uint32_t[k];
		uint32_t temp = seed;

		for (unsigned int i = 0; i < k; i++) {
			temp = temp * 37;
			stateVector[i] = (temp = temp + 23);
		}

		index = 0;
	}

	//set initial value
	void setSeed(uint32_t seed) override {
		this->seed = seed;

		for (unsigned int i = 0; i < k; i++) {
			seed = seed * 37;
			stateVector[i] = (seed = seed + 23);
		}

		index = 0;
	}

	// set the computation mode
	void setMode(MODE mode) {
		this->mode = mode;
	}


	//it returns 32 bit unsigned integer
	uint32_t nextUInt() override {
		uint32_t value;
		switch (mode) {
		case MODE::ADD:
			value = (stateVector[(index + k - j) %  k] + (uint64_t)stateVector[index]) % m;
			break;
		case MODE::XOR:
			value = (stateVector[(index + k - j) % k] ^ stateVector[index]) % m;
			break;
		case MODE::SUBSTRACT:
			value = (stateVector[(index + k - j) % k] - stateVector[index]) % m;
			break;
		case MODE::MULTIPLY:
			value = (stateVector[(index + k - j) % k] * (uint64_t)stateVector[index]) % m;
			break;
		default:
			value = (stateVector[(index + k - j) % k] + (uint64_t)stateVector[index]) % m;
			break;
		}
		
		stateVector[index++] = value;
		if (index >= k)
			index -= k;

		return value;
	}

	//it returns 32 bit unsigned integer, range[min, max]
	uint32_t nextUInt(const uint32_t min, const uint32_t max) override {
		if (min >= max) {
			ENG_LOG_ERROR("Error, Lagged Finonacci Generator: max must be bigger than min [{0},{1}]", min, max);
			return 0;
		}

		uint32_t value;
		switch (mode) {
		case MODE::XOR:
			value = (stateVector[k - j] ^ stateVector[0]) % m;
			break;
		case MODE::ADD:
			value = (stateVector[k - j] + (uint64_t)stateVector[0]) % m;
			break;
		case MODE::SUBSTRACT:
			value = (stateVector[k - j] - (uint64_t)stateVector[0]) % m;
			break;
		case MODE::MULTIPLY:
			value = (stateVector[k - j] * (uint64_t)stateVector[0]) % m;
			break;
		default:
			value = (stateVector[k - j] ^ stateVector[0]) % m;
			break;
		}

		for (unsigned int i = 0; i < k; i++) {
			if (i == k - 1) {
				stateVector[i] = value;
			}
			else {
				stateVector[i] = stateVector[i + 1];
			}
		}

		uint32_t diff = max - min + 1;

		return min + value % diff;
	}
};

