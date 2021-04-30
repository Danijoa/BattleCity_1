#pragma once
#include "GameNode.h"
#include <vector>

class Enemy;
class PlayerShip;
class Missile;
class MissileManager : public GameNode
{
private:
	vector<Missile*> vMissiles;
	vector<Missile*>::iterator itMissiles;

	Enemy* enemyOwner;
	PlayerShip* playerOwner;

public:
	HRESULT Init(Enemy* enemyOwner);
	HRESULT Init(PlayerShip* playerOwner);
	void Release();
	void Update();
	void Render(HDC hdc);

	void Fire();
};

