/****************************************************************************************
                               key.h
****************************************************************************************\
#ifndef _key_H
#define _key_H

#include "system.h"

// 管脚定义
/* 定义KEY1的端口、引脚及其时钟 */
#define KEY1_PORT          GPIOA  
#define KEY1_PIN           GPIO_Pin_15
#define KEY1_PORT_RCC      RCC_APB2Periph_GPIOA

/* 定义KEY2的端口、引脚及其时钟 */
#define KEY2_PORT          GPIOA  
#define KEY2_PIN           GPIO_Pin_14
#define KEY2_PORT_RCC      RCC_APB2Periph_GPIOA

/* 定义KEY3的端口、引脚及其时钟 */
#define KEY3_PORT          GPIOA  
#define KEY3_PIN           GPIO_Pin_13
#define KEY3_PORT_RCC      RCC_APB2Periph_GPIOA

/* 定义KEY4的端口、引脚及其时钟 */
#define KEY4_PORT          GPIOA  
#define KEY4_PIN           GPIO_Pin_12
#define KEY4_PORT_RCC      RCC_APB2Periph_GPIOA 	

// 使用位操作定义
#define KEY1     PAin(15) // 读取KEY1状态
#define KEY2     PAin(14) // 读取KEY2状态
#define KEY3     PAin(13) // 读取KEY3状态
#define KEY4     PAin(12) // 读取KEY4状态

// 定义各个按键值  
#define KEY1_PRESS         1
#define KEY2_PRESS         2
#define KEY3_PRESS         3
#define KEY4_PRESS         4

// 矩阵按键端口定义
/* 定义矩阵按键的高电平端口和引脚 */
#define KEY_MATRIX_H1_PORT     GPIOB
#define KEY_MATRIX_H1_PIN      GPIO_Pin_8
#define KEY_MATRIX_H1_PORT_RCC RCC_APB2Periph_GPIOB

#define KEY_MATRIX_H2_PORT     GPIOB
#define KEY_MATRIX_H2_PIN      GPIO_Pin_9
#define KEY_MATRIX_H2_PORT_RCC RCC_APB2Periph_GPIOB

#define KEY_MATRIX_H3_PORT     GPIOB
#define KEY_MATRIX_H3_PIN      GPIO_Pin_10
#define KEY_MATRIX_H3_PORT_RCC RCC_APB2Periph_GPIOB

#define KEY_MATRIX_H4_PORT     GPIOB
#define KEY_MATRIX_H4_PIN      GPIO_Pin_11
#define KEY_MATRIX_H4_PORT_RCC RCC_APB2Periph_GPIOB

/* 定义矩阵按键的低电平端口和引脚 */
#define KEY_MATRIX_L1_PORT     GPIOB
#define KEY_MATRIX_L1_PIN      GPIO_Pin_12
#define KEY_MATRIX_L1_PORT_RCC RCC_APB2Periph_GPIOB

#define KEY_MATRIX_L2_PORT     GPIOB
#define KEY_MATRIX_L2_PIN      GPIO_Pin_13
#define KEY_MATRIX_L2_PORT_RCC RCC_APB2Periph_GPIOB

#define KEY_MATRIX_L3_PORT     GPIOB
#define KEY_MATRIX_L3_PIN      GPIO_Pin_14
#define KEY_MATRIX_L3_PORT_RCC RCC_APB2Periph_GPIOB

#define KEY_MATRIX_L4_PORT     GPIOB
#define KEY_MATRIX_L4_PIN      GPIO_Pin_15
#define KEY_MATRIX_L4_PORT_RCC RCC_APB2Periph_GPIOB

// 函数声明
void KEY_Init(void); // 初始化按键
u8 KEY_Scan(u8 mode); // 扫描按键状态
void KEY_Matrix_Init(void); // 初始化矩阵按键
u8 KEY_Matrix_Scan(void); // 扫描矩阵按键状态

#endif

