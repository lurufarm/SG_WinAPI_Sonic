#pragma once
#include "sgGameObject.h"

namespace sg
{
	class WaterfallRock : public GameObject
	{
	public:
		WaterfallRock();
		~WaterfallRock();

		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);
		virtual void Release();

		virtual void OnCollisionEnter(class Collider* other);
		virtual void OnCollisionStay(class Collider* other);
		virtual void OnCollisionExit(class Collider* other);

	private:

		class Transform* mTr;
		class Animator* mAni;
		class Collider* mCol;

	};
}

