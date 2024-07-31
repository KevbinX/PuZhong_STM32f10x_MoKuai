/******************************************************************************************
                                       led.h
*******************************************************************************************/
#ifndef _led_H
#define _led_H

#include "system.h"

/* LED时钟端口和引脚定义 */
/* 定义LED0的端口、引脚及其时钟 */
#define LED0_PORT          GPIOC  
#define LED0_PIN           GPIO_Pin_13
#define LED0_PORT_RCC      RCC_APB2Periph_GPIOC

/* 定义LED1的端口、引脚及其时钟 */
#define LED1_PORT          GPIOA  
#define LED1_PIN           GPIO_Pin_0
#define LED1_PORT_RCC      RCC_APB2Periph_GPIOA

/* 定义LED2的端口、引脚及其时钟 */
#define LED2_PORT          GPIOA  
#define LED2_PIN           GPIO_Pin_1
#define LED2_PORT_RCC      RCC_APB2Periph_GPIOA

/* 定义LED3的端口、引脚及其时钟 */
#define LED3_PORT          GPIOA  
#define LED3_PIN           GPIO_Pin_2
#define LED3_PORT_RCC      RCC_APB2Periph_GPIOA

/* 定义LED4的端口、引脚及其时钟 */
#define LED4_PORT          GPIOA  
#define LED4_PIN           GPIO_Pin_3
#define LED4_PORT_RCC      RCC_APB2Periph_GPIOA

/* 定义LED5的端口、引脚及其时钟 */
#define LED5_PORT          GPIOA  
#define LED5_PIN           GPIO_Pin_4
#define LED5_PORT_RCC      RCC_APB2Periph_GPIOA

/* 定义LED6的端口、引脚及其时钟 */
#define LED6_PORT          GPIOA  
#define LED6_PIN           GPIO_Pin_5
#define LED6_PORT_RCC      RCC_APB2Periph_GPIOA

/* 定义LED7的端口、引脚及其时钟 */
#define LED7_PORT          GPIOA  
#define LED7_PIN           GPIO_Pin_6
#define LED7_PORT_RCC      RCC_APB2Periph_GPIOA

/* 定义LED8的端口、引脚及其时钟 */
#define LED8_PORT          GPIOA  
#define LED8_PIN           GPIO_Pin_7
#define LED8_PORT_RCC      RCC_APB2Periph_GPIOA

// 位带定义，提供直接访问LED的方式
#define LED0     PCout(13) // 直接控制LED0
#define LED1     PAout(0)  // 直接控制LED1  
#define LED2     PAout(1)  // 直接控制LED2 
#define LED3     PAout(2)  // 直接控制LED3  
#define LED4     PAout(3)  // 直接控制LED4
#define LED5     PAout(4)  // 直接控制LED5  
#define LED6     PAout(5)  // 直接控制LED6
#define LED7     PAout(6)  // 直接控制LED7  
#define LED8     PAout(7)  // 直接控制LED8

// 函数声明
void LED_Init(void); // LED初始化函数声明
void LED_Write_Data(u16 GPIO_Pin, u8 data); // 写入数据到LED的函数声明

#endif

/******************************************************************************************
                                       led.c
*******************************************************************************************/
#include "led.h"

