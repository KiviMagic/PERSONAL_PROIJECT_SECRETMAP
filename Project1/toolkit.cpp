#include <iostream>
#include <Windows.h>
#include <random>
#include <ctime>
using namespace std;
default_random_engine engine(static_cast<unsigned int>(time(0)));
unsigned int random(unsigned int probability)//有probability/10 的概率返回值为1，最大概率为9/10
{
	
	uniform_int_distribution<unsigned int> randomInt(0,99);
	unsigned int result = randomInt(engine) % 10;
	if (result < probability)
	{
		return 1;
	}
	else
		return  0;
}
unsigned int random_6(int n)//随机等可能返回1到n这n个整数，n最大为9，用于选择方向最多到6，故命名如是
{
	int m = (n-1) * 10+9;
	uniform_int_distribution<unsigned int> randomInt(0, m);
	int result = randomInt(engine) / 10 +1;
	
		return  result;
}
unsigned int random_position(int n)//随机等可能返回1到n个整数，用于获得随机坐标的某个坐标值
{
	if (n == 0)
		return 100;
	uniform_int_distribution<unsigned int> randomInt(1, n);
	
	return  randomInt(engine);
}
void transfer(int temp[][11][11], int (*storage)[11][11], int layer)
{
	//将临时空间的数据转移至存储空间，且从存储空间的角标为1开始，即角标为含0的全部弃用
	for (int i = 5 - layer; i <= 5 + layer; i++)
	{
		for (int j = 5 - layer; j <= 5 + layer; j++)
		{
			for (int k = 5 - layer; k <= 5 + layer; k++)
			{
				storage[i - (5 - layer) + 1][j - (5 - layer) + 1][k - (5 - layer) + 1] = temp[i][j][k];

			}
		}
	}
}
