#ifndef LOGIC_H
#define LOGIC_H
#include <iostream> 
#include <string>
#include "easyx.h"
class Cube
{
	
public:
	Cube(); //初始化数据，随机生成, 包括六视图分析
	 int get_scale_length();
	 int detect_x_channel(int y, int z);//解析一个通道上（x方向）是否有小立方体
	 int detect_y_channel(int x, int z);//解析一个通道上（y方向）是否有小立方体
	 int detect_z_channel(int x, int y);//解析一个通道上（z方向）是否有小立方体
	void analysis_block();//解析各个视图信息
	void recreate();//不改变边长大小进行生成，用于重新生成,包括六视图分析
	void create_odd();//随机生成并储存,奇数边长
	void create_even();//随机生成并储存，偶数边长
	void display_3d(IMAGE*);//在网格背景中打印3d视图
	void display_3d_90(IMAGE*);//在网格背景中打印3d视图,但是顺时针旋转90°
	void display_3d_180(IMAGE*);//在网格背景中打印3d视图，但是顺时针旋转180°
	void display_3d_270(IMAGE*);//在网格背景中打印3d视图，但是顺时针旋转270°
	void display_2d();//控制台展示，测试用
	void display_front_view();
	void display_back_view();
	void display_left_view();
	void display_right_view();
	void display_top_view();
	void display_bottom_view();
	int(*front_view)[11];
	int(*back_view)[11];
	int(*left_view)[11];
	int(*right_view)[11];
	int(*top_view)[11];
	int(*bottom_view)[11];	
	static int sum_of_submit;
	static int sum_of_right;
private:
	int scale_length;//最大边长
	int capacity;//体积大小
	int(*storage)[11][11] = nullptr;
	//int storage[11][11][11] = {0};//[x][y][z]角标为零的忽略
	//各个视图的“块”信息，从（1，1）开始；	

};

#endif 


