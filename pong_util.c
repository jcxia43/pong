#include "pong_util.h"

void color()
{
	start_color();
	init_pair(1, COLOR_BLACK, COLOR_BLUE);//BLACK_ON_BROWN
	init_pair(2, COLOR_BLACK, COLOR_WHITE);//BLACK_ON_WHITE
	init_pair(3, COLOR_BLACK, COLOR_YELLOW);//BLACK_ON_YELLOW
	init_pair(4, COLOR_BLACK, COLOR_RED);
}

void draw_border(int top, int bottom, int left, int right, int color_pairs)
{
	int i;
	color_on(color_pairs);
	for(i = left; i <= right; i++){
		move(top - 1, i);
		addstr(" ");
	}
	for(i = left; i <= right; i++){
		move(bottom + 1, i);
		addstr(" ");
	}
	for(i = top - 1; i <= bottom + 1; i++){
		move(i, left - 1);
		addstr(" ");
	}
	for(i = top - 1; i <= bottom + 1; i++){
		move(i, right + 1);
		addstr(" ");
	}
	color_off(color_pairs);
	
}
//render the point appear in the next position
//p(col + vcol, row + vrow) and make sure this does't collide with borders
void render_point(Point * p, int * vcol, int * vrow,char * chr, int color_pairs)
{
	int i, r, c;
	c = *vcol;
	r = *vrow;
	p->col += c;
	if (p->col <= LEFTEDGE){
		p->col = LEFTEDGE;
		*vcol = -c;
	}
	if (p->col >= RIGHTEDGE){
		p->col = RIGHTEDGE;
		*vcol = -c;
	}
	p->row += r;
	if (p->row <= TOP){
		p->row = TOP;
		*vrow = -r;
	}
	if (p->row >= BOTTOM){
		p->row = BOTTOM;
		*vrow = 0;
		*vcol = 0;
		printw("GAMEOVER!!!!!!!");
	}
	color_on(color_pairs);
	mvaddstr(p->row, p->col, chr);
	color_off(color_pairs);
	move(0,0);
}

void render_bar(Rect * bar, int * step, char * chr,int color_pairs)
{
	int i, n;
	int top_row = bar->left_top.row;
	int bottom_row = bar->right_bottom.row;
	int left_col = bar->left_top.col;
	int right_col = bar->right_bottom.col;
	
	if (right_col + *step <= RIGHTEDGE && left_col + *step >= LEFTEDGE)
		i = *step;
	else if (right_col + *step > RIGHTEDGE)
		i = RIGHTEDGE - right_col;
	else
		i = LEFTEDGE - left_col;

	bar->left_top.col += i;
	bar->right_bottom.col += i;
	left_col = bar->left_top.col;
	right_col = bar->right_bottom.col
		;
	for (i = top_row; i <= bottom_row; ++i){
		for (n = left_col; n <= right_col; ++n){
			color_on(color_pairs);
			mvaddstr(i, n, chr);
			color_off(color_pairs);
			move(0, 0);
		}
	}
	*step = 0;
}

void check_collide(Point * p, Rect * bar, Piles * wall, int * vrow, int * vcol)
{
	//  printw("%d, %d\n", p->col, p->row);
	//  printw("%d, %d\n", bar->left_top.col, bar->right_bottom.col);
  
	if (p->col >= bar->left_top.col && p->col <= bar->right_bottom.col){
		if (p->row == bar->left_top.row - 1){
			*vrow = -(*vrow);
		}
	}

	int prow = p->row - wall->left_top.row + (*vrow);
	int pprow = p->row - wall->left_top.row;
	int pcol = p->col - wall->left_top.col + (*vcol);
	int ppcol = p->col = wall->left_top.col;
	if (prow >= 0 && prow < wall->height && ppcol >=0 && ppcol < wall->width){
		if (0 != wall->point[prow][ppcol]){
			wall->point[prow][ppcol] = 0;
			*vrow = -(*vrow);
		}
	}
	else if (pprow >= 0 && pprow < wall->height && pcol >=0 && pcol < wall->width){
		if (0 != wall->point[pprow][pcol]){
			wall->point[pprow][pcol] = 0;
			*vcol = -(*vcol);
		}
	}
	else if (prow >= 0 && prow < wall->height && pcol >=0 && pcol < wall->width){
		if (0 != wall->point[prow][pcol]){
			wall->point[prow][pcol] = 0;
			*vrow = -(*vrow);
			*vcol = -(*vcol);
		}
	}
		

}


void render_piles(Piles * p, char * chr, int color_pairs)
{
	int i, n;
	int * b;
	for (i = 0; i < p->height; ++i){
		for (n = 0; n < p->width; ++n){
			if (0 != p->point[i][n]){
				color_on(color_pairs);
				mvaddstr(i + p->left_top.row,n + p->left_top.col,chr);
				color_off(color_pairs);
				move(0,0);
			}
		}
	}
}
