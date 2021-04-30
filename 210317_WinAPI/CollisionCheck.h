#pragma once
#include "GameNode.h"

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

public:
	virtual HRESULT Init();	
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);

	void playerMoveCheck();

	// 맵 타일 정보
	inline void SetTileInfo(TILE_INFO* tileInfo) { this->tileInfo = tileInfo; }
	inline void SetTileNumInfo(int* tileNumInfo) { this->tileNumInfo = tileNumInfo; }

	// 플레이어 정보
	inline void SetPlayerRect(RECT* rect) { this->playerRect = rect; }
	inline void SetPlayerDir(int dir) { this->playerCurrDir = dir; }
	inline void SetPlayerFuturePos(FPOINT pos) { this->playerFuturePos = pos; }
	inline bool GetPlayerCanMove() { return this->playerCanMove; }

	// 적 정보

	//미사일 정도
};

