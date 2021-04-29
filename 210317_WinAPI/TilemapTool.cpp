#include "TilemapTool.h"
#include "Image.h"
#include "CommonFunction.h"
#include "Button.h"

TILE_INFO TilemapTool::tileInfo[TILE_X * TILE_Y];
int TilemapTool::tileNumInfo[TILE_X * TILE_Y];

HRESULT TilemapTool::Init()
{
    SetClientRect(g_hWnd, TILEMAPTOOLSIZE_X, TILEMAPTOOLSIZE_Y);

    //Ȯ�ο���//
    mainBlackBack = ImageManager::GetSingleton()->AddImage("��Ÿ��", "Image/mapImage(2).bmp", 624, 624);

    sampleTile = ImageManager::GetSingleton()->AddImage("����Ÿ��", "Image/Tile/SampleTile(2).bmp", 32 * 3, 32 * 3, SAMPLE_TILE_X, SAMPLE_TILE_Y, true, RGB(255, 0, 255));
   
    hSelectedBrush = (HBRUSH)GetStockObject(NULL_BRUSH);

    // ���� ���� �̹��� ���� ����
    for (int i = 0; i < TILE_Y; i++)
    {
        for (int j = 0; j < TILE_X; j++)
        {
            // ���° �����ӿ� �ִ� �̹����� ���ͼ�
            tileInfo[i * TILE_X + j].frameX = 3;
            tileInfo[i * TILE_X + j].frameY = 1;
            
            // ���ʷ� �������ֱ�
            tileInfo[i * TILE_X + j].rcTile.left = 200 + TILESIZE * j;
            tileInfo[i * TILE_X + j].rcTile.top = 50 + TILESIZE * i;
            tileInfo[i * TILE_X + j].rcTile.right = tileInfo[i * TILE_X + j].rcTile.left + TILESIZE;
            tileInfo[i * TILE_X + j].rcTile.bottom = tileInfo[i * TILE_X + j].rcTile.top + TILESIZE;
        }
    }

    // ���� ���� �̹��� ��ȣ ���� ����
    for (int i = 0; i < TILE_Y; i++)
    {
        for (int j = 0; j < TILE_X; j++)
        {
            tileNumInfo[(i * TILE_X) + j] = 0;    // �ʱ�ȭ�� 0 (���� �ٴ� �� �ִ� ��)
        }
    }

    // ���� ���� �̹��� ���� ����
    for (int i = 0; i < SAMPLE_TILE_Y; i++)
	{
        for (int j = 0; j < SAMPLE_TILE_X; j++)
        {
            // ���° �����ӿ� �ִ� �̹����� ���ͼ�
            sampleTileInfo[i * SAMPLE_TILE_X + j].frameX = j;
            sampleTileInfo[i * SAMPLE_TILE_X + j].frameY = i;

            // ���ʷ� �������ֱ�
            //SetRect(&sampleTileInfo[i * SAMPLE_TILE_X + j].rcTile, , , , );
            sampleTileInfo[i * SAMPLE_TILE_X + j].rcTile.left = TILESIZE * j + (TILEMAPTOOLSIZE_X - sampleTile->GetWidth());
            sampleTileInfo[i * SAMPLE_TILE_X + j].rcTile.top = TILESIZE * i;
            sampleTileInfo[i * SAMPLE_TILE_X + j].rcTile.right = TILESIZE * j + (TILEMAPTOOLSIZE_X - sampleTile->GetWidth()) + TILESIZE;
            sampleTileInfo[i * SAMPLE_TILE_X + j].rcTile.bottom = TILESIZE * i + TILESIZE;
        }
	}

    // ���� ���� �̹��� ��ȣ ���� ����
    sampleTileInfo[0].num = 1;  //���� ��
    sampleTileInfo[1].num = 2;  //ȸ�� + �� �׸� Ÿ��
    sampleTileInfo[2].num = 3;  //Ǯ
    sampleTileInfo[3].num = 4;  //�����ִ� ȸ��
    sampleTileInfo[4].num = 5;  sampleTileInfo[5].num = 5;  sampleTileInfo[6].num = 5;  //��
    sampleTileInfo[7].num = 0;  //�Ϲ� ��
    sampleTileInfo[8].num = 6;  sampleTileInfo[9].num = 6;      //������
    sampleTileInfo[10].num = 6;  sampleTileInfo[11].num = 6;    //������
    sampleTileInfo[12].num = 7;  sampleTileInfo[13].num = 7;     //������
    sampleTileInfo[14].num = 7;  sampleTileInfo[15].num = 7;    //���

    //UI button
    ImageManager::GetSingleton()->AddImage("�����ư", "Image/saveButton.bmp", 85, 160, 1, 2, true, RGB(255, 255, 255));
    ImageManager::GetSingleton()->AddImage("�ҷ������ư", "Image/loadButton.bmp", 85, 160, 1, 2);

    btnSave = new Button();
    btnSave->Init("�����ư", TILEMAPTOOLSIZE_X - 400, TILEMAPTOOLSIZE_Y - 200);
    btnSave->SetFunc(Save, 0);

    btnLoad = new Button();
    btnLoad->Init("�ҷ������ư", TILEMAPTOOLSIZE_X - 200, TILEMAPTOOLSIZE_Y - 200);
    btnLoad->SetFunc(Load, 0);

    ImageManager::GetSingleton()->AddImage("����������ư", "Image/stageButton.bmp", 265, 160, 3, 2);

    btnStage = new Button();
    btnStage->Init("����������ư", TILEMAPTOOLSIZE_X - 400, TILEMAPTOOLSIZE_Y - 100);
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
        // �ε� ��� ���
        if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_F1))
            Load(1);
        else if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_F2))
            Load(2);
        else if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_F3))
            Load(3);
    }
    else
    {
        // ���̺� ��� ���
        if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_F1))
            Save(1);
        else if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_F2))
            Save(2);
        else if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_F3))
            Save(3);
    }
    */
    
    // ���� ���� ���
    rcMain.left = 200;
    rcMain.top = 50;
    rcMain.right = rcMain.left + (TILESIZE * TILE_X);
    rcMain.bottom = rcMain.top + (TILESIZE * TILE_Y);

    // ���� ���� ���
    rcSample.left = TILEMAPTOOLSIZE_X - sampleTile->GetWidth();
    rcSample.top = 0;
    rcSample.right = TILEMAPTOOLSIZE_X;
    rcSample.bottom = sampleTile->GetHeight();

    // ���� ���� Ŭ�� �ٿ�
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

    // ���� ���� �巡��
	else if (PtInRect(&rcSample, g_ptMouse))
	{
		// 1) ��� ���� �ݺ��ϸ鼭 rect �浹 Ȯ��
		/*// �ٿ�
		if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_LBUTTON))
		{
			for (int i = 0; i < SAMPLE_TILE_X * SAMPLE_TILE_Y; i++) //�̶� i�� ���콺�� Ŭ���� ��ġ�� ���� ���� RECT �ε����� ����Ŵ
			{
				if (PtInRect(&(sampleTileInfo[i].rcTile), g_ptMouse))
				{
					ptStartSelectedFrame.x = i % SAMPLE_TILE_X;
					ptStartSelectedFrame.y = i / SAMPLE_TILE_X;

					break;
				}
			}
		}*/ 

        // 2) ���콺 ��ǥ�� �ε��� ���
        // �ٿ�
        if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_LBUTTON))
        {
			int posX = g_ptMouse.x - rcSample.left;
			int posY = g_ptMouse.y - rcSample.top;
			ptStartSelectedFrame.x = posX / TILESIZE;
			ptStartSelectedFrame.y = posY / TILESIZE;

            ptSelected[0] = g_ptMouse;
		}
		// ��
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
    // �ڿ� �� �������� ĥ�ϱ�
    PatBlt(hdc, 0, 0, TILEMAPTOOLSIZE_X, TILEMAPTOOLSIZE_Y, WHITENESS);

    //Ȯ�ο�//
    mainBlackBack->Render(hdc, 200, 50);

    // ���� Ÿ�� ��ü ���
    sampleTile->Render(hdc, TILEMAPTOOLSIZE_X - sampleTile->GetWidth(), 0);

    // ���� ���� ǥ��
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

    // ���� Ÿ�� ���
    for (int i = 0; i < TILE_X * TILE_Y; i++)
    {
        sampleTile->FrameRender(hdc,
            tileInfo[i].rcTile.left,
            tileInfo[i].rcTile.top,
            tileInfo[i].frameX,
            tileInfo[i].frameY);
    }

    // ���õ� Ÿ�� 3�� ���
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
    // �巡�� ���
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

    //�� �̹��� ��ȣ ��� Ȯ�ο�//
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
    //�� �̹��� save
    string fileName = "Save/saveMapData";
    fileName += to_string(stageNum) + ".map";

	//���� �̸���, �����̴�, ������ ���ϰ�, ����, �׻� �����ϰ�, �Ϲ� ���Ϸ� ������ ���̸�, ���ø� �ӽñ�� �׳� �� �־����
    HANDLE hFile = CreateFile(fileName.c_str(), GENERIC_WRITE, 0, 0, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL); //.c_str()
    
    DWORD writtenBytes;

	WriteFile(hFile, tileInfo, sizeof(TILE_INFO) * TILE_X * TILE_Y, &writtenBytes, NULL);   //viod*�� � �ڷ����̵� ������ ���� �� �ִ�

	CloseHandle(hFile);

    //�� �̹��� ��ȣ save
    string fileNumName = "Save/saveMapNumData";
    fileNumName += to_string(stageNum) + ".map";
    HANDLE hFileNum = CreateFile(fileNumName.c_str(), GENERIC_WRITE, 0, 0, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL); 
    WriteFile(hFileNum, tileNumInfo, sizeof(int) * TILE_X * TILE_Y, &writtenBytes, NULL); 
    CloseHandle(hFileNum);
}

void TilemapTool::Load(int stageNum)
{
    //�� �̹��� load
    string fileName = "Save/saveMapData";
    fileName += to_string(stageNum) + ".map";

	HANDLE hFile = CreateFile(fileName.c_str(), GENERIC_READ, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

    DWORD readBytes;

    if (ReadFile(hFile, tileInfo, sizeof(TILE_INFO) * TILE_X * TILE_Y, &readBytes, NULL)) {}
	else
		MessageBox(g_hWnd, "�������� �ε� ����", "����", MB_OK);

	CloseHandle(hFile);

    //�� �̹��� ��ȣ load
    string fileNumName = "Save/saveMapNumData";
    fileNumName += to_string(stageNum) + ".map";
    HANDLE hFileNum = CreateFile(fileNumName.c_str(), GENERIC_READ, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (ReadFile(hFileNum, tileNumInfo, sizeof(int) * TILE_X * TILE_Y, &readBytes, NULL)) {}
    else
        MessageBox(g_hWnd, "��ȣ �������� �ε� ����", "����", MB_OK);
    CloseHandle(hFileNum);
}
