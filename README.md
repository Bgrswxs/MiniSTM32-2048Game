# 单片机实现简单2048小游戏
开发器材:
	MiniSTM32F103开发板V3版本

硬件资源:
- DS0(连接在PA8) 
- 串口1(波特率:9600,PA9/PA10连接在板载USB转串口芯片CH340上面)
- ALIENTEK 2.8/3.5/4.3/7寸TFTLCD模块(通过GPIO驱动,连接关系见lcd.h)
- 按键KEY0(PC5) 
- 触摸屏(TFTLCD模块自带了) 

