#ifndef __DRAW_H__
#define __DRAW_H__  
#include "sys.h"
#include "stdarg.h"

//画水平线
//x0,y0:坐标
//len:线长度
//color:颜色
typedef struct GridPoint {
	u16 x;
	u16 y;
} GridPoint;

//画实心圆
//x0,y0:坐标
//r:半径
//color:颜色
void gui_fill_circle(u16 x0,u16 y0,u16 r,u16 color);

//x,y为网格编号
void draw_init(void);
void draw_grid(void);
void draw_num(u8 x, u8 y, u16 num);
void draw_score(u32);
void draw_game_over(u32 score);
void draw_new_num(u8 x, u8 y, u16 num);
void draw_sum_num(u8 x, u8 y, u16 num);

void print(u16, u16, char*, ...);

#endif
