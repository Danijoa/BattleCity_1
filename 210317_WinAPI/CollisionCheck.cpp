#include "CollisionCheck.h"
#include "Missile.h"
#include "Enemy.h"


HRESULT CollisionCheck::Init()
{
	tileNumInfo = new int();
	tileInfo = new TILE_INFO();
	
	size = 35;
	
	//playerFuturePos = {0, 0};
	playerCurrDir = -1;
	playerCanMove = true;


    return E_NOTIMPL;
}

void CollisionCheck::Release()
{
}

void CollisionCheck::Update()
{
	// �÷��̾� ������ �浹 üũ
	playerMoveCheck();

	// �� ������ �浹 üũ
	enemyMoveCheck();

	mapCollisionCheck();
}

void CollisionCheck::playerMoveCheck()
{
	// �÷��̾� �浹�ڽ��� �� �浹 �ڽ��� �浹
	if (playerCurrDir == 0)			//��
	{
		if ((playerFutureIndex.x - 1) < 0)
		{
			return;
		}
		else
		{
			playerCanMove = true;
			for (int y = playerFutureRectIndex.topIndex; y <= playerFutureRectIndex.bottomIndex; y++)
			{
				if (tileNumInfo[(playerFutureIndex.x - 1) + (y * TILE_X)] != 0)
				{
					playerCanMove = false;
				}
			}
		}
	}
	else if (playerCurrDir == 1)	//��
	{
		if ((playerFutureIndex.x + 1) >= TILE_X)
		{
			return;
		}
		else
		{
			playerCanMove = true;
			for (int y = playerFutureRectIndex.topIndex; y <= playerFutureRectIndex.bottomIndex; y++)
			{
				if (tileNumInfo[(playerFutureIndex.x + 1) + (y * TILE_X)] != 0)
				{
					playerCanMove = false;
				}
			}
		}
	}
	else if (playerCurrDir == 2)	//��
	{
		if (playerFutureIndex.y - 1 < 0)
		{
			return;
		}
		else
		{
			playerCanMove = true;
			for (int x = playerFutureRectIndex.leftIndex; x <= playerFutureRectIndex.rightIndex; x++)
			{
				if (tileNumInfo[x + ((playerFutureIndex.y - 1) * TILE_X)] != 0)
				{
					playerCanMove = false;
				}
			}
		}
	}
	else if (playerCurrDir == 3)	//��
	{
		if (playerFutureIndex.y + 1 >= TILE_Y)
		{
			return;
		}
		else
		{
			playerCanMove = true;
			for (int x = playerFutureRectIndex.leftIndex; x <= playerFutureRectIndex.rightIndex; x++)
			{
				if (tileNumInfo[x + ((playerFutureIndex.y + 1) * TILE_X)] != 0)
				{
					playerCanMove = false;
				}
			}
		}
	}
}

