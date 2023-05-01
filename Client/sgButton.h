#pragma once
#include "sgGameObject.h"

namespace sg
{
	class Button : public GameObject
	{
	public:
		Button();
		~Button();

		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);
		virtual void Release();

		virtual void OnCollisionEnter(class Collider* other);
		virtual void OnCollisionStay(class Collider* other);
		virtual void OnCollisionExit(class Collider* other);

		bool mPush;

	private:

		class Transform* mTr;
		class Animator* mAni;
		class Collider* mCol;
	};
}

