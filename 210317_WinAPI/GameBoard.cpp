#include "GameBoard.h"
#include "Image.h"

HRESULT GameBoard::Init()
{
	ImageManager::GetSingleton()->AddImage("���ʹ� ������", "Image/Icon/Icon_Enemy.bmp", 8 * 3, 8 * 3);

	ImageManager::GetSingleton()->AddImage("�������� ������", "Image/Icon/StageFlag.bmp", 16*3, 16*3, true, RGB(255, 0, 255));

	ImageManager::GetSingleton()->AddImage("������ ������", "Image/Icon/player1Life.bmp", 16 * 3, 16 * 3, true, RGB(255, 0, 255));

	ImageManager::GetSingleton()->AddImage("Ÿ��Ʋ", "Image/Text/Title.bmp", 125 , 306, true , RGB(255, 0, 255));

	ImageManager::GetSingleton()->AddImage("����", "Image/Text/Number.bmp",40*3, 14*3,5,2,true,RGB(255,0,255));

	enemyNumberToKill = 20;
	stageNum = 12;
	life = 6;

	enemyIconX = WINSIZE_X -115;
	enemyIconY = 70;// WINSIZE_Y / 2;

	lifeIconX = WINSIZE_X - 115;
	lifeIconY = WINSIZE_Y - 150;

	flagIconX = WINSIZE_X - 110;
	flagIconY = WINSIZE_Y - 300;

	titleX = 30;
	titleY = 30;

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


	img = ImageManager::GetSingleton()->FindImage("�������� ������");
	img->Render(hdc,flagIconX, flagIconY);

	img = ImageManager::GetSingleton()->FindImage("����");
	img->FrameRender(hdc, flagIconX-5 , flagIconY + 50, (stageNum/10) % 5, (stageNum/10) / 5);
	img->FrameRender(hdc, flagIconX+25, flagIconY+50,(stageNum%10)%5,(stageNum%10)/5);

	img = ImageManager::GetSingleton()->FindImage("������ ������");
	img->Render(hdc, lifeIconX, lifeIconY);

	img = ImageManager::GetSingleton()->FindImage("����");
	img->FrameRender(hdc, lifeIconX + 30, lifeIconY + 25, life % 5, life / 5);


	for (int i = 0; i < enemyNumberToKill; i++)
	{
		if ((i / 2 == 0))	enemyIconY = 70;
		else if (i % 2 == 0)	enemyIconY += 30;

		img = ImageManager::GetSingleton()->FindImage("���ʹ� ������");
		img->Render(hdc, enemyIconX + (30 * (i % 2)), enemyIconY);
	}
}
