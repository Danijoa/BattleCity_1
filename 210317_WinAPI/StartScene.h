#pragma once
#include "GameNode.h"

class Image;
class StartScene : public GameNode
{
private:
	Image* backGround;
	Image* Arrow;

	FPOINT menuPos;
	FPOINT arrowPos;

	float elapsedTime;
	int frame;
	int selectFrame;

public:
	virtual HRESULT Init();		// 오버라이딩 : 다형성
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);

};

