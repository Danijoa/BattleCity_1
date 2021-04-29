#include "TilemapTool.h"
#include "Image.h"
#include "CommonFunction.h"
#include "Button.h"

TILE_INFO TilemapTool::tileInfo[TILE_X * TILE_Y];
int TilemapTool::tileNumInfo[TILE_X * TILE_Y];

HRESULT TilemapTool::Init()
{
    SetClientRect(g_hWnd, TILEMAPTOOLSIZE_X, TILEMAPTOOLSIZE_Y);

    //확인용임//
    mainBlackBack = ImageManager::GetSingleton()->AddImage("블랙타일", "Image/mapImage(2).bmp", 624, 624);

    sampleTile = ImageManager::GetSingleton()->AddImage("샘플타일", "Image/Tile/SampleTile(2).bmp", 32 * 3, 32 * 3, SAMPLE_TILE_X, SAMPLE_TILE_Y, true, RGB(255, 0, 255));
   
    hSelectedBrush = (HBRUSH)GetStockObject(NULL_BRUSH);

    // 메인 공간 이미지 정보 저장
    for (int i = 0; i < TILE_Y; i++)
    {
        for (int j = 0; j < TILE_X; j++)
        {
            // 몇번째 프레임에 있는 이미지를 들고와서
            tileInfo[i * TILE_X + j].frameX = 3;
            tileInfo[i * TILE_X + j].frameY = 1;
            
            // 차례로 저장해주기
            tileInfo[i * TILE_X + j].rcTile.left = 200 + TILESIZE * j;
            tileInfo[i * TILE_X + j].rcTile.top = 50 + TILESIZE * i;
            tileInfo[i * TILE_X + j].rcTile.right = tileInfo[i * TILE_X + j].rcTile.left + TILESIZE;
            tileInfo[i * TILE_X + j].rcTile.bottom = tileInfo[i * TILE_X + j].rcTile.top + TILESIZE;
        }
    }

    // 메인 공간 이미지 번호 정보 저장
    for (int i = 0; i < TILE_Y; i++)
    {
        for (int j = 0; j < TILE_X; j++)
        {
            tileNumInfo[(i * TILE_X) + j] = 0;    // 초기화는 0 (지나 다닐 수 있는 길)
        }
    }

    // 샘플 공간 이미지 정보 저장
    for (int i = 0; i < SAMPLE_TILE_Y; i++)
	{
        for (int j = 0; j < SAMPLE_TILE_X; j++)
        {
            // 몇번째 프레임에 있는 이미지를 들고와서
            sampleTileInfo[i * SAMPLE_TILE_X + j].frameX = j;
            sampleTileInfo[i * SAMPLE_TILE_X + j].frameY = i;

            // 차례로 저장해주기
            //SetRect(&sampleTileInfo[i * SAMPLE_TILE_X + j].rcTile, , , , );
            sampleTileInfo[i * SAMPLE_TILE_X + j].rcTile.left = TILESIZE * j + (TILEMAPTOOLSIZE_X - sampleTile->GetWidth());
            sampleTileInfo[i * SAMPLE_TILE_X + j].rcTile.top = TILESIZE * i;
            sampleTileInfo[i * SAMPLE_TILE_X + j].rcTile.right = TILESIZE * j + (TILEMAPTOOLSIZE_X - sampleTile->GetWidth()) + TILESIZE;
            sampleTileInfo[i * SAMPLE_TILE_X + j].rcTile.bottom = TILESIZE * i + TILESIZE;
        }
	}

    // 샘플 공간 이미지 번호 정보 저장
    sampleTileInfo[0].num = 1;  //갈색 벽
    sampleTileInfo[1].num = 2;  //회색 + 흰 네모 타일
    sampleTileInfo[2].num = 3;  //풀
    sampleTileInfo[3].num = 4;  //빗금있는 회색
    sampleTileInfo[4].num = 5;  sampleTileInfo[5].num = 5;  sampleTileInfo[6].num = 5;  //물
    sampleTileInfo[7].num = 0;  //일반 길
    sampleTileInfo[8].num = 6;  sampleTileInfo[9].num = 6;      //독수리
    sampleTileInfo[10].num = 6;  sampleTileInfo[11].num = 6;    //독수리
    sampleTileInfo[12].num = 7;  sampleTileInfo[13].num = 7;     //독수리
    sampleTileInfo[14].num = 7;  sampleTileInfo[15].num = 7;    //깃발

    //UI button
    ImageManager::GetSingleton()->AddImage("저장버튼", "Image/saveButton.bmp", 85, 160, 1, 2, true, RGB(255, 255, 255));
    ImageManager::GetSingleton()->AddImage("불러오기버튼", "Image/loadButton.bmp", 85, 160, 1, 2);

    btnSave = new Button();
    btnSave->Init("저장버튼", TILEMAPTOOLSIZE_X - 400, TILEMAPTOOLSIZE_Y - 200);
    btnSave->SetFunc(Save, 0);

    btnLoad = new Button();
    btnLoad->Init("불러오기버튼", TILEMAPTOOLSIZE_X - 200, TILEMAPTOOLSIZE_Y - 200);
    btnLoad->SetFunc(Load, 0);

    ImageManager::GetSingleton()->AddImage("스테이지버튼", "Image/stageButton.bmp", 265, 160, 3, 2);

    btnStage = new Button();
    btnStage->Init("스테이지버튼", TILEMAPTOOLSIZE_X - 400, TILEMAPTOOLSIZE_Y - 100);
    //btnStage->SetFunc(Load, 0);

    return S_OK;
}

