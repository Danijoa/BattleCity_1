#pragma once
#include "GameNode.h"

/*
	함수 포인터 : 함수의 메모리 주소를 담을 수 있는 (값으로 가지는) 변수
	-> 함수의 이름이 곧 함수의 메모리 주소

	변수 포인터 : 변수의 메모리 주소를 담을 수 있는 (값으로 가지는) 변수

	int a = 10;
	int* pA = &a;
	void sum(int a, int b);         //함수의 원형
	void (*funcPointer)(int, int);  //함수포인터(변수) 선언
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

//typedef pair<int, int> myPair; 이거 처럼 
typedef void (*func_t)(int); 

class Image;
class Button : public GameNode
{
private:
	ButtonState state;
	Image* img;
	RECT rc;
	POINT pos;
	
	//void (*func_t)(int); //void Save(int stageNum);와 동일한 형태의 함수들을 담을 수 있다
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

