#ifndef WINDOW_H
#define WINDOE_H
#include <iostream>
#include <easyx.h>
#include <string>
class window
{
public:
	window(int w, int h, int flag);
	void setBG();
	void set_title(const std::string&);
	int closewindow();
	
private:
	HWND  handle;
	ExMessage msg;
};

#endif // !WINDOW_H

