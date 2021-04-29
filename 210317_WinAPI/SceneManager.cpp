#include "SceneManager.h"
#include "GameNode.h"

// static�� �ҷ��� �� �����ȴ�
// ������ ������ �Ǵ� �������� �Ʒ� ������ �ʿ��ϴϱ� �ʱ�ȭ�� �̷��� �� �ش�
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
	// ��ü ���� ��ü�� �� �� ���
	if (scene == nullptr)
	{
		return nullptr;
	}

	// �����Ϸ��� �����Ͱ� �̹� �����ϴ� ���
	map<string, GameNode*>::iterator it = mSceneDatas.find(key);
	if (it != mSceneDatas.end())
	{
		return it->second;	//�ش� key�� �´� GameNode ��ȯ
	}
	
	// �����Ϸ��� �����Ͱ� �������� �ʴ� ���
	mSceneDatas.insert(pair<string, GameNode*>(key, scene));

	return scene;
}

HRESULT SceneManager::ChangeScene(string key)
{
	map<string, GameNode*>::iterator it = mSceneDatas.find(key);

	// ��ã�� ���
	if (it == mSceneDatas.end())
	{
		return E_FAIL;	// �����ϰ�, �ϰ͵� ���Ѵ�
	}

	// ã�¾��� ���� �����ְ� �ִ� ���� ���
	if (it->second == currentScene)
	{
		return S_OK;	// �����ϰ�, �ϰ͵� ���Ѵ�
	}

	// ã�¾��� ���� �����ְ� �ִ� ���� �ƴϸ�
	if (SUCCEEDED(it->second->Init()))	// ã�¾� �ʱ�ȭ ����
	{
		if (currentScene)
		{
			currentScene->Release();	// ���� �����ִ� �� ����
		}
		currentScene = it->second;	// ã�¾����� ����

		return S_OK;
	}

	//�ʱ�ȭ ����
	return E_FAIL;
}
