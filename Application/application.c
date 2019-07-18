#include "Application/application.h"
#include "Driver/button.h"
#include "Driver/led.h"
#include "Driver/pkt_hndlr.h"
#include "Application/cmd_hndlr.h"
#include <stdbool.h>

///////////////////////////////////////////////////////////////////////////////////
/*                        Private Function References                            */
///////////////////////////////////////////////////////////////////////////////////

static bool packet_ready = 0; //flag to notify data is ready
static DATA_PACKET data_packet;
bool process_status = 0;

///////////////////////////////////////////////////////////////////////////////////
/*                        Private Function References                            */
///////////////////////////////////////////////////////////////////////////////////
void button_pressed(BTN_ID_t btn_id);
void packet_captured(DATA_PACKET* packet);

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
	pkt_hndlr_init(packet_captured);
}

/**
 * @brief This function runs the appliation.
 * @param no input parameters
 * @return no return parameters.
 */
void app_run(void)
{
	if (1 == packet_ready){
		process_packet(&data_packet);
		packet_ready = 0;
	}
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

/**
 * @brief This function sets the packet_ready flag to 1 when a packet is captured.
 * @param packet - passed data packet will be stored in data_packet static variable.
 * @return nothing.
 */
void packet_captured(DATA_PACKET* packet){
	//set the flag to inform ready to process the packet.
	packet_ready = 1;
	data_packet = *packet;
	//HAL_GPIO_WritePin(GPIOD, GPIO_PIN_14, GPIO_PIN_SET);
}
