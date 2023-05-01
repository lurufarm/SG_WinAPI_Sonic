#pragma once
#include "sgGameObject.h"

namespace sg
{	
	class Bloominator;
	class Animator;
	class Rigidbody;
	class BloomBullet : public GameObject
	{
	public:
		BloomBullet();
		~BloomBullet();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

		virtual void OnCollisionEnter(class Collider* other);
		virtual void OnCollisionStay(class Collider* other);
		virtual void OnCollisionExit(class Collider* other);

	private:
		Animator* mAnimator = AddComponent<Animator>();
		Rigidbody* mRigidbody = AddComponent<Rigidbody>();
		Collider* mCollider = AddComponent<Collider>();
		eState mState;
		float mTime;
	};
}

