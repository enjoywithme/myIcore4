/**
 ******************************************************************************
 * @file    usart.c
 * @brief   This file provides code for the configuration
 *          of the USART instances.
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
 * All rights reserved.</center></h2>
 *
 * This software component is licensed by ST under Ultimate Liberty license
 * SLA0044, the "License"; You may not use this file except in compliance with
 * the License. You may obtain a copy of the License at:
 *                             www.st.com/SLA0044
 *
 ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "usart6.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include <ctype.h>
#include <math.h>
#include <stdarg.h>
#define SERIAL_DEBUG
//--------------------- Function Prototype ----------------------//

static int send_string_to_usart6(char *str);
static int initialize_usart6(unsigned long int baudrate);
static int my_printf6(const char *fmt, ...);

//--------------------------- Variable --------------------------//

UART_T usart6 = {
		.receive_ok_flag = 0,
		.counter = 0,
		.send_string = send_string_to_usart6,
		.initialize = initialize_usart6,
		.printf = my_printf6
	};

UART_HandleTypeDef huart6;

/* USART6 init function */

int initialize_usart6(unsigned long int baudrate) {

	/* USER CODE BEGIN USART6_Init 0 */

	/* USER CODE END USART6_Init 0 */

	/* USER CODE BEGIN USART6_Init 1 */

	/* USER CODE END USART6_Init 1 */
	huart6.Instance = USART6;
	huart6.Init.BaudRate = baudrate;
	huart6.Init.WordLength = UART_WORDLENGTH_8B;
	huart6.Init.StopBits = UART_STOPBITS_1;
	huart6.Init.Parity = UART_PARITY_NONE;
	huart6.Init.Mode = UART_MODE_TX_RX;
	huart6.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	huart6.Init.OverSampling = UART_OVERSAMPLING_16;
	huart6.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
	huart6.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
	if (HAL_UART_Init(&huart6) != HAL_OK) {
		Error_Handler();
		return 1;
	}
	HAL_UART_Receive_IT(&huart6, (unsigned char*) &usart6.receive_data, 1);
	return 0;

}

static int send_string_to_usart6(char *str) {
	while (*str != '\0') {
		while (!(__HAL_UART_GET_FLAG(&huart6,UART_FLAG_TC) == 1));
		HAL_UART_Transmit(&huart6, (unsigned char*) str++, 1, 1000);
	}

	return 0;
}

void USART6_IRQHandler(void) {
	HAL_UART_IRQHandler(&huart6);

	while (HAL_UART_GetState(&huart6) != HAL_UART_STATE_READY)
		;
	while (HAL_UART_Receive_IT(&huart6, (unsigned char*) &usart6.receive_data,
			1) != HAL_OK)
		;
	usart6.receive_buffer[usart6.counter++] = usart6.receive_data;

	if (usart6.receive_buffer[usart6.counter - 1] == '\n'
			&& usart6.receive_buffer[usart6.counter - 2] == '\r') {
		usart6.receive_buffer[usart6.counter - 1] = 0;
		usart6.counter = 0;
		usart6.receive_ok_flag = 1;
	}
}

static int my_printf6(const char *fmt, ...) {
	__va_list arg_ptr;
	char buf[UART_BUFFER_SIZE];

	memset(buf, '\0', sizeof(buf));

	va_start(arg_ptr, fmt);
	vsprintf(buf, fmt, arg_ptr);
	va_end(arg_ptr);

	send_string_to_usart6(buf);

	return 0;
}

void HAL_UART_MspInit(UART_HandleTypeDef *uartHandle) {

	GPIO_InitTypeDef GPIO_InitStruct = { 0 };
	if (uartHandle->Instance == USART6) {
		/* USER CODE BEGIN USART6_MspInit 0 */

		/* USER CODE END USART6_MspInit 0 */
		/* USART6 clock enable */
		__HAL_RCC_USART6_CLK_ENABLE();

		__HAL_RCC_GPIOC_CLK_ENABLE();
		/**USART6 GPIO Configuration
		 PC6     ------> USART6_TX
		 PC7     ------> USART6_RX
		 */
		GPIO_InitStruct.Pin = GPIO_PIN_6 | GPIO_PIN_7;
		GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
		GPIO_InitStruct.Alternate = GPIO_AF8_USART6;
		HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

		/* USART6 interrupt Init */
		HAL_NVIC_SetPriority(USART6_IRQn, 1, 0);
		HAL_NVIC_EnableIRQ(USART6_IRQn);
		/* USER CODE BEGIN USART6_MspInit 1 */

		/* USER CODE END USART6_MspInit 1 */
	}
}

void HAL_UART_MspDeInit(UART_HandleTypeDef *uartHandle) {

	if (uartHandle->Instance == USART6) {
		/* USER CODE BEGIN USART6_MspDeInit 0 */

		/* USER CODE END USART6_MspDeInit 0 */
		/* Peripheral clock disable */
		__HAL_RCC_USART6_CLK_DISABLE();

		/**USART6 GPIO Configuration
		 PC6     ------> USART6_TX
		 PC7     ------> USART6_RX
		 */
		HAL_GPIO_DeInit(GPIOC, GPIO_PIN_6 | GPIO_PIN_7);

		/* USART6 interrupt Deinit */
		HAL_NVIC_DisableIRQ(USART6_IRQn);
		/* USER CODE BEGIN USART6_MspDeInit 1 */

		/* USER CODE END USART6_MspDeInit 1 */
	}
}

/* USER CODE BEGIN 1 */
/**
 * @brief  Retargets the C library printf function to the USART.
 * @param  None
 * @retval None
 */
#ifdef SERIAL_DEBUG

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#ifdef __GNUC__
/* With GCC/RAISONANCE, small printf (option LD Linker->Libraries->Small printf
 set to 'Yes') calls __io_putchar() */
#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif /* __GNUC__ */

PUTCHAR_PROTOTYPE {
	/* Place your implementation of fputc here */
	/* e.g. write a character to the USART */
	while (!(__HAL_UART_GET_FLAG(&huart6,UART_FLAG_TC) == 1));
	HAL_UART_Transmit(&huart6, (uint8_t *) &ch, 1, 1000);

	return ch;
}
#endif /* SERIAL_DEBUG */
/* USER CODE END 1 */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