void CollisionCheck::mapCollisionCheck()
{
	RECT rcTemp;
	for (int i = 0; i < TILE_X * TILE_Y; i++)
	{
		if (tileNumInfo[i] != 0)
		{
			for (itlPlayerMissiles = lPlayerMissiles.begin(); itlPlayerMissiles != lPlayerMissiles.end(); )
			{
				if (IntersectRect(&rcTemp, &(*itlPlayerMissiles)->GetAttackBox(), &tileInfo[i].rcTile))
				{
					(*itlPlayerMissiles)->SetIsBoom(true);
					(*itlPlayerMissiles)->SetBoomPos((*itlPlayerMissiles)->GetPos());
					(*itlPlayerMissiles)->SetIsFired(false);
					if (tileNumInfo[i] == 1)					collisionMapIndex = i;

					itlPlayerMissiles = lPlayerMissiles.erase(itlPlayerMissiles);

				}
				else
				{
					itlPlayerMissiles++;
				}
			}
		}
	}


	/*
	for (itlPlayerMissiles = lPlayerMissiles.begin(); itlPlayerMissiles != lPlayerMissiles.end(); )
	{
		int tempRectIndex[4];
		tempRectIndex[0] = (*itlPlayerMissiles)->GetMapRECTIndex().leftIndex + (*itlPlayerMissiles)->GetMapRECTIndex().topIndex * TILE_X;
		tempRectIndex[1] = (*itlPlayerMissiles)->GetMapRECTIndex().rightIndex + (*itlPlayerMissiles)->GetMapRECTIndex().topIndex * TILE_X;
		tempRectIndex[2] = (*itlPlayerMissiles)->GetMapRECTIndex().leftIndex + (*itlPlayerMissiles)->GetMapRECTIndex().bottomIndex * TILE_X;
		tempRectIndex[3] = (*itlPlayerMissiles)->GetMapRECTIndex().rightIndex + (*itlPlayerMissiles)->GetMapRECTIndex().bottomIndex * TILE_X;

		bool check = false;
		for (int i = 0; i < 4; i++)
		{
			if (tempRectIndex[i] >= 0 && tempRectIndex[i] < TILE_X * TILE_Y)
			{
				if (tileNumInfo[tempRectIndex[i]] == 1)
				{
					collisionMapIndex = tempRectIndex[i];
				}

				if (tileNumInfo[tempRectIndex[i]] != 0)
				{
					check = true;
				}
			}
		}

		if (check)
		{
			(*itlPlayerMissiles)->SetIsBoom(true);
			(*itlPlayerMissiles)->SetBoomPos((*itlPlayerMissiles)->GetPos());
			(*itlPlayerMissiles)->SetIsFired(false);
			itlPlayerMissiles = lPlayerMissiles.erase(itlPlayerMissiles);
		}
		else
		{
			itlPlayerMissiles++;
		}
	}
	*/
}

void CollisionCheck::enemyMoveCheck()
{
	// �� �浹�ڽ��� �� �浹 �ڽ��� �浹
	for(auto enemyIt : enemyData)
	{
		if (enemyIt->GetEnemyCurrDir() == 0)	//��
		{
			if ((enemyIt->GetEnemyFutureIndex().x - 1) < 0)
			{
				return;
			}
			else
			{
				enemyIt->SetEnemyCanMove(true);

				for (int y = enemyIt->GetEnemyFutureRectIndex().topIndex; y <= enemyIt->GetEnemyFutureRectIndex().bottomIndex; y++)
				{
					int tempID = ((int)(enemyIt->GetEnemyFutureIndex().x - 1) + (y * TILE_X));
					if (tileNumInfo[tempID] != 0)
					{
						enemyIt->SetEnemyCanMove(false);
					}
				}
			}
		}
		else if (enemyIt->GetEnemyCurrDir() == 1)	//��
		{
			if ((enemyIt->GetEnemyFutureIndex().x + 1) >= TILE_X)
			{
				return;
			}
			else
			{
				enemyIt->SetEnemyCanMove(true);

				for (int y = enemyIt->GetEnemyFutureRectIndex().topIndex; y <= enemyIt->GetEnemyFutureRectIndex().bottomIndex; y++)
				{
					int tempID = ((int)(enemyIt->GetEnemyFutureIndex().x + 1) + (y * TILE_X));
					if (tileNumInfo[tempID] != 0)
					{
						enemyIt->SetEnemyCanMove(false);
					}
				}
			}
		}
		else if (enemyIt->GetEnemyCurrDir() == 2)	//��
		{
			if ((enemyIt->GetEnemyFutureIndex().y - 1) < 0)
			{
				return;
			}
			else
			{
				enemyIt->SetEnemyCanMove(true);
				
				for (int x = enemyIt->GetEnemyFutureRectIndex().leftIndex; x <= enemyIt->GetEnemyFutureRectIndex().rightIndex; x++)
				{
					int tempID = (x + ((int)(enemyIt->GetEnemyFutureIndex().y - 1) * TILE_X));
					if (tileNumInfo[tempID] != 0)
					{
						enemyIt->SetEnemyCanMove(false);
					}
				}
			}
		}
		else if (enemyIt->GetEnemyCurrDir() == 3)	//��
		{
			if ((enemyIt->GetEnemyFutureIndex().y + 1) >= TILE_Y)
			{
				return;
			}
			else
			{
				enemyIt->SetEnemyCanMove(true);

				for (int x = enemyIt->GetEnemyFutureRectIndex().leftIndex; x <= enemyIt->GetEnemyFutureRectIndex().rightIndex; x++)
				{
					int tempID = (x + ((int)(enemyIt->GetEnemyFutureIndex().y + 1) * TILE_X));
					if (tileNumInfo[tempID] != 0)
					{
						enemyIt->SetEnemyCanMove(false);
					}
				}
			}
		}
	}
}

