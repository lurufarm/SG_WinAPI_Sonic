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
		int mAbility;

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
			jump_left,
			jump_right,
			jump2_left,
			jump2_right,
			spindash_left,
			spindash_right,
			rolling_left,
			rolling_right,
			skid_left,
			skid_right,
			hurt_left,
			hurt_right,
			death,
		};

		Sonic();
		~Sonic();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;
		virtual void GetRing() { mRings++; }
		virtual int GetRingNumber() { return mRings; }
		virtual Sonic* GetSonic() { return this; }
		eSonicState GetSonicState() { return mSonicState; }
		void SetSonicState(eSonicState state) { mSonicState = state; }

		virtual void OnCollisionEnter(class Collider* other) override;
		virtual void OnCollisionStay(class Collider* other) override;
		virtual void OnCollisionExit(class Collider* other) override;




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
		void jump_left();
		void jump_right();
		void jump2_left();
		void jump2_right();
		void spindash_left();
		void spindash_right();
		void rolling_left();
		void rolling_right();
		void skid_left();
		void skid_right();
		void hurt_left();
		void hurt_right();
		void death();

		eSonicState mSonicState;
		Animator* mAnimator = AddComponent<Animator>();
		Collider* mCollider = nullptr;
		Rigidbody* mRigidbody = AddComponent<Rigidbody>();
		
		Vector2 mSonicPos;
		float mBoredTime;

		static int mRings;
		int mLife;

	};

}

