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

void StartTimer();
void StopTimer();
///////////////////////////////////////////////////////////////////////////////////
/*                        Public Function Definitions                            */
///////////////////////////////////////////////////////////////////////////////////
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(GPIO_Pin);
	led_blink(3);
  /* NOTE: This function should not be modified, when the callback is needed,
            the HAL_GPIO_EXTI_Callback could be implemented in the user file
   */ 
}

//Blink the LED given numer of times
void led_blink(int no_of_blinks){
	Number_of_Blinks = no_of_blinks*2;
	StartTimer();
}

//Turn on the LED
void led_on(void){
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, 1);
}

//Turn off the LED
void led_off(void){
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, 0);
}

// testing LED
void led_init(){
	//htimVar = htim;
	led_on();
	HAL_Delay(1000);
	led_off();
}

void StartTimer()
{
	HAL_TIM_Base_Start_IT(&htim2);
}

void StopTimer()
{
	HAL_TIM_Base_Stop_IT(&htim2);
}

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

///////////////////////////////////////////////////////////////////////////////////
/*                        Public Function Definitions                            */
///////////////////////////////////////////////////////////////////////////////////