void CollisionCheck::Render(HDC hdc)
{
	// �� �浹 �ڽ� ���
	/*for (int i = 0; i < TILE_X * TILE_Y; i++)
	{
		if (tileNumInfo[i] != 0)
		{
			Rectangle(hdc,
				tileInfo[i].rcTile.left,
				tileInfo[i].rcTile.top,
				tileInfo[i].rcTile.right,
				tileInfo[i].rcTile.bottom);
		}
	}*/
	
	/*
	// �÷��̾� & �� �浹 �ڽ� ���
	//��
	if (playerCurrDir == 0)
	{
		if (playerIndex_X - 1 >= 0)
		{
			for (int y = playerFutureRectIndex.top; y <= playerFutureRectIndex.bottom; y++)
			{
				Rectangle(hdc,
					tileInfo[(playerIndex_X - 1) + (y * TILE_X)].rcTile.left,
					tileInfo[(playerIndex_X - 1) + (y * TILE_X)].rcTile.top,
					tileInfo[(playerIndex_X - 1) + (y * TILE_X)].rcTile.right,
					tileInfo[(playerIndex_X - 1) + (y * TILE_X)].rcTile.bottom);
			} 
		}
	}
	//��
	if (playerCurrDir == 1)
	{
		if (playerIndex_X + 1 < TILE_X)
		{
			for (int y = playerFutureRectIndex.top; y <= playerFutureRectIndex.bottom; y++)
			{
				Rectangle(hdc,
					tileInfo[(playerIndex_X + 1) + (y * TILE_X)].rcTile.left,
					tileInfo[(playerIndex_X + 1) + (y * TILE_X)].rcTile.top,
					tileInfo[(playerIndex_X + 1) + (y * TILE_X)].rcTile.right,
					tileInfo[(playerIndex_X + 1) + (y * TILE_X)].rcTile.bottom);
			}
		}
	}
	//��
	if (playerCurrDir == 2)
	{
		if (playerIndex_Y - 1 >= 0)
		{
			for (int x = playerFutureRectIndex.left; x <= playerFutureRectIndex.right; x++)
			{
				Rectangle(hdc,
					tileInfo[x + ((playerIndex_Y - 1) * TILE_X)].rcTile.left,
					tileInfo[x + ((playerIndex_Y - 1) * TILE_X)].rcTile.top,
					tileInfo[x + ((playerIndex_Y - 1) * TILE_X)].rcTile.right,
					tileInfo[x + ((playerIndex_Y - 1) * TILE_X)].rcTile.bottom);
			}
		}
	}
	//��
	if (playerCurrDir == 3)
	{
		if (playerIndex_Y + 1 < TILE_Y)
		{
			for (int x = playerFutureRectIndex.left; x <= playerFutureRectIndex.right; x++)
			{
				Rectangle(hdc,
					tileInfo[x + ((playerIndex_Y + 1) * TILE_X)].rcTile.left,
					tileInfo[x + ((playerIndex_Y + 1) * TILE_X)].rcTile.top,
					tileInfo[x + ((playerIndex_Y + 1) * TILE_X)].rcTile.right,
					tileInfo[x + ((playerIndex_Y + 1) * TILE_X)].rcTile.bottom);
			}
		}
	}

	// �� & �� �浹 �ڽ� ���
	for (auto e : enemyData)
	{
		//��
		if (e->GetEnemyCurrDir() == 0)
		{
			if (e->GetEnemyFutureIndex().x - 1 >= 0)
			{
				for (int y = e->GetEnemyFutureRectIndex().top; y <= e->GetEnemyFutureRectIndex().bottom; y++)
				{
					Rectangle(hdc,
						tileInfo[((int)(e->GetEnemyFutureIndex().x - 1) + (y * TILE_X))].rcTile.left,
						tileInfo[((int)(e->GetEnemyFutureIndex().x - 1) + (y * TILE_X))].rcTile.top,
						tileInfo[((int)(e->GetEnemyFutureIndex().x - 1) + (y * TILE_X))].rcTile.right,
						tileInfo[((int)(e->GetEnemyFutureIndex().x - 1) + (y * TILE_X))].rcTile.bottom);
				}
			}
		}
		//��
		if (e->GetEnemyCurrDir() == 1)
		{
			if (e->GetEnemyFutureIndex().x + 1 < TILE_X)
			{
				for (int y = e->GetEnemyFutureRectIndex().top; y <= e->GetEnemyFutureRectIndex().bottom; y++)
				{
					Rectangle(hdc,
						tileInfo[((int)(e->GetEnemyFutureIndex().x + 1) + (y * TILE_X))].rcTile.left,
						tileInfo[((int)(e->GetEnemyFutureIndex().x + 1) + (y * TILE_X))].rcTile.top,
						tileInfo[((int)(e->GetEnemyFutureIndex().x + 1) + (y * TILE_X))].rcTile.right,
						tileInfo[((int)(e->GetEnemyFutureIndex().x + 1) + (y * TILE_X))].rcTile.bottom);
				}
			}
		}
		//��
		if (e->GetEnemyCurrDir() == 2)
		{
			if (e->GetEnemyFutureIndex().y - 1 >= 0)
			{
				for (int x = e->GetEnemyFutureRectIndex().left; x <= e->GetEnemyFutureRectIndex().right; x++)
				{
					Rectangle(hdc,
						tileInfo[(x + ((int)(e->GetEnemyFutureIndex().y - 1) * TILE_X))].rcTile.left,
						tileInfo[(x + ((int)(e->GetEnemyFutureIndex().y - 1) * TILE_X))].rcTile.top,
						tileInfo[(x + ((int)(e->GetEnemyFutureIndex().y - 1) * TILE_X))].rcTile.right,
						tileInfo[(x + ((int)(e->GetEnemyFutureIndex().y - 1) * TILE_X))].rcTile.bottom);
				}
			}
		}
		//��
		if (e->GetEnemyCurrDir() == 3)
		{
			if (e->GetEnemyFutureIndex().y + 1 < TILE_Y)
			{
				for (int x = e->GetEnemyFutureRectIndex().left; x <= e->GetEnemyFutureRectIndex().right; x++)
				{
					int tempID = (x + ((int)(e->GetEnemyFutureIndex().y + 1) * TILE_X));
					Rectangle(hdc,
						tileInfo[tempID].rcTile.left,
						tileInfo[tempID].rcTile.top,
						tileInfo[tempID].rcTile.right,
						tileInfo[tempID].rcTile.bottom);
				}
			}
		}
	}

	// �÷��̾� �浹 �ڽ� ���
	Rectangle(hdc,
		playerRect->left,
		playerRect->top,
		playerRect->right,
		playerRect->bottom);

	// �� �浹 �ڽ� ���
	for (auto enemyIt : enemyData)
	{
		Rectangle(hdc,
			enemyIt->GetEnemyRect().left,
			enemyIt->GetEnemyRect().top,
			enemyIt->GetEnemyRect().right,
			enemyIt->GetEnemyRect().bottom);
	}

	// �̻��� �浹 �ڽ� ���
	for (itlPlayerMissiles = lPlayerMissiles.begin(); itlPlayerMissiles != lPlayerMissiles.end(); itlPlayerMissiles++)
	{
		Rectangle(hdc,
			(*itlPlayerMissiles)->GetAttackBox().left,
			(*itlPlayerMissiles)->GetAttackBox().top,
			(*itlPlayerMissiles)->GetAttackBox().right,
			(*itlPlayerMissiles)->GetAttackBox().bottom);
	}

	for (itlEnemyMissiles = lEnemyMissiles.begin(); itlEnemyMissiles != lEnemyMissiles.end(); itlEnemyMissiles++)
	{
		Rectangle(hdc,
			(*itlEnemyMissiles)->GetAttackBox().left,
			(*itlEnemyMissiles)->GetAttackBox().top,
			(*itlEnemyMissiles)->GetAttackBox().right,
			(*itlEnemyMissiles)->GetAttackBox().bottom);
	}
	*/
}