void TilemapTool::Release()
{
    SAFE_RELEASE(btnSave);
    SAFE_RELEASE(btnLoad);
    SAFE_RELEASE(btnStage);
}

void TilemapTool::Update()
{
    if (btnSave)
    {
        btnSave->SetCurrStageIndex(btnStage->GetCurrStageIndex());
        btnSave->Update();
    }
    if (btnLoad)
    {
        btnLoad->SetCurrStageIndex(btnStage->GetCurrStageIndex());
        btnLoad->Update();
    }
    if (btnStage)
    {
        btnStage->Update();
    }

    /*
    if (KeyManager::GetSingleton()->IsStayKeyDown(VK_CONTROL))
    {
        // 로드 기능 사용
        if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_F1))
            Load(1);
        else if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_F2))
            Load(2);
        else if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_F3))
            Load(3);
    }
    else
    {
        // 세이브 기능 사용
        if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_F1))
            Save(1);
        else if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_F2))
            Save(2);
        else if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_F3))
            Save(3);
    }
    */
    
    // 메인 영역 계산
    rcMain.left = 200;
    rcMain.top = 50;
    rcMain.right = rcMain.left + (TILESIZE * TILE_X);
    rcMain.bottom = rcMain.top + (TILESIZE * TILE_Y);

    // 샘플 영역 계산
    rcSample.left = TILEMAPTOOLSIZE_X - sampleTile->GetWidth();
    rcSample.top = 0;
    rcSample.right = TILEMAPTOOLSIZE_X;
    rcSample.bottom = sampleTile->GetHeight();

    // 메인 영역 클릭 다운
    if (PtInRect(&rcMain, g_ptMouse))
    {
        if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_LBUTTON)
            || KeyManager::GetSingleton()->IsStayKeyDown(VK_LBUTTON))
        {
			for (int i = 0; i < TILE_X * TILE_Y; i++)
			{
                if (PtInRect(&(tileInfo[i].rcTile), g_ptMouse))
                {
                    tileInfo[i].frameX = ptStartSelectedFrame.x;
                    tileInfo[i].frameY = ptStartSelectedFrame.y;

                    tileNumInfo[i] = sampleTileInfo[ptStartSelectedFrame.x + (SAMPLE_TILE_X * ptStartSelectedFrame.y)].num;

                    for (int j = 0; j <= ptEndSelectedFrame.y - ptStartSelectedFrame.y; j++)
                    {
                        for (int k = 0; k <= ptEndSelectedFrame.x - ptStartSelectedFrame.x; k++)
                        { 
                            if ((i % TILE_X) + k >= TILE_X) continue;
                            if ((i / TILE_X) + j >= TILE_Y) continue;

                            tileInfo[i + (k + j * TILE_X)].frameX = ptStartSelectedFrame.x + k;
                            tileInfo[i + (k + j * TILE_X)].frameY = ptStartSelectedFrame.y + j;

                            tileNumInfo[i + (k + j * TILE_X)] = 
                                sampleTileInfo[ptStartSelectedFrame.x + (SAMPLE_TILE_X * ptStartSelectedFrame.y)].num;
                        }
                    }

					break;
				}
			}
        }
    }

    // 샘플 영역 드래그
	else if (PtInRect(&rcSample, g_ptMouse))
	{
		// 1) 모든 파일 반복하면서 rect 충돌 확인
		/*// 다운
		if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_LBUTTON))
		{
			for (int i = 0; i < SAMPLE_TILE_X * SAMPLE_TILE_Y; i++) //이때 i는 마우스가 클릭된 위치의 범위 안의 RECT 인덱스를 가리킴
			{
				if (PtInRect(&(sampleTileInfo[i].rcTile), g_ptMouse))
				{
					ptStartSelectedFrame.x = i % SAMPLE_TILE_X;
					ptStartSelectedFrame.y = i / SAMPLE_TILE_X;

					break;
				}
			}
		}*/ 

        // 2) 마우스 좌표로 인덱스 계산
        // 다운
        if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_LBUTTON))
        {
			int posX = g_ptMouse.x - rcSample.left;
			int posY = g_ptMouse.y - rcSample.top;
			ptStartSelectedFrame.x = posX / TILESIZE;
			ptStartSelectedFrame.y = posY / TILESIZE;

            ptSelected[0] = g_ptMouse;
		}
		// 업
        else if (KeyManager::GetSingleton()->IsOnceKeyUp(VK_LBUTTON))
        {
            int posX = g_ptMouse.x - rcSample.left;
            int posY = g_ptMouse.y - rcSample.top;
            ptEndSelectedFrame.x = posX / TILESIZE;
            ptEndSelectedFrame.y = posY / TILESIZE;

            ptSelected[0].x = -1;
            ptSelected[0].y = -1;
            ptSelected[1].x = -1;
            ptSelected[1].y = -1;
        }
		else if (KeyManager::GetSingleton()->IsStayKeyDown(VK_LBUTTON))
		{
			ptSelected[1] = g_ptMouse;
		}
	}
}

