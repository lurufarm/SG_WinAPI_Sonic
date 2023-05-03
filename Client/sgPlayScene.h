#pragma once
#include "sgScene.h"

namespace sg
{
	class Sonic;
	class PlayScene : public Scene
	{
	public:
		PlayScene();
		~PlayScene();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;
	

		virtual void OnEnter() override;
		virtual void OnExit() override;

	private:

		class PlayUI* mUI;
		class Sound* mBG;
		class Sound* mMBBG;

		bool mMB;

		std::vector<class Clouds*> mClouds;

	};
}

