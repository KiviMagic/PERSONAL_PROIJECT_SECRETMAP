#include "window.h"

window::window(int w, int h, int flag)
{
	handle = initgraph(w, h, flag);
}

void window::setBG()
{	
	IMAGE background;
	loadimage(&background, _T("image\\home.png"));
	putimage(0, 0, &background);
}

void window::set_title(const std::string& title)
{
	::SetWindowText(handle, _T("window"));
}

int window::closewindow()
{
	return 0;
}


