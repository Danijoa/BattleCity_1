// config.h

#pragma once
#pragma comment(lib, "Winmm.lib")

#include <Windows.h>
#include <string>
#include <ctime>
#include <bitset>
#include <map>
#include <list>
#include <vector>

using namespace std;

#include "KeyManager.h"
#include "ImageManager.h"
#include "TimerManager.h"
#include "SceneManager.h"

//น่ฦฒ
#define WINSIZE_X	1000
#define WINSIZE_Y	720
//
#define TILEMAPTOOLSIZE_X 1440
#define TILEMAPTOOLSIZE_Y 720
//
#define TILESIZE 24
#define TILE_X 26
#define TILE_Y 26

#define PI			3.141592f
#define DegToRad(x)	((x) * PI / 180.0f)
#define SAFE_DELETE(p) { if (p) { delete p; p = nullptr; } }
#define SAFE_RELEASE(p) { if (p) { p->Release(); delete p; p = nullptr; } }

typedef struct tagFPoint
{
	float x;
	float y;
} FPOINT, *PFPOINT;

typedef struct tagTile
{
	RECT rcTile;
	int frameX;
	int frameY;
	int num;
} TILE_INFO;

//typedef tagFPoint FPOINT2;
//typedef tagFPoint* PFPOINT2;

extern HWND g_hWnd;
extern HINSTANCE g_hInstance;
extern POINT g_ptMouse;