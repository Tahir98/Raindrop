#pragma once
#include <chrono>
#include "Log.h"
#include "BitConverter.h"


class LaggedFibonacciGenerator64 {
private:
	uint32_t j, k;
	uint64_t m;
	uint64_t* stateVector = nullptr;
	uint64_t seed; //Seed value will be used in constructors and setParemeters method
	uint32_t index = 0;
public:
	LaggedFibonacciGenerator64(bool useTimeAsSeed = true) {
		j = 5;
		k = 17;
		m = (uint64_t)std::pow(2, 63) - 1 + (uint64_t)std::pow(2, 63);

		seed = 1234554321;

		if (useTimeAsSeed) {
			std::chrono::steady_clock::time_point now = std::chrono::high_resolution_clock::now();

			auto time = now.time_since_epoch();
			auto time_cast = std::chrono::duration_cast<std::chrono::nanoseconds>(time);
			seed = (uint64_t)time_cast.count();
		}

		stateVector = new uint64_t[k];

		uint64_t m_seed = seed;
		stateVector[0] = seed;
		//Filing the initial state vector
		for (unsigned int i = 1; i < k; i++) {
			m_seed = m_seed * 37 + 23;
			stateVector[i] = m_seed;;
		}
	}

	LaggedFibonacciGenerator64(uint32_t j, uint32_t k, uint64_t m, bool useTimeAsSeed = true) : j(j), k(k), m(m) {
		seed = 1234554321;

		if (useTimeAsSeed) {
			std::chrono::steady_clock::time_point now = std::chrono::high_resolution_clock::now();

			auto time = now.time_since_epoch();
			auto time_cast = std::chrono::duration_cast<std::chrono::nanoseconds>(time);
			seed = (uint64_t)time_cast.count();
		}

		stateVector = new uint64_t[k];

		uint64_t m_seed = seed;
		stateVector[0] = seed;
		//Filing the initial state vector
		for (unsigned int i = 1; i < k; i++) {
			m_seed = m_seed * 37 + 23;
			stateVector[i] = m_seed;;
		}
	}

	LaggedFibonacciGenerator64(uint64_t seed) : seed(seed) {
		j = 5;
		k = 17;
		m = (uint64_t)std::pow(2, 63) - 1 + (uint64_t)std::pow(2, 63);

		stateVector = new uint64_t[k];

		uint64_t m_seed = seed;
		stateVector[0] = seed;
		//Filing the initial state vector
		for (unsigned int i = 1; i < k; i++) {
			m_seed = m_seed * 37 + 23;
			stateVector[i] = m_seed;;
		}
	}

	LaggedFibonacciGenerator64(uint64_t seed, uint32_t j, uint32_t k, uint64_t m) : seed(seed), j(j), k(k), m(m) {
		stateVector = new uint64_t[k];

		uint64_t m_seed = seed;
		stateVector[0] = seed;
		//Filing the initial state vector
		for (unsigned int i = 1; i < k; i++) {
			m_seed = m_seed * 37 + 23;
			stateVector[i] = m_seed;;
		}
	}

	~LaggedFibonacciGenerator64() {
		delete stateVector;
	}


	// 0 < j < k
	void setParemeters(const uint32_t j, const uint32_t k, const uint64_t m) {
		if (j >= k) {
			ENG_LOG_ERROR("Error, Lagged Finonacci Generator64: k must be bigger than j [{0},{1}]", j, k);
			return;
		}
		else if (j <= 0) {
			ENG_LOG_ERROR("Error, Lagged Finonacci Generator64: j must be bigger than 0, j = {0}]", j);
			return;
		}
		else if (m < 2) {
			ENG_LOG_ERROR("Error, Lagged Finonacci Generator64: m must be bigger than 0, m = {0}]", m);
			return;
		}

		delete stateVector;

		this->j = j;
		this->k = k;
		this->m = m;

		stateVector = new uint64_t[k];

		uint64_t m_seed = seed;
		stateVector[0] = seed;
		//Filing the initial state vector
		for (unsigned int i = 1; i < k; i++) {
			m_seed = m_seed * 37 + 23;
			stateVector[i] = m_seed;;
		}

		index = 0;
	}

	//set initial value
	void setSeed(uint32_t seed) {
		this->seed = seed;

		uint64_t m_seed = seed;
		stateVector[0] = seed;
		//Filing the initial state vector
		for (unsigned int i = 1; i < k; i++) {
			m_seed = m_seed * 37 + 23;
			stateVector[i] = m_seed;;
		}

		index = 0;
	}

	//it returns 64 bit unsigned integer
	uint64_t nextUInt64() {
		uint64_t value = (stateVector[(index + k - j) % k] ^ stateVector[index]) % m;

		stateVector[index++] = value;
		if (index >= k)
			index -= k;

		return value;
	}

	//it returns 64 bit unsigned integer, range[min, max]
	uint64_t nextUInt64(const uint64_t min, const uint64_t max) {
		if (min >= max) {
			ENG_LOG_ERROR("Error, Lagged Finonacci Generator64: max must be bigger than min [{0},{1}]", min, max);
			return 0;
		}

		uint64_t value = (stateVector[(index + k - j) % k] ^ stateVector[index]) % m;

		stateVector[index++] = value;
		if (index >= k)
			index -= k;

		uint64_t diff = max - min + 1;

		return min + value % diff;
	}

	//it returns 64 bit signed integer
	int64_t nextInt() {
		int64_t value = (int64_t)nextUInt64();
		return value;
	}

	//it returns 64 bit signed integer, range[min,max]
	int64_t nextInt64(const int64_t min, const int64_t max) {
		if (min >= max) {
			ENG_LOG_ERROR("Error, Lagged Finonacci Generator64: max must be bigger than min [{0},{1}]", min, max);
			return 0;
		}

		int64_t value = (int64_t)nextUInt64();
		int64_t diff = max - min + 1;

		return min + value % diff;
	}

	// It returns 32 bit floating point
	float nextFloat() {
		uint64_t random = nextUInt64();

		return BitConverter::Ran32Flt1((uint32_t)random);
	}

	// It returns 64 bit floating point
	long double nextDouble() {
		uint64_t random = nextUInt64();
		int32_t random1 = (int32_t)random;
		int32_t random2 = (int32_t)(random >> 32);

		return BitConverter::Ran32Dbl1(random1, random2);
	}

};