void TilemapTool::Render(HDC hdc)
{
    // 뒤에 흰 바탕으로 칠하기
    PatBlt(hdc, 0, 0, TILEMAPTOOLSIZE_X, TILEMAPTOOLSIZE_Y, WHITENESS);

    //확인용//
    mainBlackBack->Render(hdc, 200, 50);

    // 샘플 타일 전체 출력
    sampleTile->Render(hdc, TILEMAPTOOLSIZE_X - sampleTile->GetWidth(), 0);

    // 선택 영역 표시
    hOldSelectedBrush = (HBRUSH)SelectObject(hdc, hSelectedBrush);
    Rectangle(hdc, ptSelected[0].x, ptSelected[0].y, ptSelected[1].x, ptSelected[1].y);
    SelectObject(hdc, hOldSelectedBrush);

    //ui button
    if (btnSave)
        btnSave->Render(hdc);
    if (btnLoad)
       btnLoad->Render(hdc);
    if (btnStage)
        btnStage->Render(hdc);

    // 메인 타일 출력
    for (int i = 0; i < TILE_X * TILE_Y; i++)
    {
        sampleTile->FrameRender(hdc,
            tileInfo[i].rcTile.left,
            tileInfo[i].rcTile.top,
            tileInfo[i].frameX,
            tileInfo[i].frameY);
    }

    // 선택된 타일 3배 출력
    if (ptStartSelectedFrame.x == ptEndSelectedFrame.x
        && ptStartSelectedFrame.y == ptEndSelectedFrame.y)
    {
        sampleTile->FrameRender(hdc,
            TILEMAPTOOLSIZE_X - sampleTile->GetWidth(),
            sampleTile->GetHeight() + 50,
            ptStartSelectedFrame.x,
            ptStartSelectedFrame.y,
            false, 3);
    }
    // 드래그 출력
    else
    {
        for (int i = 0; i <= ptEndSelectedFrame.y - ptStartSelectedFrame.y; i++)
        {
            for (int j = 0; j <= ptEndSelectedFrame.x - ptStartSelectedFrame.x; j++)
            {
                sampleTile->FrameRender(hdc,
                    TILEMAPTOOLSIZE_X - sampleTile->GetWidth() + (j * TILESIZE),
                    sampleTile->GetHeight() + 50 + (i * TILESIZE),
                    ptStartSelectedFrame.x + j,
                    ptStartSelectedFrame.y + i,
                    false, 1);
            }
        }
    }

    //맵 이미지 번호 출력 확인용//
    for (int i = 0; i < TILE_Y; i++)
    {
        for (int j = 0; j < TILE_X; j++)
        {
            wsprintf(szText, "%d", tileNumInfo[(i * TILE_X) + j]);
            TextOut(hdc, j * 50, i * 20, szText, strlen(szText));
        }
    }
}

