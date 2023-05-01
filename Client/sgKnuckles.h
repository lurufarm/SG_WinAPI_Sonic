#pragma once
#include "sgGameObject.h"

namespace sg
{

	class Knuckles : public GameObject
	{
	public:
		Knuckles();
		~Knuckles();

		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);
		virtual void Release();


		virtual void OnCollisionEnter(class Collider* other) override;
		virtual void OnCollisionStay(class Collider* other) override;
		virtual void OnCollisionExit(class Collider* other) override;


	private:

		float mTime;
		class Transform* mTr;
		class Animator* mAni;
		class Collider* mCol;
		class Rigidbody* mRb;

		bool mWalk;
		bool mJump;
		bool mLaugh;


	};
}

