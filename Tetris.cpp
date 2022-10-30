#include "myclude.h" 

void gotoxy(int x,int y);  //移动光标
int color(int c);   //颜色
void hidden_cursor();  //隐藏光标
void inter_face();  //初始化界面
void init_dia();   //初始化方块信息
void draw_dia(int base,int space_c,int x,int y);   //覆盖方块
void draw_kong(int base,int space_c,int x,int y); //画方块
int panduan(int n,int space_c,int x,int y);  //判断方块是否到底
void start_game();   //开始游戏
int xiaochu();  //方块填满一行时进行消除
void read_file();   //读写最高记录
void write_file();  //写最高纪录
int grade=0;  //当前分数
int max=0;  //最高记录
int nn=0;
int main(); 

struct Face
{
    int data[FACE_X][FACE_Y+10];    //数值，为1是方块，为0是空格
    int color[FACE_X][FACE_Y+10];   //对应方块的颜色
}face;

typedef struct Diamonds
{   
    int space[4][4];        //4*4矩阵，为1为方块，为0 为空
}Dia;

Dia dia[7][4];  //一维基础7个板块，二维表示旋转次数，通过旋转可得到21个板块 

/////////////////////////////////////////////////
int main()//主函数 
{   
    system("cls"); //实现清屏操作 
    system("title 一起来挑战俄罗斯方块！！");  //标题 
    color(7);
    system("mode con cols=70 lines=30");  //显示窗口的宽度和高度 
    hidden_cursor(); //隐藏光标
    srand(time(NULL)); //利用时间随机种子产生随机数 
    read_file();  //读写最高记录
    grade=0;
    inter_face(); //初始化界面
    init_dia();  //初始化方块信息
    nn=rand()%7; //随机生成下一块
    while(1)
    {
        start_game();
    }
    return 0;
}


void start_game()
{   
    int n,ch,t=0,x=0,y=FACE_Y/2-2,i,j;
    int space_c=0;  //旋转次数
    draw_kong(nn,space_c,4,FACE_Y+3);
    n=nn;   
    nn=rand()%7;    //随机生成下一块
    color(nn);
    draw_dia(nn,space_c,4,FACE_Y+3); //覆盖方块 
    while(1)
    {   
        color(n);
        draw_dia(n,space_c,x,y);//画出图形
        if(t==0)
            t=15000;//设置板块下落的时间 
        while(--t)
        {  
		    if(kbhit()!=0)// 判断当前是否有键盘输入，如果有输入就跳出
                break;  
        }
        if(t==0)
        {
            if(panduan(n,space_c,x+1,y)==1) //判断方块是否到底
            {   
			    draw_kong(n,space_c,x,y);
                x++;            //方块继续向下降落
            }
            else
            {
                for(i=0;i<4;i++)
                {
                    for(j=0;j<4;j++)
                    { 
                        if(dia[n][space_c].space[i][j]==1)
                        {   
                            face.data[x+i][y+j]=Box;
                            face.color[x+i][y+j]=n;
                            while(xiaochu());
                        }
                    }
                }
                return;
            }
        }
        else
        {
            ch=getch();  //从键盘接收
            switch(ch)     //移动
            {
            case LEFT: if(panduan(n,space_c,x,y-1)==1)   //判断方块是否可以向左移动
                       {   draw_kong(n,space_c,x,y);
                           y--;
                       }
                       break;
            case RIGHT: if(panduan(n,space_c,x,y+1)==1)  //判断方块是否可以向右移动
                        {   draw_kong(n,space_c,x,y);
                            y++;
                        }
                        break;
            case DOWN: if(panduan(n,space_c,x+1,y)==1)  //判断方块是否可以向下移动
                        {   draw_kong(n,space_c,x,y);
                            x++;
                        }
                        break;
            case SPACE: if(panduan(n,(space_c+1)%4,x+1,y)==1) //判断方块是否可以进行旋转 
                        {   draw_kong(n,space_c,x,y);
                            space_c=(space_c+1)%4;
                        }
                        break;
            case ESC  : system("cls");   //结束游戏 
                        gotoxy(FACE_X/2,FACE_Y);   //移动光标 
                        printf("---游戏结束!---\n\n");
                        gotoxy(FACE_X/2+2,FACE_Y);  //移动光标 
                        printf("---按任意键退出!---\n");
                        getch();
                        exit(0);
                        break;
            case  'R':          //重新开始游戏 
            case  'r':  main();
                        exit(0);
            case  'S':          //暂停游戏
            case  's':  while(1)
                        {   if(kbhit()!=0)//有输入就跳出
                            break;  
                        }
                        break;
            }
        }
    }
}

