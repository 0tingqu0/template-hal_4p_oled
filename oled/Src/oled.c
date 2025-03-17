/*
 * oled.c
 *
 *  Created on: Mar 16, 2025
 *      Author: zhang
 */

/*
 *本驱动文件仅适配HAL库版本
 */
#include "oled.h"       //声明
#include "Font.h"    //字库文件

#define OLED_I2C_ADDRESS 0x3c
#define OLED_CMD        0x00
#define OLED_DATA          0x40

 uint8_t init_cmds[] = {
        0xAE, // 关闭显示
        0xD5, 0x80, // 设置显示时钟分频
        0xA8, 0x3F, // 设置多路复用比率
        0xD3, 0x00, // 设置显示偏移
        0x40, // 设置显示起始行
        0xA1, // 设置段重映射（正常方向）
        0xC8, // 设置 COM 扫描方向（正常方向）
        0xDA, 0x12, // 设置 COM 引脚硬件配置
        0x81, 0xCF, // 设置对比度
        0xD9, 0xF1, // 设置预充电周期
        0xDB, 0x30, // 设置 VCOMH 电压
        0xA4, // 设置整个显示开启
        0xA6, // 设置正常显示（非反色）
        0x8D, 0x14, // 设置电荷泵
        0xAF // 开启显示
    };
/*
 *Prototype        : void OLED_Init(void)
 *Parameters     : none
 *return             : none
 *Description    : 初始化OLED模块（不难发现，其实都是一些向0x00写入的命令）
 */
void Oled_Init(I2C_HandleTypeDef *hi2c)
{
        // 1. 关闭显示
        HAL_I2C_WriteCommand(hi2c, OLED_I2C_ADDRESS, OLED_CMD,0xAE); // 关闭显示

        // 2. 设置显示时钟分频
        HAL_I2C_WriteCommand(hi2c, OLED_I2C_ADDRESS, OLED_CMD,0xD5); // 设置显示时钟分频
        HAL_I2C_WriteCommand(hi2c, OLED_I2C_ADDRESS,OLED_CMD, 0x80); // 分频值

        // 3. 设置多路复用比率
        HAL_I2C_WriteCommand(hi2c, OLED_I2C_ADDRESS, OLED_CMD,0xA8); // 设置多路复用比率
        HAL_I2C_WriteCommand(hi2c, OLED_I2C_ADDRESS,OLED_CMD, 0x3F); // 比率值（64MUX）

        // 4. 设置显示偏移
        HAL_I2C_WriteCommand(hi2c, OLED_I2C_ADDRESS, OLED_CMD,0xD3); // 设置显示偏移
        HAL_I2C_WriteCommand(hi2c, OLED_I2C_ADDRESS,OLED_CMD, 0x00); // 偏移值

        // 5. 设置起始行
        HAL_I2C_WriteCommand(hi2c, OLED_I2C_ADDRESS,OLED_CMD, 0x40); // 设置起始行

        // 6. 设置电荷泵
        HAL_I2C_WriteCommand(hi2c, OLED_I2C_ADDRESS, OLED_CMD,0x8D); // 设置电荷泵
        HAL_I2C_WriteCommand(hi2c, OLED_I2C_ADDRESS,OLED_CMD, 0x14); // 启用电荷泵

        // 7. 设置内存地址模式
        HAL_I2C_WriteCommand(hi2c, OLED_I2C_ADDRESS, OLED_CMD,0x20); // 设置内存地址模式
        HAL_I2C_WriteCommand(hi2c, OLED_I2C_ADDRESS,OLED_CMD, 0x00); // 水平地址模式

        // 8. 设置段重映射
        HAL_I2C_WriteCommand(hi2c, OLED_I2C_ADDRESS, OLED_CMD,0xA1); // 段重映射（0xA1 或 0xA0）

        // 9. 设置 COM 扫描方向
        HAL_I2C_WriteCommand(hi2c, OLED_I2C_ADDRESS, OLED_CMD,0xC8); // COM 扫描方向（0xC8 或 0xC0）

        // 10. 设置对比度
        HAL_I2C_WriteCommand(hi2c, OLED_I2C_ADDRESS,OLED_CMD, 0x81); // 设置对比度
        HAL_I2C_WriteCommand(hi2c, OLED_I2C_ADDRESS,OLED_CMD, 0xCF); // 对比度值

        // 11. 设置预充电周期
        HAL_I2C_WriteCommand(hi2c, OLED_I2C_ADDRESS,OLED_CMD, 0xD9); // 设置预充电周期
        HAL_I2C_WriteCommand(hi2c, OLED_I2C_ADDRESS, OLED_CMD,0xF1); // 预充电周期值

        // 12. 设置 VCOMH 电压
        HAL_I2C_WriteCommand(hi2c, OLED_I2C_ADDRESS, OLED_CMD,0xDA); // 设置 VCOMH 电压
        HAL_I2C_WriteCommand(hi2c, OLED_I2C_ADDRESS, OLED_CMD,0x12); // VCOMH 电压值

        // 13. 设置整个显示开启
        HAL_I2C_WriteCommand(hi2c, OLED_I2C_ADDRESS, OLED_CMD,0xA4); // 设置整个显示开启

        // 14. 设置非反色显示
        HAL_I2C_WriteCommand(hi2c, OLED_I2C_ADDRESS, OLED_CMD,0xA6); // 设置非反色显示

        // 15. 打开显示
        HAL_I2C_WriteCommand(hi2c, OLED_I2C_ADDRESS, OLED_CMD,0xAF); // 打开显示

        OLED_Clear(&hi2c1);
}

