#include "CollisionCheck.h"
#include "Enemy.h"

HRESULT CollisionCheck::Init()
{
	tileNumInfo = new int();
	tileInfo = new TILE_INFO();
	
	size = 40;
	
	playerFuturePos = {0, 0};
	playerCurrDir = -1;
	playerCanMove = true;


    return E_NOTIMPL;
}

void CollisionCheck::Release()
{
}

void CollisionCheck::Update()
{
	// tileNumInfo와 tileInfo 상에서 플레이어 (future)인덱스 위치
	findPlayerFutureData();
	// 플레이어 움직임 충돌 체크
	playerMoveCheck();

	// 적 움직임 충돌 체크
	enemyMoveCheck();
}

void CollisionCheck::findPlayerFutureData()
{
	// 맵 상에 있는 플레이어가 움직일 위치의 인덱스
	playerIndex_X = (playerFuturePos.x - 200) / TILESIZE;
	playerIndex_Y = (playerFuturePos.y - 50) / TILESIZE;

	// 맵 상에 있는 플레이어가 움직일 위치의 인덱스
	playerFutureRectIndex.left = ((playerFuturePos.x - size / 2) - 200) / TILESIZE;
	playerFutureRectIndex.right = ((playerFuturePos.x + size / 2) - 200) / TILESIZE;

	playerFutureRectIndex.top = ((playerFuturePos.y - size / 2) - 50) / TILESIZE;
	playerFutureRectIndex.bottom = ((playerFuturePos.y + size / 2) - 50) / TILESIZE;
}

void CollisionCheck::playerMoveCheck()
{
	// 플레이어 충돌박스랑 맵 충돌 박스랑 충돌
	if (playerCurrDir == 0)			//좌
	{
		if ((playerIndex_X - 1) < 0)
		{
			return;
		}
		else
		{
			playerCanMove = true;
			for (int y = playerFutureRectIndex.top; y <= playerFutureRectIndex.bottom; y++)
			{
				if (tileNumInfo[(playerIndex_X - 1) + (y * TILE_X)] != 0)
				{
					playerCanMove = false;
				}
			}
		}
	}
	else if (playerCurrDir == 1)	//우
	{
		if ((playerIndex_X + 1) >= TILE_X)
		{
			return;
		}
		else
		{
			playerCanMove = true;
			for (int y = playerFutureRectIndex.top; y <= playerFutureRectIndex.bottom; y++)
			{
				if (tileNumInfo[(playerIndex_X + 1) + (y * TILE_X)] != 0)
				{
					playerCanMove = false;
				}
			}
		}
	}
	else if (playerCurrDir == 2)	//상
	{
		if (playerIndex_Y - 1 < 0)
		{
			return;
		}
		else
		{
			playerCanMove = true;
			for (int x = playerFutureRectIndex.left; x <= playerFutureRectIndex.right; x++)
			{
				if (tileNumInfo[x + ((playerIndex_Y - 1) * TILE_X)] != 0)
				{
					playerCanMove = false;
				}
			}
		}
	}
	else if (playerCurrDir == 3)	//하
	{
		if (playerIndex_Y + 1 >= TILE_Y)
		{
			return;
		}
		else
		{
			playerCanMove = true;
			for (int x = playerFutureRectIndex.left; x <= playerFutureRectIndex.right; x++)
			{
				if (tileNumInfo[x + ((playerIndex_Y + 1) * TILE_X)] != 0)
				{
					playerCanMove = false;
				}
			}
		}
	}
}

void CollisionCheck::enemyMoveCheck()
{
	// 적 충돌박스랑 맵 충돌 박스랑 충돌
	for(auto enemyIt : enemyData)
	{
		if (enemyIt->GetEnemyCurrDir() == 0)	//좌
		{
			if ((enemyIt->GetEnemyFutureIndex().x - 1) < 0)
			{
				return;
			}
			else
			{
				enemyIt->SetEnemyCanMove(true);

				for (int y = enemyIt->GetEnemyFutureRectIndex().top; y <= enemyIt->GetEnemyFutureRectIndex().bottom; y++)
				{
					int tempID = ((int)(enemyIt->GetEnemyFutureIndex().x - 1) + (y * TILE_X));
					if (tileNumInfo[tempID] != 0)
					{
						enemyIt->SetEnemyCanMove(false);
					}
				}
			}
		}
		else if (enemyIt->GetEnemyCurrDir() == 1)	//우
		{
			if ((enemyIt->GetEnemyFutureIndex().x + 1) >= TILE_X)
			{
				return;
			}
			else
			{
				enemyIt->SetEnemyCanMove(true);

				for (int y = enemyIt->GetEnemyFutureRectIndex().top; y <= enemyIt->GetEnemyFutureRectIndex().bottom; y++)
				{
					int tempID = ((int)(enemyIt->GetEnemyFutureIndex().x + 1) + (y * TILE_X));
					if (tileNumInfo[tempID] != 0)
					{
						enemyIt->SetEnemyCanMove(false);
					}
				}
			}
		}
		else if (enemyIt->GetEnemyCurrDir() == 2)	//상
		{
			if ((enemyIt->GetEnemyFutureIndex().y - 1) < 0)
			{
				return;
			}
			else
			{
				enemyIt->SetEnemyCanMove(true);

				for (int x = enemyIt->GetEnemyFutureRectIndex().left; x <= enemyIt->GetEnemyFutureRectIndex().right; x++)
				{
					int tempID = (x + ((int)(enemyIt->GetEnemyFutureIndex().y - 1) * TILE_X));
					if (tileNumInfo[tempID] != 0)
					{
						enemyIt->SetEnemyCanMove(false);
					}
				}
			}
		}
		else if (enemyIt->GetEnemyCurrDir() == 3)	//하
		{
			if ((enemyIt->GetEnemyFutureIndex().y + 1) >= TILE_Y)
			{
				return;
			}
			else
			{
				enemyIt->SetEnemyCanMove(true);

				for (int x = enemyIt->GetEnemyFutureRectIndex().left; x <= enemyIt->GetEnemyFutureRectIndex().right; x++)
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
	// 맵 충돌 박스 출력
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
	
	// 플레이어 & 맵 충돌 박스 출력
	//좌
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
	//우
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
	//상
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
	//하
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

	// 적 & 맵 충돌 박스 출력
	for (auto e : enemyData)
	{
		//좌
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
		//우
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
		//상
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
		//하
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

	// 플레이어 충돌 박스 출력
	Rectangle(hdc,
		playerRect->left,
		playerRect->top,
		playerRect->right,
		playerRect->bottom);

	// 적 충돌 박스 출력
	for (auto enemyIt : enemyData)
	{
		Rectangle(hdc,
			enemyIt->GetEnemyRect().left,
			enemyIt->GetEnemyRect().top,
			enemyIt->GetEnemyRect().right,
			enemyIt->GetEnemyRect().bottom);
	}

	// 미사일 충돌 박스 출력
}
