#include "myclude.h" 

void gotoxy(int x,int y);  //�ƶ����
int color(int c);   //��ɫ
void hidden_cursor();  //���ع��
void inter_face();  //��ʼ������
void init_dia();   //��ʼ��������Ϣ
void draw_dia(int base,int space_c,int x,int y);   //���Ƿ���
void draw_kong(int base,int space_c,int x,int y); //������
int panduan(int n,int space_c,int x,int y);  //�жϷ����Ƿ񵽵�
void start_game();   //��ʼ��Ϸ
int xiaochu();  //��������һ��ʱ��������
void read_file();   //��д��߼�¼
void write_file();  //д��߼�¼
int grade=0;  //��ǰ����
int max=0;  //��߼�¼
int nn=0;
int main(); 

struct Face
{
    int data[FACE_X][FACE_Y+10];    //��ֵ��Ϊ1�Ƿ��飬Ϊ0�ǿո�
    int color[FACE_X][FACE_Y+10];   //��Ӧ�������ɫ
}face;

typedef struct Diamonds
{   
    int space[4][4];        //4*4����Ϊ1Ϊ���飬Ϊ0 Ϊ��
}Dia;

Dia dia[7][4];  //һά����7����飬��ά��ʾ��ת������ͨ����ת�ɵõ�21����� 

/////////////////////////////////////////////////
int main()//������ 
{   
    system("cls"); //ʵ���������� 
    system("title һ������ս����˹���飡��");  //���� 
    color(7);
    system("mode con cols=70 lines=30");  //��ʾ���ڵĿ�Ⱥ͸߶� 
    hidden_cursor(); //���ع��
    srand(time(NULL)); //����ʱ��������Ӳ�������� 
    read_file();  //��д��߼�¼
    grade=0;
    inter_face(); //��ʼ������
    init_dia();  //��ʼ��������Ϣ
    nn=rand()%7; //���������һ��
    while(1)
    {
        start_game();
    }
    return 0;
}


