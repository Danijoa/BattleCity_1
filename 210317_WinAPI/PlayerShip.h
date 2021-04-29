#pragma once
#include "GameNode.h"

class Image;
class MissileManager;
class CollisionCheck;
class PlayerShip : public GameNode
{
private:
	Image* image;
	FPOINT pos;
	float moveSpeed;	// �ʴ� �̵��Ÿ�

	RECT playerRect;

	int size;

	int currFrameX, currFrameY;

	MissileManager* missileMgr;

	CollisionCheck* collisionCheck;

	int playerCurrMove;	// �� �� �� ��

public:
	HRESULT Init() { return E_FAIL; };
	HRESULT Init(CollisionCheck* collisionCheck);
	void Release();
	void Update();
	void Move();
	void Render(HDC hdc);

	// �÷��̾� ������ ����
};

