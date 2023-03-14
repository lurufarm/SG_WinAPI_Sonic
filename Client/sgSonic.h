#pragma once
#include "sgGameObject.h"
#include "sgImage.h"

namespace sg
{
	class Rigidbody;
	class Animator;
	class Sonic : public GameObject
	{
	public:

		enum class eSonicState
		{
			idle_left,
			idle_right,
			idle_bored,
			crouch_left,
			crouch_right,
			lookup_left,
			lookup_right,
			walk_left,
			walk_right,
			run_left,
			run_right,
			skid_left,
			skid_right,

		};

		Sonic();
		~Sonic();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

		virtual void OnCollisionEnter(class Collider* other) override;
		virtual void OnCollisionStay(class Collider* other) override;
		virtual void OnCollisionExit(class Collider* other) override;
		static int mRingNumber;

	private:
		void idle_left();
		void idle_right();
		void idle_bored();
		void crouch_left();
		void crouch_right();
		void lookup_left();
		void lookup_right();
		void walk_left();
		void walk_right();
		void run_left();
		void run_right();
		void skid_left();
		void skid_right();

		eSonicState mSonicState;
		Animator* mAnimator = AddComponent<Animator>();
		float mBoredTime;
		Vector2 mSonicPos;
		Rigidbody* mRigidbody;
	};

}

