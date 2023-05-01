#pragma once
#include "sgGameObject.h"
#include "sgImage.h"

namespace sg
{
	class Background2 : public GameObject
	{
	public:

		enum class eBGState {
			bg1,
			bg2,
			bg3,
		};

		Background2();
		~Background2();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

		void SetBG(eBGState state, Vector2 pos) { mBGState = state; mPos = pos; }

	private:

		Image* background2Image[3];

		eBGState mBGState;
		class Transform* mTr;
		class Animator* mAni;
		Vector2 mPos;

		float mParallaxOffsetX;

	};

}

