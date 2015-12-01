
/** \file
	\brief Analog subsystem
*/

#include "analog.h"

#define TEACUP_C_INCLUDE
#include "analog-avr.c"
#include "analog-arm_lpc11xx.c"
#include "analog-arm_stm32f4xx.c"
#undef TEACUP_C_INCLUDE

// No common code so far.
