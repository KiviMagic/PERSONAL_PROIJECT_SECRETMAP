#pragma once
#ifndef INTERACTION_H
#define INTERACTION_H
# include <iostream>
#include "easyx.h"
#include <vector>
#include "BASIC_BUTTON.h"
#include "Logic.h"
class interaction
{
	enum CLICK{ LOGIN, RANKING_lIST, EXIT, HOME };
public:
	interaction();
	void run();
	int home();
	int login();
	int ranking_list();
	void exit();
	int display_menu_of_show();
	int answer(int,Cube *);
	int answer_v1(int, Cube*);
	~interaction();
private:
	ExMessage msg = {0};
	IMAGE home_bk, view_bk, answer_bk ;
	std::vector<BASIC_BUTTON*> menu_btns;
	std::vector<SEC_BUTTON*> second_btns;
};
#endif // !INTERACTION_H

