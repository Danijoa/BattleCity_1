#pragma once
#include "GameNode.h"

// TODO : 업캐스팅, 다운캐스팅 설명
class Image;
class Tank;
class MissileManager;
class CollisionCheck;
class Enemy : public GameNode
{
private:
	MissileManager* missileMgr;

	Image* image;
	int currFrameX, currFrameY;
	int updateCount;

	FPOINT pos;
	int size;
	string name;
	RECT shape;
	float moveSpeed;
	bool isAlive;
	float angle;

	//GameNode* target;
	Tank* target;
	int dir;

	int fireCount;

	CollisionCheck* collisionCheck;

public:
	HRESULT Init(CollisionCheck* collisionCheck = nullptr , int posX = 0, int posY = 0);
	void Release();		
	void Update();		
	void Render(HDC hdc);

	inline void SetPos(FPOINT pos) { this->pos = pos; }
	inline FPOINT GetPos() { return this->pos; }
	inline void SetTarget(Tank* target) { this->target = target; }
	inline int GetSize() { return this->size; }
	inline void SetIsAlive(bool isAlive) { this->isAlive = isAlive; }
	inline bool GetIsAlive() { return this->isAlive; }
};

