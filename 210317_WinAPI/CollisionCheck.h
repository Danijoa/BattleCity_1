#pragma once
#include "GameNode.h"

class Missile;
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
	int playerIndex_X;
	int playerIndex_Y;
	RECT playerFutureRectIndex;
	int futureIndexDiff_X;
	int futureIndexDiff_Y;

	// 적

	// 미사일
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

	void playerMoveCheck();
	void mapCollisionCheck();

	// 맵 타일 정보
	inline void SetTileInfo(TILE_INFO* tileInfo) { this->tileInfo = tileInfo; }
	inline void SetTileNumInfo(int* tileNumInfo) { this->tileNumInfo = tileNumInfo; }
	inline int GetTileNumInfoIndex() { return Index; }

	// 플레이어 정보
	inline void SetPlayerRect(RECT* rect) { this->playerRect = rect; }
	inline void SetPlayerDir(int dir) { this->playerCurrDir = dir; }
	inline void SetPlayerFuturePos(FPOINT pos) { this->playerFuturePos = pos; }
	inline bool GetPlayerCanMove() { return this->playerCanMove; }

	// 적 정보

	//미사일 정보
	void AddFiredEnemyMissile(Missile* missile) { lEnemyMissiles.push_back(missile); }
	void EraseEnemyMissile(Missile* missile) { lEnemyMissiles.remove(missile); }

	void AddFiredPlayerMissile(Missile* missile) { lPlayerMissiles.push_back(missile); }
	void ErasePlayerMissile(Missile* missile) { lPlayerMissiles.remove(missile); }

};

