#pragma once
#include "sgComponent.h"
#include "sgTestGround.h"

extern sg::Ground* ground;

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
		
		void AddForce(Vector2 force) { mForce += force ; }
		Vector2 GetForce() { return mForce; }
		void SetForce(Vector2 force) { mForce = force; }
		
		void SetGround(bool ground) { mbGround = ground; }
		bool GetGround() { return mbGround; }

		void SetVelocity(Vector2 velocity) { mVelocity = velocity; }
		Vector2 GetVelocity() { return mVelocity; }
		void AddVelocity(Vector2 velocity) { mVelocity += velocity; }
		
		void SetFriction(float friction) { mFriction = friction; }
		void AddFriction(float friction) { mFriction += friction; }

		void SetGravity(Vector2 gravity) { mGravity = gravity; }
		Vector2 GetGrabity() { return mGravity; }
		void AddGravity(Vector2 gravity) { mGravity += gravity; }
		void SetLVel(Vector2 lvel) { mLimitedVelocity = lvel; }

		void AddAccel(Vector2 accel) { mAccelation += accel; }
		Vector2 GetAccel() { return mAccelation; }
		void SetAccel(Vector2 accel) { mAccelation = accel; }

		//void SetGroundClass(class Ground* ground) { mGround = ground; }

	private:
		float mMass;
		Vector2 mForce;
		Vector2 mAccelation;
		Vector2 mVelocity;
		Vector2 mLimitedVelocity;

		Vector2 mGravity;
		float mFriction;
		bool mbGround;

		//class Ground* mGround;
		//float mStaticFrinction;
		//float mKineticFriction;
		//float mCoefficientFriction;
		//float mNormalForce;

	};
}

