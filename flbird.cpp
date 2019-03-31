#include "flbird.h"

void GAME::Init()
{
	srand((unsigned)time(NULL));
	//初始化柱子
	a[0].x = LENGTH + PilarWid;
	a[0].height = 60 + rand() % (LENGTH - 180);
	for(int i = 1;i<3;i++)
	{
		int gap =PilarGap + rand() %  PilarGap;
		a[i].x = a[i-1].x + gap;
		a[i].height = 60 + rand() % (LENGTH - 180);
	}
	//初始化鸟
	bird.height = 340;
	bird.v = 5;
	bird.count = 0; 
	score = 0;
	loadimage(&bird.img,_T("C:\\1.jpg"),BIRDWID,BIRDWID,true);
	loadimage(&bkimg,_T("C:\\360wallpaper.jpg"),WIDTH,LENGTH);
}

void GAME::Refresh()
{
	//移动柱子
	for(int i = 0;i<3; i++)
	{
		a[i].x -=3;
		if(a[i].x < -PilarWid) 
		{
			a[i].height = 60 + rand() % (LENGTH - 180);
			int gap =PilarGap + rand() %  PilarGap;
			if(i > 0) a[i].x = a[i-1].x + gap;
			else a[i].x = a[2].x + gap;
			
		}
	}
	//刷新鸟的高度
	bird.count++;
	if(bird.count > 7)
	{
		bird.v -= G; 	
		bird.count = 0;
	}
	bird.height -= bird.v;
	
	
	//重画
	BeginBatchDraw();
	cleardevice();	//清屏
	putimage(0,0,&bkimg);
	setfillcolor(GREEN);	
	for(int i = 0;i<3; i++)	DrawPilar(a[i]);
	DrawBird(bird);
	outtextxy(700,20,_T("得分："));
	TCHAR s[5];
	_stprintf(s, _T("%d"), score); 
	outtextxy(700,40,s);
	FlushBatchDraw();
	EndBatchDraw();
	GetCmd();
	Sleep(Time);
	
}

void GAME::GetCmd()
{
	if(bird.v <= 0)
	{		
		if(kbhit()) 
			if(getch() == ' ') {bird.v = 4;}			
	}
	FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
}

inline void GAME::DrawPilar(const Pilar &p)
{
	// 画上柱子
	fillrectangle(p.x - PilarWid, 1, p.x + PilarWid, p.height - PilarHei);

	//画下柱子
	fillrectangle(p.x - PilarWid, p.height + PilarHei, p.x + PilarWid, LENGTH  - 1);
}
inline void GAME::DrawBird(const Bird &b)
{
//	fillcircle(BIRDX,bird.height,10);
	putimage(BIRDX,bird.height,&bird.img);
}
bool GAME::Die()
{
	int i;
	//判定第几根柱子处于危险
	for(i = 0; i < 3; i++)
		if(a[i].x - PilarWid - 21 < BIRDX) break;
	if(i == 3) return 0;
	if((BIRDX + BIRDWID < a[i].x + PilarWid) && (BIRDX + BIRDWID > a[i].x - PilarWid) && (bird.height < a[i].height - PilarHei) ) return 1;	//右上点
	if((BIRDX + BIRDWID < a[i].x + PilarWid) && (BIRDX + BIRDWID > a[i].x - PilarWid) && (bird.height +BIRDWID > a[i].height + PilarHei) ) return 1;	//右下点
	if((BIRDX < a[i].x + PilarWid) && (BIRDX > a[i].x - PilarWid) && (bird.height < a[i].height - PilarHei) ) return 1;	//左上点
	if((BIRDX < a[i].x + PilarWid) && (BIRDX > a[i].x - PilarWid) && (bird.height + BIRDWID > a[i].height + PilarHei) ) return 1;	//左下点
	if(BIRDX < a[i].x + 2 && BIRDX > a[i].x - 2)	score++;	//通过一点
	return 0;
}