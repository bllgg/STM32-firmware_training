#ifndef _LED_H
#define _LED_H
#include "stm32f4xx_hal.h"
///////////////////////////////////////////////////////////////////////////////////
/*                                  Public APIs                                  */
///////////////////////////////////////////////////////////////////////////////////
void led_init();
void led_blink(int);
void led_on(void);
void led_off(void);

#endif