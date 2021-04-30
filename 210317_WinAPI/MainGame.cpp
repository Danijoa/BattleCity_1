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

	ImageManager::GetSingleton()->AddImage("�Ʒ��̻���",
		"Image/Bullet/Missile_Down.bmp", 6, 8, true, RGB(255, 0, 255));
	ImageManager::GetSingleton()->AddImage("���̻���",
		"Image/Bullet/Missile_Up.bmp", 6, 8, true, RGB(255, 0, 255));
	ImageManager::GetSingleton()->AddImage("���ʹ̻���",
		"Image/Bullet/Missile_Left.bmp", 8, 6, true, RGB(255, 0, 255));
	ImageManager::GetSingleton()->AddImage("�����ʹ̻���",
		"Image/Bullet/Missile_Right.bmp", 8, 6, true, RGB(255, 0, 255));

	ImageManager::GetSingleton()->AddImage("�̻�������",
		"Image/Effect/Boom_Effect.bmp", 48*2, 16*2,3,1, true, RGB(255, 0, 255));

	ImageManager::GetSingleton()->AddImage("�÷��̾� ��ũ",
		"Image/Player/Player.bmp", 8 * 24 * 2, 4 * 24 * 2, 8, 4, true, RGB(255, 0, 255));//512*256


	// ���ΰ����� �ʱ�ȭ �Լ�
	//hTimer = (HANDLE)SetTimer(g_hWnd, 0, 1, NULL);

	// ����� �̹���
	int maxWidth, maxHeight;
	maxWidth = max(WINSIZE_X, TILEMAPTOOLSIZE_X);
	maxHeight = max(WINSIZE_Y, TILEMAPTOOLSIZE_Y);

	backBuffer = new Image();
	backBuffer->Init(maxWidth, maxHeight);
	
	// Ű�� �� ����
	SceneManager::GetSingleton()->AddScene("����_1", new BattleScene());
	SceneManager::GetSingleton()->AddScene("Ÿ�ϸ���", new TilemapTool());
	SceneManager::GetSingleton()->AddScene("���۸޴�", new StartScene());
	
	// ù �� init
	SceneManager::GetSingleton()->ChangeScene("����_1");
	//SceneManager::GetSingleton()->ChangeScene("Ÿ�ϸ���");
	//SceneManager::GetSingleton()->ChangeScene("���۸޴�");

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

	// �λ�
	TextOut(hBackDC, 20, 20, "MainGame ���� ��", strlen("MainGame ���� ��"));
	// ���콺 ��ǥ
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
