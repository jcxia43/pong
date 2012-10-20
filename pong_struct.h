#include <stdio.h>


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
  int *point;
  Point left_top;
  int width;
  int height;
};
