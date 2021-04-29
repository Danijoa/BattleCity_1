#pragma once
#include "GameNode.h"

/*
	�Լ� ������ : �Լ��� �޸� �ּҸ� ���� �� �ִ� (������ ������) ����
	-> �Լ��� �̸��� �� �Լ��� �޸� �ּ�

	���� ������ : ������ �޸� �ּҸ� ���� �� �ִ� (������ ������) ����

	int a = 10;
	int* pA = &a;
	void sum(int a, int b);         //�Լ��� ����
	void (*funcPointer)(int, int);  //�Լ�������(����) ����
	funcPointer = sum;
	sum(10, 20);
	funcPointer(10, 20);

	void Print(void);
	void (*funcPrint)(void);
*/

enum class ButtonState
{
	NONE, DOWN, UP
};

//typedef pair<int, int> myPair; �̰� ó�� 
typedef void (*func_t)(int); 

class Image;
class Button : public GameNode
{
private:
	ButtonState state;
	Image* img;
	RECT rc;
	POINT pos;
	
	//void (*func_t)(int); //void Save(int stageNum);�� ������ ������ �Լ����� ���� �� �ִ�
	func_t func;
	int func_arg;

	POINT ptSelectedFrame;

public:
	HRESULT Init(const char* fileName, int posX, int posY);
	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);

	void SetFunc(func_t func, int funcArg) 
	{ 
		this->func = func; 
		this->func_arg = funcArg;
	}

	inline POINT GetCurrStageIndex() { return ptSelectedFrame; }
	inline void SetCurrStageIndex(POINT ptSelectedFrame) { this->ptSelectedFrame = ptSelectedFrame; }

	virtual ~Button() {};
};