void start_game()
{   
    int n,ch,t=0,x=0,y=FACE_Y/2-2,i,j;
    int space_c=0;  //��ת����
    draw_kong(nn,space_c,4,FACE_Y+3);
    n=nn;   
    nn=rand()%7;    //���������һ��
    color(nn);
    draw_dia(nn,space_c,4,FACE_Y+3); //���Ƿ��� 
    while(1)
    {   
        color(n);
        draw_dia(n,space_c,x,y);//����ͼ��
        if(t==0)
            t=15000;//���ð�������ʱ�� 
        while(--t)
        {  
		    if(kbhit()!=0)// �жϵ�ǰ�Ƿ��м������룬��������������
                break;  
        }
        if(t==0)
        {
            if(panduan(n,space_c,x+1,y)==1) //�жϷ����Ƿ񵽵�
            {   
			    draw_kong(n,space_c,x,y);
                x++;            //����������½���
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
            ch=getch();  //�Ӽ��̽���
            switch(ch)     //�ƶ�
            {
            case LEFT: if(panduan(n,space_c,x,y-1)==1)   //�жϷ����Ƿ���������ƶ�
                       {   draw_kong(n,space_c,x,y);
                           y--;
                       }
                       break;
            case RIGHT: if(panduan(n,space_c,x,y+1)==1)  //�жϷ����Ƿ���������ƶ�
                        {   draw_kong(n,space_c,x,y);
                            y++;
                        }
                        break;
            case DOWN: if(panduan(n,space_c,x+1,y)==1)  //�жϷ����Ƿ���������ƶ�
                        {   draw_kong(n,space_c,x,y);
                            x++;
                        }
                        break;
            case SPACE: if(panduan(n,(space_c+1)%4,x+1,y)==1) //�жϷ����Ƿ���Խ�����ת 
                        {   draw_kong(n,space_c,x,y);
                            space_c=(space_c+1)%4;
                        }
                        break;
            case ESC  : system("cls");   //������Ϸ 
                        gotoxy(FACE_X/2,FACE_Y);   //�ƶ���� 
                        printf("---��Ϸ����!---\n\n");
                        gotoxy(FACE_X/2+2,FACE_Y);  //�ƶ���� 
                        printf("---��������˳�!---\n");
                        getch();
                        exit(0);
                        break;
            case  'R':          //���¿�ʼ��Ϸ 
            case  'r':  main();
                        exit(0);
            case  'S':          //��ͣ��Ϸ
            case  's':  while(1)
                        {   if(kbhit()!=0)//�����������
                            break;  
                        }
                        break;
            }
        }
    }
}

void draw_kong(int base,int space_c,int x,int y) //����� 
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

void draw_dia(int base,int space_c,int x,int y)  //���ǰ�� 
{
    int i,j;
    for(i=0;i<4;i++)
    {
        for(j=0;j<4;j++)
        {
            gotoxy(x+i,2*(y+j));
            if(dia[base][space_c].space[i][j]==1)
            printf("��");
        }
    }
}

void init_dia()  //���Ĳ����Լ������״�ĸı� 
{
    int i,j,k,z;
    int tmp[4][4];
    for(i=0;i<3;i++)
        dia[0][0].space[1][i]=1;
    dia[0][0].space[2][1]=1;     //������

    for(i=1;i<4;i++)
        dia[1][0].space[i][1]=1;
    dia[1][0].space[1][2]=1;    //L��--1

    for(i=1;i<4;i++)
        dia[2][0].space[i][2]=1;
    dia[2][0].space[1][1]=1;    //L��--2

    for(i=0;i<2;i++)
    {   dia[3][0].space[1][i]=1;
        dia[3][0].space[2][i+1]=1; //Z��--1

        dia[4][0].space[1][i+1]=1;
        dia[4][0].space[2][i]=1;//Z��--2

        dia[5][0].space[1][i+1]=1;
        dia[5][0].space[2][i+1]=1;//������
    }
    for(i=0;i<4;i++)
        dia[6][0].space[i][2]=1;//һ���� 
    //////////////////////////////////������7����״
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
///////////////////////////////////��ת���21����״
}
//////////////////////////////////////
void inter_face() //��ʼ������
{   int i,j;
    for(i=0;i<FACE_X;i++)
    {   
	    for(j=0;j<FACE_Y+15;j++)
        {   
            if(j==0 || j==FACE_Y-1 || j==FACE_Y+14)
            {   
			    face.data[i][j]=Wall;
                gotoxy(i,2*j);
                printf("��");
            }
            else if(i==FACE_X-1)
            {   
			    face.data[i][j]=Box;
                gotoxy(i,2*j);
                printf("��");
            }
            else
            face.data[i][j]=Kong;
        }
    }
    gotoxy(FACE_X-18,2*FACE_Y+2);
    printf("��    ת��  space");

    gotoxy(FACE_X-16,2*FACE_Y+2);
    printf("��/�� �ƣ�  ��/��");

    gotoxy(FACE_X-14,2*FACE_Y+2);
    printf("��    ͣ:   S");

    gotoxy(FACE_X-12,2*FACE_Y+2);
    printf("����ͣ��enter��ʼ��");

    gotoxy(FACE_X-10,2*FACE_Y+2);
    printf("��    ��:   ESC");

    gotoxy(FACE_X-8,2*FACE_Y+2);
    printf("���¿�ʼ:   R");

    gotoxy(FACE_X-6,2*FACE_Y+2);
    printf("��߼�¼:   %d",max);

    gotoxy(FACE_X-4,2*FACE_Y+2);
    printf("��    ����  %d",grade);

}



int panduan(int n,int space_c,int x,int y)   //�жϰ���Ƿ񵽵�
{
    int i,j;
    for(i=0;i<4;i++)
    {
        for(j=0;j<4;j++)
        {
           if(dia[n][space_c].space[i][j]==0)
               continue;
           else if(face.data[x+i][y+j]==Wall || face.data[x+i][y+j]==Box)//�жϰ������������Ƿ���ǽ��� 
               return 0;
        }
    }
    return 1;
}


int xiaochu()  //�жϷ����Ƿ�����һ�У���������һ��ʱ����������ͬʱ�жϽ����������һ���Ƿ��з��飬���У�����Ϸ���� 
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
        if(sum==FACE_Y-2)   //���������һ�У����������ҷ���+100 
        {   
            grade+=100;   //����+100 
            color(7);
            gotoxy(FACE_X-4,2*FACE_Y+2);
            printf("��    ����  %d",grade);
            for(j=1;j<FACE_Y-1;j++)  //������������һ�н������ 
            {
                face.data[i][j]=Kong;
                gotoxy(i,2*j);
                printf(" ");
            }
            for(j=i;j>1;j--)  //���µ����������״ 
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
                        printf("��");
                    }
                }
                if(sum==0)
                    return 1;
            }

        }
    }
    for(i=1;i<FACE_Y-1;i++)//�ж���Ϸ�Ƿ�������������������һ���Ƿ��з��� 
    {
        if(face.data[1][i]==Box)
        {
            char n;
            Sleep(2000);  //��ʱ
            system("cls"); //���� 
            color(7);
            gotoxy(FACE_X/2-2,2*(FACE_Y/3));
            if(grade>max)
            {
                printf("��ϲ�����Ƽ�¼��Ŀǰ��߼�¼Ϊ��%d",grade);
                write_file();
            }
            else if(grade==max)
                printf("���¼��ƽ����ͻ����ļ��ޣ�");
            else
                printf("�����Ŭ����������߼�¼ֻ�%d",max-grade);
            gotoxy(FACE_X/2,2*(FACE_Y/3));
            printf("GAME OVER!\n");
            do
            {
                gotoxy(FACE_X/2+2,2*(FACE_Y/3));
                printf("�Ƿ����¿�ʼ��Ϸ(y/n): ");
                scanf("%c",&n);
                gotoxy(FACE_X/2+4,2*(FACE_Y/3));
                if(n!='n' && n!='N' && n!='y' && n!='Y')
                    printf("�����������������!");
                else
                    break;
            }while(1);
            if(n=='n' || n=='N')
            {
                gotoxy(FACE_X/2+4,2*(FACE_Y/3));
                printf("��������˳���Ϸ��");
                exit(0);
            }
            else if(n=='y' || n=='Y')
                main();
        }       
    }
    return 0; //��Ϸ���������������� 
}
//////////////////////////////////////////////
void read_file()    //��ȡ��Ϸ����߼�¼
{
    FILE *fp;
    fp=fopen("����˹�����¼.txt","r+");
    if(fp==NULL)
    {
        fp=fopen("����˹�����¼.txt","w+");
        fwrite(&max,sizeof(int),1,fp);
    }
    fseek(fp,0,0);
    fread(&max,sizeof(int),1,fp);
    fclose(fp);
}
void write_file()   //������Ϸ����߼�¼
{
    FILE *fp;
    fp=fopen("����˹�����¼.txt","r+");
    fwrite(&grade,sizeof(int),1,fp);
    fclose(fp);
}


//////////////////////////////////////////////
void gotoxy(int x,int y) //�ƶ�����
{
    COORD coord;
    coord.X=y;
    coord.Y=x;
    SetConsoleCursorPosition( GetStdHandle( STD_OUTPUT_HANDLE ), coord );
}
//////////////////////////////////////////////
void hidden_cursor()//���ع��
{
  HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
  CONSOLE_CURSOR_INFO cci;
  GetConsoleCursorInfo(hOut,&cci);
  cci.bVisible=0;//��1Ϊ��ʾ����0Ϊ����
  SetConsoleCursorInfo(hOut,&cci);
}
//////////////////////////////////////////////
int color(int c)  //����������ɫ
{
    switch(c)
    {
    case 0: c=14;break;  //����ɫ
    case 1:
    case 2: c=13;break;  //����ɫ
    case 3:
    case 4: c=10;break;  //����ɫ
    case 5: c=12;break;  //����ɫ
    case 6: c=9;break;   //����ɫ 
    default: c=15;break; //����ɫ
    }
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), c);       
    return 0;
}
