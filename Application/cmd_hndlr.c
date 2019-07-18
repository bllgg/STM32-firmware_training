#include "Application/cmd_hndlr.h"
#include "Driver/led.h"
#include <stdbool.h>
#include "usart.h"
#include "Driver/pkt_hndlr.h"

static int sq_dist;
static uint8_t result;

///////////////////////////////////////////////////////////////////////////////////
/*                        Public Function Definitions                            */
///////////////////////////////////////////////////////////////////////////////////

/**
 * @brief This function processes a given data packet
 * @param packet - processed data packet that contain command type, x and y coordinates of the center, radius and x and y coordinates of point.
 * @return nothing returns, but process the packet and give commands to hardware layer..
 */

void process_packet(DATA_PACKET *packet){
		if (0 == packet -> type){
			sq_dist = ((packet -> x_center - packet -> x_point)*(packet -> x_center - packet -> x_point)) + ((packet -> y_center - packet -> y_point)*(packet -> y_center - packet -> y_point));
			if (sq_dist <= (packet->radius * packet->radius)){
				result = 0x01;
			}else{
				result = 0x00;
			}
			transmit_packet(result);
		}
		else if(1 == packet -> type){
			// turn on the light
			led_on();
		}
		else if(2 == packet -> type){
			//turn off the light
			led_off();
		}
	
}

///////////////////////////////////////////////////////////////////////////////////
/*                              Private functions                                */
///////////////////////////////////////////////////////////////////////////////////

/**
 * @brief This function transmit the processed result to the packet handler module
 * @param result- processed result
 * @return nothing returns
 */
void transmit_packet(uint8_t result){
	//write data on HAL layer
	sendPacket(result);
	
}
