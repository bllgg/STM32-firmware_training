#ifndef _CMD_HNDLR_H
#define _CMD_HNDLR_H

#include "Utils/error.h"
#include "Driver/pkt_hndlr.h"

///////////////////////////////////////////////////////////////////////////////////
/*                                  Public APIs                                  */
///////////////////////////////////////////////////////////////////////////////////
void process_packet(DATA_PACKET *packet);

///////////////////////////////////////////////////////////////////////////////////
/*                              Private functions                                */
///////////////////////////////////////////////////////////////////////////////////
void transmit_packet(uint8_t);

#endif
