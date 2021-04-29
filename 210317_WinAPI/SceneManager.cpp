#include "SceneManager.h"
#include "GameNode.h"

// static은 불러올 때 생성된다
// 하지만 컴파일 되는 시점에도 아래 내용을 필요하니까 초기화를 이렇게 해 준다
GameNode* SceneManager::currentScene = nullptr;
GameNode* SceneManager::loadingScene = nullptr;
GameNode* SceneManager::readyScene = nullptr;

HRESULT SceneManager::Init()
{
	return S_OK;
}

void SceneManager::Release()
{
	map<string, GameNode*>::iterator it;
	for (it = mSceneDatas.begin(); it != mSceneDatas.end(); it++)
	{
		if (it->second)
		{
			SAFE_RELEASE(it->second);
		}
	}

	mSceneDatas.clear();

	ReleaseSingleton();
}

void SceneManager::Update()
{
	if (currentScene)
	{
		currentScene->Update();
	}
}

void SceneManager::Render(HDC hdc)
{
	if (currentScene)
	{
		currentScene->Render(hdc);
	}
}

GameNode* SceneManager::AddScene(string key, GameNode* scene)
{
	// 객체 생성 자체가 안 된 경우
	if (scene == nullptr)
	{
		return nullptr;
	}

	// 삽입하려는 데이터가 이미 존재하는 경우
	map<string, GameNode*>::iterator it = mSceneDatas.find(key);
	if (it != mSceneDatas.end())
	{
		return it->second;	//해당 key에 맞는 GameNode 반환
	}
	
	// 삽입하려는 데이터가 존재하지 않는 경우
	mSceneDatas.insert(pair<string, GameNode*>(key, scene));

	return scene;
}

HRESULT SceneManager::ChangeScene(string key)
{
	map<string, GameNode*>::iterator it = mSceneDatas.find(key);

	// 못찾은 경우
	if (it == mSceneDatas.end())
	{
		return E_FAIL;	// 실패하고, 암것도 안한다
	}

	// 찾는씬이 지금 보여주고 있는 씬인 경우
	if (it->second == currentScene)
	{
		return S_OK;	// 성공하고, 암것도 안한다
	}

	// 찾는씬이 지금 보여주고 있는 씬이 아니며
	if (SUCCEEDED(it->second->Init()))	// 찾는씬 초기화 성공
	{
		if (currentScene)
		{
			currentScene->Release();	// 지금 보여주는 씬 해제
		}
		currentScene = it->second;	// 찾는씬으로 변경

		return S_OK;
	}

	//초기화 실패
	return E_FAIL;
}
