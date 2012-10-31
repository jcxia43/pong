/* Pong is a very simple game based on lib curses.h
 * just for fun and practicing
 * by onlyme at Lab305 2012.04.17
 */

#include <stdio.h>
#include <curses.h>
#include <unistd.h>
#include <signal.h>
#include "pong_time.h"
#include "pong_util.h"



#define VCOL 1
#define VROW 1

#define BORDER_COLOR WHITE
#define BALL_COLOR BLUE
#define BAR_COLOR YELLOW
#define BAR_LEN 12
#define WALL_COLOR RED
#define WALL_HEIGHT 10
#define WALL_WIDTH  50

void ticker(int signum);



int speed, Vcol, Vrow, step;
int refresh_frame;

char point = ' ';

Point ball;
Rect bar;
Piles wall;

int main(int argc, char *argv[])
{
	int i, n;

	ball.row = TOP;
	ball.col = LEFTEDGE;

	Vcol = VCOL;
	Vrow = VROW;
	
	
	bar.left_top.row = BOTTOM;
	bar.left_top.col = LEFTEDGE;
	bar.right_bottom.row = BOTTOM;
	bar.right_bottom.col = LEFTEDGE + BAR_LEN;


	wall.left_top.row = TOP + 2;
	wall.left_top.col = LEFTEDGE + 10;
	wall.width = WALL_WIDTH;
	wall.height = WALL_HEIGHT;
	for (i = 0; i < wall.height; ++i){
		for (n = 0; n < wall.width; ++n){
			wall.point[i][n] = 1;
		}
		
	}



	step = 0;

	speed = 20;
	
	initscr();
	color();
	
	char input;
	signal(SIGALRM, ticker);// hook the ticker

	if(-1 == set_ticker(1000, 5, ITIMER_REAL)) // ticker inter
		perror("set_ticker"); 


	while(1){
		input = getchar();
		if (input == 'a'){
			step = -4;
		}
		if (input == 'd'){
			step = 4;
		}
		if(input == 'q'){
			clear();
			break;
		}
	}

	
    return 0;

}


void ticker(int signum)
{
	signal(SIGALRM, ticker);// hook the ticker
    static int flag = 0;
	flag++;
	if(flag >= speed){
		clear();
		draw_border(TOP, BOTTOM, LEFTEDGE, RIGHTEDGE, BORDER_COLOR);
		render_point(&ball, &Vcol, &Vrow, &point, BALL_COLOR);
		render_bar(&bar, &step, &point, BAR_COLOR);
		render_piles(&wall, &point, WALL_COLOR);
		check_collide(&ball, &bar, &wall, &Vrow, &Vcol);

		refresh();
		flag = 0;
	}
}












