#include "MainGame.h" 
#include "Image.h"
#include "BattleScene.h"
#include "TilemapTool.h"
#include "StartScene.h"

HRESULT MainGame::Init()
{
	hdc = GetDC(g_hWnd);

	KeyManager::GetSingleton()->Init();
	ImageManager::GetSingleton()->Init();
	SceneManager::GetSingleton()->Init();

	ImageManager::GetSingleton()->AddImage("아래미사일",
		"Image/Bullet/Missile_Down.bmp", 6, 8, true, RGB(255, 0, 255));
	ImageManager::GetSingleton()->AddImage("위미사일",
		"Image/Bullet/Missile_Up.bmp", 6, 8, true, RGB(255, 0, 255));
	ImageManager::GetSingleton()->AddImage("왼쪽미사일",
		"Image/Bullet/Missile_Left.bmp", 8, 6, true, RGB(255, 0, 255));
	ImageManager::GetSingleton()->AddImage("오른쪽미사일",
		"Image/Bullet/Missile_Right.bmp", 8, 6, true, RGB(255, 0, 255));

	ImageManager::GetSingleton()->AddImage("미사일폭발",
		"Image/Effect/Boom_Effect.bmp", 48*2, 16*2,3,1, true, RGB(255, 0, 255));

	ImageManager::GetSingleton()->AddImage("플레이어 탱크",
		"Image/Player/Player.bmp", 8 * 24 * 2, 4 * 24 * 2, 8, 4, true, RGB(255, 0, 255));//512*256


	// 메인게임의 초기화 함수
	//hTimer = (HANDLE)SetTimer(g_hWnd, 0, 1, NULL);

	// 백버퍼 이미지
	int maxWidth, maxHeight;
	maxWidth = max(WINSIZE_X, TILEMAPTOOLSIZE_X);
	maxHeight = max(WINSIZE_Y, TILEMAPTOOLSIZE_Y);

	backBuffer = new Image();
	backBuffer->Init(maxWidth, maxHeight);
	
	// 키와 씬 저장
	SceneManager::GetSingleton()->AddScene("전투_1", new BattleScene());
	SceneManager::GetSingleton()->AddScene("타일맵툴", new TilemapTool());
	SceneManager::GetSingleton()->AddScene("시작메뉴", new StartScene());
	
	// 첫 씬 init
	SceneManager::GetSingleton()->ChangeScene("전투_1");
	//SceneManager::GetSingleton()->ChangeScene("타일맵툴");
	//SceneManager::GetSingleton()->ChangeScene("시작메뉴");

	isInited = true;

	return S_OK;
}

void MainGame::Release()
{
	KeyManager::GetSingleton()->Release();
	ImageManager::GetSingleton()->Release(); 
	SceneManager::GetSingleton()->Release();

	SAFE_RELEASE(backBuffer);
	ReleaseDC(g_hWnd, hdc);
}

void MainGame::Update()
{
	SceneManager::GetSingleton()->Update();
}

void MainGame::Render()
{
	HDC hBackDC = backBuffer->GetMemDC();

	SceneManager::GetSingleton()->Render(hBackDC);

	// 인사
	TextOut(hBackDC, 20, 20, "MainGame 렌더 중", strlen("MainGame 렌더 중"));
	// 마우스 좌표
	wsprintf(szText, "X : %d, Y : %d", g_ptMouse.x, g_ptMouse.y);
	TextOut(hBackDC, 200, 20, szText, strlen(szText));
	// FPS
	TimerManager::GetSingleton()->Render(hBackDC);

	backBuffer->Render(hdc);
}

LRESULT MainGame::MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	switch (iMessage)
	{
	case WM_CREATE:
		break;
	case WM_LBUTTONDOWN:
		g_ptMouse.x = LOWORD(lParam);
		g_ptMouse.y = HIWORD(lParam);
		break;
	case WM_LBUTTONUP:
		g_ptMouse.x = LOWORD(lParam);
		g_ptMouse.y = HIWORD(lParam);
		break;
	case WM_RBUTTONDOWN:
		break;
	case WM_MOUSEMOVE:
		g_ptMouse.x = LOWORD(lParam);
		g_ptMouse.y = HIWORD(lParam);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}

	return DefWindowProc(hWnd, iMessage, wParam, lParam);
}

MainGame::MainGame()
{
	isInited = false;
}

MainGame::~MainGame()
{
}
