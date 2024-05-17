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
		std::cout << "������Ϸ���Χ�ڵĽ���,1��9:" ;
		std::cin >> scale_length;
	}	
	while (capacity < 1 || capacity > scale_length * scale_length * scale_length)
	{
		std::cout << "������Ϸ���Χ�ڵ����:";
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
	memset(storage, 0,_msize(storage));//��գ�ȫ����ֵΪ0	
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
	int layer = 0, num = 1, x = 5, y = 5, z = 5;//numΪ���ɵ�С��������Ŀ��x��y��zΪ���㼶��
	int temp[11][11][11] = {0};//����һ����ʱ�Ŀռ����ڳ���
	temp[x][y][z] = 1;//�������С�����壬Ϊ�����Ļ���

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
						if (temp[i][j][k] == 1)//������������С�����壬�������������Ͻ����ж�
						{
							if (num == capacity)//�ж�С��������Ŀ�Ƿ�ﵽָ����Ŀ�����㹻���˳�ѭ��
								break;
							if (random(pro) && temp[i + 1][j][k] == 0)//ǰ
								temp[i + 1][j][k] = 1, num++;
							if (num == capacity)
								break;
							if (random(pro) && temp[i - 1][j][k] == 0)//��
								temp[i - 1][j][k] = 1, num++;
							if (num == capacity)
								break;
							if (random(pro) && temp[i][j + 1][k] == 0)//��
								temp[i][j + 1][k] = 1, num++;
							if (num == capacity)
								break;
							if (random(pro) && temp[i][j - 1][k] == 0)//��
								temp[i][j - 1][k] = 1, num++;
							if (num == capacity)
								break;
							if (random(pro) && temp[i][j][k + 1] == 0)//��
								temp[i][j][k + 1] = 1, num++;
							if (num == capacity)
								break;
							if (random(pro) && temp[i][j][k - 1] == 0)//��
								temp[i][j][k - 1] = 1, num++;
							if (num == capacity)
								break;
						}
					}
				}
			}
			layer++;
		}
		if (num == capacity)//������������Ҫ��ת�棬�˳�
		{
			transfer(temp, storage, (scale_length - 1) / 2);
			return;
		}
		//�������Ŀ�����Ǹ����������
		for (int j = y - layer + 1, i = x - layer; j <= y + layer - 1; j++)
			{
			if (num == capacity)
				break;
				for (int k = z - layer + 1; k <= z + layer - 1; k++)
				{
					if (num == capacity)
						break;
					if (temp[i][j][k] == 1)//������������С�����壬������������Ͻ����ж�
					{
						if (num == capacity)//�ж�С��������Ŀ�Ƿ�ﵽָ����Ŀ�����㹻���˳�ѭ��
							break;
						if (random(pro) && temp[i + 1][j][k] == 0)//ǰ
							temp[i + 1][j][k] = 1, num++;
						if (num == capacity)
							break;
						if (random(pro) && temp[i][j + 1][k] == 0)//��
							temp[i][j + 1][k] = 1, num++;
						if (num == capacity)
							break;
						if (random(pro) && temp[i][j - 1][k] == 0)//��
							temp[i][j - 1][k] = 1, num++;
						if (num == capacity)
							break;
						if (random(pro) && temp[i][j][k + 1] == 0)//��
							temp[i][j][k + 1] = 1, num++;
						if (num == capacity)
							break;
						if (random(pro) && temp[i][j][k - 1] == 0)//��
							temp[i][j][k - 1] = 1, num++;
						if (num == capacity)
							break;
					}
				}
			}
		if (num == capacity)//������������Ҫ��ת�棬�˳�
		{
			transfer(temp, storage, (scale_length - 1) / 2);
			return;
		}
		//�������Ŀ�ǰ���Ǹ����������
		for (int j = y - layer + 1, i = x + layer; j <= y + layer - 1; j++)
			{
			if (num == capacity)
				break;
				for (int k = z - layer + 1; k <= z + layer - 1; k++)
				{
					if (num == capacity)
						break;
					if (temp[i][j][k] == 1)//������������С�����壬������������Ͻ����ж�
					{
						if (num == capacity)//�ж�С��������Ŀ�Ƿ�ﵽָ����Ŀ�����㹻���˳�ѭ��
							break;
						if (random(pro) && temp[i - 1][j][k] == 0)//��
							temp[i - 1][j][k] = 1, num++;
						if (num == capacity)
							break;
						if (random(pro) && temp[i][j + 1][k] == 0)//��
							temp[i][j + 1][k] = 1, num++;
						if (num == capacity)
							break;
						if (random(pro) && temp[i][j - 1][k] == 0)//��
							temp[i][j - 1][k] = 1, num++;
						if (num == capacity)
							break;
						if (random(pro) && temp[i][j][k + 1] == 0)//��
							temp[i][j][k + 1] = 1, num++;
						if (num == capacity)
							break;
						if (random(pro) && temp[i][j][k - 1] == 0)//��
							temp[i][j][k - 1] = 1, num++;
						if (num == capacity)
							break;
					}
				}
			}
		if (num == capacity)//������������Ҫ��ת�棬�˳�
		{
			transfer(temp, storage, (scale_length - 1) / 2);
			return;
		}
		//�������Ŀ�����Ǹ����������
		for (int i = x - layer + 1, j = y - layer; i <= x + layer - 1; i++)
		{
			if (num == capacity)
				break;
			for (int k = z - layer + 1; k <= z + layer - 1; k++)
			{
				if (num == capacity)
					break;
				if (temp[i][j][k] == 1)//������������С�����壬������������Ͻ����ж�
				{
					if (num == capacity)//�ж�С��������Ŀ�Ƿ�ﵽָ����Ŀ�����㹻���˳�ѭ��
						break;
					if (random(pro) && temp[i + 1][j][k] == 0)//ǰ
						temp[i + 1][j][k] = 1, num++;
					if (num == capacity)
						break;
					if (random(pro) && temp[i - 1][j][k] == 0)//��
						temp[i - 1][j][k] = 1, num++;
					if (num == capacity)
						break;
					if (random(pro) && temp[i][j + 1][k] == 0)//��
						temp[i][j + 1][k] = 1, num++;
					if (num == capacity)
						break;
					if (random(pro) && temp[i][j][k + 1] == 0)//��
						temp[i][j][k + 1] = 1, num++;
					if (num == capacity)
						break;
					if (random(pro) && temp[i][j][k - 1] == 0)//��
						temp[i][j][k - 1] = 1, num++;
					if (num == capacity)
						break;
				}
			}
		}
		if (num == capacity)//������������Ҫ��ת�棬�˳�
		{
			transfer(temp, storage, (scale_length - 1) / 2);
			return;
		}
		//�������Ŀ��ҵ��Ǹ����������
		for (int i = x - layer + 1, j = y + layer; i <= x + layer - 1; i++)
		{
			if (num == capacity)
				break;
			for (int k = z - layer + 1; k <= z + layer - 1; k++)
			{
				if (num == capacity)
					break;
				if (temp[i][j][k] == 1)//������������С�����壬������������Ͻ����ж�
				{
					if (num == capacity)//�ж�С��������Ŀ�Ƿ�ﵽָ����Ŀ�����㹻���˳�ѭ��
						break;
					if (random(pro) && temp[i + 1][j][k] == 0)//ǰ
						temp[i + 1][j][k] = 1, num++;
					if (num == capacity)
						break;
					if (random(pro) && temp[i - 1][j][k] == 0)//��
						temp[i - 1][j][k] = 1, num++;
					if (num == capacity)
						break;
					if (random(pro) && temp[i][j - 1][k] == 0)//��
						temp[i][j - 1][k] = 1, num++;
					if (num == capacity)
						break;
					if (random(pro) && temp[i][j][k + 1] == 0)//��
						temp[i][j][k + 1] = 1, num++;
					if (num == capacity)
						break;
					if (random(pro) && temp[i][j][k - 1] == 0)//��
						temp[i][j][k - 1] = 1, num++;
					if (num == capacity)
						break;
				}
			}
		}
		if (num == capacity)//������������Ҫ��ת�棬�˳�
		{
			transfer(temp, storage, (scale_length - 1) / 2);
			return;
		}
		//�������Ŀ��ϵ��Ǹ����������
		for (int i = x - layer + 1, k = z + layer; i <= x + layer - 1; i++)
		{
			if (num == capacity)
				break;
			for (int j = y - layer + 1, i = x - layer; j <= y + layer - 1; j++)
			{
				if (num == capacity)
					break;
				if (temp[i][j][k] == 1)//������������С�����壬������������Ͻ����ж�
				{
					if (num == capacity)//�ж�С��������Ŀ�Ƿ�ﵽָ����Ŀ�����㹻���˳�ѭ��
						break;
					if (random(pro) && temp[i + 1][j][k] == 0)//ǰ
						temp[i + 1][j][k] = 1, num++;
					if (num == capacity)
						break;
					if (random(pro) && temp[i - 1][j][k] == 0)//��
						temp[i - 1][j][k] = 1, num++;
					if (num == capacity)
						break;
					if (random(pro) && temp[i][j + 1][k] == 0)//��
						temp[i][j + 1][k] = 1, num++;
					if (num == capacity)
						break;
					if (random(pro) && temp[i][j - 1][k] == 0)//��
						temp[i][j - 1][k] = 1, num++;
					if (num == capacity)
						break;
					if (random(pro) && temp[i][j][k - 1] == 0)//��
						temp[i][j][k - 1] = 1, num++;
					if (num == capacity)
						break;
				}
			}
		}
		if (num == capacity)//������������Ҫ��ת�棬�˳�
		{
			transfer(temp, storage, (scale_length - 1) / 2);
			return;
		}
		//�������Ŀ��µ��Ǹ����������
		for (int i = x - layer + 1, k = z - layer; i <= x + layer - 1; i++)
		{
			if (num == capacity)
				break;
			for (int j = y - layer + 1, i = x - layer; j <= y + layer - 1; j++)
			{
				if (num == capacity)
					break;
				if (temp[i][j][k] == 1)//������������С�����壬������������Ͻ����ж�
				{
					if (num == capacity)//�ж�С��������Ŀ�Ƿ�ﵽָ����Ŀ�����㹻���˳�ѭ��
						break;
					if (random(pro) && temp[i + 1][j][k] == 0)//ǰ
						temp[i + 1][j][k] = 1, num++;
					if (num == capacity)
						break;
					if (random(pro) && temp[i - 1][j][k] == 0)//��
						temp[i - 1][j][k] = 1, num++;
					if (num == capacity)
						break;
					if (random(pro) && temp[i][j + 1][k] == 0)//��
						temp[i][j + 1][k] = 1, num++;
					if (num == capacity)
						break;
					if (random(pro) && temp[i][j - 1][k] == 0)//��
						temp[i][j - 1][k] = 1, num++;
					if (num == capacity)
						break;
					if (random(pro) && temp[i][j][k + 1] == 0)//��
						temp[i][j][k + 1] = 1, num++;
					if (num == capacity)
						break;
				}
			}
		}
		if (num == capacity)//������������Ҫ��ת�棬�˳�
		{
			transfer(temp, storage, (scale_length - 1) / 2);
			return;
		}
		//���Բ������������Խϴ�������
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
					if (random(7)&&temp[i][j][k] == 0)//��������򲻴���С�����壬�������������Ͻ����ж�
					{
						//�ж������������Ƿ���С�����屣֤������,�����ڣ���䣬����							
						if (i < x + layer)//��ֹ����Խ��
						{
							if (temp[i + 1][j][k] == 1)//ǰ
							{
								temp[i][j][k] = 1, num++;
								continue;
							}
						}
						if (i > x - layer)//��ֹ����Խ��
						{
							if (temp[i - 1][j][k] == 1)//��
							{
								temp[i][j][k] = 1, num++;
								continue;
							}
						}
						if (j < y + layer)//��ֹ����Խ��
						{
							if (temp[i][j + 1][k] == 1)//��
							{
								temp[i][j][k] = 1, num++;
								continue;
							}
						}
						if (j > y - layer)//��ֹ����Խ��
						{
							if (temp[i][j - 1][k] == 1)//��
							{
								temp[i][j][k] = 1, num++;
								continue;
							}
						}
						if (k < z + layer)//��ֹ����Խ��
						{
							if (temp[i][j][k + 1] == 1)//��
							{
								temp[i][j][k] = 1, num++;
								continue;
							}
						}
						if (k > z - layer)//��ֹ����Խ��
						{
							if (temp[i][j][k - 1] == 1)//��
							{
								temp[i][j][k] = 1, num++;
								continue;
							}
						}
					}
				}
			}
		}
		if (num == capacity)//������������Ҫ��ת�棬�˳�
		{
			transfer(temp, storage, (scale_length - 1) / 2);
			return;
		}
		//���Բ���������ֱ�����
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
						if (temp[i][j][k] == 0)//��������򲻴���С�����壬�������������Ͻ����ж�
						{
							//�ж������������Ƿ���С������,�����ڣ���䣬����							
							if (i < x + layer)//��ֹ����Խ��
							{
								if (temp[i + 1][j][k] == 1)//ǰ
								{
									temp[i ][j][k] = 1, num++;
									continue;
								}								
							}
							if (i > x - layer)//��ֹ����Խ��
							{
								if (temp[i - 1][j][k] == 1)//��
								{
									temp[i][j][k] = 1, num++;
									continue;
								}
							}
							if (j < y + layer)//��ֹ����Խ��
							{
								if (temp[i][j + 1][k] == 1)//��
								{
									temp[i][j][k] = 1, num++;
									continue;
								}
							}
							if (j > y - layer)//��ֹ����Խ��
							{
								if (temp[i][j - 1][k] == 1)//��
								{
									temp[i][j][k] = 1, num++;
									continue;
								}
							}
							if (k < z + layer)//��ֹ����Խ��
							{
								if (temp[i][j][k + 1] == 1)//��
								{
									temp[i][j][k] = 1, num++;
									continue;
								}
							}
							if (k > z - layer)//��ֹ����Խ��
							{
								if (temp[i][j][k - 1] == 1)//��
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
	transfer(temp, storage, (scale_length-1)/2);//ת�棬�˳�
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
void Cube::analysis_block()//��������Ϣ,�õ���ͼ�Ĳ�����Ϣ
{//x����ͨ����ǰ����ͼ
	for (int i = 1; i <= scale_length; i ++)
	{
		for (int j = 1; j <= scale_length; j++)
		{
			if (detect_x_channel( i, j))
			{
				front_view[i][j] = 1;
				back_view[scale_length + 1 - i][j] = 1;//���ҵߵ�
			}
			else
			{
				front_view[i][j] = 0;
				back_view[scale_length + 1 - i][j] = 0;//���ҵߵ�
			}
		}
	}
//y����ͨ����������ͼ
	for (int i = 1; i <= scale_length; i++)
	{
		for (int j = 1; j <= scale_length; j++)
		{
			if (detect_y_channel( i, j))
			{
				left_view[i][j] = 1;
				right_view[scale_length + 1 - i][j] = 1;//���ҵߵ�
			}
			else
			{
				left_view[i][j] = 0;
				right_view[scale_length + 1 - i][j] = 0;//���ҵߵ�
			}
		}
	}
//z����ͨ����������ͼ
	for (int i = 1; i <= scale_length; i++)
	{
		for (int j = 1; j <= scale_length; j++)
		{
			if (detect_z_channel( i, j))
			{
				bottom_view[j][i] = 1;
				top_view[j][scale_length + 1 - i] = 1;//���µߵ�
			}
			else
			{
				bottom_view[j][i] = 0;
				top_view[j][scale_length + 1 - i] = 0;//���µߵ�
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
	SetWorkingImage(draw_bk);//���û�ͼ�豸
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
	SetWorkingImage();//�ָ�Ĭ�ϻ�ͼ�豸
}
void Cube::display_3d_90(IMAGE* draw_bk)
{
	SetWorkingImage(draw_bk);//���û�ͼ�豸
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
	SetWorkingImage();//�ָ�Ĭ�ϻ�ͼ�豸
}
void Cube::display_3d_180(IMAGE* draw_bk)
{
	SetWorkingImage(draw_bk);//���û�ͼ�豸
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
	SetWorkingImage();//�ָ�Ĭ�ϻ�ͼ�豸
}
void Cube::display_3d_270(IMAGE* draw_bk)
{
	SetWorkingImage(draw_bk);//���û�ͼ�豸
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
	SetWorkingImage();//�ָ�Ĭ�ϻ�ͼ�豸
}
void Cube::create_even()
{	//������ɵ�һ��С�����������
	int  x = random_position(scale_length);
	int  y = random_position(scale_length);
	int  z = random_position(scale_length);
	int  x_next = 0, y_next = 0, z_next = 0;
	storage[x][y][z] = 1;
	int num = 1;
	for (int time = 1; time < capacity; time ++)
	{
		int possible = 0, top = 0, bottom = 0, left = 0, right = 0, front = 0, back = 0;
		//��z�������ֵ������¼���Ϸ�����ֹ����Խ��
		if (z < scale_length)
		{
			if (storage[x][y][z + 1] == 0)//���Ϸ�Ϊ�գ����ܷ����һ�������÷�����
			{
				possible++;
				top = possible;
			}
			else
				top = -1;
		}
		else
			top = -1;
		//��z������Сֵ������¼���·�����ֹ����Խ��
		if (z > 1)
		{
			if (storage[x][y][z - 1] == 0)//���·�Ϊ�գ����ܷ����һ�������÷�����
			{
				possible++;
				bottom = possible;
			}
			else
				bottom = -2;
		}
		else
			bottom = -2;
		//��y������Сֵ������¼���󷽣���ֹ����Խ��
		if (y > 1)
		{
			if (storage[x][y - 1][z] == 0)//����Ϊ�գ����ܷ����һ�������÷�����
			{
				possible++;
				left = possible;
			}
			else
				left = -3;
		}
		else
			left = -3;
		//��y�������ֵ������¼���ҷ�����ֹ����Խ��
		if (y < scale_length)
		{
			if (storage[x][y + 1][z] == 0)//���ҷ�Ϊ�գ����ܷ����һ�������÷�����
			{
				possible++;
				right = possible;
			}
			else
				right = -4;
		}
		else
			right = -4;
		//��x�������ֵ������¼��ǰ������ֹ����Խ��
		if (x < scale_length)
		{
			if (storage[x + 1][y][z] == 0)//��ǰ��Ϊ�գ����ܷ����һ�������÷�����
			{
				possible++;
				front = possible;
			}
			else
				front = -5;
		}
		else
			front = -5;
		//��x������Сֵ������¼��󷽣���ֹ����Խ��
		if (x > 1)
		{
			if (storage[x - 1][y][z] == 0)//����Ϊ�գ����ܷ����һ�������÷�����
			{
				possible++;
				back = possible;
			}
			else
				back = -6;
		}
		else
			back = -6;
		//ѡ��һ���������
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

	//���������㣬�������
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
					if (storage[i][j][k] == 0)//��������򲻴���С�����壬�������������Ͻ����ж�
					{
						//�ж������������Ƿ���С������,�����ڣ���䣬����							
						if (i < scale_length)//��ֹ����Խ��
						{
							if (storage[i + 1][j][k] == 1)//ǰ
							{
								storage[i][j][k] = 1, num++;
								continue;
							}
						}
						if (i > 1)//��ֹ����Խ��
						{
							if (storage[i - 1][j][k] == 1)//��
							{
								storage[i][j][k] = 1, num++;
								continue;
							}
						}
						if (j < scale_length)//��ֹ����Խ��
						{
							if (storage[i][j + 1][k] == 1)//��
							{
								storage[i][j][k] = 1, num++;
								continue;
							}
						}
						if (j > 1)//��ֹ����Խ��
						{
							if (storage[i][j - 1][k] == 1)//��
							{
								storage[i][j][k] = 1, num++;
								continue;
							}
						}
						if (k < scale_length)//��ֹ����Խ��
						{
							if (storage[i][j][k + 1] == 1)//��
							{
								storage[i][j][k] = 1, num++;
								continue;
							}
						}
						if (k > 1)//��ֹ����Խ��
						{
							if (storage[i][j][k - 1] == 1)//��
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