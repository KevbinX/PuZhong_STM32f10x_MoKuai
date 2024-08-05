/*******************************************************************************
* 函 数 名         : delay_us
* 函数功能		      : us延时，
* 输    入         : nus：要延时的us数
					        注意:nus的值,不要大于798915us(最大值即2^24/fac_us@fac_us=21)
* 输    出         : 无
* 总    结         ；delay_us 函数通过配置 SysTick 定时器，实现了精确的微秒级延时。
                    它的实现依赖于 SysTick 的 LOAD、VAL 和 CTRL 寄存器
                    通过设置加载值并监控计时器状态，确保延时的准确性。
*******************************************************************************/
void delay_us(u32 nus)
{		
	u32 temp;	  

  //这行代码将要延时的微秒数 nus 乘以每微秒的计数值 fac_us，
  //将结果加载到 SysTick 的 LOAD 寄存器中。
  //这样，SysTick 定时器将在计数到这个值时产生中断。
	SysTick->LOAD=nus*fac_us; 					//时间加载	

  //将 VAL 寄存器清零，以确保计时器从零开始计数。
	SysTick->VAL=0x00;        					//清空计数器

  //启动 SysTick 定时器，使其开始计数。
	SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk ;	//开始倒数	  

  //该循环会持续检查 SysTick 的 CTRL 寄存器：
  //temp & 0x01：检查计时器是否仍在运行（即 ENABLE 位）。
  //!(temp & (1 << 16))：检查是否发生了计时器溢出（即 COUNTFLAG 位）。
  //当计时器停止（即时间到达）时，循环结束。
	do
	{
		temp=SysTick->CTRL;
	}while((temp&0x01)&&!(temp&(1<<16)));		//等待时间到达   

  //关闭 SysTick 定时器，停止计数。
	SysTick->CTRL&=~SysTick_CTRL_ENABLE_Msk;	//关闭计数器
  
  //清空计数器，以确保其状态重置。
	SysTick->VAL =0X00;      					 //清空计数器	 
}
