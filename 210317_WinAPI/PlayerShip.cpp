#include "PlayerShip.h"
#include "CommonFunction.h"
#include "Image.h"
#include "MissileManager.h"
#include "CollisionCheck.h"

HRESULT PlayerShip::Init(CollisionCheck* collisionCheck)
{
	this->collisionCheck = collisionCheck;

	image = ImageManager::GetSingleton()->FindImage("�÷��̾� ��ũ");

	if (image == nullptr)
	{
		MessageBox(g_hWnd, "�÷��̾� ��ũ �̹��� �ε� ����", "�ʱ�ȭ ����", MB_OK);
		return E_FAIL;
	}

	pos.x = WINSIZE_X - 200;
	pos.y = WINSIZE_Y / 2;

	size = 35;

	moveSpeed = 150.0f;

	currFrameX = 0;
	currFrameY = 0;

	// �̻��� �Ŵ���
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
	if (KeyManager::GetSingleton()->IsStayKeyDown(VK_LEFT))	//��
	{
		// ���� ����Ű
		playerCurrDir = 0;
		(this->collisionCheck)->SetPlayerDir(playerCurrDir);

		// �ݸ��� üũ
		playerFuturePos = { pos.x - moveSpeed * TimerManager::GetSingleton()->GetElapsedTime() , pos.y };
		SetFutureIndex(playerFuturePos);

		// ������ ������
		FrameMove(2, 3);

		// ������ ���� ����
		if ((this->collisionCheck)->GetPlayerCanMove()
			&& (pos.x - size / 2 - moveSpeed * TimerManager::GetSingleton()->GetElapsedTime()) > 200)
			pos.x -= moveSpeed * TimerManager::GetSingleton()->GetElapsedTime();
	}
	else if (KeyManager::GetSingleton()->IsStayKeyDown(VK_RIGHT))	//��
	{
		// ���� ����Ű
		playerCurrDir = 1;
		(this->collisionCheck)->SetPlayerDir(playerCurrDir);

		// �ݸ��� üũ
		playerFuturePos = { pos.x + moveSpeed * TimerManager::GetSingleton()->GetElapsedTime() , pos.y };
		SetFutureIndex(playerFuturePos);

		// ������ ������
		FrameMove(6, 7);

		// ������ ���� ����
		if ((this->collisionCheck)->GetPlayerCanMove()
			&& (pos.x + size / 2 + moveSpeed * TimerManager::GetSingleton()->GetElapsedTime()) < 200 + (TILE_X * TILESIZE))
			pos.x += moveSpeed * TimerManager::GetSingleton()->GetElapsedTime();
	}
	else if (KeyManager::GetSingleton()->IsStayKeyDown(VK_UP))	//��
	{
		// ���� ����Ű
		playerCurrDir = 2;
		(this->collisionCheck)->SetPlayerDir(playerCurrDir);

		// �ݸ��� üũ
		playerFuturePos = { pos.x, pos.y - moveSpeed * TimerManager::GetSingleton()->GetElapsedTime() };
		SetFutureIndex(playerFuturePos);

		// ������ ������
		FrameMove(0, 1);

		// ������ ���� ����
		if ((this->collisionCheck)->GetPlayerCanMove()
			&& (pos.y - size / 2 - moveSpeed * TimerManager::GetSingleton()->GetElapsedTime()) > 50)
			pos.y -= moveSpeed * TimerManager::GetSingleton()->GetElapsedTime();
	}
	else if (KeyManager::GetSingleton()->IsStayKeyDown(VK_DOWN))	//��
	{
		// ���� ����Ű
		playerCurrDir = 3;
		(this->collisionCheck)->SetPlayerDir(playerCurrDir);

		// �ݸ��� üũ
		playerFuturePos = { pos.x, pos.y + moveSpeed * TimerManager::GetSingleton()->GetElapsedTime() };
		SetFutureIndex(playerFuturePos);

		// ������ ������
		FrameMove(4, 5);

		// ������ ���� ����
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
