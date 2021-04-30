#include "MissileManager.h"
#include "Missile.h"
#include "PlayerShip.h"

HRESULT MissileManager::Init(CollisionCheck* collisionCheck, Enemy* enemyOwner)
{
    this->enemyOwner = enemyOwner;
    this->collisionCheck = collisionCheck;

    vMissiles.resize(50);
    vector<Missile*>::iterator it;
    for (it = vMissiles.begin(); it != vMissiles.end(); it++)
    {
        (*it) = new Missile();
        (*it)->Init(this->collisionCheck,this->enemyOwner);

        // 미사일 매니저를 들고 있는 적 객체의 정보를 전달
    }

    return S_OK;
}

HRESULT MissileManager::Init(CollisionCheck* collisionCheck, PlayerShip* playerOwner)
{
    this->playerOwner = playerOwner;
    this->collisionCheck = collisionCheck;

    vMissiles.resize(50);
    vector<Missile*>::iterator it;
    for (it = vMissiles.begin(); it != vMissiles.end(); it++)
    {
        (*it) = new Missile();
        (*it)->Init(this->collisionCheck,this->playerOwner);

        // 미사일 매니저를 들고 있는 적 객체의 정보를 전달
    }

    return S_OK;
}

void MissileManager::Release()
{
    vector<Missile*>::iterator it;
    for (it = vMissiles.begin(); it != vMissiles.end(); it++)
    {
        (*it)->Release();
        delete (*it);
        (*it) = nullptr;
    }
    vMissiles.clear();
}

void MissileManager::Update()
{
    for (int i = 0; i < vMissiles.size(); i++)
    {
        vMissiles[i]->Update();
    }

    //vector<Missile*>::iterator it;
    //for (it = vMissiles.begin(); it != vMissiles.end(); it++)
    //{
    //    (*it)->Update();
    //}
}

void MissileManager::Render(HDC hdc)
{
    for (int i = 0; i < vMissiles.size(); i++)
    {
        vMissiles[i]->Render(hdc);
    }
    //vector<Missile*>::iterator it;
    //for (it = vMissiles.begin(); it != vMissiles.end(); it++)
    //{
    //    (*it)->Render(hdc);
    //}
}

void MissileManager::Fire()
{
    vector<Missile*>::iterator it;
    for (it = vMissiles.begin(); it != vMissiles.end(); it++)
    {
        if ((*it)->GetIsFired() == false)
        {
            (*it)->SetIsFired(true);

            if (playerOwner)
            {
                switch (playerOwner->GetCurrMove())
                {
                case 0:
                    (*it)->SetAngle(DegToRad(180));
                    (*it)->SetCurrMove(0);
                    break;
                case 1:
                    (*it)->SetAngle(DegToRad(0));
                    (*it)->SetCurrMove(1);
                    break;
                case 2:
                    (*it)->SetAngle(DegToRad(90));
                    (*it)->SetCurrMove(2);
                    break;
                case 3:
                    (*it)->SetAngle(DegToRad(-90));
                    (*it)->SetCurrMove(3);
                    break;
                }
                break;
            }

            if (enemyOwner)
            {
                (*it)->SetAngle(DegToRad(90));
                (*it)->SetCurrMove(2);
                break;
            }

        }

    }
}
