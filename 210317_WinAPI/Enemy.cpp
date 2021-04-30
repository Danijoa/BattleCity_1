#include "Enemy.h"
#include "CommonFunction.h"
#include "Image.h"
#include "MissileManager.h"

HRESULT Enemy::Init(CollisionCheck* collisionCheck, int posX, int posY)
{
    this->collisionCheck = collisionCheck;

    // �̹����� �̸� �ε��Ѵ�
    image = ImageManager::GetSingleton()->AddImage("Enemy",
        "Image/Enemy/Enemy.bmp", 8*24*2, 6*24*2, 8, 6, true, RGB(255, 0, 255));   //512*384

    if (image == nullptr)
    {
        MessageBox(g_hWnd, "���ʹ� ��ũ �̹��� �ε� ����", "�ʱ�ȭ ����", MB_OK);
        return E_FAIL;
    }

    currFrameX = 0;
    currFrameY = 0;
    updateCount = 0;

    pos.x =  posX;
    pos.y = posY;
    size = 40;
    name = "NormalEnemy";
    shape = { 0, 0, 0, 0 };
    moveSpeed = 3.3f;
    isAlive = true;
    angle = 0.0f;
    target = nullptr;
    dir = 1;

    // �̻��� �Ŵ���
    missileMgr = new MissileManager();
    missileMgr->Init(this->collisionCheck, this);

    fireCount = 0;

    return S_OK;
}

void Enemy::Release()
{
    SAFE_RELEASE(missileMgr);
}

void Enemy::Update()
{
    if (missileMgr)
    {
        missileMgr->Update();
    }


    if (KeyManager::GetSingleton()->IsOnceKeyDown('X'))
    {
        missileMgr->Fire();
    }
}

void Enemy::Render(HDC hdc)
{
    if (isAlive)
    {
        RenderRectToCenter(hdc, pos.x, pos.y, size, size);

        if (image)
        {
            image->FrameRender(hdc, pos.x, pos.y, currFrameX, currFrameY, true);
        }

        if (missileMgr)
        {
            missileMgr->Render(hdc);
        }
    }
}
