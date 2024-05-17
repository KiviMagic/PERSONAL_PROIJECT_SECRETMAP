#pragma once
//1、产生从m到n的非负数随机数
#ifndef TOOLKIT_H
#define TOOLKIT_H
#include <iostream>
unsigned int random(unsigned int);
unsigned int random_6();
unsigned int random_position(int);
void transfer(int[][11][11], int(*)[11][11], int time);

#endif // !TOOLKIT_H

