/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    spi.h
  * @brief   This file contains all the function prototypes for
  *          the spi.c file
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __SPI_H__
#define __SPI_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

extern SPI_HandleTypeDef hspi4;

/* USER CODE BEGIN Private defines */

// w5500_spi.h

#ifndef SRC_W5500_W5500_SPI_H_
#define SRC_W5500_W5500_SPI_H_

void W5500Init();
void Net_Conf();
void MutiIP_set(void);

void W5500_Send_UDP(void);
void UDP_Send(uint8_t *data, uint16_t len);

#endif /* SRC_W5500_W5500_SPI_H_ */


/* USER CODE END Private defines */

void MX_SPI4_Init(void);

/* USER CODE BEGIN Prototypes */

/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif

#endif /* __SPI_H__ */

