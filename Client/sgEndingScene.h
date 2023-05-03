#pragma once
#include "sgScene.h"

namespace sg
{
	class EndingScene : public Scene
	{
	public:

		EndingScene();
		~EndingScene();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;


		virtual void OnEnter() override;
		virtual void OnExit() override;

	private:

		GameObject* mTarget;
		class Sound* mBG;
		LOGFONT mFont;

		std::vector<Clouds*> mClouds;

		float mTime;

	};
}

