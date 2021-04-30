#include "PlayerShip.h"
#include "CommonFunction.h"
#include "Image.h"
#include "MissileManager.h"
#include "CollisionCheck.h"

HRESULT PlayerShip::Init(CollisionCheck* collisionCheck)
{
	this->collisionCheck = collisionCheck;

	image = ImageManager::GetSingleton()->AddImage("플레이어 탱크",
		"Image/Player/Player.bmp", 8*24*2, 4*24*2, 8, 4, true, RGB(255, 0, 255));//512*256

	if (image == nullptr)
	{
		MessageBox(g_hWnd, "플레이어 탱크 이미지 로드 실패", "초기화 실패", MB_OK);
		return E_FAIL;
	}

	pos.x = WINSIZE_X - 200;
	pos.y = WINSIZE_Y / 2;

	size = 40;

	moveSpeed = 150.0f;

	currFrameX = 0;
	currFrameY = 0;

	// 미사일 매니저
	missileMgr = new MissileManager();
	missileMgr->Init(this->collisionCheck,this);

	playerCurrMove = 2;

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

void PlayerShip::Move()
{
	if (KeyManager::GetSingleton()->IsStayKeyDown(VK_LEFT))
	{
		// 현재 방향키
		playerCurrMove = 0;
		(this->collisionCheck)->SetPlayerDir(playerCurrMove);

		// 콜리전 체크
		(this->collisionCheck)->SetPlayerFuturePos({ pos.x - moveSpeed * TimerManager::GetSingleton()->GetElapsedTime() , pos.y});

		// 프레임 움직임
		if (currFrameX != 2 && currFrameX != 3)
			currFrameX = 2;

		currFrameX++;
		if (currFrameX % 4 == 0)
		{
			currFrameX = 2;
		}

		// 움직임 가능 여부
		if((this->collisionCheck)->GetPlayerCanMove() && (pos.x - size / 2 - moveSpeed * TimerManager::GetSingleton()->GetElapsedTime()) > 200)
			pos.x -= moveSpeed * TimerManager::GetSingleton()->GetElapsedTime();
	}
	else if (KeyManager::GetSingleton()->IsStayKeyDown(VK_RIGHT))
	{
		// 현재 방향키
		playerCurrMove = 1;
		(this->collisionCheck)->SetPlayerDir(playerCurrMove);

		// 콜리전 체크
		(this->collisionCheck)->SetPlayerFuturePos({ pos.x + moveSpeed * TimerManager::GetSingleton()->GetElapsedTime() , pos.y });

		// 프레임 움직임
		if (currFrameX != 6 && currFrameX != 7)
			currFrameX = 6;

		currFrameX++;
		if (currFrameX % 8 == 0)
		{
			currFrameX = 6;
		}

		// 움직임 가능 여부
		if ((this->collisionCheck)->GetPlayerCanMove() && (pos.x + size / 2 + moveSpeed * TimerManager::GetSingleton()->GetElapsedTime()) < 200 + (TILE_X * TILESIZE))
			pos.x += moveSpeed * TimerManager::GetSingleton()->GetElapsedTime();
	}
	else if (KeyManager::GetSingleton()->IsStayKeyDown(VK_UP))
	{
		// 현재 방향키
		playerCurrMove = 2;
		(this->collisionCheck)->SetPlayerDir(playerCurrMove);

		// 콜리전 체크
		(this->collisionCheck)->SetPlayerFuturePos({ pos.x , pos.y - moveSpeed * TimerManager::GetSingleton()->GetElapsedTime() });

		// 프레임 움직임
		if (currFrameX != 0 && currFrameX != 1)
			currFrameX = 0;

		currFrameX++;
		if (currFrameX % 2 == 0)
		{
			currFrameX = 0;
		}

		// 움직임 가능 여부
		if ((this->collisionCheck)->GetPlayerCanMove() && (pos.y - size / 2 - moveSpeed * TimerManager::GetSingleton()->GetElapsedTime()) > 50)
			pos.y -= moveSpeed * TimerManager::GetSingleton()->GetElapsedTime();
	}
	else if (KeyManager::GetSingleton()->IsStayKeyDown(VK_DOWN))
	{
		// 현재 방향키
		playerCurrMove = 3;
		(this->collisionCheck)->SetPlayerDir(playerCurrMove);

		// 콜리전 체크
		(this->collisionCheck)->SetPlayerFuturePos({ pos.x , pos.y + moveSpeed * TimerManager::GetSingleton()->GetElapsedTime() });

		// 프레임 움직임

		if (currFrameX != 4 && currFrameX != 5)
			currFrameX = 4;

		currFrameX++;
		if (currFrameX % 6 == 0)
		{
			currFrameX = 4;
		}

		// 움직임 가능 여부
		if ((this->collisionCheck)->GetPlayerCanMove() && (pos.y + size/2 + moveSpeed * TimerManager::GetSingleton()->GetElapsedTime()) < 50 + (TILE_X * TILESIZE))
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
