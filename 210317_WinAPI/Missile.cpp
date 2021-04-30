#include "Missile.h"
#include "Enemy.h"
#include "PlayerShip.h"
#include "CommonFunction.h"
#include "Image.h"
#include "CollisionCheck.h"

HRESULT Missile::Init(CollisionCheck* collisionCheck,Enemy* enemyOwner)
{
	this->enemyOwner = enemyOwner;
	this->collisionCheck = collisionCheck;

	playerOwner = nullptr;
	pos = {-100, -100};
	moveSpeed = 400.0f;
	moveTime = 1.0f;
	size = 50;
	shape = { 0, 0, 0, 0 };
	damage = 5000;
	angle = 0.0f;
	isFired = false;
	missileType = TYPE::Normal;
	fireStep = 0;
	target = nullptr;
	destAngle = 0.0f;

	// �̹���
	img = ImageManager::GetSingleton()->FindImage("���̻���");
	if (img == nullptr)
	{
		MessageBox(g_hWnd,
			"EnemyMissile�� �ش��ϴ� �̹����� �߰����� �ʾ���!", "���", MB_OK);
		return E_FAIL;
	}

    return S_OK;
}

HRESULT Missile::Init(CollisionCheck* collisionCheck,  PlayerShip* playerOwner)
{
	this->playerOwner = playerOwner;
	this->collisionCheck = collisionCheck;

	enemyOwner = nullptr;
	pos = { -100, -100 };
	moveSpeed = 400.0f;
	moveTime = 1.0f;
	size = 50;
	shape = { 0, 0, 0, 0 };
	damage = 5000;
	angle = 0.0f;
	isFired = false;
	missileType = TYPE::Normal;
	fireStep = 0;
	target = nullptr;
	destAngle = 0.0f;

	// �̹���
	img = ImageManager::GetSingleton()->FindImage("���̻���");
	if (img == nullptr)
	{
		MessageBox(g_hWnd,
			"EnemyMissile�� �ش��ϴ� �̹����� �߰����� �ʾ���!", "���", MB_OK);
		return E_FAIL;
	}

	return S_OK;
}

void Missile::Release()
{

}

void Missile::Update()
{
	if (playerCurrMove == 0 || playerCurrMove == 1)			attackBox = GetRectToCenter(pos.x, pos.y, 16, 12);
	else if (playerCurrMove == 2 || playerCurrMove == 3)	attackBox = GetRectToCenter(pos.x, pos.y, 12, 16);

	// ��ġ �̵�
	if (isFired)
	{
		// �̻��� ��翡 ���� RECT ũ��

		switch (missileType)
		{
		case TYPE::Normal:
			MovingNormal();
			break;
		case TYPE::Skill_01:
			MovingSkill_01();
			break;
		case TYPE::FollowTarget:
			MovingFollowTarget();
			break;
		}


		if (pos.x < 200 || pos.y < 50 || pos.x > 200 + (TILE_X * TILESIZE) || pos.y > 50 + (TILE_X * TILESIZE))
		{
			isFired = false;
			fireStep = 0;

			if (enemyOwner)
			{
				collisionCheck->EraseEnemyMissile(this);
			}
			else if (playerOwner)
			{
				collisionCheck->ErasePlayerMissile(this);
			}
		}
	}

}

void Missile::Render(HDC hdc)
{
	if (isFired)
	{
		switch (playerCurrMove)
		{
		case 0:		//��
			img = ImageManager::GetSingleton()->FindImage("���ʹ̻���");
			break;
		case 1:		//��
			img = ImageManager::GetSingleton()->FindImage("�����ʹ̻���");
			break;
		case 2:		//��
			img = ImageManager::GetSingleton()->FindImage("���̻���");
			break;
		case 3:		//��
			img = ImageManager::GetSingleton()->FindImage("�Ʒ��̻���");
			break;
		}
		
		img->Render(hdc, pos.x, pos.y, true);
	}
}

void Missile::MovingNormal()
{
	float elapsedTime = TimerManager::GetSingleton()->GetElapsedTime();
	pos.x += cosf(angle) * moveSpeed * elapsedTime / moveTime;
	pos.y -= sinf(angle) * moveSpeed * elapsedTime / moveTime;
}

void Missile::MovingSkill_01()
{
	if (fireStep == 0 && pos.y < 300.0f)
	{
		angle = fireIndex * 3.14f * 2.0f / 36.0f;
		fireStep++;
	}

	pos.x += cosf(angle) * moveSpeed;
	pos.y -= sinf(angle) * moveSpeed;
}

void Missile::MovingFollowTarget()
{
	if (target)
	{
		destAngle = GetAngle(pos, target->GetPos());
		float ratio = (destAngle - angle) / 50.0f;

		if (-0.01f < ratio && ratio < 0.01f)
		{
			angle = destAngle;
		}
		else
		{
			angle += ratio;
		}
	}

	pos.x += cosf(angle) * moveSpeed;
	pos.y -= sinf(angle) * moveSpeed;
}

void Missile::SetIsFired(bool isFired)
{
	this->isFired = isFired;

	if (isFired == true)
	{
		if (enemyOwner)
		{
			collisionCheck->AddFiredEnemyMissile(this);
		}
		else if (playerOwner)
		{
			collisionCheck->AddFiredPlayerMissile(this);
		}
	}

	else if (isFired == false)
	{
		pos.x = -100.0f;
		pos.y = -100.0f;
	}

	if (enemyOwner)
	{
		pos.x = enemyOwner->GetPos().x;
		pos.y = enemyOwner->GetPos().y;
	}

	else if (playerOwner)
	{
		pos.x = playerOwner->GetPos().x;
		pos.y = playerOwner->GetPos().y;
	}

}
