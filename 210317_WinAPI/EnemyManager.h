#pragma once
#include "GameNode.h"
#include <vector>

class Enemy;
class CollisionCheck;
class EnemyManager : public GameNode
{
private:
	vector<Enemy*> vEnemys;
	CollisionCheck* collisionCheck;

public:
	HRESULT Init() { return E_FAIL; };
	HRESULT Init(CollisionCheck* collisionCheck);
	void Release();
	void Update();
	void Render(HDC hdc);

	void AddEnemy(int size);
};

