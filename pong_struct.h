#include <stdio.h>

#define MAXSIZE 100

typedef struct point Point;
typedef struct rect Rect;
typedef struct piles Piles;

struct point
{
  int row;
  int col;
};
struct rect
{
  Point left_top;
  Point right_bottom;
};
struct piles
{
  int point[MAXSIZE][MAXSIZE];
  Point left_top;
  int width;
  int height;
};
