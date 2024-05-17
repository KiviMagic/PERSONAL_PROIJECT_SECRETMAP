#ifndef LOGIC_H
#define LOGIC_H
#include <iostream> 
#include <string>
#include "easyx.h"
class Cube
{
	
public:
	Cube(); //��ʼ�����ݣ��������, ��������ͼ����
	 int get_scale_length();
	 int detect_x_channel(int y, int z);//����һ��ͨ���ϣ�x�����Ƿ���С������
	 int detect_y_channel(int x, int z);//����һ��ͨ���ϣ�y�����Ƿ���С������
	 int detect_z_channel(int x, int y);//����һ��ͨ���ϣ�z�����Ƿ���С������
	void analysis_block();//����������ͼ��Ϣ
	void recreate();//���ı�߳���С�������ɣ�������������,��������ͼ����
	void create_odd();//������ɲ�����,�����߳�
	void create_even();//������ɲ����棬ż���߳�
	void display_3d(IMAGE*);//�����񱳾��д�ӡ3d��ͼ
	void display_3d_90(IMAGE*);//�����񱳾��д�ӡ3d��ͼ,����˳ʱ����ת90��
	void display_3d_180(IMAGE*);//�����񱳾��д�ӡ3d��ͼ������˳ʱ����ת180��
	void display_3d_270(IMAGE*);//�����񱳾��д�ӡ3d��ͼ������˳ʱ����ת270��
	void display_2d();//����̨չʾ��������
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
	int scale_length;//���߳�
	int capacity;//�����С
	int(*storage)[11][11] = nullptr;
	//int storage[11][11][11] = {0};//[x][y][z]�Ǳ�Ϊ��ĺ���
	//������ͼ�ġ��顱��Ϣ���ӣ�1��1����ʼ��	

};

#endif 


