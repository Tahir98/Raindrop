#pragma once
#include "Random.h"
#include <cmath>

class MultiplyWithCarry : public Random {
private:
	uint64_t a;
	uint64_t b;
	uint32_t power;
	uint32_t c;

	uint32_t value = 123456789; //Default seed
	uint32_t size = 10; //State vector size, default is 1, lag-1,
	uint32_t index = 0; //State vector index
	uint32_t* sv = nullptr;//State vector stores previous values of mwc,intial values is produced by myself using seed
	//if size is 1 than no need to be use state vector, there is only one previous value. At the beginning, previous value is the seed
public:
	MultiplyWithCarry(bool useTimeAsSeed = true){
		a = (uint32_t)(std::pow(2,32) - 178);
		b = (uint64_t)std::pow(2,32);
		power = 32;
		c = 97;

		if(size > 1) {
			sv = new uint32_t[size];
			sv[0] = value;
			for (unsigned int i = 1; i < size; i++) {
				sv[i] = 181243323UL * (sv[i - 1] ^ (sv[i - 1] >> 30)) + i;
			}
			index = 0;
		}

		if (useTimeAsSeed) {
			std::chrono::steady_clock::time_point now = std::chrono::high_resolution_clock::now();

			auto time = now.time_since_epoch();
			auto time_cast = std::chrono::duration_cast<std::chrono::nanoseconds>(time);
			value = (uint32_t)time_cast.count();
		}
	}

	MultiplyWithCarry(const uint32_t seed): value(seed) {
		a = (uint32_t)(std::pow(2, 32) - 178);	  //
		b = (uint64_t)std::pow(2, 32);
		power = 32;//Default parameters
		c = 97;			
		
		if (size > 1) {
			sv = new uint32_t[size];
			sv[0] = value;
			for (unsigned int i = 1; i < size; i++) {
				sv[i] = 181243323UL * (sv[i - 1] ^ (sv[i - 1] >> 30)) + i;
			}
			index = 0;
		}
	}											 

	~MultiplyWithCarry() {
		delete sv;
	}

	
	/*state vector size*/
	void setSize(uint32_t size) {
		if (size == 0) {
			ENG_LOG_ERROR("Multply With Carry: state vector size must be at least 1");
			return;
		}
		this->size = size;

		if (size > 1) {
			delete sv;
			sv = new uint32_t[size];
			sv[0] = value;
			for (unsigned int i = 1; i < size; i++) {
				sv[i] = 181243323UL * (sv[i - 1] ^ (sv[i - 1] >> 30)) + i;
			}
			index = 0;
		}
	}

	/*set initial value that will be used to calculate random values*/
	void setSeed(const uint32_t seed) override {
		if (size > 1) {
			delete sv;
			sv = new uint32_t[size];
			sv[0] = seed;
			for (unsigned int i = 1; i < size; i++) {
				sv[i] = 181243323UL * (sv[i - 1] ^ (sv[i - 1] >> 30)) + i;
			}
			index = 0;
			c = 97;
		}
		else {
			value = seed;
			c = 97;
		}
		
	}

	void setParameters(const uint32_t a, const uint32_t power, const uint32_t c) {
		if (a == 0 || power == 0) {
			ENG_LOG_ERROR("a and b must be bigger than 1");
			return;
		}
		else if (power > 64) {
			ENG_LOG_ERROR("b must be smaller or equal than 64");
		}
		
		this->a = a;
		this->b = b;
		this->c = c;
	}

	/* It returns 32 bit unsigned integer*/
	uint32_t nextUInt() override {
		uint32_t result = 0;
		if (size == 1) {
			result = (uint32_t)((a * value + c) % b);
			c = ((uint32_t)(a * value + c) >> power);
		}
		else {
			value = sv[index];
			result = (uint32_t)((a * value + c) % b);
			c = (uint32_t)((a * value + c) >> power);
			sv[index++] = result;
		}

		if (index >= size)
			index -= size;

		value = result;
		return value;
	}

	/* It returns 32 bit unsigned integer, range[min, max]*/
	uint32_t nextUInt(const uint32_t min, const uint32_t max) override {
		if (min >= max) {
			ENG_LOG_ERROR("Multiply With Carry: Max must be bigger than min");
			return 0;
		}

		uint32_t result = 0;
		if (size == 1) {
			result = (uint32_t)((a * value + c) % b);
			c = ((uint32_t)(a * value + c) >> power);
		}
		else {
			value = sv[index];
			result = (uint32_t)((a * value + c) % b);
			c = (uint32_t)((a * value + c) >> power);
			sv[index++] = result;
		}

		if (index >= size)
			index -= size;

		value = result;

		uint32_t diff = max - min + 1;

		return min + value % diff;
	}

};