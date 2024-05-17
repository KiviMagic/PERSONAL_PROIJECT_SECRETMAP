#include "draw.h"
//画小正方形，边长50
void draw_unit_square(int x, int y)
{
	solidrectangle(x, y, x + 50, y + 50);
}
//画小立方体，(x,y)为顶面左上角坐标
void draw_unit_cube(int x, int y)
{
	POINT pts1[] = { {x,y}, {x + 50,y}, {x + 30,y + 20}, {x - 20,y + 20} };
	POINT pts2[] = { {x - 20,y + 20},{x + 30,y + 20},{x + 30,y + 70},{x - 20,y + 70} };
	POINT pts3[] = { {x + 30, y + 20},{x + 50,y},{x + 50,y + 50},{x + 30,y + 70} };
	setfillcolor(RGB(0, 0, 255));
	fillpolygon(pts1, 4);
	setfillcolor(RGB(0, 0, 200));
	fillpolygon(pts2, 4);
	setfillcolor(RGB(0, 0, 145));
	fillpolygon(pts3, 4);
}