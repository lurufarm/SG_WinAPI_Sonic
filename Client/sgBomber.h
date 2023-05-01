#pragma once
#include "sgGameObject.h"

namespace sg
{
	class Bomber : public GameObject
	{
	public:

		Bomber();
		~Bomber();

		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);
		virtual void Release();

		bool mthrowBomb;

	private:

		class Transform* mTr;
		class Animator* mAni;

		float mTime;
		class Bomberbomb* mBomb[14];
		int mBombindex;

		class Sound* sBomb;
	};
}

