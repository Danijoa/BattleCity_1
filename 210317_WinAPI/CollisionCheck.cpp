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
	 futureIndexDiff_X = playerFutureRectIndex.right - playerFutureRectIndex.left;

	 playerFutureRectIndex.top = ((playerFuturePos.y - size / 2) - 50) / TILESIZE;
	 playerFutureRectIndex.bottom = ((playerFuturePos.y + size / 2) - 50) / TILESIZE;
	 futureIndexDiff_Y = playerFutureRectIndex.bottom - playerFutureRectIndex.top;

	//
	 //5playerMoveCheckThree();
}

void CollisionCheck::playerMoveCheckThree()
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
		//// 현재 플레이어 위치 오른 3개 확인
		//if (tileNumInfo[playerIndex_X + ((playerIndex_Y - 1) * TILE_X) + 1] != 0
		//	|| tileNumInfo[playerIndex_X + (playerIndex_Y * TILE_X) + 1] != 0
		//	|| tileNumInfo[playerIndex_X + ((playerIndex_Y + 1) * TILE_X) + 1] != 0)
		//{
		//	playerCanMoveRight = false;
		//}
		//else
		//{
		//	playerCanMoveRight = true;
		//}
	}
	else if (playerCurrDir == 2)	//상
	{
		if (playerIndex_Y - 1 < 0)
		{
			return;
		}
		else
		{

		}

		//// 현재 플레이어 위치 위 3개 확인
		//if (tileNumInfo[playerIndex_X + ((playerIndex_Y - 1) * TILE_X) - 1] != 0
		//	|| tileNumInfo[playerIndex_X + ((playerIndex_Y - 1) * TILE_X)] != 0
		//	|| tileNumInfo[playerIndex_X + (((playerIndex_Y - 1) + 1) * TILE_X) + 1] != 0)
		//{
		//	playerCanMoveUp = false;
		//}
		//else
		//{
		//	playerCanMoveUp = true;
		//}
	}
	else if (playerCurrDir == 3)	//하
	{
		if (playerIndex_Y + 1 >= TILE_Y)
		{
			return;
		}
		else
		{

		}
		//// 현재 플레이어 위치 아래 3개 확인
		//if (tileNumInfo[playerIndex_X + ((playerIndex_Y + 1) * TILE_X) - 1] != 0
		//	|| tileNumInfo[playerIndex_X + ((playerIndex_Y + 1) * TILE_X)] != 0
		//	|| tileNumInfo[playerIndex_X + (((playerIndex_Y + 1) + 1) * TILE_X) + 1] != 0)
		//{
		//	playerCanMoveDown = false;
		//}
		//else
		//{
		//	playerCanMoveDown = true;
		//}
	}
}

