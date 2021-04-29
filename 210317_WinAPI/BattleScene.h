#pragma once
#include "GameNode.h"

// 기존 MainGame 클래스의 내용을 이동
class PlayerShip;
class EnemyManager;
class Image;
class GameBoard;
class TilemapTool;
class CollisionCheck;
class BattleScene : public GameNode
{
private:
	// 샘플 타일 이미지
	Image* sampleTile;

	// 메인 타일의 정보
	static TILE_INFO tileInfo[TILE_X * TILE_Y];	// 배열이니까 이미 포인터...
	static int tileNumInfo[TILE_X * TILE_Y];
	
	//충돌
	CollisionCheck* collisionCheck;

	Image* bin;
	Image* mainBlackBack;
	EnemyManager* enemyMgr;
	PlayerShip* playerShip;
	GameBoard* gameBoard;

	char szText[128] = "";

public:
	virtual HRESULT Init();		// 오버라이딩 : 다형성
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);

	void loadStage(int stageNum);

	//맵 정보 변화 받아오기
	inline TILE_INFO SetTileInfo(int index) { (this->tileInfo[index]).frameX = 3; (this->tileInfo[index]).frameY = 1;}	//일반 길 프레임으로 변화(3,1)
	inline int SetTileNumInfo(int index) { this->tileNumInfo[index] = 0; }	//일반 길 맵 번호로 변화(0)

	virtual ~BattleScene() {};
};

