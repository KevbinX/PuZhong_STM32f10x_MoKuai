//该函数用于将指定的引脚设置为高电平。
void GPIO_SetPin(int pin)
{
  
  //通过位操作，将GPIOA的输出数据寄存器（ODR）中对应引脚的位置设置为1（高电平）
  GPIOA->ODR |= (1<<pin);
}

//该函数用于将指定的引脚设置为低电平。
void GPIO_ResetPin(int pin)
{
  
  //通过位操作，将GPIOA的输出数据寄存器（ODR）中对应引脚的位置清零（低电平）
  GPIOA->ODR &= ~(1<<pin);
}
