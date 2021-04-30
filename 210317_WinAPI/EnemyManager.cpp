#include "EnemyManager.h"
#include "Enemy.h"
#include "CollisionCheck.h"

HRESULT EnemyManager::Init(CollisionCheck* collisionCheck)
{
    vEnemys.resize(1);
    for (int i = 0; i < 1; i++)
    {
        vEnemys[i] = new Enemy();
        vEnemys[i]->Init(collisionCheck, 500 + (i % 5) * 200, 100 + (i / 5) * 500);
    }

    return S_OK;
}

void EnemyManager::Release()
{
    // 반복자(iterator) : STL 자료구조를 구성하는 원소의 메모리를 저장하는 객체
    vector<Enemy*>::iterator it;
    for (it = vEnemys.begin(); it != vEnemys.end(); it++)
    {
        (*it)->Release();   // (*it) -> Enemy* 데이터타입확인
        delete (*it);
        (*it) = nullptr;
    }
}

void EnemyManager::Update()
{
    vector<Enemy*>::iterator it;
    for (it = vEnemys.begin(); it != vEnemys.end(); it++)
    {
        (*it)->Update();
    }
}

void EnemyManager::Render(HDC hdc)
{
    vector<Enemy*>::iterator it;
    for (it = vEnemys.begin(); it != vEnemys.end(); it++)
    {
        (*it)->Render(hdc);
    }
}

void EnemyManager::AddEnemy(int size)
{
    for (int i = 0; i < size; i++)
    {
        vEnemys.push_back(new Enemy());
        vEnemys[vEnemys.size() - 1]->Init();
    }
}