/****************************************************************************************
                               key.c
****************************************************************************************\
  #include "key.h"  // 引用按键功能相关的头文件
#include "SysTick.h"  // 引用系统滴答定时器功能相关的头文件

/*******************************************************************************
* 函 数 名         : KEY_Init
* 函数功能		   : 按键初始化
* 输    入         : 无
* 输    出         : 无
*******************************************************************************/
void KEY_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure; //定义结构体变量	
	RCC_APB2PeriphClockCmd(KEY1_PORT_RCC,ENABLE);  // 使能按键1所在的GPIO端口时钟
	RCC_APB2PeriphClockCmd(KEY2_PORT_RCC,ENABLE);  // 使能按键2所在的GPIO端口时钟
	RCC_APB2PeriphClockCmd(KEY3_PORT_RCC,ENABLE);  // 使能按键3所在的GPIO端口时钟
	RCC_APB2PeriphClockCmd(KEY4_PORT_RCC,ENABLE);  // 使能按键4所在的GPIO端口时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);  // 使能复用功能时钟
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable,ENABLE);  // 禁用JTAG调试功能
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_Disable,ENABLE);  // 禁用SWD调试功能
	
	GPIO_InitStructure.GPIO_Pin=KEY1_PIN;  // 选择要设置的IO口为按键1
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;  // 配置为上拉输入
	GPIO_Init(KEY1_PORT,&GPIO_InitStructure);  // 初始化GPIO
	
	GPIO_InitStructure.GPIO_Pin=KEY2_PIN;  // 选择要设置的IO口为按键2
	GPIO_Init(KEY2_PORT,&GPIO_InitStructure);  // 初始化GPIO
	
	GPIO_InitStructure.GPIO_Pin=KEY3_PIN;  // 选择要设置的IO口为按键3
	GPIO_Init(KEY3_PORT,&GPIO_InitStructure);  // 初始化GPIO
	
	GPIO_InitStructure.GPIO_Pin=KEY4_PIN;  // 选择要设置的IO口为按键4
	GPIO_Init(KEY4_PORT,&GPIO_InitStructure);  // 初始化GPIO
}


/*******************************************************************************
* 函 数 名         : KEY_Scan
* 函数功能		     : 按键扫描检测
* 输    入         : mode=0:单次按下按键
                   : mode=1：连续按下按键
* 输    出         : 0：未有按键按下
									 KEY1_PRESS：KEY1键按下
									 KEY2_PRESS：KEY2键按下
									 KEY3_PRESS：KEY3键按下
									 KEY4_PRESS：KEY4键按下
*******************************************************************************/
u8 KEY_Scan(u8 mode)
{
	static u8 key=1;  // 定义静态变量key，用于记录按键状态
	
	if(mode==1)  // 连续按键按下
		key=1;
	if(key==1&&(KEY1==0||KEY2==0||KEY3==0||KEY4==0))  // 任意一个按键按下
	{
		delay_ms(10);  // 消抖
		key=0;
		if(KEY1==0)
			return KEY1_PRESS; 
		else if(KEY2==0)
			return KEY2_PRESS; 
		else if(KEY3==0)
			return KEY3_PRESS; 
		else if(KEY4==0)
			return KEY4_PRESS; 
	}
	else if(KEY1==1&&KEY2==1&&KEY3==1&&KEY4==1)  // 无按键按下
		key=1;
	return 0;
}


// 矩阵按键初始化
void KEY_Matrix_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;  // 定义结构体变量，用于配置GPIO参数
	
	// 使能行管脚所在的GPIO端口时钟
	RCC_APB2PeriphClockCmd(KEY_MATRIX_H1_PORT_RCC | KEY_MATRIX_H2_PORT_RCC | KEY_MATRIX_H3_PORT_RCC | KEY_MATRIX_H4_PORT_RCC, ENABLE);
	
	// 使能列管脚所在的GPIO端口时钟
	RCC_APB2PeriphClockCmd(KEY_MATRIX_L1_PORT_RCC | KEY_MATRIX_L2_PORT_RCC | KEY_MATRIX_L3_PORT_RCC | KEY_MATRIX_L4_PORT_RCC, ENABLE);
	
	// 配置行管脚为推挽输出模式
	GPIO_InitStructure.GPIO_Pin = KEY_MATRIX_H1_PIN | KEY_MATRIX_H2_PIN | KEY_MATRIX_H3_PIN | KEY_MATRIX_H4_PIN;  // 选择要设置的IO口为行管脚
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;  // 配置为推挽输出模式
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;  // 设置传输速率
	GPIO_Init(KEY_MATRIX_H1_PORT, &GPIO_InitStructure);  // 初始化GPIO
	
	// 配置列管脚为上拉输入模式
	GPIO_InitStructure.GPIO_Pin = KEY_MATRIX_L1_PIN | KEY_MATRIX_L2_PIN | KEY_MATRIX_L3_PIN | KEY_MATRIX_L4_PIN;  // 选择要设置的IO口为列管脚
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;  // 配置为上拉输入模式
	GPIO_Init(KEY_MATRIX_L1_PORT, &GPIO_InitStructure);  // 初始化GPIO
}


