#include "Button.h"
#include "Image.h"
#include "TilemapTool.h"

//버튼 기능에 따라 어떤 이미지를 불러 올 것인가, 위치는 어디로
HRESULT Button::Init(const char* fileName, int posX, int posY)
{
    //이미지 불러오기
    state = ButtonState::NONE;
    img = ImageManager::GetSingleton()->FindImage(fileName);
    if (img == nullptr)
    {
        string warningText = string(fileName) + "가 없다!!";
        MessageBox(g_hWnd, warningText.c_str(), "실패", MB_OK);
        return E_FAIL;
    }

    //위치
    pos.x = posX;
    pos.y = posY;

    //rect 정보
    rc.left = pos.x;
    rc.top = pos.y;
    rc.right = rc.left + img->GetWidth();
    rc.bottom = rc.top + img->GetFrameHeight();

    //
    ptSelectedFrame = { 0, 0 };
    func = nullptr;

    return S_OK;
}

HRESULT Button::Init()
{
    return E_NOTIMPL;
}

void Button::Release()
{
}

void Button::Update()
{
    if (PtInRect(&rc, g_ptMouse))
    {
        if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_LBUTTON))
        {
            if (!func)
            {
                int posX = g_ptMouse.x - rc.left;
                ptSelectedFrame.x = posX / img->GetFrameWidth();
            }

            state = ButtonState::DOWN;
        }
        else if(state == ButtonState::DOWN && KeyManager::GetSingleton()->IsOnceKeyUp(VK_LBUTTON))
        {
            state = ButtonState::UP;

            //버튼다운 후 업 하는 순간 수행 할 동작들 : 세이브, 로드 ...
            if(func)
                func((int)(ptSelectedFrame.x + 1));
        }
    }
    else
    {
        state = ButtonState::NONE;
    }
}

void Button::Render(HDC hdc)
{
    switch (state)
    {
    case ButtonState::NONE:
        //break;
    case ButtonState::UP:
        for (int i = 0; i < (img->GetWidth() / img->GetFrameWidth()); i++)
        {
            img->FrameRender(hdc, pos.x + (i * img->GetFrameWidth()), pos.y, i, 0);
        }
        break;
    case ButtonState::DOWN:
        for (int i = 0; i < (img->GetWidth() / img->GetFrameWidth()); i++)
        {
            img->FrameRender(hdc, pos.x + (i * img->GetFrameWidth()), pos.y, i, 0);
        }

        if (!func)
        {
            switch ((int)(ptSelectedFrame.x))
            {
            case 0:
                img->FrameRender(hdc, pos.x + ((int)(ptSelectedFrame.x) * img->GetFrameWidth()), pos.y, 0, 1);
                break;
            case 1:
                img->FrameRender(hdc, pos.x + ((int)(ptSelectedFrame.x) * img->GetFrameWidth()), pos.y, 1, 1);
                break;
            case 2:
                img->FrameRender(hdc, pos.x + ((int)(ptSelectedFrame.x) * img->GetFrameWidth()), pos.y, 2, 1);
                break;
            }
        }
        else
        {
            img->FrameRender(hdc, pos.x , pos.y, 0, 1);
        }
        break;
    }
}
