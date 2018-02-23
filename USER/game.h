#ifndef __GAME_H
#define __GAME_H 

#include "sys.h"
#include "draw.h"
#define WAIT_FOR_BEGIN 1
#define WAIT_FOR_END 2
#define UP 1
#define DOWN 2
#define LEFT 3
#define RIGHT 4
#define INVALID 5


void ready_to_play(u8);
void game_init(void);

void move_left(void);
void move_right(void);
void move_up(void);
void move_down(void);
void gen_num(void);
void game_over(void);
void update_score(u32);
void replay(void);
#endif