void draw_kong(int base,int space_c,int x,int y) //画板块 
{
    int i,j;
    for(i=0;i<4;i++)
    {
        for(j=0;j<4;j++)
        {
            gotoxy(x+i,2*(y+j));
            if(dia[base][space_c].space[i][j]==1)
            printf("  ");
        }
    }

}

void draw_dia(int base,int space_c,int x,int y)  //覆盖板块 
{
    int i,j;
    for(i=0;i<4;i++)
    {
        for(j=0;j<4;j++)
        {
            gotoxy(x+i,2*(y+j));
            if(dia[base][space_c].space[i][j]==1)
            printf("●");
        }
    }
}

void init_dia()  //板块的产生以及板块形状的改变 
{
    int i,j,k,z;
    int tmp[4][4];
    for(i=0;i<3;i++)
        dia[0][0].space[1][i]=1;
    dia[0][0].space[2][1]=1;     //土字形

    for(i=1;i<4;i++)
        dia[1][0].space[i][1]=1;
    dia[1][0].space[1][2]=1;    //L形--1

    for(i=1;i<4;i++)
        dia[2][0].space[i][2]=1;
    dia[2][0].space[1][1]=1;    //L形--2

    for(i=0;i<2;i++)
    {   dia[3][0].space[1][i]=1;
        dia[3][0].space[2][i+1]=1; //Z形--1

        dia[4][0].space[1][i+1]=1;
        dia[4][0].space[2][i]=1;//Z形--2

        dia[5][0].space[1][i+1]=1;
        dia[5][0].space[2][i+1]=1;//田字形
    }
    for(i=0;i<4;i++)
        dia[6][0].space[i][2]=1;//一字形 
    //////////////////////////////////基础的7个形状
    for(i=0;i<7;i++)
    {
        for(z=0;z<3;z++)
        {
            for(j=0;j<4;j++)
            {
                for(k=0;k<4;k++)
                {
                  tmp[j][k]=dia[i][z].space[j][k];
                }   
            }
            for(j=0;j<4;j++)
            {
                for(k=0;k<4;k++)
                {
                  dia[i][z+1].space[j][k]=tmp[4-k-1][j];
                }   
            }
        }
    }
///////////////////////////////////旋转后的21个形状
}
//////////////////////////////////////
void inter_face() //初始化界面
{   int i,j;
    for(i=0;i<FACE_X;i++)
    {   
	    for(j=0;j<FACE_Y+15;j++)
        {   
            if(j==0 || j==FACE_Y-1 || j==FACE_Y+14)
            {   
			    face.data[i][j]=Wall;
                gotoxy(i,2*j);
                printf("★");
            }
            else if(i==FACE_X-1)
            {   
			    face.data[i][j]=Box;
                gotoxy(i,2*j);
                printf("★");
            }
            else
            face.data[i][j]=Kong;
        }
    }
    gotoxy(FACE_X-18,2*FACE_Y+2);
    printf("旋    转：  space");

    gotoxy(FACE_X-16,2*FACE_Y+2);
    printf("左/右 移：  ←/→");

    gotoxy(FACE_X-14,2*FACE_Y+2);
    printf("暂    停:   S");

    gotoxy(FACE_X-12,2*FACE_Y+2);
    printf("（暂停后按enter开始）");

    gotoxy(FACE_X-10,2*FACE_Y+2);
    printf("退    出:   ESC");

    gotoxy(FACE_X-8,2*FACE_Y+2);
    printf("重新开始:   R");

    gotoxy(FACE_X-6,2*FACE_Y+2);
    printf("最高纪录:   %d",max);

    gotoxy(FACE_X-4,2*FACE_Y+2);
    printf("分    数：  %d",grade);

}



int panduan(int n,int space_c,int x,int y)   //判断板块是否到底
{
    int i,j;
    for(i=0;i<4;i++)
    {
        for(j=0;j<4;j++)
        {
           if(dia[n][space_c].space[i][j]==0)
               continue;
           else if(face.data[x+i][y+j]==Wall || face.data[x+i][y+j]==Box)//判断板块的上下左右是否是墙或底 
               return 0;
        }
    }
    return 1;
}


