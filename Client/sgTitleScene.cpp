#include "sgTitleScene.h"
#include "sgTitlebg.h"
#include "sgTitlesonic.h"
#include "sgTitletitle.h"
#include "sgTitletails.h"
#include "sgTitleUI.h"
#include "sgRedcard.h"
#include "sgZone1.h"
#include "sgAct1.h"

#include "sgInput.h"
#include "sgSceneManager.h"
#include "sgImage.h"
#include "sgResources.h"
#include "sgObject.h"
#include "sgCamera.h"
#include "sgSound.h"

#include "sgTransform.h"
#include "sgCollisionManager.h"

namespace sg
{
	TitleScene::TitleScene()
	{
	}
	TitleScene::~TitleScene()
	{
	}

	void TitleScene::Initialize()
	{
		Camera::SetTarget(nullptr);
		mBG = Resources::Load<Sound>(L"TitleTheme", L"..\\Resources\\sound\\music\\title.wav");
		mBG->Play(true);
		//object::Instantiate<Titlebg>(Vector2(260,2110), eLayerType::BG, eSceneType::Title);
		//object::Instantiate<Titletails>(Vector2(50,1530),eLayerType::MapObjects, eSceneType::Title);
		//object::Instantiate<Titlesonic>(Vector2(280,1930), eLayerType::MapObjects, eSceneType::Title);
		object::Instantiate<Titlebg>(Vector2(-560, -420), eLayerType::BG, eSceneType::Title);
		object::Instantiate<Titletails>(Vector2(-480, -300), eLayerType::MapObjects, eSceneType::Title);
		object::Instantiate<Titlesonic>(Vector2(-540, -600), eLayerType::MapObjects, eSceneType::Title);
		object::Instantiate<Titletitle>(eLayerType::UI, eSceneType::Title);
		object::Instantiate<TitleUI>(eLayerType::UI, eSceneType::Title);
		
	}
	void TitleScene::Update()
	{
		if (Input::GetKeyDown(eKeyCode::Enter))
		{
			SceneManager::LoadScene(eSceneType::Play);
		}
		Scene::Update();
	}
	void TitleScene::Render(HDC hdc)
	{
		Scene::Render(hdc);
	}
	void TitleScene::Release()
	{
		Scene::Release();
	}
	void TitleScene::OnEnter()
	{
		Camera::SetTarget(nullptr);
	}
	void TitleScene::OnExit()
	{
		mBG->Stop(true);
		Redcard* rc = object::Instantiate<Redcard>(eLayerType::UI, eSceneType::Play);
		Zone1* zone1 = object::Instantiate<Zone1>(eLayerType::UI, eSceneType::Play);
		Act1* act1 = object::Instantiate<Act1>(eLayerType::UI, eSceneType::Play);
	}
}