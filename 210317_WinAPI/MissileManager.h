#pragma once
#include "GameNode.h"
#include <vector>

class Enemy;
class PlayerShip;
class Missile;
class CollisionCheck;
class MissileManager : public GameNode
{
private:
	vector<Missile*> vMissiles;
	vector<Missile*>::iterator itMissiles;

	Enemy* enemyOwner;
	PlayerShip* playerOwner;
	CollisionCheck* collisionCheck;


public:
	HRESULT Init(CollisionCheck* collisionCheck, Enemy* enemyOwner);
	HRESULT Init(CollisionCheck* collisionCheck, PlayerShip* playerOwner);
	void Release();
	void Update();
	void Render(HDC hdc);

	void Fire();
};

