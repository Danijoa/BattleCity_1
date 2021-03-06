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
	float moveSpeed;	// 초당 이동거리

	RECT playerRect;

	int size;

	int currFrameX, currFrameY;

	MissileManager* missileMgr;

	CollisionCheck* collisionCheck;

	FPOINT playerFuturePos;
	IndexPair playerFutureIndex;
	RECTIndexPair playerFutureRectIndex;
	int playerCurrDir;	// 좌 우 상 하

public:
	HRESULT Init() { return E_FAIL; };
	HRESULT Init(CollisionCheck* collisionCheck);
	void Release();
	void Update();
	void Move();
	void Render(HDC hdc);

	void SetFutureIndex(FPOINT playerFuturePos);
	void FrameMove(int start, int end);

	inline void SetPos(FPOINT pos) { this->pos = pos; }
	inline FPOINT GetPos() { return this->pos; }
	inline int GetCurrDir() { return this->playerCurrDir; }
	// 플레이어 움직임 여부
};