void CollisionCheck::playerMoveCheckTwo()
{}

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
			Rectangle(hdc,
				tileInfo[playerIndex_X + ((playerIndex_Y - 1) * TILE_X) - 1].rcTile.left,
				tileInfo[playerIndex_X + ((playerIndex_Y - 1) * TILE_X) - 1].rcTile.top,
				tileInfo[playerIndex_X + ((playerIndex_Y - 1) * TILE_X) - 1].rcTile.right,
				tileInfo[playerIndex_X + ((playerIndex_Y - 1) * TILE_X) - 1].rcTile.bottom);
			Rectangle(hdc,
				tileInfo[playerIndex_X + (playerIndex_Y * TILE_X) - 1].rcTile.left,
				tileInfo[playerIndex_X + (playerIndex_Y * TILE_X) - 1].rcTile.top,
				tileInfo[playerIndex_X + (playerIndex_Y * TILE_X) - 1].rcTile.right,
				tileInfo[playerIndex_X + (playerIndex_Y * TILE_X) - 1].rcTile.bottom);
			Rectangle(hdc,
				tileInfo[playerIndex_X + ((playerIndex_Y + 1) * TILE_X) - 1].rcTile.left,
				tileInfo[playerIndex_X + ((playerIndex_Y + 1) * TILE_X) - 1].rcTile.top,
				tileInfo[playerIndex_X + ((playerIndex_Y + 1) * TILE_X) - 1].rcTile.right,
				tileInfo[playerIndex_X + ((playerIndex_Y + 1) * TILE_X) - 1].rcTile.bottom);
		}
	}
	//우
	if (playerCurrDir == 1)
	{
		if (playerIndex_X + 1 < TILE_X)
		{
			Rectangle(hdc,
				tileInfo[playerIndex_X + ((playerIndex_Y - 1) * TILE_X) + 1].rcTile.left,
				tileInfo[playerIndex_X + ((playerIndex_Y - 1) * TILE_X) + 1].rcTile.top,
				tileInfo[playerIndex_X + ((playerIndex_Y - 1) * TILE_X) + 1].rcTile.right,
				tileInfo[playerIndex_X + ((playerIndex_Y - 1) * TILE_X) + 1].rcTile.bottom);
			Rectangle(hdc,
				tileInfo[playerIndex_X + (playerIndex_Y * TILE_X) + 1].rcTile.left,
				tileInfo[playerIndex_X + (playerIndex_Y * TILE_X) + 1].rcTile.top,
				tileInfo[playerIndex_X + (playerIndex_Y * TILE_X) + 1].rcTile.right,
				tileInfo[playerIndex_X + (playerIndex_Y * TILE_X) + 1].rcTile.bottom);
			Rectangle(hdc,
				tileInfo[playerIndex_X + ((playerIndex_Y + 1) * TILE_X) + 1].rcTile.left,
				tileInfo[playerIndex_X + ((playerIndex_Y + 1) * TILE_X) + 1].rcTile.top,
				tileInfo[playerIndex_X + ((playerIndex_Y + 1) * TILE_X) + 1].rcTile.right,
				tileInfo[playerIndex_X + ((playerIndex_Y + 1) * TILE_X) + 1].rcTile.bottom);
		}
	}
	//상
	if (playerCurrDir == 2)
	{
		if (playerIndex_Y - 1 >= 0)
		{
			Rectangle(hdc,
				tileInfo[playerIndex_X + ((playerIndex_Y - 1) * TILE_X) - 1].rcTile.left,
				tileInfo[playerIndex_X + ((playerIndex_Y - 1) * TILE_X) - 1].rcTile.top,
				tileInfo[playerIndex_X + ((playerIndex_Y - 1) * TILE_X) - 1].rcTile.right,
				tileInfo[playerIndex_X + ((playerIndex_Y - 1) * TILE_X) - 1].rcTile.bottom);
			Rectangle(hdc,
				tileInfo[playerIndex_X + ((playerIndex_Y - 1) * TILE_X)].rcTile.left,
				tileInfo[playerIndex_X + ((playerIndex_Y - 1) * TILE_X)].rcTile.top,
				tileInfo[playerIndex_X + ((playerIndex_Y - 1) * TILE_X)].rcTile.right,
				tileInfo[playerIndex_X + ((playerIndex_Y - 1) * TILE_X)].rcTile.bottom);
			Rectangle(hdc,
				tileInfo[playerIndex_X + ((playerIndex_Y - 1) * TILE_X) + 1].rcTile.left,
				tileInfo[playerIndex_X + ((playerIndex_Y - 1) * TILE_X) + 1].rcTile.top,
				tileInfo[playerIndex_X + ((playerIndex_Y - 1) * TILE_X) + 1].rcTile.right,
				tileInfo[playerIndex_X + ((playerIndex_Y - 1) * TILE_X) + 1].rcTile.bottom);
		}
	}
	//하
	if (playerCurrDir == 3)
	{
		if (playerIndex_Y + 1 < TILE_Y)
		{
			Rectangle(hdc,
				tileInfo[playerIndex_X + ((playerIndex_Y + 1) * TILE_X) - 1].rcTile.left,
				tileInfo[playerIndex_X + ((playerIndex_Y + 1) * TILE_X) - 1].rcTile.top,
				tileInfo[playerIndex_X + ((playerIndex_Y + 1) * TILE_X) - 1].rcTile.right,
				tileInfo[playerIndex_X + ((playerIndex_Y + 1) * TILE_X) - 1].rcTile.bottom);
			Rectangle(hdc,
				tileInfo[playerIndex_X + ((playerIndex_Y + 1) * TILE_X)].rcTile.left,
				tileInfo[playerIndex_X + ((playerIndex_Y + 1) * TILE_X)].rcTile.top,
				tileInfo[playerIndex_X + ((playerIndex_Y + 1) * TILE_X)].rcTile.right,
				tileInfo[playerIndex_X + ((playerIndex_Y + 1) * TILE_X)].rcTile.bottom);
			Rectangle(hdc,
				tileInfo[playerIndex_X + ((playerIndex_Y + 1) * TILE_X) + 1].rcTile.left,
				tileInfo[playerIndex_X + ((playerIndex_Y + 1) * TILE_X) + 1].rcTile.top,
				tileInfo[playerIndex_X + ((playerIndex_Y + 1) * TILE_X) + 1].rcTile.right,
				tileInfo[playerIndex_X + ((playerIndex_Y + 1) * TILE_X) + 1].rcTile.bottom);
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
