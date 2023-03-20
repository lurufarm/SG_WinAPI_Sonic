#pragma once
#include "sgComponent.h"

namespace sg
{
	class Rigidbody : public Component
	{
	public:
		Rigidbody();
		~Rigidbody();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

		void SetMass(float mass) { mMass = mass; }
		void AddForce(Vector2 force);
		Vector2 GetForce() { return mForce; }
		void SetForce(Vector2 force) { mForce = force; }
		void SetGround(bool ground) { mbGround = ground; }
		bool GetGround() { return mbGround; }
		void SetVelocity(Vector2 velocity) { mVelocity = velocity; }
		Vector2 GetVelocity() { return mVelocity; }
		void SetFriction(float friction) { mFriction = friction; }

	private:
		float mMass;
		Vector2 mForce;
		Vector2 mAccelation;
		Vector2 mVelocity;
		Vector2 mLimitedVelocity;

		Vector2 mGravity;
		float mFriction;
		bool mbGround;

		//float mStaticFrinction;
		//float mKineticFriction;
		//float mCoefficientFriction;
		//float mNormalForce;

	};
}

