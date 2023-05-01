#include "sgRing.h"
#include "sgSonic.h"
#include "sgPlayScene.h"

#include "sgTime.h"
#include "sgSceneManager.h"
#include "sgResources.h"
#include "sgObject.h"
#include "sgSound.h"
#include "sgCollisionManager.h"

#include "sgTransform.h"
#include "sgAnimator.h"
#include "sgRigidbody.h"
#include "sgCollider.h"

extern sg::Sonic* mSonic;

namespace sg
{
	Ring::Ring()
	{
	}
	Ring::~Ring()
	{
	}
	void Ring::Initialize()
	{
		mAnimator = AddComponent<Animator>();
		mRingCollider = AddComponent<Collider>();
		mRingCollider->SetCenter(Vector2::Zero);
		mRingCollider->SetSize(Vector2(40.f, 40.f));
		Transform* tr = GetComponent<Transform>();
		tr->SetScale(Vector2(2.5f, 2.5f));
		Image* ring = Resources::Load<Image>(L"ring", L"..\\Resources\\object\\ring.bmp");
		mAnimator->CreateAnimation(L"ring_exist", ring, Vector2::Zero, 4, 2, 4, Vector2::Zero, 0.1);
		mAnimator->CreateAnimation(L"ring_nonex", ring, Vector2(0, 16), 4, 2, 4, Vector2::Zero, 0.01);
		mAnimator->Play(L"ring_exist", true);

		mRingState = eRingState::exist;

		sRing = Resources::Load<Sound>(L"s_ring", L"..\\Resources\\sound\\sonic_getring.wav");

		GameObject::Initialize();

	}
	void Ring::Update()
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 ringpos = tr->GetPos();
		Vector2 dir = mSonic->GetComponent<Transform>()->GetPos() - tr->GetPos();
		dir.Nomalize();
		/*Vector2(mSonic->GetComponent<Transform>()->GetPos().x - 1045, mSonic->GetComponent<Transform>()->GetPos().y - 690);*/
		if (mSonic->mThunder)
		{
			if (fabs((mSonic->GetComponent<Transform>()->GetPos() - ringpos).Length()) <= 500.0f)
			{
				
				float x = dir.x * cosf(PI / 7.0f) - dir.y * sinf(PI / 7.0f);
				float y = dir.x * sinf(PI / 7.0f) + dir.y * cosf(PI / 7.0f);

				ringpos.x += 500.0f * x * Time::DeltaTime();
				ringpos.y += 500.0f * y * Time::DeltaTime();

				tr->SetPos(ringpos);

				//Rigidbody* ringrb = AddComponent<Rigidbody>();
				//ringrb->SetMass(1.0f);
				//ringrb->SetGround(true);
				//Vector2 ringvel = Vector2(300.0f, 300.0f);
				//ringrb->SetVelocity(-dir * ringvel);
			
			}
		}

		switch (mRingState)
		{
		case Ring::eRingState::exist:
			Exist();
			break;
		case Ring::eRingState::nonexistent:
			Nonexistent();
			break;
		case Ring::eRingState::rigid:
			Rigid();
			break;
		}

		GameObject::Update();

	}
	void Ring::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void Ring::Release()
	{
		GameObject::Release();
	}
	void Ring::OnCollisionEnter(Collider* other)
	{
		Sonic* sonic = dynamic_cast<Sonic*>(other->GetOwner());
		if (sonic == nullptr)
			return;

		if (other->GetOwner() == sonic)
		{
			sRing->Play(false);
			mAnimator->Play(L"ring_nonex", true);
			mRingState = eRingState::nonexistent;
		}
	}
	void Ring::OnCollisionStay(Collider* other)
	{
	}
	void Ring::OnCollisionExit(Collider* other)
	{
	}
	void Ring::Exist()
	{
		mAnimator->Play(L"ring_exist", true);
	}
	void Ring::Nonexistent()
	{
		object::Destroy(this);
	}
	void Ring::Rigid()
	{
		mTime += Time::DeltaTime();
		mAnimator->Play(L"ring_exist", true);
		if (mTime >= 3.0f)
		{
			mRingState = eRingState::nonexistent;
		}
	}
}