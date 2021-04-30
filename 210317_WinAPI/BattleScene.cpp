#include "BattleScene.h"
#include "EnemyManager.h"
#include "Image.h"
#include "GameBoard.h"
#include "PlayerShip.h"
#include "TilemapTool.h"
#include "CollisionCheck.h"

TILE_INFO BattleScene::tileInfo[TILE_X * TILE_Y];
int BattleScene::tileNumInfo[TILE_X * TILE_Y];

HRESULT BattleScene::Init()
{
	bin = new Image();
	bin->Init("Image/Tile/mapImage.bmp", WINSIZE_X, WINSIZE_Y);

	mainBlackBack = ImageManager::GetSingleton()->AddImage("블랙타일", "Image/mapImage(2).bmp", 624, 624);

	sampleTile = ImageManager::GetSingleton()->AddImage("샘플타일", "Image/Tile/SampleTile(2).bmp", 32 * 3, 32 * 3, SAMPLE_TILE_X, SAMPLE_TILE_Y, true, RGB(255, 0, 255));

	collisionCheck = new CollisionCheck();
	collisionCheck->Init();

	enemyMgr = new EnemyManager();
	enemyMgr->Init(collisionCheck);

	playerShip = new PlayerShip();
	playerShip->Init(collisionCheck);

	gameBoard = new GameBoard();
	gameBoard->Init();

	//로드할 스테이지 결정 
	loadStage(2);

	return S_OK;
}

void BattleScene::Release()
{
	SAFE_RELEASE(playerShip);
	SAFE_RELEASE(bin);
	SAFE_RELEASE(enemyMgr);
	SAFE_RELEASE(gameBoard);
}

void BattleScene::Update()
{
	float currTime1 = TimerManager::GetSingleton()->GetCurrTime();

	//스테이지 변경 load

	if (enemyMgr)
	{
		enemyMgr->Update();
	}

	if (playerShip)
	{
		playerShip->Update();
	}

	if (gameBoard)
	{
		gameBoard->Update();
	}

	if (collisionCheck)
	{
		collisionCheck->SetTileInfo(tileInfo);
		collisionCheck->SetTileNumInfo(tileNumInfo);
		collisionCheck->Update();
		SetTileNumInfo(collisionCheck->GetTileNumInfoIndex());
		SetTileInfo(collisionCheck->GetTileNumInfoIndex());
	}
}

void BattleScene::Render(HDC hdc)
{
	// 회색 배경 출력
	if (bin)
	{
		bin->Render(hdc);
	}

	// 맵 검정 배경 출력
	if (mainBlackBack)
	{
		mainBlackBack->Render(hdc, 200, 50);
	}

	// 맵 이미지 출력
	for (int i = 0; i < TILE_X * TILE_Y; i++)
	{
		sampleTile->FrameRender(hdc,
			tileInfo[i].rcTile.left,
			tileInfo[i].rcTile.top,
			tileInfo[i].frameX,
			tileInfo[i].frameY);
	}

	// 맵 충돌 박스 출력
	if (collisionCheck)
	{
		collisionCheck->Render(hdc);
	}

	// 맵 숫자 출력
	for (int i = 0; i < TILE_Y; i++)
	{
		for (int j = 0; j < TILE_X; j++)
		{
			wsprintf(szText, "%d", tileNumInfo[(i * TILE_X) + j]);
			TextOut(hdc, 1000 + j * 10, i * 20, szText, strlen(szText));
		}
	}

	// 플레이어 그리기
	if (playerShip)
	{
		playerShip->Render(hdc);
	}

	// 적 그리기
	if (enemyMgr)
	{
		enemyMgr->Render(hdc);
	}

	// 게임보드(전광판) 출력
	if (gameBoard)
	{
		gameBoard->Render(hdc);
	}

}

void BattleScene::loadStage(int stageNum)
{
	DWORD readBytes;

	//맵 이미지 load
	string fileName = "Save/saveMapData";
	fileName += to_string(stageNum) + ".map";
	HANDLE hFile = CreateFile(fileName.c_str(), GENERIC_READ, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (ReadFile(hFile, tileInfo, sizeof(TILE_INFO) * TILE_X * TILE_Y, &readBytes, NULL)) {}
	else
		MessageBox(g_hWnd, "저장파일 로드 실패", "실패", MB_OK);
	CloseHandle(hFile);

	//맵 이미지 번호 load
	string fileNumName = "Save/saveMapNumData";
	fileNumName += to_string(stageNum) + ".map";
	HANDLE hFileNum = CreateFile(fileNumName.c_str(), GENERIC_READ, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (ReadFile(hFileNum, tileNumInfo, sizeof(int) * TILE_X * TILE_Y, &readBytes, NULL)) {}
	else
		MessageBox(g_hWnd, "번호 저장파일 로드 실패", "실패", MB_OK);
	CloseHandle(hFileNum);
}