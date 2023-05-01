#pragma once
#include "sgGameObject.h"

namespace sg
{

	class Watersplash : public GameObject
	{
	public:
		Watersplash();
		~Watersplash();

		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);
		virtual void Release();

	private:

		class Transform* mTr;
		class Animator* mAni;

	};

}
