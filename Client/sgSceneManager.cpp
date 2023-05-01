#include "sgSceneManager.h"
#include "sgPlayScene.h"
#include "sgPlayScene2.h"
#include "sgTitleScene.h"
#include "sgEndingScene.h"
#include "sgCollisionManager.h"
#include "sgCamera.h"
#include "sgApplication.h"

extern sg::Application application;

namespace sg
{
	std::vector<Scene*> SceneManager::mScenes = {};
	Scene* SceneManager::mActiveScene = nullptr;

	void SceneManager::Initialize()
	{
		mScenes.resize((UINT)eSceneType::End);
		
		mScenes[(UINT)eSceneType::Title] = new TitleScene();
		mScenes[(UINT)eSceneType::Play] = new PlayScene();
		mScenes[(UINT)eSceneType::Play2] = new PlayScene2();
		mScenes[(UINT)eSceneType::Ending] = new EndingScene();

		for (Scene* scene : mScenes)
		{
			if (scene == nullptr)
				continue;

			scene->Initialize();
		}
		mActiveScene = mScenes[(UINT)eSceneType::Title];
	}

	void SceneManager::Update()
	{
		mActiveScene->Update();
	}

	void SceneManager::Render(HDC hdc)
	{
		Camera::Render(hdc);
		mActiveScene->Render(hdc);
	}

	void SceneManager::Destroy()
	{
		mActiveScene->Destroy();
	}

	void SceneManager::Release()
	{
		for (Scene* scene : mScenes)
		{
			if (scene == nullptr)
				continue;

			delete scene;
			scene = nullptr;
		}
	}

	void SceneManager::LoadScene(eSceneType type)
	{
		Camera::Clear();

		//ÇöÀç ¾À
		mActiveScene->OnExit();
		CollisionManager::Clear();
		//´ÙÀ½ ¾À
		mActiveScene = mScenes[(UINT)type];
		mActiveScene->OnEnter();

	}

}