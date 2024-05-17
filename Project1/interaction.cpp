#include "interaction.h"
#include "Logic.h"
#include "fstream"
#include <conio.h>
#include <string>
#include <iostream>
//��ʼ����Դ
interaction::interaction()
{
    loadimage(&home_bk, _T("image\\home.png"));
    loadimage(&view_bk, _T("image\\3d_view.png"));
    //��ҳ�˵���ť
    menu_btns.push_back(new BASIC_BUTTON(1000, 450, 160, 50));//��¼��
    menu_btns[0]->set_sticker(_T("image\\login_touch.png"));
    menu_btns.push_back(new BASIC_BUTTON(1000, 525, 160, 50));//���а��
    menu_btns[1]->set_sticker(_T("image\\ranking_list_touch.png"));
    menu_btns.push_back(new BASIC_BUTTON(1000, 600, 160, 50));//�˳���
    menu_btns[2]->set_sticker(_T("image\\exit_touch.png"));

    second_btns.push_back(new  SEC_BUTTON(1000, 100, 160, 50));//Ĭ�ϽǶȼ�,0
    second_btns[0]->set_stickers(_T("image\\default_normal.png"), _T("image\\default_touch.png"));
    second_btns.push_back(new  SEC_BUTTON(1000, 180, 160, 50));//90���,1
    second_btns[1]->set_stickers(_T("image\\90_normal.png"), _T("image\\90_touch.png"));
    second_btns.push_back(new  SEC_BUTTON(1000, 260, 160, 50));//180���,2
    second_btns[2]->set_stickers(_T("image\\180_normal.png"), _T("image\\180_touch.png"));
    second_btns.push_back(new  SEC_BUTTON(1000, 340, 160, 50));//270���,3
    second_btns[3]->set_stickers(_T("image\\270_normal.png"), _T("image\\270_touch.png"));
    second_btns.push_back(new  SEC_BUTTON(1000, 460, 160, 50));//��ʼ�����,4
    second_btns[4]->set_stickers(_T("image\\answer_normal.png"), _T("image\\answer_touch.png"));  
    second_btns.push_back(new  SEC_BUTTON(1120, 0, 160, 50));//չʾͼ���淵�ؼ�,5
    second_btns[5]->set_stickers(_T("image\\back_normal.png"), _T("image\\back_touch.png"));
    second_btns.push_back(new  SEC_BUTTON(1000, 540, 160, 50));//�������ü�,6
    second_btns[6]->set_stickers(_T("image\\reset_normal.png"), _T("image\\reset_touch.png"));
    second_btns.push_back(new  SEC_BUTTON(1000, 620, 160, 50));//�������ɼ�,7
    second_btns[7]->set_stickers(_T("image\\recreate_normal.png"), _T("image\\recreate_touch.png"));
    second_btns.push_back(new  SEC_BUTTON(1050, 360, 160, 50));//�ύ��,8
    second_btns[8]->set_stickers(_T("image\\submit_normal.png"), _T("image\\submit_touch.png"));
    second_btns.push_back(new  SEC_BUTTON(1050, 260, 160, 50));//������淵�ؼ�,9
    second_btns[9]->set_stickers(_T("image\\back_normal.png"), _T("image\\back_touch.png"));
}
//���к���
void interaction::run()
{
    int click = HOME;
    bool cycle = true;
    while (cycle)
    {        
        switch (click)
        {
        case interaction::HOME:
            click = home();
            break;
        case interaction::LOGIN:
            click = login();
            break;
        case interaction::RANKING_lIST:
            click = ranking_list();
            break;
        case interaction::EXIT:
        {
            exit();
            cycle = false;
        }
            break;
        default:
            break;
        }
     
    }
}
//��ҳ����ѭ�������ݵ����תҳ��
int interaction::home()
{
    while(true)
    {   
        int flag = 0;
        BeginBatchDraw();//��������
        getmessage(&msg, EX_MOUSE);
        for (int i = 0; i < menu_btns.size(); i++)
        {           
            menu_btns[i]->getmessage(msg);
            int detect = menu_btns[i]->is_inside();//�������ͷ�Ƿ��ڰ�ť��Χ��
            if (detect)
            {   
                menu_btns[i]->show();//����ڰ�ť��Χ�ڣ���ʾ��ť��������ʱ����ʽ��
                flag += detect;
                if (menu_btns[i]->beclicked())//����ڰ�ť��Χ���ҽ����˵��������home()���������ص��ѡ��
                {
                    return i;
                }
            }
            else if(flag == 0)//�����겻������һ����ť�ķ�Χ�ڣ�ˢ��������ҳҳ���Իָ���ť��������ʽ
            {
                putimage(0, 0, &home_bk);             
            }
        }
        EndBatchDraw();//�����������
    }
    return HOME;
}
//��¼��ʼ��Ϸ
int interaction::login()
{
    BeginBatchDraw();
    bool modified = true;
    Cube* cubeptr = nullptr;
    bool cycle = true, back = false, recreate = false, reset = false;//�����ź�
    while (true)
    {
        //���modified�ź�Ϊ�棬���г�ʼ������Ҫ�������ò���;  ���modified�ź�Ϊ�٣������������趨��������ԭ�趨����������ɣ������ԭ�����������ݣ�
        if (modified)
        {
            cubeptr = new Cube();
        }
        else
        {
            cubeptr->recreate();
        }
        //���������������3d��ͼ,ֱ��
        IMAGE draw_bk;
        loadimage(&draw_bk, _T("image//3d_view.png"));
        cubeptr->display_3d(&draw_bk);

        //���������������3d��ͼ����ת90��
        IMAGE draw_bk_90;
        loadimage(&draw_bk_90, _T("image//3d_view.png"));
        cubeptr->display_3d_90(&draw_bk_90);

        //���������������3d��ͼ����ת180��
        IMAGE draw_bk_180;
        loadimage(&draw_bk_180, _T("image//3d_view.png"));
        cubeptr->display_3d_180(&draw_bk_180);

        //���������������3d��ͼ����ת270��
        IMAGE draw_bk_270;
        loadimage(&draw_bk_270, _T("image//3d_view.png"));
        cubeptr->display_3d_270(&draw_bk_270);

        //Ĭ�ϽǶ�չʾ
        cleardevice();
        putimage(0, 0, &draw_bk);
        cubeptr->display_2d();//����̨�汾
        cubeptr->display_front_view();
        cubeptr->display_back_view();
        cubeptr->display_left_view();
        cubeptr->display_right_view();
        cubeptr->display_top_view();
        cubeptr->display_bottom_view();

        EndBatchDraw();
        //ѡ��չʾ�Ƕ�
        cycle = true, back = false, recreate = false, reset = false, modified = false;
        while (cycle)
        {
            BeginBatchDraw();
            int choice = display_menu_of_show();
                //��ӡ��ͬ�Ƕȵ�ֱ��ͼ
                switch (choice)
                {
                case 0:putimage(0, 0, &draw_bk); break;
                case 1:putimage(0, 0, &draw_bk_90); break;
                case 2:putimage(0, 0, &draw_bk_180); break;
                case 3:putimage(0, 0, &draw_bk_270); break;
                case 4:
                {
                    int choice = answer_v1(cubeptr->get_scale_length(),cubeptr);
                    if (choice)
                    {
                        cycle = false;
                        recreate = true;//�ύ��󷵻أ�����������
                    }
                    else
                    putimage(0, 0, &draw_bk); //ֻ�Ƿ��ص���ǰѡ��ѭ������ӡĬ�ϽǶ�չʾͼ������������
                    break; 
                }
                case 5: 
                {
                    cycle = false;
                    back = true;
                    break;
                } 
                case 6:
                {
                    cycle = false;
                    reset = true;
                    break;
                }
                case 7:
                {
                    cycle = false;
                     recreate = true;
                    break;
                }
                default:
                    break;
                }
                EndBatchDraw();
        }
        if (back)
        {
        delete cubeptr;//�ͷŶѿռ�
        break;//������أ����˳���ѭ�����ص���ҳ
        }
        else if(recreate)
        {
            modified = false;
            continue;
        }
        else if (reset)
        {
            modified = true;
            delete cubeptr;//�ͷŶѿռ�
            continue;
        }                  
    }       
        return HOME;
}
//���а�
int interaction::ranking_list()
{
    int s_sub =0, s_rig = 0;

    std::ifstream _rank("ranking.dat", std::ios::in | std::ios::binary);
    _rank.seekg(0);
    _rank.read((char*)&s_sub, sizeof(Cube::sum_of_submit));
    _rank.read((char*)&s_rig, sizeof(Cube::sum_of_right));
    _rank.close();
  
    s_sub += Cube::sum_of_submit, s_rig += Cube::sum_of_right;

    std::cout << "���ύ���� " << s_sub << "     �ܴ������ " << s_rig << std::endl;
    std::cout << "�����ύ�� " << Cube::sum_of_submit << "     ���մ�ԣ� " << Cube::sum_of_right << std::endl;

    IMAGE sum_submit, sum_right, today_submit, today_right;
    loadimage(&sum_submit, _T("image\\sum_submit.png"));
    loadimage(&sum_right, _T("image\\sum_right.png"));
    loadimage(&today_submit, _T("image\\today_submit.png"));
    loadimage(&today_right, _T("image\\today_right.png"));
    SetWorkingImage();
    cleardevice();
    putimage(200, 290, &sum_submit);
    putimage(640, 290, &sum_right);
    putimage(200, 380, &today_submit);
    putimage(640, 380, &today_right);
    EndBatchDraw();
    while (true)
    {
        getmessage(&msg, EX_MOUSE);
        //���ؼ�
        second_btns[5]->getmessage(msg);
        if (second_btns[5]->is_inside())
        {
            second_btns[5]->show_touch();//����ڷ��ؼ���Χ�ڣ���ʾ��ť��������ʱ����ʽ��                      
            if (second_btns[5]->beclicked())//����ڷ��ؼ���Χ���ҽ����˵�����ؼ�������ѭ��
            {
                break;//����ѭ����������һ����
            }
        }
        else //�����겻�ڰ�ť�ķ�Χ�ڣ���ӡ��ť��������ʽ
        {
            second_btns[5]->show();
        }
    }  
    return HOME;
}
//�˳�����
void interaction::exit()
{
    int s_sub = 0 , s_rig = 0;
    std::ifstream _rank("ranking.dat", std::ios::in | std::ios::binary);
    _rank.read((char*)&s_sub, sizeof(Cube::sum_of_submit));
    _rank.read((char*)&s_rig, sizeof(Cube::sum_of_right));
    _rank.close();
    s_sub += Cube::sum_of_submit, s_rig += Cube::sum_of_right;
    std::ofstream rank("ranking.dat", std::ios::out | std::ios::binary);
    rank.seekp(0);
    rank.write((const char*)&s_sub, sizeof(s_sub));
    rank.write((const char*)&s_rig, sizeof(s_rig));
    rank.close();
    std::cout << "�˳���Ϸ���Ѵ浵��";
    closegraph();    
}
//չʾѡ�����������������ѡ���򷵻�ѡ��
int interaction::display_menu_of_show()
{
    int choice = -1;
   BeginBatchDraw();
    while (true)
    {        
        getmessage(&msg, EX_MOUSE);
        for (int i = 0; i < 8; i++)
        {
            second_btns[i]->getmessage(msg);
            int detect = second_btns[i]->is_inside();//�������ͷ�Ƿ��ڰ�ť��Χ��
            if (detect)
            {
                second_btns[i]->show_touch();//����ڰ�ť��Χ�ڣ���ʾ��ť��������ʱ����ʽ��                      
                if (second_btns[i]->beclicked())//����ڰ�ť��Χ���ҽ����˵��������ѭ�������ص��ѡ��
                {
                    choice = i;
                    break;
                }
            }
            else //�����겻�ڰ�ť�ķ�Χ�ڣ���ӡ��ť��������ʽ
            {
                second_btns[i]->show();
            }
        }
    EndBatchDraw();//�����������
        if (choice != -1)
            break;
    }
    return choice;
}
//��ʼ���𣬽���������(������)
int interaction::answer(int length, Cube*cubeptr)
{
    BeginBatchDraw();
    //�����ź�
    bool submit = false, back = false;
    int button_len = 240 / length;//����Ӧ��ť��С
    int block_width = button_len * length;//ԭ��ÿһ��Ŀ��Ϊ240������Ҫ���¶����ȣ���Ϊ����Ϊ��������
     //������ͼ�豸
    IMAGE answer_sheet(1000, 720);
    //�������մ��⿨
    SetWorkingImage(&answer_sheet);
    for (int i = 0; i < 6; i++)
    {
        if (i < 1)
        {
            for (int j = 0; j < length; j++)
            {
                for (int k = 0; k < length; k++)
                {
                    setfillcolor(RGB(150, 150, 150));
                    fillrectangle(20 + button_len * k, 240 + button_len * j, 20 + button_len * k + button_len, 240 + button_len * j + button_len);
                }
            }
        }
        else if (i < 2)
        {
            for (int j = 0; j < length; j++)
            {
                for (int k = 0; k < length; k++)
                {
                    setfillcolor(RGB(150, 150, 150));
                    fillrectangle(260 + button_len * k, 240 + button_len * j, 260 + button_len * k + button_len, 240 + button_len * j + button_len);
                }
            }
        }
        else if (i < 3)
        {
            for (int j = 0; j < length; j++)
            {
                for (int k = 0; k < length; k++)
                {
                    setfillcolor(RGB(150, 150, 150));
                    fillrectangle(500 + button_len * k, 240 + button_len * j, 500 + button_len * k + button_len, 240 + button_len * j + button_len);
                }
            }
        }
        else if (i < 4)
        {
            for (int j = 0; j < length; j++)
            {
                for (int k = 0; k < length; k++)
                {
                    setfillcolor(RGB(150, 150, 150));
                    fillrectangle(500 + button_len * k, button_len * j, 500 + button_len * k + button_len, button_len * j + button_len);
                }
            }
        }
        else if (i < 5)
        {
            for (int j = 0; j < length; j++)
            {
                for (int k = 0; k < length; k++)
                {
                    setfillcolor(RGB(150, 150, 150));
                    fillrectangle(500 + button_len * k, 480 + button_len * j, 500 + button_len * k + button_len, 480 + button_len * j + button_len);
                }
            }
        }
        else if (i < 6)
        {
            for (int j = 0; j < length; j++)
            {
                for (int k = 0; k < length; k++)
                {
                    setfillcolor(RGB(150, 150, 150));
                    fillrectangle(740 + button_len * k, 240 + button_len * j, 740 + button_len * k + button_len, 240 + button_len * j + button_len);

                }
            }
        }
    }
    SetWorkingImage();
    //�����һ����
     cleardevice();
    //������ťָ���������ڶ���ʵ�����ڶ���ť����
    std::vector<THIRD_BUTTON*> third_button;
    //��ť����
    for (int i = 0; i < 6; i++)
    {
        if (i < 1)
        {
            for (int j = 0; j < length; j++)
            {
                for (int k = 0; k < length; k++)
                {
                    third_button.push_back(new THIRD_BUTTON(20 + button_len * k, 240 + button_len * j, button_len, button_len));
                }
            }           
        }
        else if(i < 2)
        {
            for (int j = 0; j < length; j++)
            {
                for (int k = 0; k < length; k++)
                {
                    third_button.push_back(new THIRD_BUTTON(260 + button_len * k, 240 + button_len * j, button_len, button_len));
                }
            }
        }
        else if (i < 3)
        {
            for (int j = 0; j < length; j++)
            {
                for (int k = 0; k < length; k++)
                {
                    third_button.push_back(new THIRD_BUTTON(500 + button_len * k, 240 + button_len * j, button_len, button_len));
                }
            }
        }
        else if (i < 4)
        {
            for (int j = 0; j < length; j++)
            {
                for (int k = 0; k < length; k++)
                {
                    third_button.push_back(new THIRD_BUTTON(500 + button_len * k,  button_len * j, button_len, button_len));
                }
            }
        }
        else if (i < 5)
        {
            for (int j = 0; j < length; j++)
            {
                for (int k = 0; k < length; k++)
                {
                    third_button.push_back(new THIRD_BUTTON(500 + button_len * k, 480 + button_len * j, button_len, button_len));
                }
            }
        }
        else if (i < 6)
        {
            for (int j = 0; j < length; j++)
            {
                for (int k = 0; k < length; k++)
                {
                    third_button.push_back(new THIRD_BUTTON(740 + button_len * k, 240 + button_len * j, button_len, button_len));
                }
            }
        }
        
    }
    int touch = 0; 
    //����׶�
    while (true)
    {              
        getmessage(&msg, EX_MOUSE);
        //���ؼ�
        second_btns[9]->getmessage(msg);
        if(second_btns[9]->is_inside())
        {
            second_btns[9]->show_touch();//����ڷ��ؼ���Χ�ڣ���ʾ��ť��������ʱ����ʽ��                      
            if (second_btns[9]->beclicked())//����ڷ��ؼ���Χ���ҽ����˵�����ؼ�������ѭ��
            {    
                back = true;
                break;//����ѭ��,�˳����𣬷�����һ����
            }
        }
        else //�����겻�ڰ�ť�ķ�Χ�ڣ���ӡ��ť��������ʽ
        {
            second_btns[9]->show();
        }
        //�ύ��
        second_btns[8]->getmessage(msg);
        if (second_btns[8]->is_inside())
        {
            second_btns[8]->show_touch();//������ύ����Χ�ڣ���ʾ��ť��������ʱ����ʽ��                      
            if (second_btns[8]->beclicked())//������ύ����Χ���ҽ����˵���ύ��������ѭ��
            {
                submit = true;
                break;//����ѭ��,�ύ��
            }
        }
        else //�����겻�ڰ�ť�ķ�Χ�ڣ���ӡ��ť��������ʽ
        {
            second_btns[8]->show();
        }
        for (int i = 0; i < third_button.size(); i++)
        {
            touch = 0;
            third_button[i]->getmessage(msg);
            int detect = third_button[i]->is_inside();//�������ͷ�Ƿ��ڰ�ť��Χ��
            if (detect)
            {
                //����ڰ�ť��Χ�ڣ����touch
                touch = 1;
                //std::cout << i;//����̨�����                       
                if (third_button[i]->beclicked())//����ڰ�ť��Χ���ҽ����˵�������flag
                {         
                    third_button[i]->set_flag();//flag�븺һ���
                }
            }
            //�����겻�ڰ�ť�ķ�Χ�ڣ�������� 
            //�����ź��ռ���ϣ�ȷ��ĳһ����ť���������״̬            
            third_button[i]->show_3(touch);
        }
        EndBatchDraw();//�����������
    }
    int(*view_6)[11][11] = nullptr;
    //����
    if (back)
    {
        cleardevice();
    }
    //����𰸲��˶�
    else if (submit)
    {   
        view_6 = new int[7][11][11]{ 0 };
        int order = 0, column = 0, line = 0;
        //����⿨������
        for (int i = 0; i < length * length * 6; i++)
        {
            if (i < length * length * 1)
            {
                order = i + 1;
                line = order / length + 1;//y
                column = order - length * (line - 1);//x
                if (third_button[i]->get_flag() == 1)
                    view_6[1][length - (column - 1)][length - (line - 1)] = 1;
            }
            else if (i < length * length * 2)
            {
                order = i + 1 - length * length;
                line = order / length + 1;
                column = order - length * (line - 1);
                if (third_button[i]->get_flag() == 1)
                    view_6[2][line ][length - (column - 1)] = 1;
            }
            else if (i < length * length * 3)
            {
                order = i + 1 - length * length * 2;
                line = order / length + 1;
                column = order - length * (line - 1);
                if (third_button[i]->get_flag() == 1)
                    view_6[3][column][line] = 1;
            }
            else if (i < length * length * 4)
            {
                order = i + 1 - length * length * 3;
                line = order / length + 1;
                column = order - length * (line - 1);
                if (third_button[i]->get_flag() == 1)
                    view_6[4][length - (column - 1)][length - (line - 1)] = 1;
            }
            else if (i < length * length * 5)
            {
                order = i + 1 - length * length * 4;
                line = order / length + 1;
                column = order - length * (line - 1);
                if (third_button[i]->get_flag() == 1)
                    view_6[5][column][line] = 1;

            }
            else if (i < length * length * 6)
            {
                order = i + 1 - length * length * 5;
                line = order / length + 1;
                column = order - length * (line - 1);
                if (third_button[i]->get_flag() == 1)
                    view_6[6][length - (line - 1)][column] = 1;
            }
        }        
        //��ӡ�����⿨��ͼ�豸�ϣ��ٴ�ӡ������
        SetWorkingImage(&answer_sheet);
        for (int i = 1; i <= 6; i++)
        {
            switch (i)
            {
            case 1:
                for (int x = 1; x <= length; x++)
                {
                    for (int y = 1; y <= length; y++)
                    {
                        if (view_6[1][length - (x - 1)][length - (y - 1)] && cubeptr->top_view[length - (x - 1)][length - (y - 1)])
                        {
                            setfillcolor(RGB(15, 200, 105));//��ɫ��ʾ����ͨ��
                            fillrectangle(20 + button_len * (x - 1), 240 + button_len * (y - 1), 20 + button_len * (x - 1) + button_len, 240 + button_len * (y - 1) + button_len);
                        }
                        else if (view_6[1][length - (x - 1)][length - (y - 1)])
                        {
                            setfillcolor(RGB(255, 55, 0));//��ɫ��ʾ����Ŀ�
                            fillrectangle(20 + button_len * (x - 1), 240 + button_len * (y - 1), 20 + button_len * (x - 1) + button_len, 240 + button_len * (y - 1) + button_len);
                        }
                        else if (cubeptr->top_view[length - (x - 1)][length - (y - 1)])
                        {
                            setfillcolor(RGB(170, 240, 170));//ǳ��ɫ��ʾȱ��Ŀ�
                            fillrectangle(20 + button_len * (x - 1), 240 + button_len * (y - 1), 20 + button_len * (x - 1) + button_len, 240 + button_len * (y - 1) + button_len);
                        }
                    }
                }break;
            case 2:
                for (int x = 1; x <= length; x++)
                {
                    for (int y = 1; y <= length; y++)
                    {
                        if (view_6[2][y][length - (x - 1)] && cubeptr->left_view[y][length - (x - 1)])
                        {
                            setfillcolor(RGB(15, 200, 105));//��ɫ��ʾ����ͨ��
                            fillrectangle(260 + button_len * (x - 1), 240 + button_len * (y - 1), 260 + button_len * (x - 1) + button_len, 240 + button_len * (y - 1) + button_len);
                        }
                        else if (view_6[2][y][length - (x - 1)])
                        {
                            setfillcolor(RGB(255, 55, 0));//��ɫ��ʾ����Ŀ�
                            fillrectangle(260 + button_len * (x - 1), 240 + button_len * (y - 1), 260 + button_len * (x - 1) + button_len, 240 + button_len * (y - 1) + button_len);
                        }
                        else if (cubeptr->left_view[y][length - (x - 1)])
                        {
                            setfillcolor(RGB(170, 240, 170));//ǳ��ɫ��ʾȱ��Ŀ�
                            fillrectangle(260 + button_len * (x - 1), 240 + button_len * (y - 1), 260 + button_len * (x - 1) + button_len, 240 + button_len * (y - 1) + button_len);
                        }
                    }
                }break;
            case 3:
                for (int x = 1; x <= length; x++)
                {
                    for (int y = 1; y <= length; y++)
                    {
                        if (view_6[3][x][y] && cubeptr->bottom_view[x][y])
                        {
                            setfillcolor(RGB(15, 200, 105));//��ɫ��ʾ����ͨ��
                            fillrectangle(500 + button_len * (x - 1), 240 + button_len * (y - 1), 500 + button_len * (x - 1) + button_len, 240 + button_len * (y - 1) + button_len);
                        }
                        else if (view_6[3][x][y])
                        {
                            setfillcolor(RGB(255, 55, 0));//��ɫ��ʾ����Ŀ�
                            fillrectangle(500 + button_len * (x - 1), 240 + button_len * (y - 1), 500 + button_len * (x - 1) + button_len, 240 + button_len * (y - 1) + button_len);
                        }
                        else if (cubeptr->bottom_view[x][y])
                        {
                            setfillcolor(RGB(170, 240, 170));//ǳ��ɫ��ʾȱ��Ŀ�
                            fillrectangle(500 + button_len * (x - 1), 240 + button_len * (y - 1), 500 + button_len * (x - 1) + button_len, 240 + button_len * (y - 1) + button_len);
                        }
                    }
                }break;
            case 4:
                for (int x = 1; x <= length; x++)
                {
                    for (int y = 1; y <= length; y++)
                    {
                        if (view_6[4][length - (x - 1)][length - (y - 1)] && cubeptr->back_view[length - (x - 1)][length - (y - 1)])
                        {
                            setfillcolor(RGB(15, 200, 105));//��ɫ��ʾ����ͨ��
                            fillrectangle(500 + button_len * (x - 1), button_len * (y - 1), 500 + button_len * (x - 1) + button_len, button_len * (y - 1) + button_len);
                        }
                        else if (view_6[4][length - (x - 1)][length - (y - 1)])
                        {
                            setfillcolor(RGB(255, 55, 0));//��ɫ��ʾ����Ŀ�
                            fillrectangle(500 + button_len * (x - 1), button_len * (y - 1), 500 + button_len * (x - 1) + button_len, button_len * (y - 1) + button_len);
                        }
                        else if (cubeptr->back_view[length - (x - 1)][length - (y - 1)])
                        {
                            setfillcolor(RGB(170, 240, 170));//ǳ��ɫ��ʾȱ��Ŀ�
                            fillrectangle(500 + button_len * (x - 1), button_len * (y - 1), 500 + button_len * (x - 1) + button_len, button_len * (y - 1) + button_len);
                        }
                    }
                }break;
            case 5:
                for (int x = 1; x <= length; x++)
                {
                    for (int y = 1; y <= length; y++)
                    {
                        if (view_6[5][x][y] && cubeptr->front_view[x][y])
                        {
                            setfillcolor(RGB(15, 200, 105));//��ɫ��ʾ����ͨ��
                            fillrectangle(500 + button_len * (x - 1), 480 + button_len * (y - 1), 500 + button_len * (x - 1) + button_len, 480 + button_len * (y - 1) + button_len);
                        }
                        else if (view_6[5][x][y])
                        {
                            setfillcolor(RGB(255, 55, 0));//��ɫ��ʾ����Ŀ�
                            fillrectangle(500 + button_len * (x - 1), 480 + button_len * (y - 1), 500 + button_len * (x - 1) + button_len, 480 + button_len * (y - 1) + button_len);
                        }
                        else if (cubeptr->front_view[x][y])
                        {
                            setfillcolor(RGB(170, 240, 170));//ǳ��ɫ��ʾȱ��Ŀ�
                            fillrectangle(500 + button_len * (x - 1), 480 + button_len * (y - 1), 500 + button_len * (x - 1) + button_len, 480 + button_len * (y - 1) + button_len);
                        }
                    }
                }break;
            case 6:
                for (int x = 1; x <= length; x++)
                {
                    for (int y = 1; y <= length; y++)
                    {
                        if (view_6[6][length - (y - 1)][x] && cubeptr->right_view[length - (y - 1)][x])
                        {
                            setfillcolor(RGB(15, 200, 105));//��ɫ��ʾ����ͨ��
                            fillrectangle(740 + button_len * (x - 1), 240 + button_len * (y - 1), 740 + button_len * (x - 1) + button_len, 240 + button_len * (y - 1) + button_len);
                        }
                        else if (view_6[6][length - (y - 1)][x])
                        {
                            setfillcolor(RGB(255, 55, 0));//��ɫ��ʾ����Ŀ�
                            fillrectangle(740 + button_len * (x - 1), 240 + button_len * (y - 1), 740 + button_len * (x - 1) + button_len, 240 + button_len * (y - 1) + button_len);
                        }
                        else if (cubeptr->right_view[length - (y - 1)][x])
                        {
                            setfillcolor(RGB(170, 240, 170));//ǳ��ɫ��ʾȱ��Ŀ�
                            fillrectangle(740 + button_len * (x - 1), 240 + button_len * (y - 1), 740 + button_len * (x - 1) + button_len, 240 + button_len * (y - 1) + button_len);
                        }
                    }
                }break;
            default:
                break;

            }
        }
        SetWorkingImage();
        putimage(0, 0, &answer_sheet);
        int waite = 0;
        std::cin >> waite;
    }
    //���ն�����Դ
    delete []view_6;
    for (int i = 0; i < length * length * 6; i++)
    {
        delete third_button[i];
    }
    cleardevice();
    return 0;
}
//��ʼ���𣬽���������
int interaction::answer_v1(int length, Cube* cubeptr)
{
    bool submit = false, back = false;//�����ź�
    int button_len = 240 / length;//����Ӧ��ť��С
    int block_width = button_len * length;//ԭ��ÿһ��Ŀ��Ϊ240������Ҫ���¶����ȣ���Ϊ����Ϊ��������
    cleardevice();//�����һ����
    //������ͼ�豸
    IMAGE answer_sheet(1000, 720);
    SetWorkingImage(&answer_sheet);//���õ�ǰ��ͼ�豸Ϊ���⿨
    //���ƴ��⿨
    for (int i = 0; i < 6 ; i++)
    {
        if (i < 1)
        {
            for (int j = 0; j < length; j++)
            {
                for (int k = 0; k < length; k++)
                {
                    setfillcolor(RGB(150, 150, 150));
                    fillrectangle(20 + button_len * k, 240 + button_len * j, 20 + button_len * k + button_len, 240 + button_len * j + button_len);
                }
            }
        }
        else if (i < 2)
        {
            for (int j = 0; j < length; j++)
            {
                for (int k = 0; k < length; k++)
                {
                    setfillcolor(RGB(150, 150, 150));
                    fillrectangle(260 + button_len * k, 240 + button_len * j, 260 + button_len * k + button_len, 240 + button_len * j + button_len);
                }
            }
        }
        else if (i < 3)
        {
            for (int j = 0; j < length; j++)
            {
                for (int k = 0; k < length; k++)
                {
                    setfillcolor(RGB(150, 150, 150));
                    fillrectangle(500 + button_len * k, 240 + button_len * j, 500 + button_len * k + button_len, 240 + button_len * j + button_len);
                }
            }
        }
        else if (i < 4)
        {
            for (int j = 0; j < length; j++)
            {
                for (int k = 0; k < length; k++)
                {
                    setfillcolor(RGB(150, 150, 150));
                    fillrectangle(500 + button_len * k, button_len * j, 500 + button_len * k + button_len, button_len * j + button_len);
                }
            }
        }
        else if (i < 5)
        {
            for (int j = 0; j < length; j++)
            {
                for (int k = 0; k < length; k++)
                {                  
                    setfillcolor(RGB(150, 150, 150));
                    fillrectangle(500 + button_len * k, 480 + button_len * j, 500 + button_len * k + button_len, 480 + button_len * j + button_len);
                }
            }
        }
        else if (i < 6)
        {
            for (int j = 0; j < length; j++)
            {
                for (int k = 0; k < length; k++)
                {
                    setfillcolor(RGB(150, 150, 150));
                    fillrectangle(740 + button_len * k, 240 + button_len * j, 740 + button_len * k + button_len, 240 + button_len * j + button_len);
                    
                }
            }
        }
    }
    //����׶� (����������⿨)
    SetWorkingImage();
    second_btns[8]->show();//��ʾ������ť
    second_btns[9]->show();
    int last_block = 1, last_pos_x = 0, last_pos_y = 0;//��һ״̬����
    bool last_click = 0;//��һ״̬����
    int mouse_x = 0, mouse_y = 0;
    int pos_x = 0, pos_y =0, block = 0;
    bool click = 0;
    int(*view_6)[11][11] = new int[7][11][11]{0};
    while (true)
    {       
        getmessage(&msg, EX_MOUSE); 
        //�����ź�
        submit = false, back = false;
        //���ؼ�
        second_btns[9]->getmessage(msg);
        if(second_btns[9]->is_inside())
        {
            second_btns[9]->show_touch();//����ڷ��ؼ���Χ�ڣ���ʾ��ť��������ʱ����ʽ��                      
            if (second_btns[9]->beclicked())//����ڷ��ؼ���Χ���ҽ����˵�����ؼ�������ѭ��
            {    
                back = true;
                break;//����ѭ��,�˳����𣬷�����һ����
            }
        }
        else //�����겻�ڰ�ť�ķ�Χ�ڣ���ӡ��ť��������ʽ
        {
            second_btns[9]->show();
        }
        //�ύ��
        second_btns[8]->getmessage(msg);
        if (second_btns[8]->is_inside())
        {
            second_btns[8]->show_touch();//������ύ����Χ�ڣ���ʾ��ť��������ʱ����ʽ��                      
            if (second_btns[8]->beclicked())//������ύ����Χ���ҽ����˵���ύ��������ѭ��
            {
                Cube::sum_of_submit++;//�ύ����һ
                submit = true;
                break;//����ѭ��,�ύ��
            }
        }
        else //�����겻�ڰ�ť�ķ�Χ�ڣ���ӡ��ť��������ʽ
        {
            second_btns[8]->show();
        }
         mouse_x = msg.x, mouse_y = msg.y;
         block = 0, click = msg.lbutton;
        //std::cout << "( " << mouse_x << ", " << mouse_y << ")" << std::endl;//����̨��ʾ����
        //��궨λ��������
        if ( (mouse_x-20)* (mouse_x - 20 - block_width) < 0 && (mouse_y - 240)*(mouse_y - 240 - block_width) < 0)//��
        {
            pos_x = (mouse_x - 20) / button_len;
            pos_y = (mouse_y - 240) / button_len;
            block = 1;
        }
        else if ((mouse_x - 260) * (mouse_x - 260 - block_width) < 0 && (mouse_y - 240) * (mouse_y - 240 - block_width) < 0)//��
        {
            pos_x = (mouse_x - 260) / button_len;
            pos_y = (mouse_y - 240) / button_len;
            block = 2; 
            
        }
        else if ((mouse_x - 500) * (mouse_x - 500 - block_width) < 0 && (mouse_y - 240) * (mouse_y - 240 - block_width) < 0)//��
        {
            pos_x = (mouse_x - 500) / button_len;
            pos_y = (mouse_y - 240) / button_len;
            block = 3; 
        }
        else if ((mouse_x - 500) * (mouse_x - 500 - block_width) < 0 && (mouse_y - 0) * (mouse_y - 0 - block_width) < 0)//��
        {
            pos_x = (mouse_x - 500) / button_len;
            pos_y = (mouse_y - 0) / button_len;
            block = 4; 
        }
        else if ((mouse_x - 500) * (mouse_x - 500 - block_width) < 0 && (mouse_y - 480) * (mouse_y - 480 - block_width) < 0)//ǰ
        {
            pos_x = (mouse_x - 500) / button_len;
            pos_y = (mouse_y - 480) / button_len;
            block = 5;
        }
        else if ((mouse_x - 740) * (mouse_x - 740 - block_width) < 0 && (mouse_y - 240) * (mouse_y - 240 - block_width) < 0)//��
        {
            pos_x = (mouse_x - 740) / button_len;
            pos_y = (mouse_y - 240) / button_len;
            block = 6; 
        }
        else
        {
            block = -1;
        }
        SetWorkingImage(&answer_sheet);//���õ�ǰ��ͼ�豸Ϊ���⿨
        //����ǰ���������ϴ������鲻ͬ�����ϴ�û�е��ȷ�������á��ҷ��顱��ԭ�ϴ������İ�ť
        if (!((pos_x == last_pos_x) && (pos_y == last_pos_y) && (block == last_block)))
        {
            setfillcolor(RGB(150, 150, 150));//��
            switch (last_block)
            {
            case 1:
            {
                if (view_6[1][length - last_pos_x][length - last_pos_y] == 0)
                fillrectangle(20 + button_len * last_pos_x, 240 + button_len * last_pos_y, 20 + button_len * last_pos_x + button_len, 240 + button_len * last_pos_y + button_len);
            }break;
            case 2:
            {
                if (view_6[2][last_pos_y + 1][length - last_pos_x] == 0)
                fillrectangle(260 + button_len * last_pos_x, 240 + button_len * last_pos_y, 260 + button_len * last_pos_x + button_len, 240 + button_len * last_pos_y + button_len);
            }break;
            case 3:
            {
                if (view_6[3][last_pos_x + 1][last_pos_y + 1] == 0)
                fillrectangle(500 + button_len * last_pos_x, 240 + button_len * last_pos_y, 500 + button_len * last_pos_x + button_len, 240 + button_len * last_pos_y + button_len);
            }break;
            case 4:
            {
                if (view_6[4][length - last_pos_x][length - last_pos_y] == 0)
                fillrectangle(500 + button_len * last_pos_x, 0 + button_len * last_pos_y, 500 + button_len * last_pos_x + button_len, 0 + button_len * last_pos_y + button_len);
            }break;
            case 5:
            {
                if (view_6[5][last_pos_x + 1][last_pos_y + 1] == 0)
                fillrectangle(500 + button_len * last_pos_x, 480 + button_len * last_pos_y, 500 + button_len * last_pos_x + button_len, 480 + button_len * last_pos_y + button_len);
            }break;
            case 6:
            {
                if (view_6[6][length - last_pos_y][last_pos_x + 1] == 0)
                fillrectangle(740 + button_len * last_pos_x, 240 + button_len * last_pos_y, 740 + button_len * last_pos_x + button_len, 240 + button_len * last_pos_y + button_len);
            }break;
            default:
                break;
            }
        }
        //���ݲ���ˢ�´��⿨
        switch (block)
        {
        case 1:
        {
            if (click)
            {
                if (view_6[1][length - pos_x][length - pos_y] == 0)
                {
                    view_6[1][length - pos_x][length - pos_y] = 1;
                    setfillcolor(RGB(0, 200, 255));//��
                    fillrectangle(20 + button_len * pos_x, 240 + button_len * pos_y, 20 + button_len * pos_x + button_len, 240 + button_len * pos_y + button_len);
                }
                else if (view_6[1][length - pos_x][length - pos_y] == 1)
                {
                    view_6[1][length - pos_x][length - pos_y] = 0;
                    setfillcolor(RGB(150, 150, 150));//��
                    fillrectangle(20 + button_len * pos_x, 240 + button_len * pos_y, 20 + button_len * pos_x + button_len, 240 + button_len * pos_y + button_len);
                }

            }
            else
            {
                if (view_6[1][length - pos_x][length - pos_y] == 0)
                {
                    setfillcolor(RGB(255, 55, 0));//��
                    fillrectangle(20 + button_len * pos_x, 240 + button_len * pos_y, 20 + button_len * pos_x + button_len, 240 + button_len * pos_y + button_len);
                }
                else
                    ;
            }
        }break;
        case 2:
        {
            if (click)
            {
                if (view_6[2][pos_y + 1][length - pos_x] == 0)
                {
                    view_6[2][pos_y + 1][length - pos_x] = 1;
                    setfillcolor(RGB(0, 200, 255));//��
                    fillrectangle(260 + button_len * pos_x, 240 + button_len * pos_y, 260 + button_len * pos_x + button_len, 240 + button_len * pos_y + button_len);
                }
                else if (view_6[2][pos_y + 1][length - pos_x] == 1)
                {
                    view_6[2][pos_y + 1][length - pos_x] = 0;
                    setfillcolor(RGB(150, 150, 150));//��
                    fillrectangle(260 + button_len * pos_x, 240 + button_len * pos_y, 260 + button_len * pos_x + button_len, 240 + button_len * pos_y + button_len);
                }
            }
            else
            {
                if (view_6[2][pos_y + 1][length - pos_x] == 0)
                {
                    setfillcolor(RGB(255, 55, 0));//��
                    fillrectangle(260 + button_len * pos_x, 240 + button_len * pos_y, 260 + button_len * pos_x + button_len, 240 + button_len * pos_y + button_len);
                }
                else
                    ;
            }
        }break;
        case 3:
        {
            if (click)
            {
                if (view_6[3][pos_x + 1][pos_y + 1] == 0)
                {
                    view_6[3][pos_x + 1][pos_y + 1] = 1;
                    setfillcolor(RGB(0, 200, 255));//��
                    fillrectangle(500 + button_len * pos_x, 240 + button_len * pos_y, 500 + button_len * pos_x + button_len, 240 + button_len * pos_y + button_len);
                }
                else if (view_6[3][pos_x + 1][pos_y + 1] == 1)
                {
                    view_6[3][pos_x + 1][pos_y+ 1] = 0;
                    setfillcolor(RGB(150, 150, 150));//��
                    fillrectangle(500 + button_len * pos_x, 240 + button_len * pos_y, 500 + button_len * pos_x + button_len, 240 + button_len * pos_y + button_len);
                }
            }
            else
            {
                if(view_6[3][pos_x + 1][pos_y + 1] == 0)
                {
                    setfillcolor(RGB(255, 55, 0));//��
                    fillrectangle(500 + button_len * pos_x, 240 + button_len * pos_y, 500 + button_len * pos_x + button_len, 240 + button_len * pos_y + button_len);
                }
            }
        }break;
        case 4:
        {
            if (click)
            {
                if (view_6[4][length - pos_x ][length - pos_y] == 0)
                {
                    view_6[4][length - pos_x][length - pos_y] = 1;
                    setfillcolor(RGB(0, 200, 255));//��
                    fillrectangle(500 + button_len * pos_x, 0 + button_len * pos_y, 500 + button_len * pos_x + button_len, 0 + button_len * pos_y + button_len);
                }
                else if (view_6[4][length - pos_x][length - pos_y] == 1)
                {
                    view_6[4][length - pos_x][length - pos_y] = 0;
                    setfillcolor(RGB(150, 150, 150));//��
                    fillrectangle(500 + button_len * pos_x, 0 + button_len * pos_y, 500 + button_len * pos_x + button_len, 0 + button_len * pos_y + button_len);
                }
            }
            else
            {
                if (view_6[4][length - pos_x][length - pos_y] == 0)
                {
                    setfillcolor(RGB(255, 55, 0));//��
                    fillrectangle(500 + button_len * pos_x, 0 + button_len * pos_y, 500 + button_len * pos_x + button_len, 0 + button_len * pos_y + button_len);
                }
            }
        }break;
        case 5:
        {
            if (click)
            {
                if (view_6[5][pos_x + 1][pos_y + 1] == 0)
                {
                    view_6[5][pos_x + 1][pos_y + 1] = 1;
                    setfillcolor(RGB(0, 200, 255));//��
                    fillrectangle(500 + button_len * pos_x, 480 + button_len * pos_y, 500 + button_len * pos_x + button_len, 480 + button_len * pos_y + button_len);
                }
                else if (view_6[5][pos_x + 1][pos_y + 1] == 1)
                {
                    view_6[5][pos_x + 1][pos_y + 1] = 0;
                    setfillcolor(RGB(150, 150, 150));//��
                    fillrectangle(500 + button_len * pos_x, 480 + button_len * pos_y, 500 + button_len * pos_x + button_len, 480 + button_len * pos_y + button_len);
                }
            }
            else
            {
                if (view_6[5][pos_x + 1][pos_y + 1] == 0)
                {
                    setfillcolor(RGB(255, 55, 0));//��
                    fillrectangle(500 + button_len * pos_x, 480 + button_len * pos_y, 500 + button_len * pos_x + button_len, 480 + button_len * pos_y + button_len);
                }
            }
        }break;
        case 6:
        {
            if (click)
            {
                if (view_6[6][length - pos_y][ pos_x + 1] == 0)
                {
                    view_6[6][length - pos_y][pos_x + 1] = 1;
                    setfillcolor(RGB(0, 200, 255));//��
                    fillrectangle(740 + button_len * pos_x, 240 + button_len * pos_y, 740 + button_len * pos_x + button_len, 240 + button_len * pos_y + button_len);
                }
                else if (view_6[6][length - pos_y][pos_x + 1] == 1)
                {
                    view_6[6][length - pos_y][pos_x + 1] = 0;
                    setfillcolor(RGB(150, 150, 150));//��
                    fillrectangle(740 + button_len * pos_x, 240 + button_len * pos_y, 740 + button_len * pos_x + button_len, 240 + button_len * pos_y + button_len);
                }
            }
            else
            {
                if (view_6[6][length - pos_y][pos_x + 1] == 0)
                {
                    setfillcolor(RGB(255, 55, 0));//��
                    fillrectangle(740 + button_len * pos_x, 240 + button_len * pos_y, 740 + button_len * pos_x + button_len, 240 + button_len * pos_y + button_len);
                }
            }
        }break;
        default:
            break;
        }     
        SetWorkingImage();
        putimage(0, 0, &answer_sheet);
        //��¼��ǰ״̬��Ϊ��һ��ѭ���ġ��ϸ�״̬��
        last_block = block;
        last_click = click;
        last_pos_x = pos_x;
        last_pos_y = pos_y;        
    }
    //����
    if (back)
    {
        cleardevice();
        SetWorkingImage();//�˳�����ǰ�ָ�Ĭ�ϻ�ͼ�豸
        return 0;
    }
    //����𰸲��˶�
    else if (submit)
    {
        int right = 1;//����źţ��ж��Ƿ�ȫ����ȷ
        SetWorkingImage(&answer_sheet);
        for (int i = 1; i <= 6; i++)
        {
            switch (i)
            {
            case 1:
                for (int x = 1; x <= length; x++)
                {
                    for (int y = 1; y <= length; y++)
                    {
                        if (view_6[1][length - (x - 1)][length - (y - 1)] && cubeptr->top_view[length - (x - 1)][length - (y - 1)])
                        {
                            setfillcolor(RGB(15, 200, 105));//��ɫ��ʾ����ͨ��
                            fillrectangle(20 + button_len * (x - 1), 240 + button_len * (y - 1), 20 + button_len * (x - 1) + button_len, 240 + button_len * (y - 1) + button_len);
                        }
                        else if (view_6[1][length - (x - 1)][length - (y - 1)])
                        {
                            right = 0;
                            setfillcolor(RGB(255, 55, 0));//��ɫ��ʾ����Ŀ�
                            fillrectangle(20 + button_len * (x - 1), 240 + button_len * (y - 1), 20 + button_len * (x - 1) + button_len, 240 + button_len * (y - 1) + button_len);
                        }
                        else if (cubeptr->top_view[length - (x - 1)][length - (y - 1)])
                        {
                            right = 0;
                            setfillcolor(RGB(170, 240, 170));//ǳ��ɫ��ʾȱ��Ŀ�
                            fillrectangle(20 + button_len * (x - 1), 240 + button_len * (y - 1), 20 + button_len * (x - 1) + button_len, 240 + button_len * (y - 1) + button_len);
                        }
                    }
                }break;
            case 2:
                for (int x = 1; x <= length; x++)
                {
                    for (int y = 1; y <= length; y++)
                    {
                        if (view_6[2][y][length - (x-1)] && cubeptr->left_view[y][length - (x - 1)])
                        {
                            setfillcolor(RGB(15, 200, 105));//��ɫ��ʾ����ͨ��
                            fillrectangle(260 + button_len * (x - 1), 240 + button_len * (y - 1), 260 + button_len * (x - 1) + button_len, 240 + button_len * (y - 1) + button_len);
                        }
                        else if (view_6[2][y][length - (x - 1)])
                        {
                            right = 0;
                            setfillcolor(RGB(255, 55, 0));//��ɫ��ʾ����Ŀ�
                            fillrectangle(260 + button_len * (x - 1), 240 + button_len * (y - 1), 260 + button_len * (x - 1) + button_len, 240 + button_len * (y - 1) + button_len);
                        }
                        else if (cubeptr->left_view[y][length - (x - 1)])
                        {
                            right = 0;
                            setfillcolor(RGB(170, 240, 170));//ǳ��ɫ��ʾȱ��Ŀ�
                            fillrectangle(260 + button_len * (x - 1), 240 + button_len * (y - 1), 260 + button_len * (x - 1) + button_len, 240 + button_len * (y - 1) + button_len);
                        }
                    }
                }break;
            case 3:
                for (int x = 1; x <= length; x++)
                {
                    for (int y = 1; y <= length; y++)
                    {
                        if (view_6[3][x][y] && cubeptr->bottom_view[x][y])
                        {
                            setfillcolor(RGB(15, 200, 105));//��ɫ��ʾ����ͨ��
                            fillrectangle(500 + button_len * (x - 1), 240 + button_len * (y - 1), 500 + button_len * (x - 1) + button_len, 240 + button_len * (y - 1) + button_len);
                        }
                        else if (view_6[3][x][y])
                        {
                            right = 0;
                            setfillcolor(RGB(255, 55, 0));//��ɫ��ʾ����Ŀ�
                            fillrectangle(500 + button_len * (x - 1), 240 + button_len * (y - 1), 500 + button_len * (x - 1) + button_len, 240 + button_len * (y - 1) + button_len);
                        }
                        else if (cubeptr->bottom_view[x][y])
                        {
                            right = 0;
                            setfillcolor(RGB(170, 240, 170));//ǳ��ɫ��ʾȱ��Ŀ�
                            fillrectangle(500 + button_len * (x - 1), 240 + button_len * (y - 1), 500 + button_len * (x - 1) + button_len, 240 + button_len * (y - 1) + button_len);
                        }
                    }
                }break;
            case 4:
                for (int x = 1; x <= length; x++)
                {
                    for (int y = 1; y <= length; y++)
                    {
                        if (view_6[4][length - (x - 1)][length - (y - 1)] && cubeptr->back_view[length - (x - 1)][length - (y - 1)])
                        {
                            setfillcolor(RGB(15, 200, 105));//��ɫ��ʾ����ͨ��
                            fillrectangle(500 + button_len * (x - 1), button_len * (y - 1), 500 + button_len * (x - 1) + button_len, button_len * (y - 1) + button_len);
                        }
                        else if (view_6[4][length - (x - 1)][length - (y - 1)])
                        {
                            right = 0;
                            setfillcolor(RGB(255, 55, 0));//��ɫ��ʾ����Ŀ�
                            fillrectangle(500 + button_len * (x - 1), button_len * (y - 1), 500 + button_len * (x - 1) + button_len, button_len * (y - 1) + button_len);
                        }
                        else if (cubeptr->back_view[length - (x - 1)][length - (y - 1)])
                        {
                            right = 0;
                            setfillcolor(RGB(170, 240, 170));//ǳ��ɫ��ʾȱ��Ŀ�
                            fillrectangle(500 + button_len * (x - 1), button_len * (y - 1), 500 + button_len * (x - 1) + button_len, button_len * (y - 1) + button_len);
                        }
                    }
                }break;
            case 5:
                for (int x = 1; x <= length; x++)
                {
                    for (int y = 1; y <= length; y++)
                    {
                        if (view_6[5][x][y] && cubeptr->front_view[x][y])
                        {
                            setfillcolor(RGB(15, 200, 105));//��ɫ��ʾ����ͨ��
                            fillrectangle(500 + button_len * (x - 1), 480 + button_len * (y - 1), 500 + button_len * (x - 1) + button_len, 480 + button_len * (y - 1) + button_len);
                        }
                        else if (view_6[5][x][y])
                        {
                            right = 0;
                            setfillcolor(RGB(255, 55, 0));//��ɫ��ʾ����Ŀ�
                            fillrectangle(500 + button_len * (x - 1), 480 + button_len * (y - 1), 500 + button_len * (x - 1) + button_len, 480 + button_len * (y - 1) + button_len);
                        }
                        else if (cubeptr->front_view[x][y])
                        {
                            right = 0;
                            setfillcolor(RGB(170, 240, 170));//ǳ��ɫ��ʾȱ��Ŀ�
                            fillrectangle(500 + button_len * (x - 1), 480 + button_len * (y - 1), 500 + button_len * (x - 1) + button_len, 480 + button_len * (y - 1) + button_len);
                        }
                    }
                }break;
            case 6:
                for (int x = 1; x <= length; x++)
                {
                    for (int y = 1; y <= length; y++)
                    {
                        if (view_6[6][length-(y-1)][x] && cubeptr->right_view[length - (y - 1)][x])
                        {
                            setfillcolor(RGB(15, 200, 105));//��ɫ��ʾ����ͨ��
                            fillrectangle(740 + button_len * (x - 1), 240 + button_len * (y - 1), 740 + button_len * (x - 1) + button_len, 240 + button_len * (y - 1) + button_len);
                        }
                        else if (view_6[6][length - (y - 1)][x])
                        {
                            right = 0;
                            setfillcolor(RGB(255, 55, 0));//��ɫ��ʾ����Ŀ�
                            fillrectangle(740 + button_len * (x - 1), 240 + button_len * (y - 1), 740 + button_len * (x - 1) + button_len, 240 + button_len * (y - 1) + button_len);
                        }
                        else if (cubeptr->right_view[length - (y - 1)][x])
                        {
                            right = 0;
                            setfillcolor(RGB(170, 240, 170));//ǳ��ɫ��ʾȱ��Ŀ�
                            fillrectangle(740 + button_len * (x - 1), 240 + button_len * (y - 1), 740 + button_len * (x - 1) + button_len, 240 + button_len * (y - 1) + button_len);
                        }
                    }
                }break;
            default:
                break;               
            }
        }
        if (right)
        {
            Cube::sum_of_right++;//�����Ŀ��һ
        }
        SetWorkingImage();
        cleardevice();
        putimage(0, 0, &answer_sheet);
        second_btns[9]->show();
        while (true)
        {
            getmessage(&msg, EX_MOUSE);
            //���ؼ�
            second_btns[9]->getmessage(msg);
            if (second_btns[9]->is_inside())
            {
                second_btns[9]->show_touch();//����ڷ��ؼ���Χ�ڣ���ʾ��ť��������ʱ����ʽ��                      
                if (second_btns[9]->beclicked())//����ڷ��ؼ���Χ���ҽ����˵�����ؼ�������ѭ��
                {
                    break;//����ѭ��,�˳����𣬷�����һ���棬���Զ���������
                }
            }
            else //�����겻�ڰ�ť�ķ�Χ�ڣ���ӡ��ť��������ʽ
            {
                second_btns[9]->show();
            }
        } 
        cleardevice();
        SetWorkingImage();//�˳�����ǰ�ָ�Ĭ�ϻ�ͼ�豸
        return 1;
    }
    return 1;
}
//�������������ն�����Դ
interaction::~interaction()
{
    for (int i = 0; i < 3; i++)
    {
        delete menu_btns[i];
    }
    for (int i = 0; i < 5; i++)
    {
        delete second_btns[i];
    }

}
