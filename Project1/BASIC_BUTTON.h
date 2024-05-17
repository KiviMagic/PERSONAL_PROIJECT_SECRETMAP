#pragma once
#ifndef BASIC_BUTTON_H
#define BASIC_BUTTON_H
#include "easyx.h"
class BASIC_BUTTON
{
public:
	BASIC_BUTTON(int x, int y, int w, int h);
	void set_sticker(LPCTSTR pImgFile, int nWidth = 0, int nHeight = 0, bool bResize = false);
	int getx();
	int gety();
	int width();
	int hight();
	void getmessage(const ExMessage& msg );
	void show();
	bool is_inside();
	bool beclicked();
	void reset_pos_size(int x, int y, int w, int h);
	friend bool operator< (ExMessage, BASIC_BUTTON);
private:
	int x;
	int y;
	int w;
	int h;
	ExMessage msg = {0};
	IMAGE sticker;
	bool push_flag = 0;
};

class SEC_BUTTON : public BASIC_BUTTON
{
public:
	SEC_BUTTON(int x, int y, int w, int h);
	void set_stickers(LPCTSTR , LPCTSTR, int nWidth = 0, int nHeight = 0, bool bResize = false);
	void show_touch();
private:
	IMAGE sticker_touch;

};
class THIRD_BUTTON :public BASIC_BUTTON
{
public:
	THIRD_BUTTON(int x, int y, int w, int h, int = -1);
	void show_3(int);
	void show_normal();
	void show_touch();
	void show_confirmed();
	void set_flag();
	int get_flag();
private :
	int flag;
};
#endif

