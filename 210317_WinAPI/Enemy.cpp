#include "Enemy.h"
#include "CommonFunction.h"
#include "Image.h"
#include "MissileManager.h"
#include "CollisionCheck.h"

HRESULT Enemy::Init(CollisionCheck* collisionCheck, int posX, int posY)
{
    this->collisionCheck = collisionCheck;

    // 이미지를 미리 로드한다
    image = ImageManager::GetSingleton()->AddImage("Enemy",
        "Image/Enemy/Enemy.bmp", 8 * 24 * 2, 6 * 24 * 2, 8, 6, true, RGB(255, 0, 255));   //512*384

    if (image == nullptr)
    {
        MessageBox(g_hWnd, "에너미 탱크 이미지 로드 실패", "초기화 실패", MB_OK);
        return E_FAIL;
    }

    currFrameX = 0;
    currFrameY = 0;
    updateCount = 0;

    pos.x = posX;
    pos.y = posY;
    size = 35;
    name = "NormalEnemy";
    moveSpeed = 150.0f;
    isAlive = true;

    // 미사일 매니저
    missileMgr = new MissileManager();
    missileMgr->Init(this->collisionCheck, this);

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
    // 콜리전 체크 
    (this->collisionCheck)->SetAddEnemy(this);

    // 움직임
    Move();
    enemyRect = { (LONG)(pos.x - size / 2) , (LONG)(pos.y - size / 2), (LONG)(pos.x + size / 2) , (LONG)(pos.y + size / 2) };

    // 미사일
    if (missileMgr)
    {
        missileMgr->Update();
    }

    if (KeyManager::GetSingleton()->IsOnceKeyDown('X'))
    {
        missileMgr->Fire();
    }
}

void Enemy::SetFutureIndex(FPOINT enemyFuturePos)
{
    enemyFutureIndex = { (int)(enemyFuturePos.x - 200) / TILESIZE, (int)(enemyFuturePos.y - 50) / TILESIZE };

    enemyFutureRectIndex = { ((int)(enemyFuturePos.x - size / 2) - 200) / TILESIZE,
       ((int)(enemyFuturePos.y - size / 2) - 50) / TILESIZE,
       ((int)(enemyFuturePos.x + size / 2) - 200) / TILESIZE,
       ((int)(enemyFuturePos.y + size / 2) - 50) / TILESIZE };
}

void Enemy::FrameMove(int start, int end)
{
    if (currFrameX != start && currFrameX != end)
        currFrameX = start;

    currFrameX++;
    if (currFrameX % (start + 2) == 0)
    {
        currFrameX = start;
    }
}

void Enemy::Move()
{
    if (KeyManager::GetSingleton()->IsStayKeyDown('J')) //좌
    {
        // 현재 방향키
        enemyCurrDir = 0;

        // 콜리전 세팅
        enemyFuturePos = { pos.x - moveSpeed * TimerManager::GetSingleton()->GetElapsedTime() , pos.y };
        SetFutureIndex(enemyFuturePos);

        // 프레임 움직임
        FrameMove(2, 3);

        // 움직임 가능 여부
        if (enemeyCanMove && (pos.x - size / 2 - moveSpeed * TimerManager::GetSingleton()->GetElapsedTime()) > 200)
            pos.x -= moveSpeed * TimerManager::GetSingleton()->GetElapsedTime();
    }
    else if (KeyManager::GetSingleton()->IsStayKeyDown('L')) //우
    {
        // 현재 방향키
        enemyCurrDir = 1;

        // 콜리전 세팅
        enemyFuturePos = { pos.x + moveSpeed * TimerManager::GetSingleton()->GetElapsedTime() , pos.y };
        SetFutureIndex(enemyFuturePos);

        // 프레임 움직임
        FrameMove(6, 7);

        // 움직임 가능 여부
        if (enemeyCanMove && (pos.x + size / 2 + moveSpeed * TimerManager::GetSingleton()->GetElapsedTime()) < 200 + (TILE_X * TILESIZE))
            pos.x += moveSpeed * TimerManager::GetSingleton()->GetElapsedTime();
    }
    else if (KeyManager::GetSingleton()->IsStayKeyDown('I')) //상
    {
        // 현재 방향키
        enemyCurrDir = 2;

        // 콜리전 세팅
        enemyFuturePos = { pos.x, pos.y - moveSpeed * TimerManager::GetSingleton()->GetElapsedTime() };
        SetFutureIndex(enemyFuturePos);

        // 프레임 움직임
        FrameMove(0, 1);

        // 움직임 가능 여부
        if (enemeyCanMove && (pos.y - size / 2 - moveSpeed * TimerManager::GetSingleton()->GetElapsedTime()) > 50)
            pos.y -= moveSpeed * TimerManager::GetSingleton()->GetElapsedTime();
    }
    else if (KeyManager::GetSingleton()->IsStayKeyDown('K')) //하
    {
        // 현재 방향키
        enemyCurrDir = 3;

        // 콜리전 세팅
        enemyFuturePos = { pos.x, pos.y + moveSpeed * TimerManager::GetSingleton()->GetElapsedTime() };
        SetFutureIndex(enemyFuturePos);

        // 프레임 움직임
        FrameMove(4, 5);

        // 움직임 가능 여부
        if (enemeyCanMove && (pos.y + size / 2 + moveSpeed * TimerManager::GetSingleton()->GetElapsedTime()) < 50 + (TILE_Y * TILESIZE))
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
