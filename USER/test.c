#include "sys.h"
#include "usart.h"		
#include "delay.h"	
#include "led.h"   
#include "lcd.h"  
#include "key.h"  
#include "24cxx.h"  
#include "touch.h"  
#include "game.h"
#include "stdlib.h"
#include "debug.h"



u8 tp_sta = WAIT_FOR_BEGIN;
u8 dir;
TouchPoint pathB, pathE = {0, 0};


void main_loop(void);
int main(void)
{	
	Stm32_Clock_Init(9);	
	uart_init(72,9600);	 	
	delay_init(72);	   	 	
	LCD_Init();			   	
	KEY_Init();				 	
	tp_dev.init();		
	POINT_COLOR=BLUE;	
	
	ready_to_play(100);
	//auto_play(FAST);
	main_loop();
//	color_test();
//	tp_test();
}



void main_loop(void)
{
	u8 key;
	while(1)
	{
		key=KEY_Scan(0);
		tp_dev.scan(0); 	 	    
		if(key==KEY0_PRES)	
		{
			tp_test();	 
		}
		if((tp_dev.sta&TP_PRES_DOWN) && (tp_dev.x[0]<lcddev.width&&tp_dev.y[0]<lcddev.height))
		{
			if(tp_sta == WAIT_FOR_END)
				pathE.x = tp_dev.x[0];
				pathE.y = tp_dev.y[0];
			}
			else if(tp_sta == WAIT_FOR_BEGIN) //触摸状态：无触摸，等待触摸操作开始；正在触摸，等待触摸操作结束
			{
				pathB.x = tp_dev.x[0];
				pathB.y = tp_dev.y[0];
				tp_sta = WAIT_FOR_END;
			}
		}
		else if(tp_dev.x[0]<lcddev.width&&tp_dev.y[0]<lcddev.height)
		{
			if(tp_sta == WAIT_FOR_END)
			{
				pathE.x = tp_dev.x[0];
				pathE.y = tp_dev.y[0];
				dir = getDir(pathB, pathE, 0); //通过计算余弦值获得触摸轨迹的方向
				tp_sta = WAIT_FOR_BEGIN;
				switch(dir) 
				{
					case UP:
						move_up();
						break;
					case DOWN:
						move_down();
						break;
					case LEFT:
						move_left();
						break;
					case RIGHT:
						move_right();
						break;
				}
			}
			else if(tp_sta == WAIT_FOR_BEGIN) 
			{
			}
		}
	}
}
 


