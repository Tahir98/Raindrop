#include "BitConverter.h"

/* Constants and functions below are used to convert signed and unsigned integers to
		32 bit and 64 bit floating points, range[0,1)
		https://www.doornik.com/research/randomdouble.pdf
*/


#ifndef M_RAN_INVM32
#define M_RAN_INVM32 2.32830643653869628906e-010
#endif 

#ifndef M_RAN_INVM52
#define M_RAN_INVM52 2.22044604925031308085e-016
#endif 

//uint to float converter
float BitConverter::Ran32Flt1(uint32_t uiRan) {
	return (float)((int32_t)uiRan * M_RAN_INVM32 + 0.5);
}

//2 int to 1 double converter
long double BitConverter::Ran32Dbl1(int32_t iRan1, int32_t iRan2) {
	return ((int64_t)(iRan1)*M_RAN_INVM32 + (0.5 + M_RAN_INVM52 / 2) +
		(int64_t)((iRan2) & 0x000FFFFF) * M_RAN_INVM52);
}



