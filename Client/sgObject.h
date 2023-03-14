#pragma once
#include "sgGameObject.h"
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
		gameobj->Initialize();
		gameobj->GameObject::GetComponent<Transform>()->SetPos(pos);
		return gameobj;
	}

	static void Destroy(GameObject* obj)
	{
		obj->SetState(GameObject::eState::Death);
	}
}