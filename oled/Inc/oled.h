/*
 * oled.h
 *
 *  Created on: Mar 16, 2025
 *      Author: zhang
 */

#ifndef INC_OLED_H_
#define INC_OLED_H_

#include "main.h"
#include <stdio.h>
#include "i2c.h"

void Oled_Init(I2C_HandleTypeDef *hi2c);
void OLED_Clear(I2C_HandleTypeDef *hi2c);
void OLED_SetCursor(I2C_HandleTypeDef *hi2c, uint8_t Page, uint8_t X);
void OLED_ShowChar(I2C_HandleTypeDef *hi2c, uint8_t X, uint8_t Y, char Char, uint8_t FontSize);
void OLED_ShowString(I2C_HandleTypeDef *hi2c, uint8_t X, uint8_t Y, char *String, uint8_t FontSize);
void OLED_ShowNum(I2C_HandleTypeDef *hi2c, uint8_t X, uint8_t Y, uint32_t Number, uint8_t Length, uint8_t FontSize);
void OLED_ShowImage(I2C_HandleTypeDef *hi2c, uint8_t X, uint8_t Y, uint8_t Width, uint8_t Height, const uint8_t *Image);

#endif /* INC_OLED_H_ */
