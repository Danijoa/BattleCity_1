#pragma once
#include "GameNode.h"

class Image;
class GameBoard : public GameNode
{
private:
	Image* img;				// ���ʹ� ������

	int enemyNumberToKill;			// �׿��� �� ���ʹ� ��

	int enemyIconX, enemyIconY;		// ���ʹ� ������ ������� ��ġ
	int flagIconX, flagIconY;		// �������� ��� ������ ��ġ
	int lifeIconX, lifeIconY;		// 1P ������ ������ ��ġ
	int titleX, titleY;

	int stageNum;
	int life;
	

public:
	virtual HRESULT Init();		// �������̵� : ������
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);
};

