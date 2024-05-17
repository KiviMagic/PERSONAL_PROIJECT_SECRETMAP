#include <iostream>
#include<string>
#include <malloc.h>
#include "Logic.h"
#include "draw.h"
#include "toolkit.h"
int Cube::sum_of_submit = 0;
int Cube::sum_of_right = 0;
Cube::Cube()
{
	scale_length = 0, capacity = 0;
	while (scale_length < 1 || scale_length > 9)
	{
		std::cout << "请输入合法范围内的阶数,1至9:" ;
		std::cin >> scale_length;
	}	
	while (capacity < 1 || capacity > scale_length * scale_length * scale_length)
	{
		std::cout << "请输入合法范围内的体积:";
		std::cin >> capacity;
	}
	std::cout << scale_length << " " << capacity << std::endl;
	storage = new int [11][11][11]{0};
	front_view = new int[11][11]{ 0 };
	back_view = new int[11][11]{ 0 };
	left_view = new int[11][11]{ 0 };
	right_view = new int[11][11]{ 0 };
	top_view = new int[11][11]{ 0 };
	bottom_view = new int[11][11]{ 0 };

	if (scale_length % 2 == 0)	
		create_even(); 
	else
		create_odd();
	analysis_block();
}
void Cube::recreate()
{
	memset(storage, 0,_msize(storage));//清空，全部赋值为0	
	memset(front_view, 0, _msize(front_view));
	memset(back_view, 0, _msize(back_view));
	memset(left_view, 0, _msize(left_view));
	memset(right_view, 0, _msize(right_view));
	memset(top_view, 0, _msize(top_view));
	memset(bottom_view, 0, _msize(bottom_view));
	
	if (this->scale_length % 2 == 0)
		create_even();
	else
		create_odd();
	analysis_block();
}
int Cube::get_scale_length()
{
	return scale_length;
}
void Cube::create_odd()
{
	int pro = 5;
	int layer = 0, num = 1, x = 5, y = 5, z = 5;//num为生成的小立方体数目，x，y，z为最大层级，
	int temp[11][11][11] = {0};//创建一个临时的空间用于承载
	temp[x][y][z] = 1;//中央存在小立方体，为衍生的基点

		while (layer <= 5 && (layer * 2 + 1) + 2 <= scale_length)
		{
			if (num == capacity)
				break;
			for (int i = x - layer; i <= x + layer; i++)
			{
				if (num == capacity)
					break;
				for (int j = y - layer; j <= y + layer; j++)
				{
					if (num == capacity)
						break;
					for (int k = z - layer; k <= z + layer; k++)
					{
						if (temp[i][j][k] == 1)//如果该区域存在小立方体，则在六个方向上进行判断
						{
							if (num == capacity)//判断小立方体数目是否达到指定数目，若足够则退出循环
								break;
							if (random(pro) && temp[i + 1][j][k] == 0)//前
								temp[i + 1][j][k] = 1, num++;
							if (num == capacity)
								break;
							if (random(pro) && temp[i - 1][j][k] == 0)//后
								temp[i - 1][j][k] = 1, num++;
							if (num == capacity)
								break;
							if (random(pro) && temp[i][j + 1][k] == 0)//右
								temp[i][j + 1][k] = 1, num++;
							if (num == capacity)
								break;
							if (random(pro) && temp[i][j - 1][k] == 0)//左
								temp[i][j - 1][k] = 1, num++;
							if (num == capacity)
								break;
							if (random(pro) && temp[i][j][k + 1] == 0)//上
								temp[i][j][k + 1] = 1, num++;
							if (num == capacity)
								break;
							if (random(pro) && temp[i][j][k - 1] == 0)//下
								temp[i][j][k - 1] = 1, num++;
							if (num == capacity)
								break;
						}
					}
				}
			}
			layer++;
		}
		if (num == capacity)//若以满足数量要求，转存，退出
		{
			transfer(temp, storage, (scale_length - 1) / 2);
			return;
		}
		//在最外层的靠后的那个面进行生成
		for (int j = y - layer + 1, i = x - layer; j <= y + layer - 1; j++)
			{
			if (num == capacity)
				break;
				for (int k = z - layer + 1; k <= z + layer - 1; k++)
				{
					if (num == capacity)
						break;
					if (temp[i][j][k] == 1)//如果该区域存在小立方体，则在五个方向上进行判断
					{
						if (num == capacity)//判断小立方体数目是否达到指定数目，若足够则退出循环
							break;
						if (random(pro) && temp[i + 1][j][k] == 0)//前
							temp[i + 1][j][k] = 1, num++;
						if (num == capacity)
							break;
						if (random(pro) && temp[i][j + 1][k] == 0)//右
							temp[i][j + 1][k] = 1, num++;
						if (num == capacity)
							break;
						if (random(pro) && temp[i][j - 1][k] == 0)//左
							temp[i][j - 1][k] = 1, num++;
						if (num == capacity)
							break;
						if (random(pro) && temp[i][j][k + 1] == 0)//上
							temp[i][j][k + 1] = 1, num++;
						if (num == capacity)
							break;
						if (random(pro) && temp[i][j][k - 1] == 0)//下
							temp[i][j][k - 1] = 1, num++;
						if (num == capacity)
							break;
					}
				}
			}
		if (num == capacity)//若以满足数量要求，转存，退出
		{
			transfer(temp, storage, (scale_length - 1) / 2);
			return;
		}
		//在最外层的靠前的那个面进行生成
		for (int j = y - layer + 1, i = x + layer; j <= y + layer - 1; j++)
			{
			if (num == capacity)
				break;
				for (int k = z - layer + 1; k <= z + layer - 1; k++)
				{
					if (num == capacity)
						break;
					if (temp[i][j][k] == 1)//如果该区域存在小立方体，则在五个方向上进行判断
					{
						if (num == capacity)//判断小立方体数目是否达到指定数目，若足够则退出循环
							break;
						if (random(pro) && temp[i - 1][j][k] == 0)//后
							temp[i - 1][j][k] = 1, num++;
						if (num == capacity)
							break;
						if (random(pro) && temp[i][j + 1][k] == 0)//右
							temp[i][j + 1][k] = 1, num++;
						if (num == capacity)
							break;
						if (random(pro) && temp[i][j - 1][k] == 0)//左
							temp[i][j - 1][k] = 1, num++;
						if (num == capacity)
							break;
						if (random(pro) && temp[i][j][k + 1] == 0)//上
							temp[i][j][k + 1] = 1, num++;
						if (num == capacity)
							break;
						if (random(pro) && temp[i][j][k - 1] == 0)//下
							temp[i][j][k - 1] = 1, num++;
						if (num == capacity)
							break;
					}
				}
			}
		if (num == capacity)//若以满足数量要求，转存，退出
		{
			transfer(temp, storage, (scale_length - 1) / 2);
			return;
		}
		//在最外层的靠左的那个面进行生成
		for (int i = x - layer + 1, j = y - layer; i <= x + layer - 1; i++)
		{
			if (num == capacity)
				break;
			for (int k = z - layer + 1; k <= z + layer - 1; k++)
			{
				if (num == capacity)
					break;
				if (temp[i][j][k] == 1)//如果该区域存在小立方体，则在五个方向上进行判断
				{
					if (num == capacity)//判断小立方体数目是否达到指定数目，若足够则退出循环
						break;
					if (random(pro) && temp[i + 1][j][k] == 0)//前
						temp[i + 1][j][k] = 1, num++;
					if (num == capacity)
						break;
					if (random(pro) && temp[i - 1][j][k] == 0)//后
						temp[i - 1][j][k] = 1, num++;
					if (num == capacity)
						break;
					if (random(pro) && temp[i][j + 1][k] == 0)//右
						temp[i][j + 1][k] = 1, num++;
					if (num == capacity)
						break;
					if (random(pro) && temp[i][j][k + 1] == 0)//上
						temp[i][j][k + 1] = 1, num++;
					if (num == capacity)
						break;
					if (random(pro) && temp[i][j][k - 1] == 0)//下
						temp[i][j][k - 1] = 1, num++;
					if (num == capacity)
						break;
				}
			}
		}
		if (num == capacity)//若以满足数量要求，转存，退出
		{
			transfer(temp, storage, (scale_length - 1) / 2);
			return;
		}
		//在最外层的靠右的那个面进行生成
		for (int i = x - layer + 1, j = y + layer; i <= x + layer - 1; i++)
		{
			if (num == capacity)
				break;
			for (int k = z - layer + 1; k <= z + layer - 1; k++)
			{
				if (num == capacity)
					break;
				if (temp[i][j][k] == 1)//如果该区域存在小立方体，则在五个方向上进行判断
				{
					if (num == capacity)//判断小立方体数目是否达到指定数目，若足够则退出循环
						break;
					if (random(pro) && temp[i + 1][j][k] == 0)//前
						temp[i + 1][j][k] = 1, num++;
					if (num == capacity)
						break;
					if (random(pro) && temp[i - 1][j][k] == 0)//后
						temp[i - 1][j][k] = 1, num++;
					if (num == capacity)
						break;
					if (random(pro) && temp[i][j - 1][k] == 0)//左
						temp[i][j - 1][k] = 1, num++;
					if (num == capacity)
						break;
					if (random(pro) && temp[i][j][k + 1] == 0)//上
						temp[i][j][k + 1] = 1, num++;
					if (num == capacity)
						break;
					if (random(pro) && temp[i][j][k - 1] == 0)//下
						temp[i][j][k - 1] = 1, num++;
					if (num == capacity)
						break;
				}
			}
		}
		if (num == capacity)//若以满足数量要求，转存，退出
		{
			transfer(temp, storage, (scale_length - 1) / 2);
			return;
		}
		//在最外层的靠上的那个面进行生成
		for (int i = x - layer + 1, k = z + layer; i <= x + layer - 1; i++)
		{
			if (num == capacity)
				break;
			for (int j = y - layer + 1, i = x - layer; j <= y + layer - 1; j++)
			{
				if (num == capacity)
					break;
				if (temp[i][j][k] == 1)//如果该区域存在小立方体，则在五个方向上进行判断
				{
					if (num == capacity)//判断小立方体数目是否达到指定数目，若足够则退出循环
						break;
					if (random(pro) && temp[i + 1][j][k] == 0)//前
						temp[i + 1][j][k] = 1, num++;
					if (num == capacity)
						break;
					if (random(pro) && temp[i - 1][j][k] == 0)//后
						temp[i - 1][j][k] = 1, num++;
					if (num == capacity)
						break;
					if (random(pro) && temp[i][j + 1][k] == 0)//右
						temp[i][j + 1][k] = 1, num++;
					if (num == capacity)
						break;
					if (random(pro) && temp[i][j - 1][k] == 0)//左
						temp[i][j - 1][k] = 1, num++;
					if (num == capacity)
						break;
					if (random(pro) && temp[i][j][k - 1] == 0)//下
						temp[i][j][k - 1] = 1, num++;
					if (num == capacity)
						break;
				}
			}
		}
		if (num == capacity)//若以满足数量要求，转存，退出
		{
			transfer(temp, storage, (scale_length - 1) / 2);
			return;
		}
		//在最外层的靠下的那个面进行生成
		for (int i = x - layer + 1, k = z - layer; i <= x + layer - 1; i++)
		{
			if (num == capacity)
				break;
			for (int j = y - layer + 1, i = x - layer; j <= y + layer - 1; j++)
			{
				if (num == capacity)
					break;
				if (temp[i][j][k] == 1)//如果该区域存在小立方体，则在五个方向上进行判断
				{
					if (num == capacity)//判断小立方体数目是否达到指定数目，若足够则退出循环
						break;
					if (random(pro) && temp[i + 1][j][k] == 0)//前
						temp[i + 1][j][k] = 1, num++;
					if (num == capacity)
						break;
					if (random(pro) && temp[i - 1][j][k] == 0)//后
						temp[i - 1][j][k] = 1, num++;
					if (num == capacity)
						break;
					if (random(pro) && temp[i][j + 1][k] == 0)//右
						temp[i][j + 1][k] = 1, num++;
					if (num == capacity)
						break;
					if (random(pro) && temp[i][j - 1][k] == 0)//左
						temp[i][j - 1][k] = 1, num++;
					if (num == capacity)
						break;
					if (random(pro) && temp[i][j][k + 1] == 0)//上
						temp[i][j][k + 1] = 1, num++;
					if (num == capacity)
						break;
				}
			}
		}
		if (num == capacity)//若以满足数量要求，转存，退出
		{
			transfer(temp, storage, (scale_length - 1) / 2);
			return;
		}
		//若仍不够，遍历，以较大概率添加
		for (int i = x - layer; i <= x + layer; i++)
		{
			if (num == capacity)
				break;
			for (int j = y - layer; j <= y + layer; j++)
			{
				if (num == capacity)
					break;
				for (int k = z - layer; k <= z + layer; k++)
				{
					if (num == capacity)
						break;
					if (random(7)&&temp[i][j][k] == 0)//如果该区域不存在小立方体，则在六个方向上进行判断
					{
						//判断六个方向上是否有小立方体保证连续性,若存在，填充，继续							
						if (i < x + layer)//防止数组越界
						{
							if (temp[i + 1][j][k] == 1)//前
							{
								temp[i][j][k] = 1, num++;
								continue;
							}
						}
						if (i > x - layer)//防止数组越界
						{
							if (temp[i - 1][j][k] == 1)//后
							{
								temp[i][j][k] = 1, num++;
								continue;
							}
						}
						if (j < y + layer)//防止数组越界
						{
							if (temp[i][j + 1][k] == 1)//右
							{
								temp[i][j][k] = 1, num++;
								continue;
							}
						}
						if (j > y - layer)//防止数组越界
						{
							if (temp[i][j - 1][k] == 1)//左
							{
								temp[i][j][k] = 1, num++;
								continue;
							}
						}
						if (k < z + layer)//防止数组越界
						{
							if (temp[i][j][k + 1] == 1)//上
							{
								temp[i][j][k] = 1, num++;
								continue;
							}
						}
						if (k > z - layer)//防止数组越界
						{
							if (temp[i][j][k - 1] == 1)//下
							{
								temp[i][j][k] = 1, num++;
								continue;
							}
						}
					}
				}
			}
		}
		if (num == capacity)//若以满足数量要求，转存，退出
		{
			transfer(temp, storage, (scale_length - 1) / 2);
			return;
		}
		//若仍不够，遍历直接添加
		while (num < capacity)
		{
			for (int i = x - layer; i <= x + layer; i++)
			{
				if (num == capacity)
					break;
				for (int j = y - layer; j <= y + layer; j++)
				{
					if (num == capacity)
						break;
					for (int k = z - layer; k <= z + layer; k++)
					{
						if (num == capacity)
							break;
						if (temp[i][j][k] == 0)//如果该区域不存在小立方体，则在六个方向上进行判断
						{
							//判断六个方向上是否有小立方体,若存在，填充，继续							
							if (i < x + layer)//防止数组越界
							{
								if (temp[i + 1][j][k] == 1)//前
								{
									temp[i ][j][k] = 1, num++;
									continue;
								}								
							}
							if (i > x - layer)//防止数组越界
							{
								if (temp[i - 1][j][k] == 1)//后
								{
									temp[i][j][k] = 1, num++;
									continue;
								}
							}
							if (j < y + layer)//防止数组越界
							{
								if (temp[i][j + 1][k] == 1)//右
								{
									temp[i][j][k] = 1, num++;
									continue;
								}
							}
							if (j > y - layer)//防止数组越界
							{
								if (temp[i][j - 1][k] == 1)//左
								{
									temp[i][j][k] = 1, num++;
									continue;
								}
							}
							if (k < z + layer)//防止数组越界
							{
								if (temp[i][j][k + 1] == 1)//上
								{
									temp[i][j][k] = 1, num++;
									continue;
								}
							}
							if (k > z - layer)//防止数组越界
							{
								if (temp[i][j][k - 1] == 1)//下
								{
									temp[i][j][k] = 1, num++;
									continue;
								}
							}							
						}
					}
				}
			}
		}
	transfer(temp, storage, (scale_length-1)/2);//转存，退出
	return;
}
int Cube::detect_x_channel(int y, int z)
{
	int a = 0;
	for (int i = 1; i <= scale_length; i++)
	{
		a += storage[i][y][z];
	}
	return a;
}
int Cube::detect_y_channel(int x, int z)
{
	int a = 0;
	for (int i = 1; i <= scale_length; i++)
	{
		a += storage[x][i][z];
	}
	return a;
}
int Cube::detect_z_channel(int x, int y)
{
	int a = 0;
	for (int i = 1; i <= scale_length; i++)
	{
		a += storage[x][y][i];
	}
	return a;
}
void Cube::analysis_block()//解析块信息,得到视图的部分信息
{//x方向通道，前后视图
	for (int i = 1; i <= scale_length; i ++)
	{
		for (int j = 1; j <= scale_length; j++)
		{
			if (detect_x_channel( i, j))
			{
				front_view[i][j] = 1;
				back_view[scale_length + 1 - i][j] = 1;//左右颠倒
			}
			else
			{
				front_view[i][j] = 0;
				back_view[scale_length + 1 - i][j] = 0;//左右颠倒
			}
		}
	}
//y方向通道，左右视图
	for (int i = 1; i <= scale_length; i++)
	{
		for (int j = 1; j <= scale_length; j++)
		{
			if (detect_y_channel( i, j))
			{
				left_view[i][j] = 1;
				right_view[scale_length + 1 - i][j] = 1;//左右颠倒
			}
			else
			{
				left_view[i][j] = 0;
				right_view[scale_length + 1 - i][j] = 0;//左右颠倒
			}
		}
	}
//z方向通道，上下视图
	for (int i = 1; i <= scale_length; i++)
	{
		for (int j = 1; j <= scale_length; j++)
		{
			if (detect_z_channel( i, j))
			{
				bottom_view[j][i] = 1;
				top_view[j][scale_length + 1 - i] = 1;//上下颠倒
			}
			else
			{
				bottom_view[j][i] = 0;
				top_view[j][scale_length + 1 - i] = 0;//上下颠倒
			}
		}
	}
}
void Cube::display_2d()
{
	for (int k = 1; k <= scale_length; k++)
	{
		for (int i = 1; i <= scale_length; i++)
		{
			for (int j = 1; j <= scale_length; j++)
			{
				std::cout << storage[i][j][k] << " ";
			}
			std::cout << std::endl;
		}
		std::cout << std::endl;
		std::cout << std::endl;
	}
}
void Cube::display_3d(IMAGE* draw_bk)
{
	SetWorkingImage(draw_bk);//设置画图设备
	for (int z = 1; z <= this->scale_length; z++)
	{
		for (int x = 1; x <= this->scale_length; x++)
		{
			for (int y = 1; y <= this->scale_length; y++)
			{
				if (storage[x][y][z] == 1)
					draw_unit_cube(200 + 50 * (y - 1) - 20 * (x - 1), 470 - (z-1) * 50 + 20 * (x - 1));
				else
					continue;
			}
		}
	}
	SetWorkingImage();//恢复默认画图设备
}
void Cube::display_3d_90(IMAGE* draw_bk)
{
	SetWorkingImage(draw_bk);//设置画图设备
	for (int z = 1; z <= this->scale_length; z++)
	{
		for (int y = 1; y <= this->scale_length; y++)
		{
			for (int x = scale_length; x >= 1; x--)
			{
				if (storage[x][y][z] == 1)
					draw_unit_cube(200 + 50 * (scale_length - x) - 20 * (y - 1), 470 - (z - 1) * 50 + 20 * (y - 1));
				else
					continue;
			}
		}
	}
	SetWorkingImage();//恢复默认画图设备
}
void Cube::display_3d_180(IMAGE* draw_bk)
{
	SetWorkingImage(draw_bk);//设置画图设备
	for (int z = 1; z <= this->scale_length; z++)
	{
		for (int x = scale_length; x >= 1; x--)
		{
			for (int y = scale_length; y >= 1; y--)
			{
				if (storage[x][y][z] == 1)
					draw_unit_cube(200 + 50 * (scale_length - y) - 20 * (scale_length - x), 470 - (z - 1) * 50 + 20 * (scale_length - x));
				else
					continue;
			}
		}
	}
	SetWorkingImage();//恢复默认画图设备
}
void Cube::display_3d_270(IMAGE* draw_bk)
{
	SetWorkingImage(draw_bk);//设置画图设备
	for (int z = 1; z <= this->scale_length; z++)
	{
		for (int y = scale_length; y >= 1; y--)
		{
			for (int x = 1; x <= scale_length; x++)
			{
				if (storage[x][y][z] == 1)
					draw_unit_cube(200 + 50 * (x - 1) - 20 * (scale_length - y), 470 - (z - 1) * 50 + 20 * (scale_length - y));
				else
					continue;
			}
		}
	}
	SetWorkingImage();//恢复默认画图设备
}
void Cube::create_even()
{	//随机生成第一个小立方体的坐标
	int  x = random_position(scale_length);
	int  y = random_position(scale_length);
	int  z = random_position(scale_length);
	int  x_next = 0, y_next = 0, z_next = 0;
	storage[x][y][z] = 1;
	int num = 1;
	for (int time = 1; time < capacity; time ++)
	{
		int possible = 0, top = 0, bottom = 0, left = 0, right = 0, front = 0, back = 0;
		//在z不是最大值的情况下检查上方，防止数组越界
		if (z < scale_length)
		{
			if (storage[x][y][z + 1] == 0)//若上方为空，可能方向加一，并给该方向编号
			{
				possible++;
				top = possible;
			}
			else
				top = -1;
		}
		else
			top = -1;
		//在z不是最小值的情况下检查下方，防止数组越界
		if (z > 1)
		{
			if (storage[x][y][z - 1] == 0)//若下方为空，可能方向加一，并给该方向编号
			{
				possible++;
				bottom = possible;
			}
			else
				bottom = -2;
		}
		else
			bottom = -2;
		//在y不是最小值的情况下检查左方，防止数组越界
		if (y > 1)
		{
			if (storage[x][y - 1][z] == 0)//若左方为空，可能方向加一，并给该方向编号
			{
				possible++;
				left = possible;
			}
			else
				left = -3;
		}
		else
			left = -3;
		//在y不是最大值的情况下检查右方，防止数组越界
		if (y < scale_length)
		{
			if (storage[x][y + 1][z] == 0)//若右方为空，可能方向加一，并给该方向编号
			{
				possible++;
				right = possible;
			}
			else
				right = -4;
		}
		else
			right = -4;
		//在x不是最大值的情况下检查前方，防止数组越界
		if (x < scale_length)
		{
			if (storage[x + 1][y][z] == 0)//若前方为空，可能方向加一，并给该方向编号
			{
				possible++;
				front = possible;
			}
			else
				front = -5;
		}
		else
			front = -5;
		//在x不是最小值的情况下检查后方，防止数组越界
		if (x > 1)
		{
			if (storage[x - 1][y][z] == 0)//若后方为空，可能方向加一，并给该方向编号
			{
				possible++;
				back = possible;
			}
			else
				back = -6;
		}
		else
			back = -6;
		//选择一个方向填充
		int position = random_position(possible);
		if (position == top)
		{
			storage[x][y][z + 1] = 1;
			num++;
			z = z + 1;
			continue;
		}
		if (position == bottom)
		{
			storage[x][y][z -1] = 1;
			num++;
			z = z - 1;
			continue;
		}
		if (position == right)
		{
			storage[x][y + 1][z] = 1;
			num++;
			y = y + 1;
			continue;
		}
		if (position == left)
		{
			storage[x][y - 1][z] = 1;
			num++;
			y = y - 1;
			continue;
		}
		if (position == front)
		{
			storage[x + 1][y][z] = 1;
			num++;
			x = x + 1;
			continue;
		}
		if (position == back)
		{
			storage[x - 1][y][z] = 1;
			num++;
			x = x - 1;
			continue;
		}
	}

	//若数量不足，遍历添加
	while (num < capacity)
	{
		for (int i = 1; i <= scale_length; i++)
		{
			if (num == capacity)
				break;
			for (int j = 1; j <= scale_length; j++)
			{
				if (num == capacity)
					break;
				for (int k = 1; k <= scale_length; k++)
				{
					if (num == capacity)
						break;
					if (storage[i][j][k] == 0)//如果该区域不存在小立方体，则在六个方向上进行判断
					{
						//判断六个方向上是否有小立方体,若存在，填充，继续							
						if (i < scale_length)//防止数组越界
						{
							if (storage[i + 1][j][k] == 1)//前
							{
								storage[i][j][k] = 1, num++;
								continue;
							}
						}
						if (i > 1)//防止数组越界
						{
							if (storage[i - 1][j][k] == 1)//后
							{
								storage[i][j][k] = 1, num++;
								continue;
							}
						}
						if (j < scale_length)//防止数组越界
						{
							if (storage[i][j + 1][k] == 1)//右
							{
								storage[i][j][k] = 1, num++;
								continue;
							}
						}
						if (j > 1)//防止数组越界
						{
							if (storage[i][j - 1][k] == 1)//左
							{
								storage[i][j][k] = 1, num++;
								continue;
							}
						}
						if (k < scale_length)//防止数组越界
						{
							if (storage[i][j][k + 1] == 1)//上
							{
								storage[i][j][k] = 1, num++;
								continue;
							}
						}
						if (k > 1)//防止数组越界
						{
							if (storage[i][j][k - 1] == 1)//下
							{
								storage[i][j][k] = 1, num++;
								continue;
							}
						}
					}
				}
			}
		}
	}

}
void Cube::display_front_view()
{
	for (int j = scale_length; j >= 1; j--)
	{
		for (int i = 1; i <= scale_length; i++)
		{
			std::cout << front_view[i][j] ;
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}
void Cube::display_back_view()
{
	for (int j = scale_length; j >= 1; j--)
	{
		for (int i = 1; i <= scale_length; i++)
		{
			std::cout << back_view[i][j];
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}
void Cube::display_left_view()
{
	for (int j = scale_length; j >= 1; j--)
	{
		for (int i = 1; i <= scale_length; i++)
		{
			std::cout << left_view[i][j];
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}
void Cube::display_right_view()
{
	for (int j = scale_length; j >= 1; j--)
	{
		for (int i = 1; i <= scale_length; i++)
		{
			std::cout << right_view[i][j];
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}
void Cube::display_top_view()
{
	for (int j = scale_length; j >= 1; j--)
	{
		for (int i = 1; i <= scale_length; i++)
		{
			std::cout << top_view[i][j];
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}
void Cube::display_bottom_view()
{
	for (int j = scale_length; j >= 1; j--)
	{
		for (int i = 1; i <= scale_length; i++)
		{
			std::cout << bottom_view[i][j];
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}