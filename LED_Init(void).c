#include "led.h"

/*******************************************************************************
* 函 数 名         : LED_Init
* 函数功能		       : LED初始化函数
* 输    入         : 无
* 输    出         : 无
* 总    结         ：LED_Init函数负责配置和初始化LED的GPIO引脚，以便在后续的程序中控制LED的状态
*******************************************************************************/
void LED_Init(void)
{
  
//结构体定义：
  //定义一个GPIO_InitTypeDef类型的 结构体变量 GPIO_InitStructure，用于配置GPIO的参数。
  GPIO_InitTypeDef GPIO_InitStructure;//定义结构体变量

//时钟使能：
  //调用RCC_APB2PeriphClockCmd函数使能LED所在端口的时钟，以便后续对该端口的操作。
	RCC_APB2PeriphClockCmd(LED0_PORT_RCC,ENABLE);

//GPIO配置：
  //设置要配置的GPIO引脚（LED0_PIN）
  //设置GPIO模式为推挽输出（GPIO_Mode_Out_PP），允许输出高低电平
  //设置GPIO传输速率为50MHz（GPIO_Speed_50MHz）
	GPIO_InitStructure.GPIO_Pin=LED0_PIN;  //选择你要设置的IO口
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;	 //设置推挽输出模式
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;	  //设置传输速率

//初始化GPIO：
  //调用GPIO_Init函数，使用配置好的结构体对指定的GPIO端口进行初始化
	GPIO_Init(LED0_PORT,&GPIO_InitStructure); 	   /* 初始化GPIO */

//设置初始状态：
  //通过GPIO_SetBits函数将LED端口拉高，确保LED初始状态为熄灭
	GPIO_SetBits(LED0_PORT,LED0_PIN);   //将LED端口拉高，熄灭所有LED
}

