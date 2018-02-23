//控制游戏生命周期

#include "game.h"
#include "draw.h"
#include "lcd.h"
#include "stdlib.h"
#include "touch.h"
#include "delay.h"


int score;
int num[5][5];
int space[17][2];
int tmp[5];

void ready_to_play(u8 dir) //展示欢迎信息
{
	if(dir==100)LCD_ShowString(lcddev.width/2-75,lcddev.height/2,200,16,16,"Touch to play 2048");
	while(1)
	{
		tp_dev.scan(0); 	
		if(tp_dev.sta&TP_PRES_DOWN)			
		{	
			game_init();	
			return;
		}
	}
	
}

void game_init(void)
{
	u8 i,j;
	u8 x, y;
	for(i=1;i<=4;++i)
	{
		for(j=1;j<=4;++j)
		{
			num[i][j] = 0;
		}
	}
	draw_init();
	score = 0;
	draw_score(score);
	draw_grid();
	srand(tp_dev.x[0]+tp_dev.y[0]);
	for(i=1;i<=2;++i)
	{
		x = rand()%4+1;
		y = rand()%4+1;
		num[x][y] = 2;
		draw_num(x, y, 2);
	}
}

void move_left(void)
{
	int i,j,k,t,nx=-1,ny,nn; 
	for(i=1;i<=4;++i) tmp[i] = 0;
	for(i=1;i<=4;++i)
	{
		k=0;
		for(j=1;j<=4;++j) 
		{
			if(num[i][j]) 
			{
				tmp[++k] = num[i][j];
				num[i][j] = 0;
			}
		}
		t=1;
		while(t<=k-1)
		{
			if(tmp[t]==tmp[t+1]) {
				tmp[t] *= 2;
				tmp[t+1] = 0;
				score += tmp[t];
				if(nx==-1)
				{
					nx = i;
					ny = t;
					nn = tmp[t];
				}
				t+=2;
			}
			else t++;
		}
		t=1;
		for(j=1;j<=k;++j) if(tmp[j]) num[i][t++] = tmp[j];
	}
	for(i=1;i<=4;++i)for(j=1;j<=4;++j) draw_num(i,j,num[i][j]);
	if(nx!=-1)draw_sum_num(nx,ny,nn);
	draw_score(score);
	gen_num();
}

void move_right(void)
{
	int i,j,k,t,nx=-1,ny,nn;
	for(i=1;i<=4;++i) tmp[i] = 0;
	for(i=1;i<=4;++i)
	{
		k=0;
		for(j=4;j>=1;--j) 
		{
			if(num[i][j]) 
			{
				tmp[++k] = num[i][j];
				num[i][j] = 0;
			}
		}
		t=1;
		while(t<=k-1)
		{
			if(tmp[t]==tmp[t+1]) {
				tmp[t] *= 2;
				tmp[t+1] = 0;
				score += tmp[t];
				if(nx==-1)
				{
					nx = i;
					ny = 4-t;
					nn = tmp[t];
				}
				t+=2;
			}
			else t++;
		}
		t=4;
		for(j=1;j<=k;++j) if(tmp[j]) num[i][t--] = tmp[j];
	}
	for(i=1;i<=4;++i)for(j=1;j<=4;++j) draw_num(i,j,num[i][j]);
	if(nx!=-1)draw_sum_num(nx,ny,nn);
	draw_score(score);
	gen_num();
}

void move_up(void)
{
	int i,j,k,t,nx=-1,ny,nn;
	for(i=1;i<=4;++i) tmp[i]=0;
	for(j=1;j<=4;++j)
	{
		k=0;
		for(i=1;i<=4;++i) 
		{
			if(num[i][j]) 
			{
				tmp[++k] = num[i][j];
				num[i][j] = 0;
			}
		}
		t=1;
		while(t<=k-1)
		{
			if(tmp[t]==tmp[t+1]) {
				tmp[t] *= 2;
				tmp[t+1] = 0;
				score += tmp[t];
				if(nx==-1)
				{
					nx = t;
					ny = j;
					nn = tmp[t];
				}
				t+=2;
			}
			else t++;
		}
		t=1;
		for(i=1;i<=k;++i) if(tmp[i]) num[t++][j] = tmp[i];
	}
	for(i=1;i<=4;++i)for(j=1;j<=4;++j) draw_num(i,j,num[i][j]);
	if(nx!=-1) draw_sum_num(nx,ny,tmp[nx]);
	draw_score(score);
	gen_num();
}

void move_down(void)
{
	int i,j,k,t,nx=-1,ny,nn; 
	for(i=1;i<=4;++i) tmp[i]=0;
	for(j=1;j<=4;++j)
	{
		k=0;
		for(i=4;i>=1;--i) 
		{
			if(num[i][j]) 
			{
				tmp[++k] = num[i][j];
				num[i][j] = 0;
			}
		}
		t=1;
		while(t<=k-1)
		{
			if(tmp[t]==tmp[t+1]) {
				tmp[t] *= 2;
				tmp[t+1] = 0;
				score += tmp[t];
				if(nx==-1)
				{
					nx = 4-t;
					ny = j;
					nn = tmp[t];
				}
				t+=2;
			}
			else t++;
		}
		t=4;
		for(i=1;i<=k;++i) if(tmp[i]) num[t--][j] = tmp[i];
	}
	for(i=1;i<=4;++i)for(j=1;j<=4;++j) draw_num(i,j,num[i][j]);
	if(nx!=-1) draw_sum_num(nx,ny,nn);
	draw_score(score);
	gen_num();
}

void gen_num(void)
{
	u8 x, y;
	u8 i,j,k,t;
	u16 nax, nin;
	k=0;
	nax = 0;
	nin = 2049;
	for(i=1;i<=4;++i)
	{
		for(j=1;j<=4;++j)
		{
			if(num[i][j]>nax) nax = num[i][j];
			if(num[i][j]<nin) nin = num[i][j];
			if(num[i][j]==0) 
			{
				k++;
				space[k][0] = i;
				space[k][1] = j;
			}
		}
	}
	if(k==0) 
	{
		t = 1;
		for(i=1;i<=4;++i)for(j=1;j<=3;++j)if(num[i][j]==num[i][j+1]) t = 2;
		for(i=1;i<=3;++i)for(j=1;j<=4;++j)if(num[i][j]==num[i+1][j]) t = 2;
		if(t==1) game_over();
		return;
	}
	
	i = rand()%k+1; //���ѡһ���ո���
	//�ո��ӵ�����
	x = space[i][0];
	y = space[i][1];
	
	j = rand()%100+1; 
	if(j<=85) {num[x][y]=2; draw_new_num(x, y, 2);}
	else if(j<=95) {num[x][y]=4; draw_new_num(x, y, 4);}
	else if(j<=100) {num[x][y]=8; draw_new_num(x, y, 8);}
}

void replay(void)
{
	game_init();
}

void game_over(void)
{
	draw_game_over(score);
	while(1){}
//	replay();
}

void update_score(u32 score)
{
	draw_score(score);
}
