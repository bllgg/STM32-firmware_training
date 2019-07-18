#include "Driver/pkt_hndlr.h"
#include "stm32f4xx_hal.h"
#include <stdbool.h>
#include "usart.h"
#include "utils/lrc.h"

///////////////////////////////////////////////////////////////////////////////////
/*                           Private variables                                   */
///////////////////////////////////////////////////////////////////////////////////

DATA_PACKET packet;
static STATE state = STATE_SFD;
const uint8_t max_length = 6;
static uint8_t expected_length;
static uint8_t count = 0;
PACKET_NOTIFICATION_t packet_notification;
uint8_t rxData;
char sfd[3] = "sfd";
char len[3] = "len";
char pac[3] = "pac";
char crc[3] = "crc";
//const uint8_t initialVal = 0x00;
static uint8_t lrcVal = 0x00;

///////////////////////////////////////////////////////////////////////////////////
/*                        Public Function Definitions                            */
///////////////////////////////////////////////////////////////////////////////////

/**
 * @brief This function initializes the packet handler module.
 * @param pn - pass a function that calls from application module.s
 * @return System error type error.
 */
SystemError_t pkt_hndlr_init(PACKET_NOTIFICATION_t pn)
{
	SystemError_t ret = SystemError_NullPointer;
	
	do{
		if(pn == 0){
			break;
		}
		packet_notification = pn;
		HAL_UART_Receive_IT(&huart2, &rxData, 1);
		ret = SystemError_Success;
	}while(0);
	
	return ret;
}

/**
 * @brief This function handles every byte we receive from UART interrupt.
 * @param byte - analyses every byte thats received from UART.
 * @return nothing returns.
 * @knownBugs getting charactors
 */
void handle_packet(uint8_t byte){
	switch (state){
		case STATE_SFD:
			//HAL_UART_Transmit(&huart2, (uint8_t *)sfd, 3, 10);
			count = 0;
			if (255 == byte){
				state = STATE_LENGHT;///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				//HAL_GPIO_WritePin(GPIOD, GPIO_PIN_13, GPIO_PIN_SET);
			}else{
				state = STATE_SFD;
				
			}
			break;
		case STATE_LENGHT:
			//HAL_UART_Transmit(&huart2, (uint8_t *)len, 3, 10);
			if (byte > max_length){
				state = STATE_SFD;
			}else{
				state = STATE_COLLECT_PACKET;
				expected_length = byte;
			}
			break;
		case STATE_COLLECT_PACKET:
			//HAL_UART_Transmit(&huart2, (uint8_t *)pac, 3, 10);
			//HAL_UART_Transmit(&huart2, &count, 1, 10);
			lrcVal = calcLRC(lrcVal, byte);
			if (count < expected_length){
				switch (count){
					case 0:
						packet.type = byte;
						if (byte != 0){
							state = STATE_CRC;
						}else{
							state = STATE_COLLECT_PACKET;
						}
						break;
					case 1:
						packet.x_center = byte;
						break;
					case 2:
						packet.y_center = byte;
						break;
					case 3:
						packet.radius = byte;
						break;
					case 4:
						packet.x_point = byte;
						break;
					case 5:
						packet.y_point = byte;
						state = STATE_CRC;
						break;
				}
				count++;
			}else{
				state = STATE_CRC;
			}break;
		case STATE_CRC:
			state = STATE_SFD;
			if (lrcVal == byte){
				packet_notification(&packet);
			}
			lrcVal = 0x00;
			break;
	}
}

//UART packet handling function

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(huart);
  /* NOTE: This function Should not be modified, when the callback is needed,
           the HAL_UART_TxCpltCallback could be implemented in the user file
   */
	if(huart->Instance == huart2.Instance){
		handle_packet(rxData);
		HAL_UART_Receive_IT(&huart2, &rxData, 1);
		
	}
}

/**
 * @brief This function sends the result via UART by adding headers.
 * @param rseult- processed result
 * @return nothing returns.
 */
void sendPacket(uint8_t result){
	uint8_t LRC = calcLRC(lrcVal,result);
	uint8_t data[4] = {0xFF, 0x01, result, LRC};
	HAL_UART_Transmit(&huart2, (uint8_t *)data, 4, 10);
}
