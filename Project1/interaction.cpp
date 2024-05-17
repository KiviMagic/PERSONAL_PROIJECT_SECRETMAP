#include "interaction.h"
#include "Logic.h"
#include "fstream"
#include <conio.h>
#include <string>
#include <iostream>
//初始化资源
interaction::interaction()
{
    loadimage(&home_bk, _T("image\\home.png"));
    loadimage(&view_bk, _T("image\\3d_view.png"));
    //主页菜单按钮
    menu_btns.push_back(new BASIC_BUTTON(1000, 450, 160, 50));//登录键
    menu_btns[0]->set_sticker(_T("image\\login_touch.png"));
    menu_btns.push_back(new BASIC_BUTTON(1000, 525, 160, 50));//排行榜键
    menu_btns[1]->set_sticker(_T("image\\ranking_list_touch.png"));
    menu_btns.push_back(new BASIC_BUTTON(1000, 600, 160, 50));//退出键
    menu_btns[2]->set_sticker(_T("image\\exit_touch.png"));

    second_btns.push_back(new  SEC_BUTTON(1000, 100, 160, 50));//默认角度键,0
    second_btns[0]->set_stickers(_T("image\\default_normal.png"), _T("image\\default_touch.png"));
    second_btns.push_back(new  SEC_BUTTON(1000, 180, 160, 50));//90°键,1
    second_btns[1]->set_stickers(_T("image\\90_normal.png"), _T("image\\90_touch.png"));
    second_btns.push_back(new  SEC_BUTTON(1000, 260, 160, 50));//180°键,2
    second_btns[2]->set_stickers(_T("image\\180_normal.png"), _T("image\\180_touch.png"));
    second_btns.push_back(new  SEC_BUTTON(1000, 340, 160, 50));//270°键,3
    second_btns[3]->set_stickers(_T("image\\270_normal.png"), _T("image\\270_touch.png"));
    second_btns.push_back(new  SEC_BUTTON(1000, 460, 160, 50));//开始答题键,4
    second_btns[4]->set_stickers(_T("image\\answer_normal.png"), _T("image\\answer_touch.png"));  
    second_btns.push_back(new  SEC_BUTTON(1120, 0, 160, 50));//展示图界面返回键,5
    second_btns[5]->set_stickers(_T("image\\back_normal.png"), _T("image\\back_touch.png"));
    second_btns.push_back(new  SEC_BUTTON(1000, 540, 160, 50));//重新设置键,6
    second_btns[6]->set_stickers(_T("image\\reset_normal.png"), _T("image\\reset_touch.png"));
    second_btns.push_back(new  SEC_BUTTON(1000, 620, 160, 50));//重新生成键,7
    second_btns[7]->set_stickers(_T("image\\recreate_normal.png"), _T("image\\recreate_touch.png"));
    second_btns.push_back(new  SEC_BUTTON(1050, 360, 160, 50));//提交键,8
    second_btns[8]->set_stickers(_T("image\\submit_normal.png"), _T("image\\submit_touch.png"));
    second_btns.push_back(new  SEC_BUTTON(1050, 260, 160, 50));//答题界面返回键,9
    second_btns[9]->set_stickers(_T("image\\back_normal.png"), _T("image\\back_touch.png"));
}
//运行函数
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
//主页函数循环，根据点击跳转页面
int interaction::home()
{
    while(true)
    {   
        int flag = 0;
        BeginBatchDraw();//批量绘制
        getmessage(&msg, EX_MOUSE);
        for (int i = 0; i < menu_btns.size(); i++)
        {           
            menu_btns[i]->getmessage(msg);
            int detect = menu_btns[i]->is_inside();//检测鼠标箭头是否在按钮范围内
            if (detect)
            {   
                menu_btns[i]->show();//如果在按钮范围内，显示按钮（被触碰时的样式）
                flag += detect;
                if (menu_btns[i]->beclicked())//如果在按钮范围内且进行了点击，结束home()函数，返回点击选项
                {
                    return i;
                }
            }
            else if(flag == 0)//如果鼠标不在任意一个按钮的范围内，刷新整个主页页面以恢复按钮的正常样式
            {
                putimage(0, 0, &home_bk);             
            }
        }
        EndBatchDraw();//输出批量绘制
    }
    return HOME;
}
//登录开始游戏
int interaction::login()
{
    BeginBatchDraw();
    bool modified = true;
    Cube* cubeptr = nullptr;
    bool cycle = true, back = false, recreate = false, reset = false;//控制信号
    while (true)
    {
        //如果modified信号为真，进行初始化，需要重新设置参数;  如果modified信号为假，则无需重新设定参数，按原设定重新随机生成（需清空原来数组内数据）
        if (modified)
        {
            cubeptr = new Cube();
        }
        else
        {
            cubeptr->recreate();
        }
        //画好异形立方体的3d视图,直观
        IMAGE draw_bk;
        loadimage(&draw_bk, _T("image//3d_view.png"));
        cubeptr->display_3d(&draw_bk);

        //画好异形立方体的3d视图，旋转90°
        IMAGE draw_bk_90;
        loadimage(&draw_bk_90, _T("image//3d_view.png"));
        cubeptr->display_3d_90(&draw_bk_90);

        //画好异形立方体的3d视图，旋转180°
        IMAGE draw_bk_180;
        loadimage(&draw_bk_180, _T("image//3d_view.png"));
        cubeptr->display_3d_180(&draw_bk_180);

        //画好异形立方体的3d视图，旋转270°
        IMAGE draw_bk_270;
        loadimage(&draw_bk_270, _T("image//3d_view.png"));
        cubeptr->display_3d_270(&draw_bk_270);

        //默认角度展示
        cleardevice();
        putimage(0, 0, &draw_bk);
        cubeptr->display_2d();//控制台版本
        cubeptr->display_front_view();
        cubeptr->display_back_view();
        cubeptr->display_left_view();
        cubeptr->display_right_view();
        cubeptr->display_top_view();
        cubeptr->display_bottom_view();

        EndBatchDraw();
        //选择展示角度
        cycle = true, back = false, recreate = false, reset = false, modified = false;
        while (cycle)
        {
            BeginBatchDraw();
            int choice = display_menu_of_show();
                //打印不同角度的直观图
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
                        recreate = true;//提交完后返回，需重新生成
                    }
                    else
                    putimage(0, 0, &draw_bk); //只是返回到当前选项循环并打印默认角度展示图，不重新生成
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
        delete cubeptr;//释放堆空间
        break;//如果返回，则退出外循环，回到主页
        }
        else if(recreate)
        {
            modified = false;
            continue;
        }
        else if (reset)
        {
            modified = true;
            delete cubeptr;//释放堆空间
            continue;
        }                  
    }       
        return HOME;
}
//排行榜
int interaction::ranking_list()
{
    int s_sub =0, s_rig = 0;

    std::ifstream _rank("ranking.dat", std::ios::in | std::ios::binary);
    _rank.seekg(0);
    _rank.read((char*)&s_sub, sizeof(Cube::sum_of_submit));
    _rank.read((char*)&s_rig, sizeof(Cube::sum_of_right));
    _rank.close();
  
    s_sub += Cube::sum_of_submit, s_rig += Cube::sum_of_right;

    std::cout << "总提交数： " << s_sub << "     总答对数： " << s_rig << std::endl;
    std::cout << "今日提交： " << Cube::sum_of_submit << "     今日答对： " << Cube::sum_of_right << std::endl;

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
        //返回键
        second_btns[5]->getmessage(msg);
        if (second_btns[5]->is_inside())
        {
            second_btns[5]->show_touch();//如果在返回键范围内，显示按钮（被触碰时的样式）                      
            if (second_btns[5]->beclicked())//如果在返回键范围内且进行了点击返回键，结束循环
            {
                break;//结束循环，返回上一界面
            }
        }
        else //如果鼠标不在按钮的范围内，打印按钮的正常样式
        {
            second_btns[5]->show();
        }
    }  
    return HOME;
}
//退出程序
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
    std::cout << "退出游戏，已存档。";
    closegraph();    
}
//展示选项并监视鼠标操作，若有选择则返回选项
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
            int detect = second_btns[i]->is_inside();//检测鼠标箭头是否在按钮范围内
            if (detect)
            {
                second_btns[i]->show_touch();//如果在按钮范围内，显示按钮（被触碰时的样式）                      
                if (second_btns[i]->beclicked())//如果在按钮范围内且进行了点击，结束循环，返回点击选项
                {
                    choice = i;
                    break;
                }
            }
            else //如果鼠标不在按钮的范围内，打印按钮的正常样式
            {
                second_btns[i]->show();
            }
        }
    EndBatchDraw();//输出批量绘制
        if (choice != -1)
            break;
    }
    return choice;
}
//开始作答，进入答题界面(已弃用)
int interaction::answer(int length, Cube*cubeptr)
{
    BeginBatchDraw();
    //控制信号
    bool submit = false, back = false;
    int button_len = 240 / length;//自适应按钮大小
    int block_width = button_len * length;//原本每一块的宽度为240，但是要重新定义宽度，因为上面为整数除法
     //创建绘图设备
    IMAGE answer_sheet(1000, 720);
    //绘制最终答题卡
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
    //清空上一界面
     cleardevice();
    //创建按钮指针向量，在堆区实例化第二按钮对象
    std::vector<THIRD_BUTTON*> third_button;
    //按钮布局
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
    //作答阶段
    while (true)
    {              
        getmessage(&msg, EX_MOUSE);
        //返回键
        second_btns[9]->getmessage(msg);
        if(second_btns[9]->is_inside())
        {
            second_btns[9]->show_touch();//如果在返回键范围内，显示按钮（被触碰时的样式）                      
            if (second_btns[9]->beclicked())//如果在返回键范围内且进行了点击返回键，结束循环
            {    
                back = true;
                break;//结束循环,退出作答，返回上一界面
            }
        }
        else //如果鼠标不在按钮的范围内，打印按钮的正常样式
        {
            second_btns[9]->show();
        }
        //提交键
        second_btns[8]->getmessage(msg);
        if (second_btns[8]->is_inside())
        {
            second_btns[8]->show_touch();//如果在提交键范围内，显示按钮（被触碰时的样式）                      
            if (second_btns[8]->beclicked())//如果在提交键范围内且进行了点击提交键，结束循环
            {
                submit = true;
                break;//结束循环,提交答案
            }
        }
        else //如果鼠标不在按钮的范围内，打印按钮的正常样式
        {
            second_btns[8]->show();
        }
        for (int i = 0; i < third_button.size(); i++)
        {
            touch = 0;
            third_button[i]->getmessage(msg);
            int detect = third_button[i]->is_inside();//检测鼠标箭头是否在按钮范围内
            if (detect)
            {
                //如果在按钮范围内，标记touch
                touch = 1;
                //std::cout << i;//控制台检测用                       
                if (third_button[i]->beclicked())//如果在按钮范围内且进行了点击，标记flag
                {         
                    third_button[i]->set_flag();//flag与负一相乘
                }
            }
            //如果鼠标不在按钮的范围内，不做标记 
            //所有信号收集完毕，确定某一个按钮的最终输出状态            
            third_button[i]->show_3(touch);
        }
        EndBatchDraw();//输出批量绘制
    }
    int(*view_6)[11][11] = nullptr;
    //返回
    if (back)
    {
        cleardevice();
    }
    //填入答案并核对
    else if (submit)
    {   
        view_6 = new int[7][11][11]{ 0 };
        int order = 0, column = 0, line = 0;
        //填到答题卡数组中
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
        //打印到答题卡画图设备上，再打印到窗口
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
                            setfillcolor(RGB(15, 200, 105));//绿色表示符合通过
                            fillrectangle(20 + button_len * (x - 1), 240 + button_len * (y - 1), 20 + button_len * (x - 1) + button_len, 240 + button_len * (y - 1) + button_len);
                        }
                        else if (view_6[1][length - (x - 1)][length - (y - 1)])
                        {
                            setfillcolor(RGB(255, 55, 0));//红色表示多余的块
                            fillrectangle(20 + button_len * (x - 1), 240 + button_len * (y - 1), 20 + button_len * (x - 1) + button_len, 240 + button_len * (y - 1) + button_len);
                        }
                        else if (cubeptr->top_view[length - (x - 1)][length - (y - 1)])
                        {
                            setfillcolor(RGB(170, 240, 170));//浅绿色表示缺填的块
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
                            setfillcolor(RGB(15, 200, 105));//绿色表示符合通过
                            fillrectangle(260 + button_len * (x - 1), 240 + button_len * (y - 1), 260 + button_len * (x - 1) + button_len, 240 + button_len * (y - 1) + button_len);
                        }
                        else if (view_6[2][y][length - (x - 1)])
                        {
                            setfillcolor(RGB(255, 55, 0));//红色表示多余的块
                            fillrectangle(260 + button_len * (x - 1), 240 + button_len * (y - 1), 260 + button_len * (x - 1) + button_len, 240 + button_len * (y - 1) + button_len);
                        }
                        else if (cubeptr->left_view[y][length - (x - 1)])
                        {
                            setfillcolor(RGB(170, 240, 170));//浅绿色表示缺填的块
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
                            setfillcolor(RGB(15, 200, 105));//绿色表示符合通过
                            fillrectangle(500 + button_len * (x - 1), 240 + button_len * (y - 1), 500 + button_len * (x - 1) + button_len, 240 + button_len * (y - 1) + button_len);
                        }
                        else if (view_6[3][x][y])
                        {
                            setfillcolor(RGB(255, 55, 0));//红色表示多余的块
                            fillrectangle(500 + button_len * (x - 1), 240 + button_len * (y - 1), 500 + button_len * (x - 1) + button_len, 240 + button_len * (y - 1) + button_len);
                        }
                        else if (cubeptr->bottom_view[x][y])
                        {
                            setfillcolor(RGB(170, 240, 170));//浅绿色表示缺填的块
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
                            setfillcolor(RGB(15, 200, 105));//绿色表示符合通过
                            fillrectangle(500 + button_len * (x - 1), button_len * (y - 1), 500 + button_len * (x - 1) + button_len, button_len * (y - 1) + button_len);
                        }
                        else if (view_6[4][length - (x - 1)][length - (y - 1)])
                        {
                            setfillcolor(RGB(255, 55, 0));//红色表示多余的块
                            fillrectangle(500 + button_len * (x - 1), button_len * (y - 1), 500 + button_len * (x - 1) + button_len, button_len * (y - 1) + button_len);
                        }
                        else if (cubeptr->back_view[length - (x - 1)][length - (y - 1)])
                        {
                            setfillcolor(RGB(170, 240, 170));//浅绿色表示缺填的块
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
                            setfillcolor(RGB(15, 200, 105));//绿色表示符合通过
                            fillrectangle(500 + button_len * (x - 1), 480 + button_len * (y - 1), 500 + button_len * (x - 1) + button_len, 480 + button_len * (y - 1) + button_len);
                        }
                        else if (view_6[5][x][y])
                        {
                            setfillcolor(RGB(255, 55, 0));//红色表示多余的块
                            fillrectangle(500 + button_len * (x - 1), 480 + button_len * (y - 1), 500 + button_len * (x - 1) + button_len, 480 + button_len * (y - 1) + button_len);
                        }
                        else if (cubeptr->front_view[x][y])
                        {
                            setfillcolor(RGB(170, 240, 170));//浅绿色表示缺填的块
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
                            setfillcolor(RGB(15, 200, 105));//绿色表示符合通过
                            fillrectangle(740 + button_len * (x - 1), 240 + button_len * (y - 1), 740 + button_len * (x - 1) + button_len, 240 + button_len * (y - 1) + button_len);
                        }
                        else if (view_6[6][length - (y - 1)][x])
                        {
                            setfillcolor(RGB(255, 55, 0));//红色表示多余的块
                            fillrectangle(740 + button_len * (x - 1), 240 + button_len * (y - 1), 740 + button_len * (x - 1) + button_len, 240 + button_len * (y - 1) + button_len);
                        }
                        else if (cubeptr->right_view[length - (y - 1)][x])
                        {
                            setfillcolor(RGB(170, 240, 170));//浅绿色表示缺填的块
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
    //回收堆区资源
    delete []view_6;
    for (int i = 0; i < length * length * 6; i++)
    {
        delete third_button[i];
    }
    cleardevice();
    return 0;
}
//开始作答，进入答题界面
int interaction::answer_v1(int length, Cube* cubeptr)
{
    bool submit = false, back = false;//控制信号
    int button_len = 240 / length;//自适应按钮大小
    int block_width = button_len * length;//原本每一块的宽度为240，但是要重新定义宽度，因为上面为整数除法
    cleardevice();//清空上一界面
    //创建绘图设备
    IMAGE answer_sheet(1000, 720);
    SetWorkingImage(&answer_sheet);//设置当前绘图设备为答题卡
    //绘制答题卡
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
    //作答阶段 (边做边填答题卡)
    SetWorkingImage();
    second_btns[8]->show();//显示两个按钮
    second_btns[9]->show();
    int last_block = 1, last_pos_x = 0, last_pos_y = 0;//上一状态参数
    bool last_click = 0;//上一状态参数
    int mouse_x = 0, mouse_y = 0;
    int pos_x = 0, pos_y =0, block = 0;
    bool click = 0;
    int(*view_6)[11][11] = new int[7][11][11]{0};
    while (true)
    {       
        getmessage(&msg, EX_MOUSE); 
        //控制信号
        submit = false, back = false;
        //返回键
        second_btns[9]->getmessage(msg);
        if(second_btns[9]->is_inside())
        {
            second_btns[9]->show_touch();//如果在返回键范围内，显示按钮（被触碰时的样式）                      
            if (second_btns[9]->beclicked())//如果在返回键范围内且进行了点击返回键，结束循环
            {    
                back = true;
                break;//结束循环,退出作答，返回上一界面
            }
        }
        else //如果鼠标不在按钮的范围内，打印按钮的正常样式
        {
            second_btns[9]->show();
        }
        //提交键
        second_btns[8]->getmessage(msg);
        if (second_btns[8]->is_inside())
        {
            second_btns[8]->show_touch();//如果在提交键范围内，显示按钮（被触碰时的样式）                      
            if (second_btns[8]->beclicked())//如果在提交键范围内且进行了点击提交键，结束循环
            {
                Cube::sum_of_submit++;//提交数加一
                submit = true;
                break;//结束循环,提交答案
            }
        }
        else //如果鼠标不在按钮的范围内，打印按钮的正常样式
        {
            second_btns[8]->show();
        }
         mouse_x = msg.x, mouse_y = msg.y;
         block = 0, click = msg.lbutton;
        //std::cout << "( " << mouse_x << ", " << mouse_y << ")" << std::endl;//控制台显示坐标
        //鼠标定位到块区域
        if ( (mouse_x-20)* (mouse_x - 20 - block_width) < 0 && (mouse_y - 240)*(mouse_y - 240 - block_width) < 0)//上
        {
            pos_x = (mouse_x - 20) / button_len;
            pos_y = (mouse_y - 240) / button_len;
            block = 1;
        }
        else if ((mouse_x - 260) * (mouse_x - 260 - block_width) < 0 && (mouse_y - 240) * (mouse_y - 240 - block_width) < 0)//左
        {
            pos_x = (mouse_x - 260) / button_len;
            pos_y = (mouse_y - 240) / button_len;
            block = 2; 
            
        }
        else if ((mouse_x - 500) * (mouse_x - 500 - block_width) < 0 && (mouse_y - 240) * (mouse_y - 240 - block_width) < 0)//底
        {
            pos_x = (mouse_x - 500) / button_len;
            pos_y = (mouse_y - 240) / button_len;
            block = 3; 
        }
        else if ((mouse_x - 500) * (mouse_x - 500 - block_width) < 0 && (mouse_y - 0) * (mouse_y - 0 - block_width) < 0)//后
        {
            pos_x = (mouse_x - 500) / button_len;
            pos_y = (mouse_y - 0) / button_len;
            block = 4; 
        }
        else if ((mouse_x - 500) * (mouse_x - 500 - block_width) < 0 && (mouse_y - 480) * (mouse_y - 480 - block_width) < 0)//前
        {
            pos_x = (mouse_x - 500) / button_len;
            pos_y = (mouse_y - 480) / button_len;
            block = 5;
        }
        else if ((mouse_x - 740) * (mouse_x - 740 - block_width) < 0 && (mouse_y - 240) * (mouse_y - 240 - block_width) < 0)//右
        {
            pos_x = (mouse_x - 740) / button_len;
            pos_y = (mouse_y - 240) / button_len;
            block = 6; 
        }
        else
        {
            block = -1;
        }
        SetWorkingImage(&answer_sheet);//设置当前绘图设备为答题卡
        //若当前所处块与上次所处块不同，且上次没有点击确定，则用“灰方块”还原上次所处的按钮
        if (!((pos_x == last_pos_x) && (pos_y == last_pos_y) && (block == last_block)))
        {
            setfillcolor(RGB(150, 150, 150));//灰
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
        //根据操作刷新答题卡
        switch (block)
        {
        case 1:
        {
            if (click)
            {
                if (view_6[1][length - pos_x][length - pos_y] == 0)
                {
                    view_6[1][length - pos_x][length - pos_y] = 1;
                    setfillcolor(RGB(0, 200, 255));//蓝
                    fillrectangle(20 + button_len * pos_x, 240 + button_len * pos_y, 20 + button_len * pos_x + button_len, 240 + button_len * pos_y + button_len);
                }
                else if (view_6[1][length - pos_x][length - pos_y] == 1)
                {
                    view_6[1][length - pos_x][length - pos_y] = 0;
                    setfillcolor(RGB(150, 150, 150));//灰
                    fillrectangle(20 + button_len * pos_x, 240 + button_len * pos_y, 20 + button_len * pos_x + button_len, 240 + button_len * pos_y + button_len);
                }

            }
            else
            {
                if (view_6[1][length - pos_x][length - pos_y] == 0)
                {
                    setfillcolor(RGB(255, 55, 0));//红
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
                    setfillcolor(RGB(0, 200, 255));//蓝
                    fillrectangle(260 + button_len * pos_x, 240 + button_len * pos_y, 260 + button_len * pos_x + button_len, 240 + button_len * pos_y + button_len);
                }
                else if (view_6[2][pos_y + 1][length - pos_x] == 1)
                {
                    view_6[2][pos_y + 1][length - pos_x] = 0;
                    setfillcolor(RGB(150, 150, 150));//灰
                    fillrectangle(260 + button_len * pos_x, 240 + button_len * pos_y, 260 + button_len * pos_x + button_len, 240 + button_len * pos_y + button_len);
                }
            }
            else
            {
                if (view_6[2][pos_y + 1][length - pos_x] == 0)
                {
                    setfillcolor(RGB(255, 55, 0));//红
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
                    setfillcolor(RGB(0, 200, 255));//蓝
                    fillrectangle(500 + button_len * pos_x, 240 + button_len * pos_y, 500 + button_len * pos_x + button_len, 240 + button_len * pos_y + button_len);
                }
                else if (view_6[3][pos_x + 1][pos_y + 1] == 1)
                {
                    view_6[3][pos_x + 1][pos_y+ 1] = 0;
                    setfillcolor(RGB(150, 150, 150));//灰
                    fillrectangle(500 + button_len * pos_x, 240 + button_len * pos_y, 500 + button_len * pos_x + button_len, 240 + button_len * pos_y + button_len);
                }
            }
            else
            {
                if(view_6[3][pos_x + 1][pos_y + 1] == 0)
                {
                    setfillcolor(RGB(255, 55, 0));//红
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
                    setfillcolor(RGB(0, 200, 255));//蓝
                    fillrectangle(500 + button_len * pos_x, 0 + button_len * pos_y, 500 + button_len * pos_x + button_len, 0 + button_len * pos_y + button_len);
                }
                else if (view_6[4][length - pos_x][length - pos_y] == 1)
                {
                    view_6[4][length - pos_x][length - pos_y] = 0;
                    setfillcolor(RGB(150, 150, 150));//灰
                    fillrectangle(500 + button_len * pos_x, 0 + button_len * pos_y, 500 + button_len * pos_x + button_len, 0 + button_len * pos_y + button_len);
                }
            }
            else
            {
                if (view_6[4][length - pos_x][length - pos_y] == 0)
                {
                    setfillcolor(RGB(255, 55, 0));//红
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
                    setfillcolor(RGB(0, 200, 255));//蓝
                    fillrectangle(500 + button_len * pos_x, 480 + button_len * pos_y, 500 + button_len * pos_x + button_len, 480 + button_len * pos_y + button_len);
                }
                else if (view_6[5][pos_x + 1][pos_y + 1] == 1)
                {
                    view_6[5][pos_x + 1][pos_y + 1] = 0;
                    setfillcolor(RGB(150, 150, 150));//灰
                    fillrectangle(500 + button_len * pos_x, 480 + button_len * pos_y, 500 + button_len * pos_x + button_len, 480 + button_len * pos_y + button_len);
                }
            }
            else
            {
                if (view_6[5][pos_x + 1][pos_y + 1] == 0)
                {
                    setfillcolor(RGB(255, 55, 0));//红
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
                    setfillcolor(RGB(0, 200, 255));//蓝
                    fillrectangle(740 + button_len * pos_x, 240 + button_len * pos_y, 740 + button_len * pos_x + button_len, 240 + button_len * pos_y + button_len);
                }
                else if (view_6[6][length - pos_y][pos_x + 1] == 1)
                {
                    view_6[6][length - pos_y][pos_x + 1] = 0;
                    setfillcolor(RGB(150, 150, 150));//灰
                    fillrectangle(740 + button_len * pos_x, 240 + button_len * pos_y, 740 + button_len * pos_x + button_len, 240 + button_len * pos_y + button_len);
                }
            }
            else
            {
                if (view_6[6][length - pos_y][pos_x + 1] == 0)
                {
                    setfillcolor(RGB(255, 55, 0));//红
                    fillrectangle(740 + button_len * pos_x, 240 + button_len * pos_y, 740 + button_len * pos_x + button_len, 240 + button_len * pos_y + button_len);
                }
            }
        }break;
        default:
            break;
        }     
        SetWorkingImage();
        putimage(0, 0, &answer_sheet);
        //记录当前状态作为下一次循环的“上个状态”
        last_block = block;
        last_click = click;
        last_pos_x = pos_x;
        last_pos_y = pos_y;        
    }
    //返回
    if (back)
    {
        cleardevice();
        SetWorkingImage();//退出函数前恢复默认绘图设备
        return 0;
    }
    //填入答案并核对
    else if (submit)
    {
        int right = 1;//标记信号，判断是否全部正确
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
                            setfillcolor(RGB(15, 200, 105));//绿色表示符合通过
                            fillrectangle(20 + button_len * (x - 1), 240 + button_len * (y - 1), 20 + button_len * (x - 1) + button_len, 240 + button_len * (y - 1) + button_len);
                        }
                        else if (view_6[1][length - (x - 1)][length - (y - 1)])
                        {
                            right = 0;
                            setfillcolor(RGB(255, 55, 0));//红色表示多余的块
                            fillrectangle(20 + button_len * (x - 1), 240 + button_len * (y - 1), 20 + button_len * (x - 1) + button_len, 240 + button_len * (y - 1) + button_len);
                        }
                        else if (cubeptr->top_view[length - (x - 1)][length - (y - 1)])
                        {
                            right = 0;
                            setfillcolor(RGB(170, 240, 170));//浅绿色表示缺填的块
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
                            setfillcolor(RGB(15, 200, 105));//绿色表示符合通过
                            fillrectangle(260 + button_len * (x - 1), 240 + button_len * (y - 1), 260 + button_len * (x - 1) + button_len, 240 + button_len * (y - 1) + button_len);
                        }
                        else if (view_6[2][y][length - (x - 1)])
                        {
                            right = 0;
                            setfillcolor(RGB(255, 55, 0));//红色表示多余的块
                            fillrectangle(260 + button_len * (x - 1), 240 + button_len * (y - 1), 260 + button_len * (x - 1) + button_len, 240 + button_len * (y - 1) + button_len);
                        }
                        else if (cubeptr->left_view[y][length - (x - 1)])
                        {
                            right = 0;
                            setfillcolor(RGB(170, 240, 170));//浅绿色表示缺填的块
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
                            setfillcolor(RGB(15, 200, 105));//绿色表示符合通过
                            fillrectangle(500 + button_len * (x - 1), 240 + button_len * (y - 1), 500 + button_len * (x - 1) + button_len, 240 + button_len * (y - 1) + button_len);
                        }
                        else if (view_6[3][x][y])
                        {
                            right = 0;
                            setfillcolor(RGB(255, 55, 0));//红色表示多余的块
                            fillrectangle(500 + button_len * (x - 1), 240 + button_len * (y - 1), 500 + button_len * (x - 1) + button_len, 240 + button_len * (y - 1) + button_len);
                        }
                        else if (cubeptr->bottom_view[x][y])
                        {
                            right = 0;
                            setfillcolor(RGB(170, 240, 170));//浅绿色表示缺填的块
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
                            setfillcolor(RGB(15, 200, 105));//绿色表示符合通过
                            fillrectangle(500 + button_len * (x - 1), button_len * (y - 1), 500 + button_len * (x - 1) + button_len, button_len * (y - 1) + button_len);
                        }
                        else if (view_6[4][length - (x - 1)][length - (y - 1)])
                        {
                            right = 0;
                            setfillcolor(RGB(255, 55, 0));//红色表示多余的块
                            fillrectangle(500 + button_len * (x - 1), button_len * (y - 1), 500 + button_len * (x - 1) + button_len, button_len * (y - 1) + button_len);
                        }
                        else if (cubeptr->back_view[length - (x - 1)][length - (y - 1)])
                        {
                            right = 0;
                            setfillcolor(RGB(170, 240, 170));//浅绿色表示缺填的块
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
                            setfillcolor(RGB(15, 200, 105));//绿色表示符合通过
                            fillrectangle(500 + button_len * (x - 1), 480 + button_len * (y - 1), 500 + button_len * (x - 1) + button_len, 480 + button_len * (y - 1) + button_len);
                        }
                        else if (view_6[5][x][y])
                        {
                            right = 0;
                            setfillcolor(RGB(255, 55, 0));//红色表示多余的块
                            fillrectangle(500 + button_len * (x - 1), 480 + button_len * (y - 1), 500 + button_len * (x - 1) + button_len, 480 + button_len * (y - 1) + button_len);
                        }
                        else if (cubeptr->front_view[x][y])
                        {
                            right = 0;
                            setfillcolor(RGB(170, 240, 170));//浅绿色表示缺填的块
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
                            setfillcolor(RGB(15, 200, 105));//绿色表示符合通过
                            fillrectangle(740 + button_len * (x - 1), 240 + button_len * (y - 1), 740 + button_len * (x - 1) + button_len, 240 + button_len * (y - 1) + button_len);
                        }
                        else if (view_6[6][length - (y - 1)][x])
                        {
                            right = 0;
                            setfillcolor(RGB(255, 55, 0));//红色表示多余的块
                            fillrectangle(740 + button_len * (x - 1), 240 + button_len * (y - 1), 740 + button_len * (x - 1) + button_len, 240 + button_len * (y - 1) + button_len);
                        }
                        else if (cubeptr->right_view[length - (y - 1)][x])
                        {
                            right = 0;
                            setfillcolor(RGB(170, 240, 170));//浅绿色表示缺填的块
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
            Cube::sum_of_right++;//答对数目加一
        }
        SetWorkingImage();
        cleardevice();
        putimage(0, 0, &answer_sheet);
        second_btns[9]->show();
        while (true)
        {
            getmessage(&msg, EX_MOUSE);
            //返回键
            second_btns[9]->getmessage(msg);
            if (second_btns[9]->is_inside())
            {
                second_btns[9]->show_touch();//如果在返回键范围内，显示按钮（被触碰时的样式）                      
                if (second_btns[9]->beclicked())//如果在返回键范围内且进行了点击返回键，结束循环
                {
                    break;//结束循环,退出作答，返回上一界面，并自动重新生成
                }
            }
            else //如果鼠标不在按钮的范围内，打印按钮的正常样式
            {
                second_btns[9]->show();
            }
        } 
        cleardevice();
        SetWorkingImage();//退出函数前恢复默认绘图设备
        return 1;
    }
    return 1;
}
//析构函数，回收堆区资源
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
