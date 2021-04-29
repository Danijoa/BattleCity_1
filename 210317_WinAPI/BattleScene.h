#pragma once
#include "GameNode.h"

// ���� MainGame Ŭ������ ������ �̵�
class PlayerShip;
class EnemyManager;
class Image;
class GameBoard;
class TilemapTool;
class CollisionCheck;
class BattleScene : public GameNode
{
private:
	// ���� Ÿ�� �̹���
	Image* sampleTile;

	// ���� Ÿ���� ����
	static TILE_INFO tileInfo[TILE_X * TILE_Y];	// �迭�̴ϱ� �̹� ������...
	static int tileNumInfo[TILE_X * TILE_Y];
	
	//�浹
	CollisionCheck* collisionCheck;

	Image* bin;
	Image* mainBlackBack;
	EnemyManager* enemyMgr;
	PlayerShip* playerShip;
	GameBoard* gameBoard;

	char szText[128] = "";

public:
	virtual HRESULT Init();		// �������̵� : ������
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);

	void loadStage(int stageNum);

	//�� ���� ��ȭ �޾ƿ���
	inline TILE_INFO SetTileInfo(int index) { (this->tileInfo[index]).frameX = 3; (this->tileInfo[index]).frameY = 1;}	//�Ϲ� �� ���������� ��ȭ(3,1)
	inline int SetTileNumInfo(int index) { this->tileNumInfo[index] = 0; }	//�Ϲ� �� �� ��ȣ�� ��ȭ(0)

	virtual ~BattleScene() {};
};

