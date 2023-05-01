#pragma once
#include "sgGameObject.h"
#include "sgSpring.h"
#include "sgItem.h"
#include "sgMapObjects2.h"
#include "sgWater.h"
#include "sgLBEffect.h"

#include "sgScene.h"
#include "sgSceneManager.h"
#include "sgTransform.h"

namespace sg::object
{
	template <typename T>
	static inline T* Instantiate(eLayerType type, eSceneType scenetype)
	{
		T* gameobj = new T();
		Scene* scene = SceneManager::SetScene(scenetype);
//		Scene* scene = SceneManager::GetActiveScene();
		scene->AddGameObject(gameobj, type);
		gameobj->Initialize();
		return gameobj;
	}

	template <typename T>
	static inline T* Instantiate(Vector2 pos, eLayerType type, eSceneType scenetype)
	{
		T* gameobj = new T();
		Scene* scene = SceneManager::SetScene(scenetype);
//		Scene* scene = SceneManager::GetActiveScene();
		scene->AddGameObject(gameobj, type);
		gameobj->GameObject::GetComponent<Transform>()->SetPos(pos);
		gameobj->Initialize();
		return gameobj;
	}

	static inline Spring* springInstantiate(Vector2 pos, eLayerType type, eSceneType scenetype, int a)
	{
		Spring* spring = new Spring(a);
		Scene* scene = SceneManager::SetScene(scenetype);
		//		Scene* scene = SceneManager::GetActiveScene();
		scene->AddGameObject(spring, type);
		spring->GameObject::GetComponent<Transform>()->SetPos(pos);
		spring->Initialize();
		return spring;
	}

	static inline Item* itemInstantiate(Vector2 pos, eLayerType type, eSceneType scenetype, int a)
	{
		Item* item = new Item(a);
		Scene* scene = SceneManager::SetScene(scenetype);
		//		Scene* scene = SceneManager::GetActiveScene();
		scene->AddGameObject(item, type);
		item->GameObject::GetComponent<Transform>()->SetPos(pos);
		item->Initialize();
		return item;
	}

	static inline MapObjects2* MapObjects2Instantiate(Vector2 pos, eLayerType type, eSceneType scenetype, int a)
	{
		MapObjects2* mobj2 = new MapObjects2(a);
		Scene* scene = SceneManager::SetScene(scenetype);
		//		Scene* scene = SceneManager::GetActiveScene();
		scene->AddGameObject(mobj2, type);
		mobj2->GameObject::GetComponent<Transform>()->SetPos(pos);
		mobj2->Initialize();
		return mobj2;
	}

	static inline Water* WaterInstantiate(Vector2 pos, Vector2 scale, eLayerType type, eSceneType scenetype)
	{
		Water* wat = new Water(scale, pos);
		Scene* scene = SceneManager::SetScene(scenetype);
		//		Scene* scene = SceneManager::GetActiveScene();
		scene->AddGameObject(wat, type);
		//wat->GameObject::GetComponent<Transform>()->SetPos(pos);
		wat->Initialize();
		return wat;
	}

	static inline LBEffect* LBEffectInstantiate(Vector2 pos, eLayerType type, LBEffect::eLBE lbetype)
	{
		LBEffect* lbe = new LBEffect(lbetype);
		Scene* scene = SceneManager::SetScene(eSceneType::Play2);
		scene->AddGameObject(lbe, type);
		lbe->GameObject::GetComponent<Transform>()->SetPos(pos);
		lbe->Initialize();
		return lbe;
	}


	static void Destroy(GameObject* obj)
	{
		obj->SetState(GameObject::eState::Death);
		//obj = nullptr;
	}
}