#pragma once
#include "sgGameObject.h"
#include "sgAnimator.h"
#include "sgCollider.h"
#include "sgRigidbody.h"

namespace sg
{
	class Rigidbody;
	class Animator;
	class Collider;
	class Sonic;
	class Ring : public GameObject
	{

	public:
		enum eRingState
		{
			exist,
			nonexistent,
			rigid,
		};

		Ring();
		~Ring();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;
		void SetRingState(eRingState state) { mRingState = state; }

		virtual void OnCollisionEnter(class Collider* other) override;
		virtual void OnCollisionStay(class Collider* other) override;
		virtual void OnCollisionExit(class Collider* other) override;
	
	private:
		void Exist();
		void Nonexistent();
		void Rigid();

	private:

		
		Animator* mAnimator;
		Collider* mRingCollider;
		Rigidbody* mRingRigidbody = nullptr;
		eRingState mRingState;
		float mTime;

		Sonic* mSon;

		class Sound* sRing;

	};
}

