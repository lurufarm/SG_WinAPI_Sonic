#include "sgEndingScene.h"
#include "sgEndST.h"
#include "sgTitlebg.h"
#include "sgSonic.h"

#include "sgInput.h"
#include "sgResources.h"
#include "sgSound.h"

#include "sgApplication.h"
#include "sgCamera.h"
#include "sgSceneManager.h"
#include "sgObject.h"

extern sg::Application application;

namespace sg
{
	EndingScene::EndingScene()
	{
	}
	EndingScene::~EndingScene()
	{
	}
	void EndingScene::Initialize()
	{
		mTarget = object::Instantiate<Titlebg>(Vector2(0, 0), eLayerType::BG, eSceneType::Ending);
		object::Instantiate<Titlebg>(Vector2(-250, -500), eLayerType::BG, eSceneType::Ending);
		EndST* st = object::Instantiate<EndST>(Vector2(-250, 0), eLayerType::BG2, eSceneType::Ending);
	}
	void EndingScene::Update()
	{
		if (Input::GetKeyDown(eKeyCode::ESC))
		{
			SceneManager::LoadScene(eSceneType::Title);
		}

		Scene::Update();
	}
	void EndingScene::Render(HDC hdc)
	{

		Scene::Render(hdc);
	}
	void EndingScene::Release()
	{
		Scene::Release();
	}
	void EndingScene::OnEnter()
	{
		Camera::SetTarget(mTarget);
		mBG = Resources::Load<Sound>(L"EndingTheme", L"..\\Resources\\sound\\music\\ending.wav");
		mBG->Play(false);
	}
	void EndingScene::OnExit()
	{
		mBG->Stop(true);
	}
}