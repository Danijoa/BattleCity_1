#include "EnemyManager.h"
#include "Enemy.h"
#include "CollisionCheck.h"

HRESULT EnemyManager::Init(CollisionCheck* collisionCheck)
{
    this->collisionCheck = collisionCheck;

    vEnemys.resize(2);
    for (int i = 0; i < 2; i++)
    {
        vEnemys[i] = new Enemy();
        vEnemys[i]->Init(this->collisionCheck, 500 + (i % 5) * 200, 100 + (i / 5) * 500);

    }

    return S_OK;
}

void EnemyManager::Release()
{
    // �ݺ���(iterator) : STL �ڷᱸ���� �����ϴ� ������ �޸𸮸� �����ϴ� ��ü
    vector<Enemy*>::iterator it;
    for (it = vEnemys.begin(); it != vEnemys.end(); it++)
    {
        (*it)->Release();   // (*it) -> Enemy* ������Ÿ��Ȯ��
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
        vEnemys[vEnemys.size() - 1]->Init(this->collisionCheck);
    }
}
