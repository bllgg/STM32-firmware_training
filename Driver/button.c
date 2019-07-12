
#include "Driver/button.h"
#include "Utils/error.h"
///////////////////////////////////////////////////////////////////////////////////
/*                             Private variables                                 */
///////////////////////////////////////////////////////////////////////////////////

BUTTON_EVENT_CB_t g_btn_evnt_app_cb;// uses for accept a function from application module.


///////////////////////////////////////////////////////////////////////////////////
/*                        Public Function Definitions                            */
///////////////////////////////////////////////////////////////////////////////////

/**
 * @brief This function initialize the buttton module.
 * @param cb - this is a function(parameter is button_id and nothing returns.) that passed from application module.
 * @return ret - SystemError_t type error value.
 */
SystemError_t btn_init(BUTTON_EVENT_CB_t cb)
{
	SystemError_t ret = SystemError_NullPointer;
	do{
		if(cb == 0)
			break;
		
		g_btn_evnt_app_cb = cb;
		ret = SystemError_Success;
	}while(0);
	
	return ret;
}

///////////////////////////////////////////////////////////////////////////////////
/*                        Private Function Definitions                           */
///////////////////////////////////////////////////////////////////////////////////

//Exernal interrupt handling function.
void HAL_GPIO_EXTI_Callback(uint16_t gpio_pin_mask)
{
	
	BTN_ID_t btn_id = BTN_ID_1;
	if (g_btn_evnt_app_cb != 0){
		g_btn_evnt_app_cb(btn_id);
	}
}
