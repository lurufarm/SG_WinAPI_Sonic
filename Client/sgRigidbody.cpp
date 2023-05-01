#include "sgRigidbody.h"
#include "sgTime.h"
#include "sgGameObject.h"
#include "sgTransform.h"
#include "sgTestGround.h"
#include <iostream>

extern sg::Ground* ground;

namespace sg
{
	Rigidbody::Rigidbody()
		: Component(eComponentType::Rigidbody)
		, mMass(0.0f)
		, mForce(Vector2::Zero)
		, mAccelation(Vector2::Zero)
		, mVelocity(Vector2::Zero)
	{
		mLimitedVelocity.x = 100.0f;
		mLimitedVelocity.y = 800.0f;
		mbGround = false;
		mGravity = Vector2(0.0f, 800.0f);
		mFriction = 250.0f;
		

	}
	Rigidbody::~Rigidbody()
	{
	}
	void Rigidbody::Initialize()
	{
		//SetGroundClass(&ground);
	}
	void Rigidbody::Update()
	{
		//F = M * A
		//A = M / F
		//Vector2 mAccel2 = mForce / mMass;
		//mAccelation = mAccel2 + mAccel2 * ground->GetFrontPos();
		mAccelation = mForce / mMass;	

		//속도에 가속도를 더해준다.

		mVelocity += mAccelation * Time::DeltaTime();



		if (mbGround)
		{
			//땅 위에 있을 때
			Vector2 gravity = mGravity;
			gravity.Nomalize();

			float dot = math::Dot(mVelocity, gravity);
			mVelocity -= gravity * dot;
		}
		else
		{
			mVelocity += mGravity * Time::DeltaTime();
		}

		//중력가속도 최대 속도 제한
		Vector2 gravity = mGravity;
		gravity.Nomalize();
		float dot = math::Dot(mVelocity, gravity);
		gravity = gravity * dot;

		Vector2 sideVelocity = mVelocity - gravity;
		if (mLimitedVelocity.y < gravity.Length())
		{
			gravity.Nomalize();
			gravity *= mLimitedVelocity.y;
		}
		
		if (mLimitedVelocity.x < sideVelocity.Length())
		{
			sideVelocity.Nomalize();
			sideVelocity *= mLimitedVelocity.x;
		}
		
		//마찰력 조건 (적용된 힘이 없고, 속도가 0이 아님)
		if (!(mVelocity == Vector2::Zero))
		{
			//속도의 반대방향으로 마찰력이 적용된다.
			Vector2 friction = -mVelocity;
			friction = friction.Nomalize() * mFriction * mMass * Time::DeltaTime();

			//마찰력으로 인한 속도 감소는 현재 속도보다 큰 경우

			if (mVelocity.Length() < friction.Length())
			{
				mVelocity = Vector2::Zero;
			}
			else
			{
				mVelocity += friction;
			}
		}

		//속도에 맞게끔 물체를 이동시킨다.
		Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector2 pos = tr->GetPos();

		pos += mVelocity * Time::DeltaTime();
		tr->SetPos(pos);


		//if (pos.y > 900.0f)
		//	mbGround = true;

		tr->SetPos(pos);
		mForce.Clear();
	}
	void Rigidbody::Render(HDC hdc)
	{
	}
	void Rigidbody::Release()
	{
	}

}