#pragma once

#include "stdfax.h"

#define Time 15		//ˢ��ʱ��Ƭ
#define	PilarWid 30	//������ӵĿ��
#define PilarHei 70	//�����м�Ŀ�϶
#define PilarGap 250	//���Ӽ��
#define WIDTH 900	//��Ϸ����Ŀ��
#define LENGTH 500	//��Ϸ����ĸ߶�
#define BIRDX 50	//���X����
#define G 1			//����
#define BIRDWID 20	//��Ŀ��

struct Pilar
{
	int x,height;
};


struct Bird
{
	int height;
	int count;	//����ˢ�´������Կ�������˶�
	int v;
	IMAGE img;
};

class GAME
{
private:
	Pilar a[4];	//����
	Bird bird;	//��
	BYTE score;	//�÷�
	IMAGE bkimg;//����ͼƬ
	inline void DrawPilar(const Pilar &);
	inline void DrawBird(const Bird &);
public:
	void Init();
	void Refresh();
	void GetCmd();
	bool Die();
};
