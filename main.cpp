/*************************
作者：11
开始时间：2017.3.2
*************************/
#include "stdfax.h"
#include "flbird.h"

#pragma comment(lib,"Winmm.lib")

void InitGame();

void NewGame();
void Refresh();

int main()
{
	InitGame();
	bool over = 0;
	while(!over)
	{
		HWND wnd = GetHWnd();
		if(MessageBox(wnd, _T("Do you want to play now?"), _T("New Game"), MB_YESNO | MB_ICONQUESTION) == IDYES)
			{NewGame();Sleep(1000);}
		else over = 1;
		
	}
	mciSendString(_T("close mymusic"),NULL,0,NULL);
	closegraph();
	return 0;
}

void InitGame()
{
	initgraph(WIDTH, LENGTH);
	settextstyle(20,0,_T("宋体"));
	mciSendString(_T("open \"D:\\KuGou\\李荣浩 - 老街.mp3\" alias mymusic"),NULL,0,NULL);
	mciSendString(_T("play mymusic repeat"),NULL,0,NULL);
}

void NewGame()
{
	GAME player;
	player.Init();
	while(!player.Die())
	{
		player.Refresh();
	}
}
