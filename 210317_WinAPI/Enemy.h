#pragma once
#include "GameNode.h"

// TODO : 업캐스팅, 다운캐스팅 설명
class Image;
class MissileManager;
class CollisionCheck;
class Enemy : public GameNode
{
private:
	MissileManager* missileMgr;
	CollisionCheck* collisionCheck;

	Image* image;
	int currFrameX, currFrameY;
	int updateCount;
	int fireCount;

	FPOINT pos;
	int size;
	string name;
	float moveSpeed;
	bool isAlive;

	RECT enemyRect;
	int enemyCurrDir;
	FPOINT enemyFuturePos;
	bool enemeyCanMove;
	FPOINT enemyFutureIndex;
	RECT enemyFutureRectIndex;

public:
	HRESULT Init(CollisionCheck* collisionCheck, int posX = 0, int posY = 0);
	void Release();		
	void Update();		
	void Move();
	void Render(HDC hdc);

	inline void SetPos(FPOINT pos) { this->pos = pos; }
	inline FPOINT GetPos() { return this->pos; }

	inline int GetSize() { return this->size; }
	inline void SetIsAlive(bool isAlive) { this->isAlive = isAlive; }
	inline bool GetIsAlive() { return this->isAlive; }

	inline RECT GetEnemyRect() { return enemyRect; }
	inline void SetEnemyRect() { this->enemyRect; }
	
	inline int GetEnemyCurrDir() { return enemyCurrDir; }

	inline void SetEnemyCanMove(bool canMove) { this->enemeyCanMove = canMove; }

	inline FPOINT GetEnemyFuturePos() { return enemyFuturePos; }

	inline FPOINT GetEnemyFutureIndex() { return enemyFutureIndex; }

	inline RECT GetEnemyFutureRectIndex() { return enemyFutureRectIndex; }
};

