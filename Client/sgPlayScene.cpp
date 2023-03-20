#include "sgPlayScene.h"
#include "sgSonic.h"
#include "sgRhinobot.h"
#include "sgBackground.h"
#include "sgBackground_middle.h"
#include "sgBackground_middle2.h"
#include "sgBackground_sea.h"
#include "sgMapObjects.h"
#include "sgMapWater1.h"
#include "sgMapDeco1.h"
#include "sgMapDeco2.h"
#include "sgMapDeco3.h"
#include "sgMapDeco4.h"
#include "sgRing.h"
#include "sgRedcard.h"
#include "sgZone1.h"
#include "sgAct1.h"
#include "sgTestGround.h"
#include "sgPlayUI.h"


#include "sgInput.h"
#include "sgSceneManager.h"
#include "sgCollisionManager.h"
#include "sgImage.h"
#include "sgResources.h"
#include "sgTransform.h"
#include "sgCamera.h"
#include "sgObject.h"
#include <iostream>


namespace sg
{
	PlayScene::PlayScene()
	{
	}
	PlayScene::~PlayScene()
	{
	}

	void PlayScene::Initialize()
	{


		mSonic = object::Instantiate<Sonic>(Vector2(1500.0f, 3410.0f), eLayerType::Player, eSceneType::Play);
		object::Instantiate<Rhinobot>(Vector2(2300.0f, 3430.0f), eLayerType::Monster, eSceneType::Play);

		GameObject* bg1 = object::Instantiate<Background>(eLayerType::BG, eSceneType::Play);
		Background_middle* bg2 = object::Instantiate<Background_middle>(eLayerType::BG, eSceneType::Play);
		bg2->SetSonic(mSonic);
		Background_middle2* bg3 = object::Instantiate<Background_middle2>(eLayerType::BG, eSceneType::Play);
		bg3->SetSonic(mSonic);
		for (size_t i = 0; i <= 14400; i += 576)
		{
			object::Instantiate<Backgroundsea>(Vector2(2000 + i, 2927), eLayerType::BG, eSceneType::Play);
		}
		object::Instantiate<MapObjects>(eLayerType::MapObjects, eSceneType::Play);
		object::Instantiate<MapWater1>(Vector2(1049.5, 830), eLayerType::MapDeco, eSceneType::Play);
		object::Instantiate<MapDeco1>(Vector2(4365, 3551), eLayerType::MapDeco, eSceneType::Play);
		object::Instantiate<MapDeco2>(Vector2(4525, 3551), eLayerType::MapDeco, eSceneType::Play);
		object::Instantiate<MapDeco3>(Vector2(5010, 3352), eLayerType::MapDeco, eSceneType::Play);
		object::Instantiate<MapDeco4>(Vector2(5450, 3352), eLayerType::MapDeco, eSceneType::Play);
		object::Instantiate<Ring>(Vector2(1800, 3460), eLayerType::Ring, eSceneType::Play);
		object::Instantiate<Ring>(Vector2(1800, 3400), eLayerType::Ring, eSceneType::Play);
		object::Instantiate<Ring>(Vector2(1900, 3460), eLayerType::Ring, eSceneType::Play);
		object::Instantiate<Ring>(Vector2(1900, 3400), eLayerType::Ring, eSceneType::Play);
		object::Instantiate<Ring>(Vector2(2000, 3460), eLayerType::Ring, eSceneType::Play);
		object::Instantiate<Ring>(Vector2(2000, 3400), eLayerType::Ring, eSceneType::Play);
		object::Instantiate<Ring>(Vector2(2100, 3460), eLayerType::Ring, eSceneType::Play);
		object::Instantiate<Ring>(Vector2(2100, 3400), eLayerType::Ring, eSceneType::Play);
		object::Instantiate<Ring>(Vector2(2200, 3460), eLayerType::Ring, eSceneType::Play);
		object::Instantiate<Ring>(Vector2(2200, 3400), eLayerType::Ring, eSceneType::Play);
		object::Instantiate<Ground>(Vector2(1000.0f, 3500.0f), eLayerType::MapObjects, eSceneType::Play);
		Redcard* rc = object::Instantiate<Redcard>(eLayerType::UI, eSceneType::Play);
		Zone1* zone1 = object::Instantiate<Zone1>(eLayerType::UI, eSceneType::Play);
		Act1* act1 = object::Instantiate<Act1>(eLayerType::UI, eSceneType::Play);

		Camera::SetTarget(mSonic);
		PlayUI::SetTarget(mSonic);

	}
	void PlayScene::Update()
	{
		if (Input::GetKeyDown(eKeyCode::ESC))
		{
			SceneManager::LoadScene(eSceneType::Title);
		}
		Scene::Update();
	}
	void PlayScene::Render(HDC hdc)
	{
		Scene::Render(hdc);
	}

	void PlayScene::Release()
	{
		Scene::Release();
	}
	void PlayScene::OnEnter()
	{
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Monster, true);
		CollisionManager::SetLayer(eLayerType::MapObjects, eLayerType::Monster, true);
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Ring, true);
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::MapObjects, true);
	}
	void PlayScene::OnExit()
	{
	}
}