int xiaochu()  //判断方块是否填满一行，方块填满一行时进行消除，同时判断界面的最上面一行是否有方块，若有，则游戏结束 
{
    int i,j,k,sum;
    for(i=FACE_X-2;i>4;i--)
    {
        sum=0;
        for(j=1;j<FACE_Y-1;j++)
        {
            sum+=face.data[i][j];   
        }
        if(sum==0)
            break;
        if(sum==FACE_Y-2)   //如果填满满一行，减掉，并且分数+100 
        {   
            grade+=100;   //分数+100 
            color(7);
            gotoxy(FACE_X-4,2*FACE_Y+2);
            printf("分    数：  %d",grade);
            for(j=1;j<FACE_Y-1;j++)  //将被填满的那一行进行清空 
            {
                face.data[i][j]=Kong;
                gotoxy(i,2*j);
                printf(" ");
            }
            for(j=i;j>1;j--)  //重新调整方块的形状 
            {   sum=0;
                for(k=1;k<FACE_Y-1;k++)
                {
                    sum+=face.data[j-1][k]+face.data[j][k];
                    face.data[j][k]=face.data[j-1][k];
                    if(face.data[j][k]==Kong)
                    {
                        gotoxy(j,2*k);
                        printf(" ");
                    }
                    else
                    {
                        gotoxy(j,2*k);
                        color(face.color[j][k]);
                        printf("●");
                    }
                }
                if(sum==0)
                    return 1;
            }

        }
    }
    for(i=1;i<FACE_Y-1;i++)//判断游戏是否结束，即界面的最上面一行是否有方块 
    {
        if(face.data[1][i]==Box)
        {
            char n;
            Sleep(2000);  //延时
            system("cls"); //清屏 
            color(7);
            gotoxy(FACE_X/2-2,2*(FACE_Y/3));
            if(grade>max)
            {
                printf("恭喜您打破记录，目前最高纪录为：%d",grade);
                write_file();
            }
            else if(grade==max)
                printf("与纪录持平，请突破你的极限！");
            else
                printf("请继续努力，你与最高记录只差：%d",max-grade);
            gotoxy(FACE_X/2,2*(FACE_Y/3));
            printf("GAME OVER!\n");
            do
            {
                gotoxy(FACE_X/2+2,2*(FACE_Y/3));
                printf("是否重新开始游戏(y/n): ");
                scanf("%c",&n);
                gotoxy(FACE_X/2+4,2*(FACE_Y/3));
                if(n!='n' && n!='N' && n!='y' && n!='Y')
                    printf("输入错误，请重新输入!");
                else
                    break;
            }while(1);
            if(n=='n' || n=='N')
            {
                gotoxy(FACE_X/2+4,2*(FACE_Y/3));
                printf("按任意键退出游戏！");
                exit(0);
            }
            else if(n=='y' || n=='Y')
                main();
        }       
    }
    return 0; //游戏结束界面的三种情况 
}
//////////////////////////////////////////////
void read_file()    //读取游戏的最高记录
{
    FILE *fp;
    fp=fopen("俄罗斯方块记录.txt","r+");
    if(fp==NULL)
    {
        fp=fopen("俄罗斯方块记录.txt","w+");
        fwrite(&max,sizeof(int),1,fp);
    }
    fseek(fp,0,0);
    fread(&max,sizeof(int),1,fp);
    fclose(fp);
}
void write_file()   //保存游戏的最高记录
{
    FILE *fp;
    fp=fopen("俄罗斯方块记录.txt","r+");
    fwrite(&grade,sizeof(int),1,fp);
    fclose(fp);
}


//////////////////////////////////////////////
void gotoxy(int x,int y) //移动坐标
{
    COORD coord;
    coord.X=y;
    coord.Y=x;
    SetConsoleCursorPosition( GetStdHandle( STD_OUTPUT_HANDLE ), coord );
}
//////////////////////////////////////////////
void hidden_cursor()//隐藏光标
{
  HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
  CONSOLE_CURSOR_INFO cci;
  GetConsoleCursorInfo(hOut,&cci);
  cci.bVisible=0;//赋1为显示，赋0为隐藏
  SetConsoleCursorInfo(hOut,&cci);
}
//////////////////////////////////////////////
int color(int c)  //更改文字颜色
{
    switch(c)
    {
    case 0: c=14;break;  //淡黄色
    case 1:
    case 2: c=13;break;  //淡紫色
    case 3:
    case 4: c=10;break;  //淡绿色
    case 5: c=12;break;  //淡红色
    case 6: c=9;break;   //淡蓝色 
    default: c=15;break; //亮白色
    }
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), c);       
    return 0;
}
