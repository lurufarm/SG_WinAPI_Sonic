#pragma once
#include "sgGameObject.h"
#include "sgAnimator.h"
#include "sgCollider.h"

namespace sg
{
	class Animator;
	class Collider;
	class Ring : public GameObject
	{

	public:
		enum eRingState
		{
			exist,
			nonexistent,
		};

		Ring();
		~Ring();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;
		void SetSonic(GameObject* sonic) { mSonic = sonic; }

		virtual void OnCollisionEnter(class Collider* other) override;
		virtual void OnCollisionStay(class Collider* other) override;
		virtual void OnCollisionExit(class Collider* other) override;
	
	private:
		void Exist();
		void Nonexistent();

	private:

		
		Animator* mAnimator;
		Collider* mRingCollider;
		GameObject* mSonic;
		eRingState eRingState;

	};
}

