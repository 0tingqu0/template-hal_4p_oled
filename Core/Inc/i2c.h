/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file    i2c.h
 * @brief   This file contains all the function prototypes for
 *          the i2c.c file
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
#ifndef __I2C_H__
#define __I2C_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

extern I2C_HandleTypeDef hi2c1;

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

void MX_I2C1_Init(void);

/* USER CODE BEGIN Prototypes */
void HAL_I2C_WriteCommand(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint8_t Control_bytes, uint8_t Command);
void HAL_I2C_WriteData(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint8_t Control_bytes, uint8_t *Data, uint8_t DataLength);
void HAL_I2C_DMA_WriteCommand(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint8_t Control_bytes, uint8_t Command);
void HAL_I2C_DMA_WriteData(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint8_t Control_bytes, uint8_t Command);
/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif

#endif /* __I2C_H__ */

