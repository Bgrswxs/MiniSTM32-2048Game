// show debug info in screen

#include "debug.h"
#include "game.h"
#include "lcd.h"
#include "stdlib.h"
#include "delay.h"
#include "touch.h"
#include "stdio.h"
#include "math.h"
#include "draw.h"


extern u8 tp_sta ;
extern u8 dir;
extern TouchPoint pathB, pathE;
u16 offsetY = 80, offsetX = 70;


void auto_play(u8 mode)
{
	int i, j;
	int tp1, tp2, tp3;
	tp1 = 400;
	tp2 = 1500;
	tp3 = 1100;
	if(mode == NORMAL)
	{
		tp1 = 400;
		tp2 = 1500;
		tp3 = 1100;
	}
	else if(mode == FAST)
	{
		tp1 = 1;
		tp2 = 1;
		tp3 = 1;
	}
	for(i=1;;++i)
	{
		j = rand()%4+1;
		switch(j)
		{
			case UP:
				delay_ms(tp1);
				POINT_COLOR=RED;
				LCD_ShowString(5, (lcddev.height-lcddev.width)/3-5, 200, 16, 16, "next: UP   ");
				POINT_COLOR=BLUE;
				//LCD_ShowxNum(lcddev.width/2-25, (lcddev.height-lcddev.width)/3*2-5,i,4,16,0);
				delay_ms(tp2);
				delay_ms(tp3);
				move_up();
				break;
			case DOWN:
				POINT_COLOR=RED;
				delay_ms(tp1);
				LCD_ShowString(5, (lcddev.height-lcddev.width)/3-5, 200, 16, 16, "next: DOWN ");
				POINT_COLOR=BLUE;
				//LCD_ShowxNum(lcddev.width/2-25, (lcddev.height-lcddev.width)/3*2-5,i,4,16,0);
				delay_ms(tp2);
				delay_ms(tp3);
				move_down();
				break;
		case LEFT:
				delay_ms(tp1);
				POINT_COLOR=RED;
				LCD_ShowString(5, (lcddev.height-lcddev.width)/3-5, 200, 16, 16, "next: LEFT ");
				POINT_COLOR=BLUE;
				//LCD_ShowxNum(lcddev.width/2-25, (lcddev.height-lcddev.width)/3*2-5,i,4,16,0);
				delay_ms(tp2);
				delay_ms(tp3);
				move_left();
				break;
		case RIGHT:
				delay_ms(tp1);
				POINT_COLOR=RED;
				LCD_ShowString(5, (lcddev.height-lcddev.width)/3-5, 200, 16, 16, "next: RIGHT");
				POINT_COLOR=BLUE;
				//LCD_ShowxNum(lcddev.width/2-25, (lcddev.height-lcddev.width)/3*2-5,i,4,16,0);
				delay_ms(tp2);
				delay_ms(tp3);
				move_right();
				break;
		}
	}
}



void tp_test(void) // 240x320
{
	LCD_Clear(WHITE);
	print(offsetX, 10+offsetY, "State: ");
	print(offsetX, 30+offsetY, "Begin: ");
	print(offsetX, 50+offsetY, "End  : ");
	print(offsetX, 70+offsetY, "Cos_U: ");
	print(offsetX, 90+offsetY, "Cos_D: ");
	print(offsetX,110+offsetY, "Cos_L: ");
	print(offsetX,130+offsetY, "Cos_R: ");
	print(offsetX,150+offsetY, "Dir  : ");
	while(1)
	{
		tp_dev.scan(0); 
		if((tp_dev.sta&TP_PRES_DOWN) && (tp_dev.x[0]<lcddev.width&&tp_dev.y[0]<lcddev.height))
		{
			if(tp_sta == WAIT_FOR_END) 
			{
				print(offsetX, 10+offsetY, "State: Touching");
				pathE.x = tp_dev.x[0];
				pathE.y = tp_dev.y[0];
			}
			else if(tp_sta == WAIT_FOR_BEGIN) 
			{
				print(offsetX, 10+offsetY, "State: Begin  ");
				pathB.x = tp_dev.x[0];
				pathB.y = tp_dev.y[0];
				tp_sta = WAIT_FOR_END;
				print(offsetX, 30+offsetY, "Begin: (%d,%d)", pathB.x, pathB.y);
			}
		}
		else if(tp_dev.x[0]<lcddev.width&&tp_dev.y[0]<lcddev.height)
		{
			if(tp_sta == WAIT_FOR_END) 
			{
				print(offsetX, 10+offsetY, "State: End     ");
				pathE.x = tp_dev.x[0];
				pathE.y = tp_dev.y[0];
				print(offsetX, 50+offsetY, "End  : (%d,%d)", pathE.x, pathE.y);
				dir = getDir(pathB, pathE, 1);
				tp_sta = WAIT_FOR_BEGIN;
				switch(dir) 
				{
					case UP:
						print(offsetX,150+offsetY, "Dir  : UP    ");
						break;
					case DOWN:
						print(offsetX,150+offsetY, "Dir  : Down  ");
						break;
					case LEFT:
						print(offsetX,150+offsetY, "Dir  : LEFT  ");
						break;
					case RIGHT:
						print(offsetX,150+offsetY, "Dir  : Right ");
						break;
				}
			}
			else if(tp_sta == WAIT_FOR_BEGIN) 
			{
				print(offsetX, 10+offsetY, "State: Nothing ");
			}
		}
	}
}

void color_test(void)
{
	u8 grid;
	u16 col_tb[14] = {WHITE,BLACK,BLUE,BRED,GRED,GBLUE,RED,MAGENTA,GREEN,CYAN,YELLOW,BROWN,BRRED,GRAY};
	int i,j,sz, row, col;
	GridPoint gp[17];
	sz = lcddev.width / 4;
	
	for(i=1; i <=16; ++i)
	{
		row = ceil(i*1.0/4);
		col = (i%4) == 0 ? 4 : (i%4);
		gp[i].x = sz*(col-1) + sz/2;
		gp[i].y = lcddev.height-lcddev.width + sz*(row-1) + sz/2;
	}
	for(i=1;i<=4;++i)for(j=1;j<=4;++j)
	{
		grid = (i-1)*4+j;
		LCD_Fill(gp[grid].x-sz/2+1,gp[grid].y-sz/2+1,gp[grid].x+sz/2-1, gp[grid].y+sz/2-1,col_tb[grid-1]);
	}
}

