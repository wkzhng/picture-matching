#include"graphics.h"
#include<stdio.h>
#include<Windows.h>
#include<math.h>
#include<string.h>
HANDLE hMutex = NULL;
DWORD WINAPI abc(LPVOID IpParameter);
int shijian = 0,win=1;
struct cikuai
{
	int chang = 100;
	int kuan = 80;
	char ci[10];
	int x;
	int y;
	BOOL xiao;
}fangkuai[10][8];
struct coordinate
{
	int row;
	int col;
};
coordinate move[5] = { { 0, 0 }, { -1, 0 }, { 0, 1 }, { 1, 0 }, { 0, -1 } };
char jiazhiguan[12][10] = { "��ǿ", "����", "����", "��г", "����", "ƽ��", "����", "����", "����", "��ҵ", "����", "����" };
void zhujiemian();
void lianliankan();
bool isLinked(int startRow, int startCol, int endRow, int endCol, int row, int col, int fromWitchDirection, int joinNum);
void main()
{
	zhujiemian();
	getch();
	while (1)
	{
		shijian = 0;
		win = 1;
		cleardevice();
		lianliankan();
		getch();
	}
	getch();
}
DWORD WINAPI abc(LPVOID IpParameter)
{
	while (1)
	{
		WaitForSingleObject(hMutex, INFINITE);
		if (shijian >= 76||win==2)
			break;
		setfillcolor(EGERGB(255, 255-shijian*4*255/300, 0));
		bar(1132, 102, 1179,4*shijian+102);
		shijian++;
		api_sleep(1600);
		ReleaseMutex(hMutex);
	}
	if (shijian >= 76)
		win = 0;
	return 0;
}
void lianliankan()
{
	mouse_msg msg,msg1,msg2;
	int a[100],i, j,k,l=1,m=1,n=0,o,p=0,q=1,c,d,dx=100,dy=80,g=0;
	setbkmode(TRANSPARENT);
	{
		setfont(30, 0, "����");
		outtextxy(1125, 50, "time");
		rectangle(1130, 100, 1180, 403);
	}//��ʱ��//
	setfillcolor(WHITE);
	{
		bar(1100, 500, 1200, 550);
		setfont(50, 0, "����");
		outtextxy(1100, 500, "��ʼ");
	}//��ʼ��//
	{
		bar(1100, 600, 1200, 650);
		setfont(50, 0, "����");
		outtextxy(1100, 600, "�˳�");
	}//�˳���//
	for (i = 0; i <= 9;i++)
	for (j = 0; j <= 7;j++)
	{
		if (i==0||i==9||j==0||j==7)
			fangkuai[i][j].xiao = TRUE;
		else fangkuai[i][j].xiao = FALSE;
	}//��ʼ����ȥ����//
	for (i = 0; i <= 7;i++)
	for (j = 0; j <= 5; j++)
	{
		bar(150 + i*dx, 100+ j*dy, 148 + (i + 1)*dx, 98 + (j + 1)*dy);
	}//�����������ķ���//
	for (i = 0; i <= 9; i++)
	for (j = 0; j <= 7; j++)
	{
		fangkuai[i][j].x = 50 + i*dx;
		fangkuai[i][j].y = 20 + j*dy;
	}//��ʼÿһ������Ͻ�����//
	randomize();
	for (i = 1; i <= 8;i++)
	for (j = 1; j <= 6; j++)
	{
		m = 1;
		while (m)
		{
			p = 0;
			a[n] = random(12);//���һ������//
			for (o = 0; o < n;o++)
			if (a[o] == a[n])
				p++;//������ظ�p+1//
			if (p < 4)
			{
				for (k = 0; k <= 10; k++)
				{
					fangkuai[i][j].ci[k] = jiazhiguan[a[n]][k];
				}
				m = 0;
			}//�ظ�С��4������Ч�����//
		}
		n++;
	}//��ʼ�����ϵĴ���//
	while (l)
	{
		msg = getmouse();
		if (msg.is_down() && msg.is_left())
		{
			if (msg.x >= 1100 && msg.x <= 1200 && msg.y >= 500 && msg.y <= 550)
			{
				l = 0;
			}
			else if (msg.x >= 1100 && msg.x <= 1200 && msg.y >= 600 && msg.y <= 650)
				closegraph();
		}
	}//��ʼ���˳�//
	setfont(40, 0, "����");
	for (i = 1; i <= 8; i++)
	for (j = 1; j <= 6; j++)
	{
		xyprintf(fangkuai[i][j].x + 5, fangkuai[i][j].y + 5, "%s", fangkuai[i][j].ci);
	}//�ڷ������������//
	HANDLE t1;
	t1 = CreateThread(NULL, 0, abc, NULL, 0, NULL);
	CloseHandle(t1);
	hMutex = CreateMutex(NULL, FALSE, "screen");
	api_sleep(100);
	setcolor(RED);
	while (1)
	{
		if (win == 0||win==2) break;
		msg1 = getmouse();
		if (msg1.is_down() && msg1.is_left())
		{
			if(msg1.x >= 1100 && msg1.x <= 1200 && msg1.y >= 600 && msg1.y <= 650)
				closegraph();
			for (i = 1; i <= 8; i++)
			for (j = 1; j <= 6; j++)
			{
				if (msg1.x >= fangkuai[i][j].x&&msg1.x <= fangkuai[i][j].x + 98 && msg1.y >= fangkuai[i][j].y&&msg1.y <= fangkuai[i][j].y + 78 && fangkuai[i][j].xiao == FALSE)
				{
					q = 1;
					rectangle(fangkuai[i][j].x, fangkuai[i][j].y, fangkuai[i][j].x + 98, fangkuai[i][j].y + 78);
					xyprintf(fangkuai[i][j].x + 5, fangkuai[i][j].y + 5, "%s", fangkuai[i][j].ci);
					while (q)
					{
						if (win == 0 || win == 2) break;
						msg2 = getmouse();
						if (msg2.is_down() && msg2.is_left())
						for (c = 1; c <= 8; c++)
						for (d = 1; d <= 6; d++)
						{
							if (msg2.x >= fangkuai[c][d].x&&msg2.x <= fangkuai[c][d].x + 98 && msg2.y >= fangkuai[c][d].y&&msg2.y <= fangkuai[c][d].y + 78 && ((i == c&&j == d) == 0) && fangkuai[c][d].xiao == FALSE&&strcmp(fangkuai[i][j].ci, fangkuai[c][d].ci) == 0 && isLinked(i, j, c, d, i, j, 0, 0))
							{
								setfillcolor(BLACK);
								bar(fangkuai[i][j].x, fangkuai[i][j].y, fangkuai[i][j].x + 98, fangkuai[i][j].y + 78);
								bar(fangkuai[c][d].x, fangkuai[c][d].y, fangkuai[c][d].x + 98, fangkuai[c][d].y + 78);
								fangkuai[c][d].xiao = TRUE;
								fangkuai[i][j].xiao = TRUE;
								q = 0;
								c = 9;
								d = 7;
								g++;
								if (g >= 24)
									win = 2;
							}
							else
							{
								setfillcolor(WHITE);
								bar(fangkuai[i][j].x, fangkuai[i][j].y, fangkuai[i][j].x + 98, fangkuai[i][j].y + 78);
								setcolor(BLUE);
								xyprintf(fangkuai[i][j].x + 5, fangkuai[i][j].y + 5, "%s", fangkuai[i][j].ci);
								q = 0;
							}
						}
					}
				}
			}
		}
	}
	if (win == 0)
	{
		setcolor(BLUE);
		setfont(200, 0, "�����п�");
		outtextxy(200, 200, "�����ˣ�");
		setfont(40, 0, "�����п�");
		outtextxy(400, 550, "(����������¿�ʼ)");
	}
	else if (win==2)
	{
		setcolor(BLUE);
		setfont(200, 0, "�����п�");
		outtextxy(200, 200, "��Ӯ�ˣ�");
		setfont(40, 0, "�����п�");
		outtextxy(400, 550, "(����������¿�ʼ)");
	}
}
void zhujiemian()
{
	initgraph(1280, 720);
	setcaption("������");
	setcolor(BLUE);
	setfont(100, 0, "����");
	outtextxy(500, 250, "������");
	setfont(40, 0, "�����п�");
	outtextxy(450, 450, "�������������ļ�ֵ��");
	outtextxy(480, 550, "(���������ʼ��Ϸ)");
}
bool isLinked(int startRow, int startCol, int endRow, int endCol, int row, int col, int fromWitchDirection, int joinNum)
{
	if (row>9 || row<0 || col<0 || col>7)                                               //Խ��
		return false;
	if (joinNum>3)                                                        //�۵�������3���������Զ�����һ�۵㣩
		return false;
	if (row == endRow&&col == endCol)                                        //�����յ�
		return true;
	if (fangkuai[row][col].xiao == false)                                     //�ø���û�б�����
	{
		if (row != startRow || col != startCol)                                           //�����
			return false;
	}
	if (fromWitchDirection>0)
	{
		if (isLinked(startRow, startCol, endRow, endCol, row + move[fromWitchDirection].row,
			col + move[fromWitchDirection].col, fromWitchDirection, joinNum) == true)                  //��ԭ������̽
			return true;
	}
	for (int i = 1; i <= 4; i++)                                               //�ı䷽����̽
	{
		if (i == fromWitchDirection)
			continue;
		if (fromWitchDirection>0 && abs(i - fromWitchDirection) == 2)                              //��ԭ�����෴
			continue;
		if (isLinked(startRow, startCol, endRow, endCol, row + move[i].row, col + move[i].col, i, joinNum + 1) == true)
			return true;
	}
	return false;                                                       //��Ͷ��·����ͷ
}