/**
  * 函    数：OLED 清屏
  * 参    数：hi2c，I2C 句柄（hi2c1, hi2c2, ...）
  * 返 回 值：无
  */
void OLED_Clear(I2C_HandleTypeDef *hi2c)
{
    uint8_t empty[128] = {0}; // 128 字节的空数据
    for (uint8_t i = 0; i < 8; i++) {
        OLED_SetCursor(hi2c, i, 0); // 设置光标位置
        HAL_I2C_WriteData(hi2c, OLED_I2C_ADDRESS, OLED_DATA, empty, 128); // 写入空数据
    }
}

/**
  * 函    数：OLED 设置光标位置
  * 参    数：hi2c，I2C 句柄（hi2c1, hi2c2, ...）
  * 参    数：Page，页地址（0~7）8移一格
  * 参    数：X，列地址（0~127）
  * 返 回 值：无
  */
void OLED_SetCursor(I2C_HandleTypeDef *hi2c, uint8_t Page, uint8_t X)
{
    HAL_I2C_WriteCommand(hi2c, OLED_I2C_ADDRESS, OLED_CMD, 0xB0 | Page); // 设置页地址
    HAL_I2C_WriteCommand(hi2c, OLED_I2C_ADDRESS, OLED_CMD, 0x10 | ((X & 0xF0) >> 4)); // 设置列地址高 4 位
    HAL_I2C_WriteCommand(hi2c, OLED_I2C_ADDRESS, OLED_CMD, 0x00 | (X & 0x0F)); // 设置列地址低 4 位
}

/**
  * 函    数：OLED 显示字符
  * 参    数：hi2c，I2C 句柄（hi2c1, hi2c2, ...）
  * 参    数：X，字符左上角的横坐标（0~127）
  * 参    数：Y，字符左上角的纵坐标（0~63）8移一格
  * 参    数：Char，要显示的字符
  * 参    数：FontSize，字体大小（8 或 16）
  * 返 回 值：无
  */
void OLED_ShowChar(I2C_HandleTypeDef *hi2c, uint8_t X, uint8_t Y, char Char, uint8_t FontSize)
{
    const uint8_t *font = (FontSize == 8) ? F6X8 : F8X16; // 选择字库
    uint8_t height = (FontSize == 8) ? 8 : 16; // 字符高度
    const uint8_t width = (FontSize == 8) ? 6 : 8; // 字符宽度

    // 检查字符是否在有效范围内
    if (Char < ' ' || Char > '~') {
        return; // 如果字符不在有效范围内，直接返回
    }

    // 遍历字符的每一列
    for (uint8_t i = 0; i < width; i++) {
        uint8_t data = font[(Char - ' ') * width + i]; // 获取字模数据
        OLED_SetCursor(hi2c, Y / (height / 8), X + i); // 设置光标位置
        HAL_I2C_Mem_Write(hi2c, OLED_I2C_ADDRESS, OLED_DATA, 1, &data, 1, 100); // 写入数据
    }
}

/**
  * 函    数：OLED 显示字符串
  * 参    数：hi2c，I2C 句柄（hi2c1, hi2c2, ...）
  * 参    数：X，字符串左上角的横坐标（0~127）
  * 参    数：Y，字符串左上角的纵坐标（0~63）8移一格
  * 参    数：String，要显示的字符串
  * 参    数：FontSize，字体大小（8 或 16）
  * 返 回 值：无
  */
void OLED_ShowString(I2C_HandleTypeDef *hi2c, uint8_t X, uint8_t Y, char *String, uint8_t FontSize)
{
    while (*String) {
        OLED_ShowChar(hi2c, X, Y, *String++, FontSize); // 显示字符
        X += (FontSize == 8) ? 6 : 8; // 更新 X 坐标
    }
}

/**
  * 函    数：OLED 显示数字
  * 参    数：hi2c，I2C 句柄（hi2c1, hi2c2, ...）
  * 参    数：X，数字左上角的横坐标（0~127）
  * 参    数：Y，数字左上角的纵坐标（0~63）
  * 参    数：Number，要显示的数字
  * 参    数：Length，数字的长度
  * 参    数：FontSize，字体大小（8 或 16）
  * 返 回 值：无
  */
void OLED_ShowNum(I2C_HandleTypeDef *hi2c, uint8_t X, uint8_t Y, uint32_t Number, uint8_t Length, uint8_t FontSize)
{
    char str[10];
    snprintf(str, sizeof(str), "%ld", Number); // 将数字转换为字符串
    OLED_ShowString(hi2c, X, Y, str, FontSize); // 显示字符串
}

/**
  * 函    数：OLED 显示图像
  * 参    数：hi2c，I2C 句柄（hi2c1, hi2c2, ...）
  * 参    数：X，图像左上角的横坐标（0~127）
  * 参    数：Y，图像左上角的纵坐标（0~63）
  * 参    数：Width，图像的宽度
  * 参    数：Height，图像的高度
  * 参    数：Image，图像数据
  * 返 回 值：无
  */
void OLED_ShowImage(I2C_HandleTypeDef *hi2c, uint8_t X, uint8_t Y, uint8_t Width, uint8_t Height, const uint8_t *Image)
{
    for (uint8_t i = 0; i < Height; i++) {
        OLED_SetCursor(hi2c, Y / 8 + i, X); // 设置光标位置
        HAL_I2C_WriteData(hi2c, OLED_I2C_ADDRESS, OLED_DATA, (uint8_t *)&Image[i * Width], Width); // 写入图像数据
    }
}
