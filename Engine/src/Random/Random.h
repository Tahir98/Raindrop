#pragma once
#include <stdint.h>
#include "Log.h"
#include "BitConverter.h"

class Random {
public:
	virtual void setSeed(uint32_t seed) {  }
	virtual uint32_t nextUInt(){ return 0; }
	virtual uint32_t nextUInt(const uint32_t min, const uint32_t max) { return 0; }
	
	/* @return int32_t */
	int32_t nextInt(){ 
		int32_t value = (int32_t)nextUInt();
		return value;
	}

	int32_t nextInt(const int32_t min,const int32_t max){ 
		if (min >= max) {
			ENG_LOG_ERROR("Error, max must be bigger than min [{0},{1}]", min, max);
			return 0;
		}

		uint32_t value = nextUInt();
		int32_t diff = max - min + 1;

		return min + value % diff;
	}
	
	float nextFloat(){ 
		uint32_t random = nextUInt();
		return BitConverter::Ran32Flt1(random);
	}

	long double nextDouble(){
		int32_t random1 = nextInt();
		int32_t random2 = nextInt();

		return BitConverter::Ran32Dbl1(random1, random2);
	}
};