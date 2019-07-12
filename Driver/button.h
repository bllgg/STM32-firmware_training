#ifndef _BUTTON_H
#define _BUTTON_H

#include "gpio.h"
#include "stm32f4xx_hal.h"
#include "Utils/error.h"

// defining few button ids.
typedef enum{
	BTN_ID_1 = 0,
	BTN_ID_2,
}BTN_ID_t;


typedef void (*BUTTON_EVENT_CB_t) (BTN_ID_t btn_id);

///////////////////////////////////////////////////////////////////////////////////
/*                                  Public APIs                                  */
///////////////////////////////////////////////////////////////////////////////////
SystemError_t btn_init(BUTTON_EVENT_CB_t cb);
#endif