/*******************************************************************************
* 函 数 名         : LED_Init
* 函数功能		   : LED初始化函数
* 输    入         : 无
* 输    出         : 无
*******************************************************************************/
void LED_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure; // 定义GPIO初始化结构体
	
	// 使能LED端口的时钟
	RCC_APB2PeriphClockCmd(LED0_PORT_RCC, ENABLE);
	RCC_APB2PeriphClockCmd(LED1_PORT_RCC, ENABLE);
	RCC_APB2PeriphClockCmd(LED2_PORT_RCC, ENABLE);
	RCC_APB2PeriphClockCmd(LED3_PORT_RCC, ENABLE);
	RCC_APB2PeriphClockCmd(LED4_PORT_RCC, ENABLE);
	RCC_APB2PeriphClockCmd(LED5_PORT_RCC, ENABLE);
	RCC_APB2PeriphClockCmd(LED6_PORT_RCC, ENABLE);
	RCC_APB2PeriphClockCmd(LED7_PORT_RCC, ENABLE);
	RCC_APB2PeriphClockCmd(LED8_PORT_RCC, ENABLE);
	
	// 初始化每个LED的GPIO设置
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; // 设置为推挽输出模式
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; // 设置传输速率为50MHz
	
	// LED0初始化
	GPIO_InitStructure.GPIO_Pin = LED0_PIN; // 选择LED0对应的引脚
	GPIO_Init(LED0_PORT, &GPIO_InitStructure); // 初始化GPIO
	GPIO_SetBits(LED0_PORT, LED0_PIN); // 将LED0端口拉高，熄灭LED
	
	// LED1初始化
	GPIO_InitStructure.GPIO_Pin = LED1_PIN; // 选择LED1对应的引脚
	GPIO_Init(LED1_PORT, &GPIO_InitStructure); // 初始化GPIO
	GPIO_SetBits(LED1_PORT, LED1_PIN); // 将LED1端口拉高，熄灭LED
	
	// LED2初始化
	GPIO_InitStructure.GPIO_Pin = LED2_PIN; // 选择LED2对应的引脚
	GPIO_Init(LED2_PORT, &GPIO_InitStructure); // 初始化GPIO
	GPIO_SetBits(LED2_PORT, LED2_PIN); // 将LED2端口拉高，熄灭LED
	
	// LED3初始化
	GPIO_InitStructure.GPIO_Pin = LED3_PIN; // 选择LED3对应的引脚
	GPIO_Init(LED3_PORT, &GPIO_InitStructure); // 初始化GPIO
	GPIO_SetBits(LED3_PORT, LED3_PIN); // 将LED3端口拉高，熄灭LED
	
	// LED4初始化
	GPIO_InitStructure.GPIO_Pin = LED4_PIN; // 选择LED4对应的引脚
	GPIO_Init(LED4_PORT, &GPIO_InitStructure); // 初始化GPIO
	GPIO_SetBits(LED4_PORT, LED4_PIN); // 将LED4端口拉高，熄灭LED
	
	// LED5初始化
	GPIO_InitStructure.GPIO_Pin = LED5_PIN; // 选择LED5对应的引脚
	GPIO_Init(LED5_PORT, &GPIO_InitStructure); // 初始化GPIO
	GPIO_SetBits(LED5_PORT, LED5_PIN); // 将LED5端口拉高，熄灭LED
	
	// LED6初始化
	GPIO_InitStructure.GPIO_Pin = LED6_PIN; // 选择LED6对应的引脚
	GPIO_Init(LED6_PORT, &GPIO_InitStructure); // 初始化GPIO
	GPIO_SetBits(LED6_PORT, LED6_PIN); // 将LED6端口拉高，熄灭LED
	
	// LED7初始化
	GPIO_InitStructure.GPIO_Pin = LED7_PIN; // 选择LED7对应的引脚
	GPIO_Init(LED7_PORT, &GPIO_InitStructure); // 初始化GPIO
	GPIO_SetBits(LED7_PORT, LED7_PIN); // 将LED7端口拉高，熄灭LED
	
	// LED8初始化
	GPIO_InitStructure.GPIO_Pin = LED8_PIN; // 选择LED8对应的引脚
	GPIO_Init(LED8_PORT, &GPIO_InitStructure); // 初始化GPIO
	GPIO_SetBits(LED8_PORT, LED8_PIN); // 将LED8端口拉高，熄灭LED
}

// LED端口8位数据同时操作，不影响高位
// 写入数据到8位端口，数据低位对应端口低引脚
// GPIO_Pin：8位端口低位引脚
// data：写入数据
void LED_Write_Data(u16 GPIO_Pin, u8 data)
{
	u8 i, j = GPIO_Pin; // 初始化循环变量和引脚
	for(i = 0; i < 8; i++) // 循环处理8位数据
	{
		if(data & 0x01) // 检查当前位是否为1
			GPIO_WriteBit(GPIOA, j << i, Bit_SET); // 设置对应引脚为高
		else
			GPIO_WriteBit(GPIOA, j << i, Bit_RESET); // 设置对应引脚为低
		data = data >> 1; // 右移数据，处理下一位
	}
}

