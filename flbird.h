#pragma once

#include "stdfax.h"

#define Time 15		//刷新时间片
#define	PilarWid 30	//半个柱子的宽度
#define PilarHei 70	//柱子中间的空隙
#define PilarGap 250	//柱子间隔
#define WIDTH 900	//游戏界面的宽度
#define LENGTH 500	//游戏界面的高度
#define BIRDX 50	//鸟的X坐标
#define G 1			//重力
#define BIRDWID 20	//鸟的宽度

struct Pilar
{
	int x,height;
};


struct Bird
{
	int height;
	int count;	//计算刷新次数，以控制鸟的运动
	int v;
	IMAGE img;
};

class GAME
{
private:
	Pilar a[4];	//柱子
	Bird bird;	//鸟
	BYTE score;	//得分
	IMAGE bkimg;//背景图片
	inline void DrawPilar(const Pilar &);
	inline void DrawBird(const Bird &);
public:
	void Init();
	void Refresh();
	void GetCmd();
	bool Die();
};
