#pragma once
#include "GameNode.h"

class Image;
class GameBoard : public GameNode
{
private:
	Image* img;				// 에너미 아이콘

	int enemyNumberToKill;			// 죽여야 할 에너미 수

	int enemyIconX, enemyIconY;		// 에너미 아이콘 윈도우상 위치
	int flagIconX, flagIconY;		// 스테이지 깃발 아이콘 위치
	int lifeIconX, lifeIconY;		// 1P 라이프 아이콘 위치
	int titleX, titleY;

	int stageNum;
	int life;
	

public:
	virtual HRESULT Init();		// 오버라이딩 : 다형성
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);
};

