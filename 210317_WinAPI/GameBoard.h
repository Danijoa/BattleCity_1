#pragma once
#include "GameNode.h"

class Image;
class GameBoard : public GameNode
{
private:
	Image* enemyIcon;				// 에너미 아이콘
	int enemyNumberToKill;			// 죽여야 할 에너미 수

	int enemyIconX, enemyIconY;		//에너미 아이콘 윈도우상 위치
	

public:
	virtual HRESULT Init();		// 오버라이딩 : 다형성
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);
};

