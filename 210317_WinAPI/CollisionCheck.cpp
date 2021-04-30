#include "CollisionCheck.h"

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
	// tileNumInfo와 tileInfo 상에서 플레이어 인덱스 위치
	 playerIndex_X = (playerFuturePos.x - 200) / TILESIZE;
	 playerIndex_Y = (playerFuturePos.y - 50) / TILESIZE;

	 playerFutureRectIndex.left = ((playerFuturePos.x - size / 2) - 200) / TILESIZE;
	 playerFutureRectIndex.right = ((playerFuturePos.x + size / 2) - 200) / TILESIZE;

	 playerFutureRectIndex.top = ((playerFuturePos.y - size / 2) - 50) / TILESIZE;
	 playerFutureRectIndex.bottom = ((playerFuturePos.y + size / 2) - 50) / TILESIZE;

	//
	 playerMoveCheck();
}

void CollisionCheck::playerMoveCheck()
{
	// 플레이어 충돌박스랑 충돌 박스랑 충돌
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

	// 플레이어 충돌 박스 출력
	Rectangle(hdc,
		playerRect->left,
		playerRect->top,
		playerRect->right,
		playerRect->bottom);

	// 적 충돌 박스 출력

	// 미사일 충돌 박스 출력
}
