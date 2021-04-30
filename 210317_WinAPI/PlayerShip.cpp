#include "PlayerShip.h"
#include "CommonFunction.h"
#include "Image.h"
#include "MissileManager.h"
#include "CollisionCheck.h"

HRESULT PlayerShip::Init(CollisionCheck* collisionCheck)
{
	this->collisionCheck = collisionCheck;

	image = ImageManager::GetSingleton()->AddImage("�÷��̾� ��ũ",
		"Image/Player/Player.bmp", 8*24*2, 4*24*2, 8, 4, true, RGB(255, 0, 255));//512*256

	if (image == nullptr)
	{
		MessageBox(g_hWnd, "�÷��̾� ��ũ �̹��� �ε� ����", "�ʱ�ȭ ����", MB_OK);
		return E_FAIL;
	}

	pos.x = WINSIZE_X - 200;
	pos.y = WINSIZE_Y / 2;

	size = 40;

	moveSpeed = 150.0f;

	currFrameX = 0;
	currFrameY = 0;

	// �̻��� �Ŵ���
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
	// ������
	Move();
	
	// ���
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
		// ���� ����Ű
		playerCurrMove = 0;
		(this->collisionCheck)->SetPlayerDir(playerCurrMove);

		// �ݸ��� üũ
		(this->collisionCheck)->SetPlayerFuturePos({ pos.x - moveSpeed * TimerManager::GetSingleton()->GetElapsedTime() , pos.y});

		// ������ ������
		if (currFrameX != 2 && currFrameX != 3)
			currFrameX = 2;

		currFrameX++;
		if (currFrameX % 4 == 0)
		{
			currFrameX = 2;
		}

		// ������ ���� ����
		if((this->collisionCheck)->GetPlayerCanMove() && (pos.x - size / 2 - moveSpeed * TimerManager::GetSingleton()->GetElapsedTime()) > 200)
			pos.x -= moveSpeed * TimerManager::GetSingleton()->GetElapsedTime();
	}
	else if (KeyManager::GetSingleton()->IsStayKeyDown(VK_RIGHT))
	{
		// ���� ����Ű
		playerCurrMove = 1;
		(this->collisionCheck)->SetPlayerDir(playerCurrMove);

		// �ݸ��� üũ
		(this->collisionCheck)->SetPlayerFuturePos({ pos.x + moveSpeed * TimerManager::GetSingleton()->GetElapsedTime() , pos.y });

		// ������ ������
		if (currFrameX != 6 && currFrameX != 7)
			currFrameX = 6;

		currFrameX++;
		if (currFrameX % 8 == 0)
		{
			currFrameX = 6;
		}

		// ������ ���� ����
		if ((this->collisionCheck)->GetPlayerCanMove() && (pos.x + size / 2 + moveSpeed * TimerManager::GetSingleton()->GetElapsedTime()) < 200 + (TILE_X * TILESIZE))
			pos.x += moveSpeed * TimerManager::GetSingleton()->GetElapsedTime();
	}
	else if (KeyManager::GetSingleton()->IsStayKeyDown(VK_UP))
	{
		// ���� ����Ű
		playerCurrMove = 2;
		(this->collisionCheck)->SetPlayerDir(playerCurrMove);

		// �ݸ��� üũ
		(this->collisionCheck)->SetPlayerFuturePos({ pos.x , pos.y - moveSpeed * TimerManager::GetSingleton()->GetElapsedTime() });

		// ������ ������
		if (currFrameX != 0 && currFrameX != 1)
			currFrameX = 0;

		currFrameX++;
		if (currFrameX % 2 == 0)
		{
			currFrameX = 0;
		}

		// ������ ���� ����
		if ((this->collisionCheck)->GetPlayerCanMove() && (pos.y - size / 2 - moveSpeed * TimerManager::GetSingleton()->GetElapsedTime()) > 50)
			pos.y -= moveSpeed * TimerManager::GetSingleton()->GetElapsedTime();
	}
	else if (KeyManager::GetSingleton()->IsStayKeyDown(VK_DOWN))
	{
		// ���� ����Ű
		playerCurrMove = 3;
		(this->collisionCheck)->SetPlayerDir(playerCurrMove);

		// �ݸ��� üũ
		(this->collisionCheck)->SetPlayerFuturePos({ pos.x , pos.y + moveSpeed * TimerManager::GetSingleton()->GetElapsedTime() });

		// ������ ������

		if (currFrameX != 4 && currFrameX != 5)
			currFrameX = 4;

		currFrameX++;
		if (currFrameX % 6 == 0)
		{
			currFrameX = 4;
		}

		// ������ ���� ����
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
