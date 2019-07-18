#include "stm32f4xx_hal.h"
#include "utils/lrc.h"

///////////////////////////////////////////////////////////////////////////////////
/*                         Public APIs Definition                                */
///////////////////////////////////////////////////////////////////////////////////

/**
 * @brief This function returns the bitwise XOR value of the given two values.
 * @param prev- one byte long value
 * @param byte- one byte long value
 * @return bitwise XOR value of given two numbers.
 */
uint8_t calcLRC(uint8_t prev, uint8_t byte){
	return (prev^byte);
}
