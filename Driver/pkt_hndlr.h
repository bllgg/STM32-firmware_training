#ifndef _PKT_HNDLR_H
#define _PKT_HNDLR_H

#include "utils/error.h"
#include "stm32f4xx_hal.h"

typedef struct{
	uint8_t type; // "0" for calculation, "l" for light on and "2" for light off.
	uint8_t x_center;
	uint8_t y_center;
	uint8_t radius;
	uint8_t x_point;
	uint8_t y_point;
} DATA_PACKET;

typedef enum{
	STATE_SFD,
	STATE_LENGHT,
	STATE_COLLECT_PACKET,
	STATE_CRC
} STATE;

typedef void (*PACKET_NOTIFICATION_t) (DATA_PACKET* packet);

///////////////////////////////////////////////////////////////////////////////////
/*                                  Public APIs                                  */
///////////////////////////////////////////////////////////////////////////////////

SystemError_t pkt_hndlr_init(PACKET_NOTIFICATION_t pn);
void sendPacket(uint8_t result);

///////////////////////////////////////////////////////////////////////////////////
/*                              Private functions                                */
///////////////////////////////////////////////////////////////////////////////////

void handle_packet(uint8_t byte);

#endif
