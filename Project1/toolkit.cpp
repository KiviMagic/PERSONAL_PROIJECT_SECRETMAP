#include <iostream>
#include <Windows.h>
#include <random>
#include <ctime>
using namespace std;
default_random_engine engine(static_cast<unsigned int>(time(0)));
unsigned int random(unsigned int probability)//��probability/10 �ĸ��ʷ���ֵΪ1��������Ϊ9/10
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
unsigned int random_6(int n)//����ȿ��ܷ���1��n��n��������n���Ϊ9������ѡ������ൽ6������������
{
	int m = (n-1) * 10+9;
	uniform_int_distribution<unsigned int> randomInt(0, m);
	int result = randomInt(engine) / 10 +1;
	
		return  result;
}
unsigned int random_position(int n)//����ȿ��ܷ���1��n�����������ڻ����������ĳ������ֵ
{
	if (n == 0)
		return 100;
	uniform_int_distribution<unsigned int> randomInt(1, n);
	
	return  randomInt(engine);
}
void transfer(int temp[][11][11], int (*storage)[11][11], int layer)
{
	//����ʱ�ռ������ת�����洢�ռ䣬�ҴӴ洢�ռ�ĽǱ�Ϊ1��ʼ�����Ǳ�Ϊ��0��ȫ������
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
