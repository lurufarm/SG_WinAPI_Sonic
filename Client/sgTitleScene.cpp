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
#include "sgCollisionManager.h"
#include "sgImage.h"
#include "sgResources.h"
#include "sgTransform.h"
#include "sgCamera.h"
#include "sgObject.h"

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

		object::Instantiate<Titlebg>(Vector2(1350,2880), eLayerType::BG, eSceneType::Title);
		object::Instantiate<Titletails>(Vector2(1150,2300),eLayerType::MapObjects, eSceneType::Title);
		object::Instantiate<Titlesonic>(Vector2(1370,2700), eLayerType::MapObjects, eSceneType::Title);
		object::Instantiate<Titletitle>(eLayerType::UI, eSceneType::Title);
		object::Instantiate<TitleUI>(eLayerType::UI, eSceneType::Title);
		
	}
	void TitleScene::Update()
	{
		if (Input::GetKeyDown(eKeyCode::Enter))
		{
			SceneManager::LoadScene(eSceneType::Play);
			Redcard* rc = object::Instantiate<Redcard>(eLayerType::UI, eSceneType::Play);
			Zone1* zone1 = object::Instantiate<Zone1>(eLayerType::UI, eSceneType::Play);
			Act1* act1 = object::Instantiate<Act1>(eLayerType::UI, eSceneType::Play);
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

	}
	void TitleScene::OnExit()
	{
	}
}