/*******************************************************************************
* 函 数 名       : KEY_Matrix_Scan
* 函数功能		   : 检测矩阵按键是否按下，按下则返回对应键值
* 输    入       : 无
* 输    出    	 : key_value：1-16，对应S1-S16键，
				           0：按键未按下
*******************************************************************************/
u8 KEY_Matrix_Scan(void)
{
	u8 col1, col2, col3, col4;  // 定义变量用于存储列的状态
	u8 key_value = 0;  // 初始化按键值为0
	
	// 先将所有行管脚设置为高电平，准备进行按键扫描
	GPIO_SetBits(KEY_MATRIX_H1_PORT, KEY_MATRIX_H1_PIN);  // 行1输出高
	GPIO_SetBits(KEY_MATRIX_H2_PORT, KEY_MATRIX_H2_PIN);  // 行2输出高
	GPIO_SetBits(KEY_MATRIX_H3_PORT, KEY_MATRIX_H3_PIN);  // 行3输出高
	GPIO_SetBits(KEY_MATRIX_H4_PORT, KEY_MATRIX_H4_PIN);  // 行4输出高
	
	// 检查列管脚的状态，如果所有列都为高，则没有按键按下
	if ((GPIO_ReadInputDataBit(KEY_MATRIX_L1_PORT, KEY_MATRIX_L1_PIN) |
		 GPIO_ReadInputDataBit(KEY_MATRIX_L2_PORT, KEY_MATRIX_L2_PIN) |
		 GPIO_ReadInputDataBit(KEY_MATRIX_L3_PORT, KEY_MATRIX_L3_PIN) |
		 GPIO_ReadInputDataBit(KEY_MATRIX_L4_PORT, KEY_MATRIX_L4_PIN)) == 0)  
	{
		return 0; // 如果所有列的状态都为零，则返回0
	}
	else
	{	
		delay_ms(5);  // 延时5ms以消除抖动
		// 再次检查列管脚的状态，确认按键状态
		if ((GPIO_ReadInputDataBit(KEY_MATRIX_L1_PORT, KEY_MATRIX_L1_PIN) |
			 GPIO_ReadInputDataBit(KEY_MATRIX_L2_PORT, KEY_MATRIX_L2_PIN) |
			 GPIO_ReadInputDataBit(KEY_MATRIX_L3_PORT, KEY_MATRIX_L3_PIN) |
			 GPIO_ReadInputDataBit(KEY_MATRIX_L4_PORT, KEY_MATRIX_L4_PIN)) == 0)
		{
			return 0; // 如果仍然为零，则返回0
		}
	}
	
	// 第1行检测
	GPIO_SetBits(KEY_MATRIX_H1_PORT, KEY_MATRIX_H1_PIN);  // 将行1设置为高电平，激活行1
	GPIO_ResetBits(KEY_MATRIX_H2_PORT, KEY_MATRIX_H2_PIN);  // 将行2设置为低电平，禁用行2
	GPIO_ResetBits(KEY_MATRIX_H3_PORT, KEY_MATRIX_H3_PIN);  // 将行3设置为低电平，禁用行3
	GPIO_ResetBits(KEY_MATRIX_H4_PORT, KEY_MATRIX_H4_PIN);  // 将行4设置为低电平，禁用行4 

	// 读取列管脚的状态
	col1 = GPIO_ReadInputDataBit(KEY_MATRIX_L1_PORT, KEY_MATRIX_L1_PIN);  // 读取列1的状态
	col2 = GPIO_ReadInputDataBit(KEY_MATRIX_L2_PORT, KEY_MATRIX_L2_PIN);  // 读取列2的状态
	col3 = GPIO_ReadInputDataBit(KEY_MATRIX_L3_PORT, KEY_MATRIX_L3_PIN);  // 读取列3的状态
	col4 = GPIO_ReadInputDataBit(KEY_MATRIX_L4_PORT, KEY_MATRIX_L4_PIN);  // 读取列4的状态

	// 根据列的状态确定按下的按键
	if (col1 == 1 && col2 == 0 && col3 == 0 && col4 == 0) {
			key_value = 1;  // 按下的是S1键
	}
	if (col1 == 0 && col2 == 1 && col3 == 0 && col4 == 0) {
			key_value = 2;  // 按下的是S2键
	}
	if (col1 == 0 && col2 == 0 && col3 == 1 && col4 == 0) {
			key_value = 3;  // 按下的是S3键
	}
	if (col1 == 0 && col2 == 0 && col3 == 0 && col4 == 1) {
			key_value = 4;  // 按下的是S4键
	}

	// 等待按键松开
	while (((GPIO_ReadInputDataBit(KEY_MATRIX_L1_PORT, KEY_MATRIX_L1_PIN)) |
					(GPIO_ReadInputDataBit(KEY_MATRIX_L2_PORT, KEY_MATRIX_L2_PIN)) |
					(GPIO_ReadInputDataBit(KEY_MATRIX_L3_PORT, KEY_MATRIX_L3_PIN)) |
					(GPIO_ReadInputDataBit(KEY_MATRIX_L4_PORT, KEY_MATRIX_L4_PIN))) > 0) {
			// 循环等待，直到所有列的状态均为高电平，表示按键已松开
	}
	
	// 第2行检测
	GPIO_ResetBits(KEY_MATRIX_H1_PORT, KEY_MATRIX_H1_PIN);  // 将行1设置为低电平，禁用行1
	GPIO_SetBits(KEY_MATRIX_H2_PORT, KEY_MATRIX_H2_PIN);    // 将行2设置为高电平，激活行2
	GPIO_ResetBits(KEY_MATRIX_H3_PORT, KEY_MATRIX_H3_PIN);  // 将行3设置为低电平，禁用行3
	GPIO_ResetBits(KEY_MATRIX_H4_PORT, KEY_MATRIX_H4_PIN);  // 将行4设置为低电平，禁用行4 

	// 读取列管脚的状态
	col1 = GPIO_ReadInputDataBit(KEY_MATRIX_L1_PORT, KEY_MATRIX_L1_PIN);  // 读取列1的状态
	col2 = GPIO_ReadInputDataBit(KEY_MATRIX_L2_PORT, KEY_MATRIX_L2_PIN);  // 读取列2的状态
	col3 = GPIO_ReadInputDataBit(KEY_MATRIX_L3_PORT, KEY_MATRIX_L3_PIN);  // 读取列3的状态
	col4 = GPIO_ReadInputDataBit(KEY_MATRIX_L4_PORT, KEY_MATRIX_L4_PIN);  // 读取列4的状态

	// 根据列的状态确定按下的按键
	if (col1 == 1 && col2 == 0 && col3 == 0 && col4 == 0) {
			key_value = 5;  // 按下的是S5键
	}
	if (col1 == 0 && col2 == 1 && col3 == 0 && col4 == 0) {
			key_value = 6;  // 按下的是S6键
	}
	if (col1 == 0 && col2 == 0 && col3 == 1 && col4 == 0) {
			key_value = 7;  // 按下的是S7键
	}
	if (col1 == 0 && col2 == 0 && col3 == 0 && col4 == 1) {
			key_value = 8;  // 按下的是S8键
	}

	// 等待按键松开
	while (((GPIO_ReadInputDataBit(KEY_MATRIX_L1_PORT, KEY_MATRIX_L1_PIN)) |
					(GPIO_ReadInputDataBit(KEY_MATRIX_L2_PORT, KEY_MATRIX_L2_PIN)) |
					(GPIO_ReadInputDataBit(KEY_MATRIX_L3_PORT, KEY_MATRIX_L3_PIN)) |
					(GPIO_ReadInputDataBit(KEY_MATRIX_L4_PORT, KEY_MATRIX_L4_PIN))) > 0) {
			// 循环等待，直到所有列的状态均为高电平，表示按键已松开
	}

	// 第3行检测
	GPIO_ResetBits(KEY_MATRIX_H1_PORT, KEY_MATRIX_H1_PIN);  // 将行1设置为低电平，禁用行1
	GPIO_ResetBits(KEY_MATRIX_H2_PORT, KEY_MATRIX_H2_PIN);  // 将行2设置为低电平，禁用行2
	GPIO_SetBits(KEY_MATRIX_H3_PORT, KEY_MATRIX_H3_PIN);    // 将行3设置为高电平，激活行3
	GPIO_ResetBits(KEY_MATRIX_H4_PORT, KEY_MATRIX_H4_PIN);  // 将行4设置为低电平，禁用行4 

	// 读取列管脚的状态
	col1 = GPIO_ReadInputDataBit(KEY_MATRIX_L1_PORT, KEY_MATRIX_L1_PIN);  // 读取列1的状态
	col2 = GPIO_ReadInputDataBit(KEY_MATRIX_L2_PORT, KEY_MATRIX_L2_PIN);  // 读取列2的状态
	col3 = GPIO_ReadInputDataBit(KEY_MATRIX_L3_PORT, KEY_MATRIX_L3_PIN);  // 读取列3的状态
	col4 = GPIO_ReadInputDataBit(KEY_MATRIX_L4_PORT, KEY_MATRIX_L4_PIN);  // 读取列4的状态

	// 根据列的状态确定按下的按键
	if (col1 == 1 && col2 == 0 && col3 == 0 && col4 == 0) {
			key_value = 9;  // 按下的是S9键
	}
	if (col1 == 0 && col2 == 1 && col3 == 0 && col4 == 0) {
			key_value = 10; // 按下的是S10键
	}
	if (col1 == 0 && col2 == 0 && col3 == 1 && col4 == 0) {
			key_value = 11; // 按下的是S11键
	}
	if (col1 == 0 && col2 == 0 && col3 == 0 && col4 == 1) {
			key_value = 12; // 按下的是S12键
	}

	// 等待按键松开
	while (((GPIO_ReadInputDataBit(KEY_MATRIX_L1_PORT, KEY_MATRIX_L1_PIN)) |
					(GPIO_ReadInputDataBit(KEY_MATRIX_L2_PORT, KEY_MATRIX_L2_PIN)) |
					(GPIO_ReadInputDataBit(KEY_MATRIX_L3_PORT, KEY_MATRIX_L3_PIN)) |
					(GPIO_ReadInputDataBit(KEY_MATRIX_L4_PORT, KEY_MATRIX_L4_PIN))) > 0) {
			// 循环等待，直到所有列的状态均为高电平，表示按键已松开
	}

		
	// 第4行检测
	GPIO_ResetBits(KEY_MATRIX_H1_PORT, KEY_MATRIX_H1_PIN);  // 将行1设置为低电平，禁用行1
	GPIO_ResetBits(KEY_MATRIX_H2_PORT, KEY_MATRIX_H2_PIN);  // 将行2设置为低电平，禁用行2
	GPIO_ResetBits(KEY_MATRIX_H3_PORT, KEY_MATRIX_H3_PIN);  // 将行3设置为低电平，禁用行3
	GPIO_SetBits(KEY_MATRIX_H4_PORT, KEY_MATRIX_H4_PIN);    // 将行4设置为高电平，激活行4

	// 读取列管脚的状态
	col1 = GPIO_ReadInputDataBit(KEY_MATRIX_L1_PORT, KEY_MATRIX_L1_PIN);  // 读取列1的状态
	col2 = GPIO_ReadInputDataBit(KEY_MATRIX_L2_PORT, KEY_MATRIX_L2_PIN);  // 读取列2的状态
	col3 = GPIO_ReadInputDataBit(KEY_MATRIX_L3_PORT, KEY_MATRIX_L3_PIN);  // 读取列3的状态
	col4 = GPIO_ReadInputDataBit(KEY_MATRIX_L4_PORT, KEY_MATRIX_L4_PIN);  // 读取列4的状态

	// 根据列的状态确定按下的按键
	if (col1 == 1 && col2 == 0 && col3 == 0 && col4 == 0) {
			key_value = 13;  // 按下的是S13键
	}
	if (col1 == 0 && col2 == 1 && col3 == 0 && col4 == 0) {
			key_value = 14;  // 按下的是S14键
	}
	if (col1 == 0 && col2 == 0 && col3 == 1 && col4 == 0) {
			key_value = 15;  // 按下的是S15键
	}
	if (col1 == 0 && col2 == 0 && col3 == 0 && col4 == 1) {
			key_value = 16;  // 按下的是S16键
	}

	// 等待按键松开
	while (((GPIO_ReadInputDataBit(KEY_MATRIX_L1_PORT, KEY_MATRIX_L1_PIN)) |
					(GPIO_ReadInputDataBit(KEY_MATRIX_L2_PORT, KEY_MATRIX_L2_PIN)) |
					(GPIO_ReadInputDataBit(KEY_MATRIX_L3_PORT, KEY_MATRIX_L3_PIN)) |
					(GPIO_ReadInputDataBit(KEY_MATRIX_L4_PORT, KEY_MATRIX_L4_PIN))) > 0) {
			// 循环等待，直到所有列的状态均为高电平，表示按键已松开
	}

	// 返回检测到的按键值
	return key_value;
}




