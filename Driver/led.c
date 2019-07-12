#include "Driver/led.h"
#include "stm32f4xx_hal.h"
#include "tim.h"

///////////////////////////////////////////////////////////////////////////////////
/*                           Private variables                                   */
///////////////////////////////////////////////////////////////////////////////////

static int Number_of_Blinks;
static int count = 0;

///////////////////////////////////////////////////////////////////////////////////
/*                        Private Function References                            */
///////////////////////////////////////////////////////////////////////////////////

void StartTimer(void);
void StopTimer(void);
///////////////////////////////////////////////////////////////////////////////////
/*                        Public Function Definitions                            */
///////////////////////////////////////////////////////////////////////////////////

/**
 * @brief This function blinks the LED for a given number of times.
 * @param no_of_blinks - enter the number of times that need to be blinked the LED.
 * @return no return parameters.
 */
void led_blink(int no_of_blinks){
	Number_of_Blinks = no_of_blinks*2;
	StartTimer();
}

/**
 * @brief This function turns on the blue LED light.
 * @param no input parameteres.
 * @return no return parameters.
 */
void led_on(void){
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, GPIO_PIN_SET);
}

/**
 * @brief This function turns off the blue LED light.
 * @param no input parameteres.
 * @return no return parameters.
 */
void led_off(void){
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, GPIO_PIN_RESET);
}

/**
 * @brief This function initializes the LED module.
 * @param no input parameteres.
 * @return no return parameters.
 */
void led_init(){
	led_on();
	HAL_Delay(1000);
	led_off();
	
	//__HAL_TIM_SET_PRESCALER(&htim2,7999);
}

///////////////////////////////////////////////////////////////////////////////////
/*                        Private Function Definitions                           */
///////////////////////////////////////////////////////////////////////////////////

/**
 * @brief This function starts the timer 2.
 * @param no parameters.
 * @return no return parameters.
 */
void StartTimer()
{
	HAL_TIM_Base_Start_IT(&htim2);
}

/**
 * @brief This function stops the timer 2.
 * @param no parameteres.
 * @return no return parameteres.
 */
void StopTimer()
{
	HAL_TIM_Base_Stop_IT(&htim2);
}

//Timer interrut handling function
 void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	
	if((htim->Instance==TIM2)&&(count<Number_of_Blinks))
	{
		HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_15);
		count++;
	}
	else{
		count=0;
		StopTimer();
	}
}
