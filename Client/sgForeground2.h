#pragma once
#include "sgGameObject.h"

namespace sg
{
	class Foreground2 : public GameObject
	{
	public:

		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);
		virtual void Release();


		bool mAniN;

	private:
		class Transform* mTr;
		class Animator* mAni;
		class Image* fg;
	};
}

