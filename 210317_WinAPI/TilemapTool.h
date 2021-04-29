#pragma once
#include "GameNode.h"

// 샘플 타일 정보
// (32 * 3) * (32 * 3)
#define SAMPLE_TILE_X 4
#define SAMPLE_TILE_Y 4
//#define TILESIZE 24

// 메인 그리지 공간 정보
//#define TILE_X 26
//#define TILE_Y 26

//typedef struct tagTile
//{
//	RECT rcTile;
//	int frameX;
//	int frameY;
//	int num;
//} TILE_INFO;

class Image;
class Button;
class TilemapTool : public GameNode
{
private:
	// 샘플 타일 이미지
	Image* sampleTile;
	
	TILE_INFO sampleTileInfo[SAMPLE_TILE_X * SAMPLE_TILE_Y];
	RECT rcSample;

	// 메인 타일의 정보
	static TILE_INFO tileInfo[TILE_X * TILE_Y]; 
	static int tileNumInfo[TILE_X * TILE_Y];
	
	RECT rcMain;
	Image* mainBlackBack;	//확인용임

	POINT ptStartSelectedFrame;
	POINT ptEndSelectedFrame;

	POINT ptSelected[2];
	HBRUSH hSelectedBrush;
	HBRUSH hOldSelectedBrush;

	// UI button
	Button* btnSave;
	Button* btnLoad;
	Button* btnStage;

	char szText[128] = "";

public:
	virtual HRESULT Init();			
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);

	// 컴
	static void Save(int stageNum);
	static void Load(int stageNum);

	virtual ~TilemapTool() {};
};

