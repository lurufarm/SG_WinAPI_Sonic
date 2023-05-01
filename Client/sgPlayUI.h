#pragma once
#include "sgGameObject.h"

namespace sg
{
	class Sonic;
	class PlayUI : public GameObject
	{
	public:

		PlayUI();
		~PlayUI();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

		void SetTarget(Sonic* target) { mPlayer = target; }


	private:

		Sonic* mPlayer;
		class Image* mImage;
		float mTime;
		int mTimeint;
		float mRings;
		float mLife;

		LOGFONT mFont;
		LOGFONT mFont2;

	};

}

