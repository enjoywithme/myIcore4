/*
 * FILE                : led.c
 * DESCRIPTION         : This file is led driver.
 * Author              : liu.
 * Copyright           :
 *
 * History
 * --------------------
 * Rev                 : 0.00
 * Date                : 06/13/2017
 *
 * create.
 * --------------------
 */
//--------------------------- Include ---------------------------//

#include "led.h"

#include "stm32f7xx_hal.h"

//--------------------- Function Prototype ----------------------//

static int initialize(void);

//--------------------------- Variable --------------------------//

LED_T led = {
	.initialize = initialize
};

//--------------------------- Function --------------------------//
/*
 * Name                : initialize
 * Description         : ---
 * Author              : liu.
 *
 * History
 * --------------------
 * Rev                 : 0.00
 * Date                : 06/13/2017
 * 
 * create.
 * --------------------
 */
static int initialize(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;

  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
	
	
  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_2, GPIO_PIN_SET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_9|GPIO_PIN_10, GPIO_PIN_SET);

  /*Configure GPIO pin : LEDR_Pin */
  GPIO_InitStruct.Pin = GPIO_PIN_2;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : LEDB_Pin LEDG_Pin */
  GPIO_InitStruct.Pin = GPIO_PIN_9|GPIO_PIN_10;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	return 0;
}