void TilemapTool::Save(int stageNum)
{
    //맵 이미지 save
    string fileName = "Save/saveMapData";
    fileName += to_string(stageNum) + ".map";

	//파일 이름에, 쓸것이다, 공유는 안하고, 보안, 항상 생성하고, 일반 파일로 생성할 것이며, 템플릿 머시기는 그냥 널 넣어두자
    HANDLE hFile = CreateFile(fileName.c_str(), GENERIC_WRITE, 0, 0, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL); //.c_str()
    
    DWORD writtenBytes;

	WriteFile(hFile, tileInfo, sizeof(TILE_INFO) * TILE_X * TILE_Y, &writtenBytes, NULL);   //viod*는 어떤 자료형이든 값으로 받을 수 있다

	CloseHandle(hFile);

    //맵 이미지 번호 save
    string fileNumName = "Save/saveMapNumData";
    fileNumName += to_string(stageNum) + ".map";
    HANDLE hFileNum = CreateFile(fileNumName.c_str(), GENERIC_WRITE, 0, 0, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL); 
    WriteFile(hFileNum, tileNumInfo, sizeof(int) * TILE_X * TILE_Y, &writtenBytes, NULL); 
    CloseHandle(hFileNum);
}

void TilemapTool::Load(int stageNum)
{
    //맵 이미지 load
    string fileName = "Save/saveMapData";
    fileName += to_string(stageNum) + ".map";

	HANDLE hFile = CreateFile(fileName.c_str(), GENERIC_READ, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

    DWORD readBytes;

    if (ReadFile(hFile, tileInfo, sizeof(TILE_INFO) * TILE_X * TILE_Y, &readBytes, NULL)) {}
	else
		MessageBox(g_hWnd, "저장파일 로드 실패", "실패", MB_OK);

	CloseHandle(hFile);

    //맵 이미지 번호 load
    string fileNumName = "Save/saveMapNumData";
    fileNumName += to_string(stageNum) + ".map";
    HANDLE hFileNum = CreateFile(fileNumName.c_str(), GENERIC_READ, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (ReadFile(hFileNum, tileNumInfo, sizeof(int) * TILE_X * TILE_Y, &readBytes, NULL)) {}
    else
        MessageBox(g_hWnd, "번호 저장파일 로드 실패", "실패", MB_OK);
    CloseHandle(hFileNum);
}
