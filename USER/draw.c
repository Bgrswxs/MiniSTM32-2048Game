//绘图相关

#include "draw.h"
#include "lcd.h"
#include "math.h"
#include "delay.h"
#include "stdarg.h"
#include "stdio.h"
#include "string.h"

#define BLK_COL GRED
#define NEW_NUM_BLK_COL GREEN
#define SUM_NUM_BLK_COL GRAY



GridPoint gp[17];
u16 sz;
void draw_init(void) //初始化，计算网格等信息
{
	int i = 1;
	int row, col;
	sz = lcddev.width / 4;
	for(; i <=16; ++i)
	{
		row = ceil(i*1.0/4);
		col = (i%4) == 0 ? 4 : (i%4);
		gp[i].x = sz*(col-1) + sz/2;
		gp[i].y = lcddev.height-lcddev.width + sz*(row-1) + sz/2;
	}
}

void draw_grid(void) //绘制背景网格
{
	int i = 1;
	LCD_Fill(0,lcddev.height-lcddev.width,lcddev.width, lcddev.height,GRED);
	for(i = 0; i <= 3; ++i)
	{
		LCD_DrawLine(0, lcddev.height-lcddev.width+sz*i, lcddev.width, lcddev.height-lcddev.width+sz*i);
	}
	for(i = 1; i <= 3; ++i)
	{
		LCD_DrawLine(sz*i, lcddev.height-lcddev.width, sz*i, lcddev.height);
	}
}

void draw_num(u8 xp, u8 yp, u16 num) //绘制数字
{
	u8 grid;
	u16 x, y;
	u16 color;
	grid = (xp-1)*4+yp;
	x = gp[grid].x - 35;
	if(num<10) x = x-5;
	y = gp[grid].y - 12;
	color = BROWN;
	if(num==0)
		LCD_Fill(gp[grid].x-sz/2+1,gp[grid].y-sz/2+1,gp[grid].x+sz/2-1, gp[grid].y+sz/2-1,BLK_COL);
	else
	{
		LCD_Fill(gp[grid].x-sz/2+1,gp[grid].y-sz/2+1,gp[grid].x+sz/2-1, gp[grid].y+sz/2-1,BLK_COL);
		LCD_ShowxNum(x,y,num,4,24,1);
	}
}

void draw_game_over(u32 score)  //游戏结束后画一个方框用于显示信息
{
	LCD_DrawRectangle(sz/2, lcddev.height-lcddev.width+sz/2+10, sz*3.5, lcddev.height-sz*1.5+10);
	LCD_Fill(sz/2+1, lcddev.height-lcddev.width+sz/2+11, sz*3.5-1, lcddev.height-sz*1.5+9, WHITE);
	LCD_ShowString(lcddev.width/2-34,lcddev.height-lcddev.width+sz*1.5,200,16,16,"Score:");
	LCD_ShowxNum(lcddev.width/2+10,lcddev.height-lcddev.width+sz*1.5,score,4,16,1);
}

void draw_score(u32 score) //绘制得分
{
	LCD_ShowString(lcddev.width/2-15, (lcddev.height-lcddev.width)/3-5, 200, 16, 16, "Score");
	LCD_ShowxNum(lcddev.width/2-25, (lcddev.height-lcddev.width)/3*2-5,score,4,16,0);
}


void draw_new_num(u8 xp, u8 yp, u16 num) //绘制每次滑动屏幕后产生的新数字
{
	u8 grid;
	u16 x, y, i;
	grid = (xp-1)*4+yp;
	x = gp[grid].x - 35;
	if(num<10) x = x-5;
	y = gp[grid].y - 12;
	for(i=1;i<=20;++i)
	{
		LCD_Fill(gp[grid].x-sz/2+1+sz/4-i*(sz*1.0/4/20),gp[grid].y-sz/2+1+sz/4-i*(sz*1.0/4/20),gp[grid].x+sz/2-1-sz/4+i*(sz*1.0/4/20), gp[grid].y+sz/2-1-sz/4+i*(sz*1.0/4/20),NEW_NUM_BLK_COL);
		LCD_ShowxNum(x,y,num,4,24,1);
		delay_ms(10);
	}
}

void draw_sum_num(u8 xp, u8 yp, u16 num)
{
//	u8 grid;
//	u16 x, y, i;
//	grid = (xp-1)*4+yp;
//	x = gp[grid].x - 35;
//	if(num<10) x = x-5;
//	y = gp[grid].y - 12;
//	for(i=1;i<=10;++i)
//	{
//		LCD_Fill(gp[grid].x-sz/2+1+sz/4-i*(sz*1.0/4/10),gp[grid].y-sz/2+1+sz/4-i*(sz*1.0/4/10),gp[grid].x+sz/2-1-sz/4+i*(sz*1.0/4/10), gp[grid].y+sz/2-1-sz/4+i*(sz*1.0/4/10),SUM_NUM_BLK_COL);
//		LCD_ShowxNum(x,y,num,4,24,1);
//		delay_ms(10);
//	}
}

void print(u16 x, u16 y, char* fmt, ...) //模仿stdio中 ‘printf’函数，使用可变参数、格式控制符，用于打印相关信息
{
	va_list ap;
	char *pfmt, *pstr;
	char tmp[15];
	char str[100]; 
	int ival;
	float fval;
	va_start(ap, fmt);
	for (pfmt=fmt, pstr=str; *pfmt; pfmt++) 
	{
		if(*pfmt != '%') 
		{
			*pstr++ = *pfmt;
			continue;
		}
		switch(*++pfmt) 
		{
			case 'd':
				ival = va_arg(ap, int);
				sprintf(tmp, "%d", ival);
				sprintf(pstr, "%d", ival);
				pstr += strlen(tmp);
				break;
			case 'f':
				fval = va_arg(ap, double);
				sprintf(tmp, "%.2f", fval);
				sprintf(pstr, "%.2f", fval);
				pstr += strlen(tmp);
				break;
		}
	}
	*pstr = '\0';
	LCD_ShowString(x, y, 200, 16, 16, str);
	va_end(ap);
}
