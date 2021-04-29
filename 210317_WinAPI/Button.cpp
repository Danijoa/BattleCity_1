#include "Button.h"
#include "Image.h"
#include "TilemapTool.h"

//��ư ��ɿ� ���� � �̹����� �ҷ� �� ���ΰ�, ��ġ�� ����
HRESULT Button::Init(const char* fileName, int posX, int posY)
{
    //�̹��� �ҷ�����
    state = ButtonState::NONE;
    img = ImageManager::GetSingleton()->FindImage(fileName);
    if (img == nullptr)
    {
        string warningText = string(fileName) + "�� ����!!";
        MessageBox(g_hWnd, warningText.c_str(), "����", MB_OK);
        return E_FAIL;
    }

    //��ġ
    pos.x = posX;
    pos.y = posY;

    //rect ����
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

            //��ư�ٿ� �� �� �ϴ� ���� ���� �� ���۵� : ���̺�, �ε� ...
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
