#pragma once
#include "GameNode.h"

class Enemy;
class CollisionCheck : public GameNode
{
private:
	//교차 영역을 저장할 RECT
	RECT rcTemp;
	int size;

	// 맵
	int* tileNumInfo;	// [TILE_X * TILE_Y];
	TILE_INFO* tileInfo;

	// 플레이어
	FPOINT playerFuturePos;
	RECT* playerRect;
	int playerCurrDir;
	bool playerCanMove;
	int playerIndex_X, playerIndex_Y;
	RECT playerFutureRectIndex;

	// 적
	list<Enemy*> enemyData;
	FPOINT enemyFuturePos; 
	FPOINT enemyFutureIndex;
	RECT* enemyRect;
	RECT* enemyFutureRect;
	int enemyCurrDir;
	bool enemyCanMove;
	int enemyIndex_X, enemyIndex_Y;
	RECT enemyFutureRectIndex;

	// 미사일

public:
	virtual HRESULT Init();	
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);

	// 플레이어 함수
	void findPlayerFutureData();
	void playerMoveCheck();

	// 적 함수
	void enemyMoveCheck();
	//void enemyCheck();

	// 맵 타일 정보
	inline void SetTileInfo(TILE_INFO* tileInfo) { this->tileInfo = tileInfo; }
	inline void SetTileNumInfo(int* tileNumInfo) { this->tileNumInfo = tileNumInfo; }

	// 플레이어 정보
	inline void SetPlayerRect(RECT* rect) { this->playerRect = rect; }
	inline void SetPlayerDir(int dir) { this->playerCurrDir = dir; }
	inline void SetPlayerFuturePos(FPOINT pos) { this->playerFuturePos = pos; }
	inline bool GetPlayerCanMove() { return this->playerCanMove; }

	// 적 정보
	inline void SetAddEnemy(Enemy* enemy) { this->enemyData.push_back(enemy); }
	inline void SetEnemyRect(RECT* rect) { this->enemyRect = rect; }
	inline void SetEnemyDir(int dir) { this->enemyCurrDir = dir; }
	inline void SetEnemyFuturePos(FPOINT pos) { this->enemyFuturePos = pos; }
	inline void SetEnemyFutureIndex(FPOINT index) { this->enemyFutureIndex = index; }
	inline void SetEnemyFutureRectIndex(RECT* rect) { this->enemyFutureRect = rect; }
	inline bool GetEnemyCanMove() { return this->enemyCanMove; }

	//미사일 정도
};

