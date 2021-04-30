#include "Missile.h"
#include "Enemy.h"
#include "PlayerShip.h"
#include "CommonFunction.h"
#include "Image.h"

HRESULT Missile::Init(Enemy* enemyOwner)
{
	this->enemyOwner = enemyOwner;

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

HRESULT Missile::Init(PlayerShip* playerOwner)
{
	this->playerOwner = playerOwner;

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
	// ��ġ �̵�
	if (isFired)
	{
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

		if (pos.x < 0 || pos.y < 0 || pos.x > WINSIZE_X || pos.y > WINSIZE_Y)
		{
			isFired = false;
			fireStep = 0;
		}
	}

	shape.left = pos.x - size / 2;
	shape.top = pos.y - size / 2;
	shape.right = pos.x + size / 2;
	shape.bottom = pos.y + size / 2;
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
		//Ellipse(hdc, shape.left, shape.top, shape.right, shape.bottom);
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
	if (enemyOwner)
	{
		pos.x = enemyOwner->GetPos().x;
		pos.y = enemyOwner->GetPos().y;
	}

	if (playerOwner)
	{
		pos.x = playerOwner->GetPos().x;
		pos.y = playerOwner->GetPos().y;
	}

}
