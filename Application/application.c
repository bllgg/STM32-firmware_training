#include "Application/application.h"
#include "Driver/button.h"
#include "Driver/led.h"

///////////////////////////////////////////////////////////////////////////////////
/*                        Private Function References                            */
///////////////////////////////////////////////////////////////////////////////////
void button_pressed(BTN_ID_t btn_id);

///////////////////////////////////////////////////////////////////////////////////
/*                        Public Function Definitions                            */
///////////////////////////////////////////////////////////////////////////////////

/**
 * @brief This function initializes the application module.
 * @param no inut parameters.
 * @return no return parameters.
 */
void app_init()
{
	// button and led modules will be initialized.
	btn_init(button_pressed);
	led_init();
}

/**
 * @brief This function runs the appliation.
 * @param no input parameters
 * @return no return parameters.
 */
void app_run(void)
{
	// nothing happens here for right now.
}

///////////////////////////////////////////////////////////////////////////////////
/*                        Private Function Definitions                           */
///////////////////////////////////////////////////////////////////////////////////

/**
 * @brief This function checks the pressed button and select suitable action.
 * @param button_id - pass the id of the button because each utton assigned to various activities.
 * @return nothing.
 */
void button_pressed(BTN_ID_t button_id){
	
	// if button id is equals to TN_ID_1 led will blinks three times
	if (button_id == BTN_ID_1){
		led_blink(3); 
	}
}
