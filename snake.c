/*
 * =====================================================================================
 *
 *       Filename:  snake.c
 *
 *    Description:  
 *
 *        Version:  4.0
 *        Created:  2012年06月01日 02时09分37秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  LIUYU yuliu314@gmail.com
 *        Company:  UESTC
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <signal.h>
#include <curses.h>
#include <stdlib.h>

#define SNAKE "*"
#define BLANK " "
#define SNAKELEN 3
#define MAXLEN 1000
#define UP    1
#define DOWN  2
#define LEFT  3
#define RIGHT 4
#define DELAY 100
void pattern_up();
void pattern_down();
void pattern_left();
void pattern_right();
void seed_generate();
struct point {
	int x;
	int y;
} snake[MAXLEN], seed;
int delay;
int lastsnake_len = SNAKELEN;
int snake_len = SNAKELEN;
int input = RIGHT;
int c;

int main()
{
   	void init_game();
   	void move_msg(int);	
   	init_game();
   	signal(SIGALRM, move_msg);
   	set_ticker(delay);
	
	while (1) {
		c = getch();
	  	if (c == 'w') input = UP;
	  	if (c == 's') input = DOWN;
	   	if (c == 'a') input = LEFT;
	   	if (c == 'd') input = RIGHT;	
		if (c == 'q') break;   
   	}
	endwin();
	return 0;
}

void init_game()
{
	int i;	
	initscr(); /* turn on curses */
	crmode();  /* draw some stuff */
	noecho();  
	clear();
	move(20, 20);
	addstr("Welcome to SNAKE, wish you have fun!");
	move(21, 20);
	addstr("UP-w, Down-s, LEFT-a, RIGHT-d, QUIT-q");
	move(22, 20);
	addstr("Input any botton to start!");
	refresh();
	c = getch();
	clear();
	delay = DELAY;
	for (i = 0; i < snake_len; i++) {
		snake[i].x = 10;
		snake[i].y = 10 + i;
	}
	for (i = 0; i < snake_len; i++) {
		move(snake[i].x, snake[i].y);
		addstr(SNAKE);
	}
	seed_generate();
	refresh();
}

void move_msg(int signum)
{
	signal(SIGALRM, move_msg);	/* reset, just in case	*/

    switch (input) {
		case UP: pattern_up();
				 break;
		case DOWN: pattern_down();
				   break;
		case LEFT: pattern_left();
			  	   break;
		case RIGHT:pattern_right();
				   break;
	}
	if (snake[snake_len - 1].x < 0 || snake[snake_len - 1].x >= LINES || snake[snake_len - 1].y < 0 || snake[snake_len - 1].y >= COLS) {
		clear();
		move(20, 20);
		addstr("GAME OVER");
		refresh();
		c = getch();
		endwin();
		exit(0);
	}
}	
void pattern_up()
{
	int i;
   
	move(snake[0].x, snake[0].y);
	if (lastsnake_len != snake_len) {
		addstr(SNAKE);
		lastsnake_len = snake_len;
		snake[snake_len - 1].x = snake[snake_len - 2].x - 1;
		snake[snake_len - 1].y = snake[snake_len - 2].y;
	}
	else {
		addstr(BLANK);
		for (i = 0; i < snake_len - 1; i++) {
			snake[i] = snake[i + 1];
			move(snake[i].x, snake[i].y);
			addstr(SNAKE);
		}
		snake[snake_len - 1].x -= 1;
	}
	for (i = 0; i < snake_len - 1; i++) 
		if (snake[snake_len - 1].x == snake[i].x && snake[snake_len - 1].y == snake[i].y) 
		{
			move(20, 20);
			addstr("GAME OVER");
			refresh();
			c = getch();
			endwin();
			exit(0);
		}	
	move(snake[snake_len - 1].x, snake[snake_len -1].y);
	addstr(SNAKE);
	if (snake[snake_len - 1].x == seed.x && snake[snake_len - 1].y == seed.y) {
		snake_len++;
		seed_generate();
	}
	refresh();
}

