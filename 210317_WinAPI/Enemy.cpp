#include "Enemy.h"
#include "CommonFunction.h"
#include "Image.h"
#include "MissileManager.h"
#include "CollisionCheck.h"

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
    moveSpeed = 150.0f;
    isAlive = true;

    // �̻��� �Ŵ���
    missileMgr = new MissileManager();
    missileMgr->Init(this);

    fireCount = 0;

    enemeyCanMove = true;

    return S_OK;
}

void Enemy::Release()
{
    SAFE_RELEASE(missileMgr);
}

void Enemy::Update()
{
    //
    (this->collisionCheck)->SetAddEnemy(this);

    // ������
    Move();

    // �ݸ��� �ڽ�
    enemyRect = { (LONG)(pos.x - size / 2) , (LONG)(pos.y - size / 2), (LONG)(pos.x + size / 2) , (LONG)(pos.y + size / 2) };

    if (missileMgr)
    {
        missileMgr->Update();
    }

    if (KeyManager::GetSingleton()->IsOnceKeyDown('X'))
    {
        missileMgr->Fire();
    }
}

void Enemy::Move()
{
    if (KeyManager::GetSingleton()->IsStayKeyDown('J')) //��
    {
        // ���� ����Ű
        enemyCurrDir = 0;
        (this->collisionCheck)->SetEnemyDir(enemyCurrDir);

        // �ݸ��� üũ
        enemyFuturePos = { pos.x - moveSpeed * TimerManager::GetSingleton()->GetElapsedTime() , pos.y };
        (this->collisionCheck)->SetEnemyFuturePos(enemyFuturePos);
        enemyFutureIndex = { (enemyFuturePos.x - 200) / TILESIZE, (enemyFuturePos.y - 50) / TILESIZE };
        (this->collisionCheck)->SetEnemyFutureIndex(enemyFutureIndex);
        enemyFutureRectIndex = { (LONG)(((enemyFuturePos.x - size / 2) - 200) / TILESIZE),
            (LONG)(((enemyFuturePos.y - size / 2) - 50) / TILESIZE),
            (LONG)(((enemyFuturePos.x + size / 2) - 200) / TILESIZE),
            (LONG)(((enemyFuturePos.y + size / 2) - 50) / TILESIZE) };
        (this->collisionCheck)->SetEnemyFutureRectIndex(&enemyFutureRectIndex);

        // ������ ������
        if (currFrameX != 2 && currFrameX != 3)
            currFrameX = 2;

        currFrameX++;
        if (currFrameX % 4 == 0)
        {
            currFrameX = 2;
        }

        // ������ ���� ����
        if (enemeyCanMove/*(this->collisionCheck)->GetEnemyCanMove()*/ && (pos.x - size / 2 - moveSpeed * TimerManager::GetSingleton()->GetElapsedTime()) > 200)
            pos.x -= moveSpeed * TimerManager::GetSingleton()->GetElapsedTime();
    }
    else if (KeyManager::GetSingleton()->IsStayKeyDown('L')) //��
    {
        // ���� ����Ű
        enemyCurrDir = 1;
        (this->collisionCheck)->SetEnemyDir(enemyCurrDir);

        // �ݸ��� üũ
        enemyFuturePos = { pos.x + moveSpeed * TimerManager::GetSingleton()->GetElapsedTime() , pos.y };
        (this->collisionCheck)->SetEnemyFuturePos(enemyFuturePos);
        enemyFutureIndex = { (enemyFuturePos.x - 200) / TILESIZE, (enemyFuturePos.y - 50) / TILESIZE };
        (this->collisionCheck)->SetEnemyFutureIndex(enemyFutureIndex);
        enemyFutureRectIndex = { (LONG)(((enemyFuturePos.x - size / 2) - 200) / TILESIZE),
            (LONG)(((enemyFuturePos.y - size / 2) - 50) / TILESIZE),
            (LONG)(((enemyFuturePos.x + size / 2) - 200) / TILESIZE),
            (LONG)(((enemyFuturePos.y + size / 2) - 50) / TILESIZE) };
        (this->collisionCheck)->SetEnemyFutureRectIndex(&enemyFutureRectIndex);

        // ������ ������
        if (currFrameX != 6 && currFrameX != 7)
            currFrameX = 6;

        currFrameX++;
        if (currFrameX % 8 == 0)
        {
            currFrameX = 6;
        }

        // ������ ���� ����
        if (enemeyCanMove/*(this->collisionCheck)->GetEnemyCanMove()*/ && (pos.x + size / 2 + moveSpeed * TimerManager::GetSingleton()->GetElapsedTime()) < 200 + (TILE_X * TILESIZE))
            pos.x += moveSpeed * TimerManager::GetSingleton()->GetElapsedTime();
    }
    else if (KeyManager::GetSingleton()->IsStayKeyDown('I')) //��
    {
        // ���� ����Ű
        enemyCurrDir = 2;
        (this->collisionCheck)->SetEnemyDir(enemyCurrDir);

        // �ݸ��� üũ
        enemyFuturePos = { pos.x, pos.y - moveSpeed * TimerManager::GetSingleton()->GetElapsedTime() };
        (this->collisionCheck)->SetEnemyFuturePos(enemyFuturePos);
        enemyFutureIndex = { (enemyFuturePos.x - 200) / TILESIZE, (enemyFuturePos.y - 50) / TILESIZE };
        (this->collisionCheck)->SetEnemyFutureIndex(enemyFutureIndex);
        enemyFutureRectIndex = { (LONG)(((enemyFuturePos.x - size / 2) - 200) / TILESIZE),
            (LONG)(((enemyFuturePos.y - size / 2) - 50) / TILESIZE),
            (LONG)(((enemyFuturePos.x + size / 2) - 200) / TILESIZE),
            (LONG)(((enemyFuturePos.y + size / 2) - 50) / TILESIZE) };
        (this->collisionCheck)->SetEnemyFutureRectIndex(&enemyFutureRectIndex);

        // ������ ������
        if (currFrameX != 0 && currFrameX != 1)
            currFrameX = 0;

        currFrameX++;
        if (currFrameX % 2 == 0)
        {
            currFrameX = 0;
        }

        // ������ ���� ����
        if (enemeyCanMove/*(this->collisionCheck)->GetEnemyCanMove()*/ && (pos.y - size / 2 - moveSpeed * TimerManager::GetSingleton()->GetElapsedTime()) > 50)
            pos.y -= moveSpeed * TimerManager::GetSingleton()->GetElapsedTime();
    }
    else if (KeyManager::GetSingleton()->IsStayKeyDown('K')) //��
    {
        // ���� ����Ű
        enemyCurrDir = 3;
        (this->collisionCheck)->SetEnemyDir(enemyCurrDir);

        // �ݸ��� üũ
        enemyFuturePos = { pos.x, pos.y + moveSpeed * TimerManager::GetSingleton()->GetElapsedTime() };
        (this->collisionCheck)->SetEnemyFuturePos(enemyFuturePos);
        enemyFutureIndex = { (enemyFuturePos.x - 200) / TILESIZE, (enemyFuturePos.y - 50) / TILESIZE };
        (this->collisionCheck)->SetEnemyFutureIndex(enemyFutureIndex);
        enemyFutureRectIndex = { (LONG)(((enemyFuturePos.x - size / 2) - 200) / TILESIZE),
            (LONG)(((enemyFuturePos.y - size / 2) - 50) / TILESIZE),
            (LONG)(((enemyFuturePos.x + size / 2) - 200) / TILESIZE),
            (LONG)(((enemyFuturePos.y + size / 2) - 50) / TILESIZE) };
        (this->collisionCheck)->SetEnemyFutureRectIndex(&enemyFutureRectIndex);

        // ������ ������
        if (currFrameX != 4 && currFrameX != 5)
            currFrameX = 4;

        currFrameX++;
        if (currFrameX % 6 == 0)
        {
            currFrameX = 4;
        }

        // ������ ���� ����
        if (enemeyCanMove/*(this->collisionCheck)->GetEnemyCanMove()*/ && (pos.y + size / 2 + moveSpeed * TimerManager::GetSingleton()->GetElapsedTime()) < 50 + (TILE_Y * TILESIZE))
            pos.y += moveSpeed * TimerManager::GetSingleton()->GetElapsedTime();
    }
}

void Enemy::Render(HDC hdc)
{
    if (isAlive)
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
}
