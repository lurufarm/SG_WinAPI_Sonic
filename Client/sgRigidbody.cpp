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

		//�ӵ��� ���ӵ��� �����ش�.

		mVelocity += mAccelation * Time::DeltaTime();



		if (mbGround)
		{
			//�� ���� ���� ��
			Vector2 gravity = mGravity;
			gravity.Nomalize();

			float dot = math::Dot(mVelocity, gravity);
			mVelocity -= gravity * dot;
		}
		else
		{
			mVelocity += mGravity * Time::DeltaTime();
		}

		//�߷°��ӵ� �ִ� �ӵ� ����
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
		
		//������ ���� (����� ���� ����, �ӵ��� 0�� �ƴ�)
		if (!(mVelocity == Vector2::Zero))
		{
			//�ӵ��� �ݴ�������� �������� ����ȴ�.
			Vector2 friction = -mVelocity;
			friction = friction.Nomalize() * mFriction * mMass * Time::DeltaTime();

			//���������� ���� �ӵ� ���Ҵ� ���� �ӵ����� ū ���

			if (mVelocity.Length() < friction.Length())
			{
				mVelocity = Vector2::Zero;
			}
			else
			{
				mVelocity += friction;
			}
		}

		//�ӵ��� �°Բ� ��ü�� �̵���Ų��.
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