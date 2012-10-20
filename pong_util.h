#include <stdio.h>
#include <unistd.h>
#include <curses.h>
#include "pong_struct.h"

#define color_on(x)    attron(COLOR_PAIR(x))
#define color_off(x)   attroff(COLOR_PAIR(x))

//define color pairs
//   FORECOLOR_ON_BACKCOLOR
#define BLUE    1
#define WHITE   2
#define YELLOW  3
#define RED     4

#define LEFTEDGE 5
#define RIGHTEDGE 120
#define BOTTOM 30
#define TOP 5


void color();// initialize the color function, setting color pairs
void draw_border(int top, int bottom, int left, int right, int color_pairs);
//draw a rectangle border with color
void render_point(Point * p, int * vcol, int * vrow, char * chr,int color_pairs);//render the motion of a single object
void render_bar(Rect * bar, int * step, char * chr, int color_pairs);
void render_piles(Piles * p, char * chr, int color_pairs);
void check_collide(Point * p, Rect * bar, int * vrow);
