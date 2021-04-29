#include "GameBoard.h"
#include "Image.h"

HRESULT GameBoard::Init()
{
	enemyIcon = ImageManager::GetSingleton()->AddImage("에너미 아이콘", "Image/Icon/Icon_Enemy.bmp", 8 * 3, 8 * 3);

	enemyNumberToKill = 6;

	enemyIconX = WINSIZE_X / 2 + 200;
	enemyIconY = 0;// WINSIZE_Y / 2;

	return S_OK;
}

void GameBoard::Release()
{
}

void GameBoard::Update()
{
}

void GameBoard::Render(HDC hdc)
{
	for (int i = 0; i < enemyNumberToKill; i++)
	{
		if (i == 0)
			enemyIconY = WINSIZE_Y / 2;
		else if (i % 2 == 0)
			enemyIconY += 30;

		enemyIcon->Render(hdc, enemyIconX + (30 * (i % 2)), enemyIconY);
	}
}
