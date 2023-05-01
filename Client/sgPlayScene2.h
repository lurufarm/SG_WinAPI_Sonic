#pragma once
#include "sgScene.h"

namespace sg
{
	class Sonic;
	class PlayScene2 : public Scene
	{
	public:
		PlayScene2();
		~PlayScene2();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

		virtual void OnEnter() override;
		virtual void OnExit() override;

	private:

		Sonic* mSonic2;
		Bomber* mBomber;
		class Lastboss* mLB;
		class LastbossR* mLBr;
		class Button* mButton;

		class Foreground2* mTrees;

		bool mLBrb;
		bool mKnuc;
		class Logbridge* logb;

		float mTime;
		
		class Sound* mBG;
		class Sound* mLBBG;
		class Sound* mBombermove;
		class Sound* mLBmove;

	};
}

