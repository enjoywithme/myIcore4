/**
  ******************************************************************************
  * @file    udp_echoclient.h
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    31-October-2011 
  * @brief   Header file for udp_echoclient.c
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/  
#ifndef __UDP_ECHOCLIENT_H__
#define __UDP_ECHOCLIENT_H__

/* Includes ------------------------------------------------------------------*/
#include "lwip/pbuf.h"
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void udp_echoclient_Send(struct pbuf *p);

#endif /* __UDP_ECHOCLIENT_H__ */


/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
