#pragma once
#include "sgScene.h"

namespace sg 
{
	class SceneManager
	{
	public:
		static void Initialize();
		static void Update();
		static void Render(HDC hdc);
		static void Destroy();
		static void Release();

		static void LoadScene(eSceneType type);
		static Scene* GetActiveScene() { return mActiveScene; }
		static eSceneType GetActiveScene2()
		{
			Scene* now = mActiveScene;

			for (size_t i = 0; i < 5; i++)
			{
				if (now == mScenes[i])
				{
					return (eSceneType)i;
				}
			}
		}
		static void SetActiveScene(Scene* scene) { mActiveScene = scene; }
		static Scene* SetScene(eSceneType type)
		{
			mActiveScene = mScenes[(UINT)type];
			return mActiveScene;
		}


	private:
		static std::vector<Scene*> mScenes;
		static Scene* mActiveScene;
	};
}

