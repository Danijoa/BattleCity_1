#pragma once
#include "GameNode.h"

class Image;
class GameBoard : public GameNode
{
private:
	Image* enemyIcon;				// ���ʹ� ������
	int enemyNumberToKill;			// �׿��� �� ���ʹ� ��

	int enemyIconX, enemyIconY;		//���ʹ� ������ ������� ��ġ
	

public:
	virtual HRESULT Init();		// �������̵� : ������
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);
};

