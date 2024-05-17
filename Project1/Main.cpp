#include <iostream>
#include <conio.h>
#include "easyx.h"
#include "Logic.h"
#include "toolkit.h" 
#include "window.h"
#include "BASIC_BUTTON.h"
#include "interaction.h"
#include "draw.h"
#include <fstream>
#include <Windows.h>
using namespace std;

int main()
 {

	window win(1280, 720, EX_SHOWCONSOLE);
	interaction interact ;
	interact.run();
	return 0;
}
