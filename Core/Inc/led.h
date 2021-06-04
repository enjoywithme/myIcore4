/*
 * FILE                : led.h
 * DESCRIPTION         : This file is for led.c
 * Author              : zh.
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
#ifndef __led_h__
#define __led_h__

//--------------------------- Define ---------------------------//

#define LED_RED_ON HAL_GPIO_WritePin(GPIOB, GPIO_PIN_2, GPIO_PIN_RESET)
#define LED_RED_OFF HAL_GPIO_WritePin(GPIOB, GPIO_PIN_2, GPIO_PIN_SET)

#define LED_BLUE_ON HAL_GPIO_WritePin(GPIOA, GPIO_PIN_9, GPIO_PIN_RESET)
#define LED_BLUE_OFF HAL_GPIO_WritePin(GPIOA, GPIO_PIN_9, GPIO_PIN_SET)

#define LED_GREEN_ON HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10, GPIO_PIN_RESET)
#define LED_GREEN_OFF HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10, GPIO_PIN_SET)

//----------------------- Include files ------------------------//

//-------------------------- Typedef----------------------------//
typedef struct {
	int (* initialize)(void);
}LED_T;

//--------------------------- Extern ---------------------------//
extern LED_T led;

#endif //__led_h__
