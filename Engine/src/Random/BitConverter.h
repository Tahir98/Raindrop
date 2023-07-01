#pragma once
#include <cstdint>

/* Constants and functions below are used to convert sing and unsigned integers to
		32 bit and 64 bit floating points, range[0,1)
		https://www.doornik.com/research/randomdouble.pdf
*/

class BitConverter {
public:
	//uint to float converter
	static float Ran32Flt1(uint32_t uiRan);

	//2 int to 1 double converter
	static long double Ran32Dbl1(int32_t iRan1, int32_t iRan2);
};