void pattern_down()
{
	int i;

	move(snake[0].x, snake[0].y);
	if (lastsnake_len != snake_len) {
		addstr(SNAKE);
		lastsnake_len = snake_len;
		snake[snake_len - 1].x = snake[snake_len - 2].x + 1;
		snake[snake_len - 1].y = snake[snake_len - 2].y;
	}
	else {
		addstr(BLANK);
		for (i = 0; i < snake_len - 1; i++) {
			snake[i] = snake[i + 1];
			move(snake[i].x, snake[i].y);
			addstr(SNAKE);
		}
		snake[snake_len - 1].x += 1;
	}
	for (i = 0; i < snake_len - 1; i++) 
		if (snake[snake_len - 1].x == snake[i].x && snake[snake_len - 1].y == snake[i].y) 
		{
			move(20, 20);
			addstr("GAME OVER");
			refresh();
			c = getch();
			endwin();
			exit(0);
		}	
	move(snake[snake_len - 1].x, snake[snake_len -1].y);
	addstr(SNAKE);
	if (snake[snake_len - 1].x == seed.x && snake[snake_len - 1].y == seed.y) {
		snake_len++;
		seed_generate();
	}
	refresh();
}

void pattern_left()
{
	int i;

	move(snake[0].x, snake[0].y);
	if (lastsnake_len != snake_len) {
		addstr(SNAKE);
		lastsnake_len = snake_len;
		snake[snake_len - 1].x = snake[snake_len - 2].x;
		snake[snake_len - 1].y = snake[snake_len - 2].y - 1;
	}
	else {
		addstr(BLANK);
	 	for (i = 0; i < snake_len - 1; i++) {
			snake[i] = snake[i + 1];
			move(snake[i].x, snake[i].y);
			addstr(SNAKE);
		}
		snake[snake_len - 1].y -= 1;
	}
	for (i = 0; i < snake_len - 1; i++) 
		if (snake[snake_len - 1].x == snake[i].x && snake[snake_len - 1].y == snake[i].y) 
		{
			move(20, 20);
			addstr("GAME OVER");
			refresh();
			c = getch();
			endwin();
			exit(0);
		}	
	move(snake[snake_len - 1].x, snake[snake_len -1].y);
	addstr(SNAKE);
	if (snake[snake_len - 1].x == seed.x && snake[snake_len - 1].y == seed.y) {
		snake_len++;
		seed_generate();
	}
	refresh();
}

void pattern_right()
{
	int i;

	move(snake[0].x, snake[0].y);
	if (lastsnake_len != snake_len) {
		addstr(SNAKE);
		lastsnake_len = snake_len;
		snake[snake_len - 1].x = snake[snake_len - 2].x;
		snake[snake_len - 1].y = snake[snake_len - 2].y + 1;
	}
	else {
		addstr(BLANK);
		for (i = 0; i < snake_len - 1; i++) {
			snake[i] = snake[i + 1];
			move(snake[i].x, snake[i].y);
			addstr(SNAKE);
		}
		snake[snake_len - 1].y += 1;
	}
	for (i = 0; i < snake_len - 1; i++) 
		if (snake[snake_len - 1].x == snake[i].x && snake[snake_len - 1].y == snake[i].y) 
		{
			move(20, 20);
			addstr("GAME OVER");
			refresh();
			c = getch();
			endwin();
			exit(0);
		}	
	move(snake[snake_len - 1].x, snake[snake_len -1].y);
	addstr(SNAKE);
	if (snake[snake_len - 1].x == seed.x && snake[snake_len - 1].y == seed.y) {
		snake_len++;
		seed_generate();
	}
	refresh();
}

void seed_generate()
{
	int same, i;

	while (1) {
		same = 0;
		seed.x = rand() % LINES;
		seed.y = rand() % COLS;
		for (i = 0; i < snake_len; i++) {
			if (seed.x == snake[i].x && seed.y == snake[i].y) {
				same = 1;
			}
		}
		if (same == 0)
			break;
	}
	move(seed.x, seed.y);
	addstr("*");
	refresh();
}
