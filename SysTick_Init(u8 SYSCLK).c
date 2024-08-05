#include "SysTick.h"

//全局变量设置：
static u8  fac_us=0;  // us延时倍乘数
static u16 fac_ms=0;  // ms延时倍乘数

// 初始化延迟函数
// SYSTICK的时钟固定为AHB时钟的1/8
// SYSCLK: 系统时钟频率
void SysTick_Init(u8 SYSCLK)
{
//时钟源配置：
    //这行代码将 SysTick 的时钟源配置为 AHB 时钟的 1/8。也就是说，
    //如果系统时钟（SYSCLK）为 72 MHz，则 SysTick 的时钟频率将为 9 MHz（72 MHz / 8）。
    SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8); 
  
//延时倍乘数计算：
    // 这一行计算出每毫秒的延时倍乘数。由于每毫秒有 1000 微秒，
    //因此 fac_ms 的值为 fac_us 乘以 1000，即 9000。
    fac_us = SYSCLK / 8;  

    // 这一行计算出每毫秒的延时倍乘数。由于每毫秒有 1000 微秒，
	  //因此 fac_ms 的值为 fac_us 乘以 1000，即 9000。
    fac_ms = (u16)fac_us * 1000;  
}
