#include "sgKnuckles.h"
#include "sgButton.h"

#include "sgImage.h"
#include "sgResources.h"
#include "sgTime.h"

#include "sgTransform.h"
#include "sgAnimator.h"
#include "sgCollider.h"
#include "sgRigidbody.h"

namespace sg
{
	Knuckles::Knuckles()
		: mTime(0.0)
		, mWalk(false)
		, mJump(false)
		, mLaugh(false)
	{
		SetName(L"Knuckles");
	}
	Knuckles::~Knuckles()
	{
	}
	void Knuckles::Initialize()
	{
		mTr = GetComponent<Transform>();
		mAni = AddComponent<Animator>();
		mCol = AddComponent<Collider>();
		mRb = AddComponent<Rigidbody>();

		mRb->SetGround(true);
		mRb->SetMass(1.0);
		
		Image* knuckles = Resources::Load<Image>(L"knuckles", L"..\\Resources\\enemies\\knuckles.bmp");

		mAni->CreateAnimation(L"k_walk", knuckles, Vector2::Zero, 8, 3, 8, Vector2::Zero, 0.1);
		mAni->CreateAnimation(L"k_jump", knuckles, Vector2(0, 50), 8, 3, 8, Vector2::Zero, 0.1);
		mAni->CreateAnimation(L"k_laugh", knuckles, Vector2(0, 100), 8, 3, 2, Vector2::Zero, 0.1);
		
		mTr->SetScale(Vector2(2.5f, 2.5f));
		mAni->Play(L"k_walk", true);
		mCol->SetCenter(Vector2(0, 30));

		GameObject::Initialize();
	}
	void Knuckles::Update()
	{
		GameObject::Update();

		Vector2 pos = mTr->GetPos();
		Vector2 vel = mRb->GetVelocity();

		if (mWalk == false)
		{
			mAni->Play(L"k_walk", true);
			pos.x -= 200 * Time::DeltaTime();
			mTr->SetPos(pos);

			if (pos.x <= 29365)
			{
				mWalk = true;
			}
		}
		if (mWalk == true && mJump == false)
		{
			mAni->Play(L"k_jump", true);
			mRb->SetGround(false);
			vel.y -= 500;
			vel.x -= 200;
			mRb->SetVelocity(vel);
			mRb->SetGround(false);
			mJump = true;
		}
		if (mJump && mRb->GetGround() == false)
		{
			if (pos.y >= 890)
			{
				mRb->SetGround(true);
				mAni->Play(L"k_laugh", true);

			}
		}

	}
	void Knuckles::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void Knuckles::Release()
	{
		GameObject::Release();
	}
	void Knuckles::OnCollisionEnter(Collider* other)
	{
		Button* button = dynamic_cast<Button*>(other->GetOwner());

		if (other->GetOwner())
		{
			mRb->SetGround(true);
			mAni->Play(L"k_laugh", true);
		}
	}
	void Knuckles::OnCollisionStay(Collider* other)
	{
		Button* button = dynamic_cast<Button*>(other->GetOwner());

		if (other->GetOwner())
		{
			mRb->SetGround(true);
			mAni->Play(L"k_laugh", true);
		}
	}
	void Knuckles::OnCollisionExit(Collider* other)
	{
	}
}