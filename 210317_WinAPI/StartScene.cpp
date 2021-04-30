#include "StartScene.h"
#include "Image.h"

HRESULT StartScene::Init()
{
	backGround = ImageManager::GetSingleton()->AddImage("시작메뉴", "Image/TitleMenu.bmp", 512*3,240*3,2,1);
	Arrow = ImageManager::GetSingleton()->FindImage("플레이어 탱크");

	menuPos.x = ((WINSIZE_X / 2) - (backGround->GetWidth() / 4));
	menuPos.y = 0;

	arrowPos.x = (WINSIZE_X / 2)-180;
	arrowPos.y = (WINSIZE_Y / 2)+35;

	elapsedTime = 0;
	frame = 6;
	selectFrame = 0;
	return S_OK;
}

void StartScene::Release()
{
}

void StartScene::Update()
{
	elapsedTime += TimerManager::GetSingleton()->GetElapsedTime();
	if (elapsedTime >= 0.1f)
	{
		frame++;
		if (frame > 7)
		{
			frame = 6;
		}
		elapsedTime = 0;
	}

	if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_UP))
	{
		selectFrame = 0;
		arrowPos.y = (WINSIZE_Y / 2) + 35;
	}

	else if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_DOWN))
	{
		selectFrame = 1;
		arrowPos.y = (WINSIZE_Y / 2) + 80;
	}
}

void StartScene::Render(HDC hdc)
{
	backGround->FrameRender(hdc, menuPos.x, menuPos.y, selectFrame, 0);
	Arrow->FrameRender(hdc, arrowPos.x, arrowPos.y,frame, 0);
}
