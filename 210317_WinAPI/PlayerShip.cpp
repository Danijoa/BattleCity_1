#include "PlayerShip.h"
#include "CommonFunction.h"
#include "Image.h"
#include "MissileManager.h"
#include "CollisionCheck.h"

HRESULT PlayerShip::Init(CollisionCheck* collisionCheck)
{
	this->collisionCheck = collisionCheck;

	image = ImageManager::GetSingleton()->FindImage("플레이어 탱크");

	if (image == nullptr)
	{
		MessageBox(g_hWnd, "플레이어 탱크 이미지 로드 실패", "초기화 실패", MB_OK);
		return E_FAIL;
	}

	pos.x = WINSIZE_X - 200;
	pos.y = WINSIZE_Y / 2;

	size = 35;

	moveSpeed = 150.0f;

	currFrameX = 0;
	currFrameY = 0;

	// 미사일 매니저
	missileMgr = new MissileManager();
	missileMgr->Init(this->collisionCheck,this);

	playerCurrDir = 2;

	return S_OK;
}

void PlayerShip::Release()
{
}

void PlayerShip::Update()
{
	// 움직임
	Move();
	
	// 출력
	playerRect = { (LONG)(pos.x - size / 2) , (LONG)(pos.y - size / 2), (LONG)(pos.x + size / 2) , (LONG)(pos.y + size / 2) };
	(this->collisionCheck)->SetPlayerRect(&playerRect);

	if (missileMgr)
	{
		missileMgr->Update();
	}

	if (KeyManager::GetSingleton()->IsOnceKeyDown('Z'))
	{
		missileMgr->Fire();
	}
}

void PlayerShip::SetFutureIndex(FPOINT playerFuturePos)
{
	playerFutureIndex = { (int)(playerFuturePos.x - 200) / TILESIZE, (int)(playerFuturePos.y - 50) / TILESIZE };
	(this->collisionCheck)->SetPlayerFutureIndex(playerFutureIndex);

	playerFutureRectIndex = { ((int)(playerFuturePos.x - size / 2) - 200) / TILESIZE,
	   ((int)(playerFuturePos.y - size / 2) - 50) / TILESIZE,
	   ((int)(playerFuturePos.x + size / 2) - 200) / TILESIZE,
	   ((int)(playerFuturePos.y + size / 2) - 50) / TILESIZE };
	(this->collisionCheck)->SetPlayerFutureRECTIndex(playerFutureRectIndex);
}

void PlayerShip::FrameMove(int start, int end)
{
	if (currFrameX != start && currFrameX != end)
		currFrameX = start;

	currFrameX++;
	if (currFrameX % (start + 2) == 0)
	{
		currFrameX = start;
	}
}

void PlayerShip::Move()
{
	if (KeyManager::GetSingleton()->IsStayKeyDown(VK_LEFT))	//좌
	{
		// 현재 방향키
		playerCurrDir = 0;
		(this->collisionCheck)->SetPlayerDir(playerCurrDir);

		// 콜리전 체크
		playerFuturePos = { pos.x - moveSpeed * TimerManager::GetSingleton()->GetElapsedTime() , pos.y };
		SetFutureIndex(playerFuturePos);

		// 프레임 움직임
		FrameMove(2, 3);

		// 움직임 가능 여부
		if ((this->collisionCheck)->GetPlayerCanMove()
			&& (pos.x - size / 2 - moveSpeed * TimerManager::GetSingleton()->GetElapsedTime()) > 200)
			pos.x -= moveSpeed * TimerManager::GetSingleton()->GetElapsedTime();
	}
	else if (KeyManager::GetSingleton()->IsStayKeyDown(VK_RIGHT))	//우
	{
		// 현재 방향키
		playerCurrDir = 1;
		(this->collisionCheck)->SetPlayerDir(playerCurrDir);

		// 콜리전 체크
		playerFuturePos = { pos.x + moveSpeed * TimerManager::GetSingleton()->GetElapsedTime() , pos.y };
		SetFutureIndex(playerFuturePos);

		// 프레임 움직임
		FrameMove(6, 7);

		// 움직임 가능 여부
		if ((this->collisionCheck)->GetPlayerCanMove()
			&& (pos.x + size / 2 + moveSpeed * TimerManager::GetSingleton()->GetElapsedTime()) < 200 + (TILE_X * TILESIZE))
			pos.x += moveSpeed * TimerManager::GetSingleton()->GetElapsedTime();
	}
	else if (KeyManager::GetSingleton()->IsStayKeyDown(VK_UP))	//상
	{
		// 현재 방향키
		playerCurrDir = 2;
		(this->collisionCheck)->SetPlayerDir(playerCurrDir);

		// 콜리전 체크
		playerFuturePos = { pos.x, pos.y - moveSpeed * TimerManager::GetSingleton()->GetElapsedTime() };
		SetFutureIndex(playerFuturePos);

		// 프레임 움직임
		FrameMove(0, 1);

		// 움직임 가능 여부
		if ((this->collisionCheck)->GetPlayerCanMove()
			&& (pos.y - size / 2 - moveSpeed * TimerManager::GetSingleton()->GetElapsedTime()) > 50)
			pos.y -= moveSpeed * TimerManager::GetSingleton()->GetElapsedTime();
	}
	else if (KeyManager::GetSingleton()->IsStayKeyDown(VK_DOWN))	//하
	{
		// 현재 방향키
		playerCurrDir = 3;
		(this->collisionCheck)->SetPlayerDir(playerCurrDir);

		// 콜리전 체크
		playerFuturePos = { pos.x, pos.y + moveSpeed * TimerManager::GetSingleton()->GetElapsedTime() };
		SetFutureIndex(playerFuturePos);

		// 프레임 움직임
		FrameMove(4, 5);

		// 움직임 가능 여부
		if ((this->collisionCheck)->GetPlayerCanMove()
			&& (pos.y + size / 2 + moveSpeed * TimerManager::GetSingleton()->GetElapsedTime()) < 50 + (TILE_Y * TILESIZE))
			pos.y += moveSpeed * TimerManager::GetSingleton()->GetElapsedTime();
	}
}

void PlayerShip::Render(HDC hdc)
{
	if (image)
	{
		image->FrameRender(hdc, pos.x, pos.y, currFrameX, currFrameY, true);
	}

	if (missileMgr)
	{
		missileMgr->Render(hdc);
	}
}
