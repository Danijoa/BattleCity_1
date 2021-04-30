#pragma once
#include "GameNode.h"

class Missile;
class Enemy;
class CollisionCheck : public GameNode
{
private:
	//���� ������ ������ RECT
	RECT rcTemp;
	int size;

	// ��
	int* tileNumInfo;	// [TILE_X * TILE_Y];
	TILE_INFO* tileInfo;

	// �÷��̾�
	FPOINT playerFuturePos;
	RECT* playerRect;
	int playerCurrDir;
	bool playerCanMove;
	int playerIndex_X, playerIndex_Y;
	RECT playerFutureRectIndex;

	// ��
	list<Enemy*> enemyData;
	FPOINT enemyFuturePos; 
	FPOINT enemyFutureIndex;
	RECT* enemyRect;
	RECT* enemyFutureRect;
	int enemyCurrDir;
	bool enemyCanMove;
	int enemyIndex_X, enemyIndex_Y;
	RECT enemyFutureRectIndex;

	// �̻���
	list<Missile*> lPlayerMissiles;
	list<Missile*>::iterator itlPlayerMissiles;

	list<Missile*> lEnemyMissiles;
	list<Missile*>::iterator itlEnemyMissiles;
	int Index;

public:
	virtual HRESULT Init();	
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);

	// �÷��̾� �Լ�
	void findPlayerFutureData();
	void playerMoveCheck();
	void mapCollisionCheck();

	// �� �Լ�
	void enemyMoveCheck();
	//void enemyCheck();

	// �� Ÿ�� ����
	inline void SetTileInfo(TILE_INFO* tileInfo) { this->tileInfo = tileInfo; }
	inline void SetTileNumInfo(int* tileNumInfo) { this->tileNumInfo = tileNumInfo; }
	inline int GetTileNumInfoIndex() { return Index; }

	// �÷��̾� ����
	inline void SetPlayerRect(RECT* rect) { this->playerRect = rect; }
	inline void SetPlayerDir(int dir) { this->playerCurrDir = dir; }
	inline void SetPlayerFuturePos(FPOINT pos) { this->playerFuturePos = pos; }
	inline bool GetPlayerCanMove() { return this->playerCanMove; }

	// �� ����
	inline void SetAddEnemy(Enemy* enemy) { this->enemyData.push_back(enemy); }
	inline void SetEnemyRect(RECT* rect) { this->enemyRect = rect; }
	inline void SetEnemyDir(int dir) { this->enemyCurrDir = dir; }
	inline void SetEnemyFuturePos(FPOINT pos) { this->enemyFuturePos = pos; }
	inline void SetEnemyFutureIndex(FPOINT index) { this->enemyFutureIndex = index; }
	inline void SetEnemyFutureRectIndex(RECT* rect) { this->enemyFutureRect = rect; }
	inline bool GetEnemyCanMove() { return this->enemyCanMove; }

	//�̻��� ����
	void AddFiredEnemyMissile(Missile* missile) { lEnemyMissiles.push_back(missile); }
	void EraseEnemyMissile(Missile* missile) { lEnemyMissiles.remove(missile); }

	void AddFiredPlayerMissile(Missile* missile) { lPlayerMissiles.push_back(missile); }
	void ErasePlayerMissile(Missile* missile) { lPlayerMissiles.remove(missile); }

};

