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
	RECT* playerRect;
	int playerCurrDir;
	bool playerCanMove;
	IndexPair playerFutureIndex;
	RECTIndexPair playerFutureRectIndex;

	// ��
	list<Enemy*> enemyData;

	// �̻���
	list<Missile*> lPlayerMissiles;
	list<Missile*>::iterator missilesIt;
	list<Missile*>::iterator itlPlayerMissiles;

	list<Missile*> lEnemyMissiles;
	list<Missile*>::iterator itlEnemyMissiles;
	int collisionMapIndex;

public:
	virtual HRESULT Init();	
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);

	// �÷��̾� �Լ�
	void playerMoveCheck();
	void mapCollisionCheck();

	// �� �Լ�
	void enemyMoveCheck();
	//void enemyCheck();

	// �� Ÿ�� ����
	inline void SetTileInfo(TILE_INFO* tileInfo) { this->tileInfo = tileInfo; }
	inline void SetTileNumInfo(int* tileNumInfo) { this->tileNumInfo = tileNumInfo; }
	inline int GetTileNumInfoIndex() { return collisionMapIndex; }

	// �÷��̾� ����
	inline void SetPlayerRect(RECT* rect) { this->playerRect = rect; }
	inline void SetPlayerDir(int dir) { this->playerCurrDir = dir; }
	inline void SetPlayerFutureIndex(IndexPair index) { this->playerFutureIndex = index; }
	inline void SetPlayerFutureRECTIndex(RECTIndexPair rectIndex) { this->playerFutureRectIndex = rectIndex; }
	inline bool GetPlayerCanMove() { return this->playerCanMove; }

	// �� ����
	inline void SetAddEnemy(Enemy* enemy) { this->enemyData.push_back(enemy); }

	//�̻��� ����
	void AddFiredEnemyMissile(Missile* missile) { lEnemyMissiles.push_back(missile); }
	void EraseEnemyMissile(Missile* missile) { lEnemyMissiles.remove(missile); }

	void AddFiredPlayerMissile(Missile* missile) { lPlayerMissiles.push_back(missile); }
	void ErasePlayerMissile(Missile* missile) { lPlayerMissiles.remove(missile); }

};

