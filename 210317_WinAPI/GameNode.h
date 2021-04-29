#pragma once
#include "config.h"
// ��� ����, ��� �Լ� ���� ���� ����

/*
	������ ������� ���ӱ����� ���� �⺻�� �Ǵ� Ŭ����
*/

class GameNode
{
public:
	// virtual�� �ٿ� �ڷ����� �θ��� �Լ��� �ƴ� new�� ������ �ڽ��� �Լ��� ��� �� �� �հ� �Ѵ�
	virtual HRESULT Init();			// ��� ������ �ʱ�ȭ, �޸� �Ҵ�
	virtual void Release();			// �޸� ����
	virtual void Update();			// ������ ������ ���� ���� ���� (������ ����)
	virtual void Render(HDC hdc);	// ������ ������ ��� (�̹���, �ؽ�Ʈ ��)

	GameNode();
	virtual ~GameNode();
};

