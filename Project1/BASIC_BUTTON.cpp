#include "BASIC_BUTTON.h"
#include <iostream>
BASIC_BUTTON::BASIC_BUTTON(int x, int y, int w, int h)
{
	this->x = x;
	this->y = y;
	this->w = w;
	this->h = h;
}

void BASIC_BUTTON::set_sticker( LPCTSTR pImgFile, int nWidth, int nHeight , bool bResize )
{
	loadimage(&this->sticker, pImgFile, nWidth, nHeight, bResize);
}

int BASIC_BUTTON::getx()
{
	return x;
}

int BASIC_BUTTON::gety()
{
	return y;
}

int BASIC_BUTTON::width()
{
	return w;
}

int BASIC_BUTTON::hight()
{
	return h;
}

void BASIC_BUTTON::getmessage(const ExMessage& msg)
{
	this->msg = msg;
}


void BASIC_BUTTON::show()
{
	putimage(x, y, &sticker);
}

bool BASIC_BUTTON::is_inside()
{
	if (msg.x >= x && msg.x <= x + w && msg.y >= y && msg.y <= y + h)
		return true;
	else
		return false;
	
}

bool BASIC_BUTTON::beclicked()
{
	if (msg.lbutton)
		return true;
	else
	return false;
}

void BASIC_BUTTON::reset_pos_size(int x, int y, int w, int h)
{
	this->x = x;
	this->y = y;
	this->w = w;
	this->h = h;
}

bool operator<(ExMessage msg, BASIC_BUTTON button)
{
	if (msg.x >= button.x && msg.x <= button.x + button.w && msg.y >= button.y && msg.y <= button.y + button.h)
		return true;
	else
		return false;
}

SEC_BUTTON::SEC_BUTTON(int x, int y, int w, int h)
	:BASIC_BUTTON(x, y, w, h)
{
}

void SEC_BUTTON::set_stickers(LPCTSTR normal, LPCTSTR touch, int nWidth, int nHeight, bool bResizeLPCTSTR)
{
	BASIC_BUTTON::set_sticker(normal, nWidth, nHeight, bResizeLPCTSTR);
	loadimage(&this->sticker_touch, touch, nWidth, nHeight, bResizeLPCTSTR);
}

void SEC_BUTTON::show_touch()
{
	putimage(getx(), gety(), &sticker_touch);
}


THIRD_BUTTON::THIRD_BUTTON(int x, int y, int w, int h, int f)
	:BASIC_BUTTON(x, y, w, h),flag(f)
{
}

//正常样式灰色
void THIRD_BUTTON::show_normal()
{
	int x = getx(), y = gety();
	int x_r = x + width(), y_b = y + hight();	
	setfillcolor(RGB(150, 150, 150));
	fillrectangle(x, y, x_r, y_b);
}
//确定样式，蓝色
void THIRD_BUTTON::show_confirmed()
{
	int x = getx(), y = gety();
	int x_r = x + width(), y_b = y + hight();
	setfillcolor(RGB(0, 200, 255));
	fillrectangle(x, y, x_r, y_b);
}
void THIRD_BUTTON::set_flag()
{
	flag *= -1;
}
int THIRD_BUTTON::get_flag()
{
	return flag;
}
//触碰样式，红色
void THIRD_BUTTON::show_touch()
{
	int x = getx(), y = gety();
	int x_r = x + width(), y_b = y + hight();
	setfillcolor(RGB(255, 55, 0));
	fillrectangle(x, y,x_r, y_b);
}
void THIRD_BUTTON::show_3(int touch)
{
	if (flag == 1)
		show_confirmed();
	else if (touch)
		show_touch();
	else
		show_normal();		
}
