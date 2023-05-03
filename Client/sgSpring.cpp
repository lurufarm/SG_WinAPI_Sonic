#include "sgSpring.h"
#include "sgSonic.h"

#include "sgTime.h"
#include "sgImage.h"
#include "sgResources.h"
#include "sgObject.h"
#include "sgSound.h"

#include "sgTransform.h"
#include "sgAnimator.h"
#include "sgCollider.h"
#include "sgRigidbody.h"

namespace sg
{
	Spring::Spring(int a)
	{
		SetName(L"Spring");
		if (a == 0)
		{
			mSpringState = eSpringState::up_norm;
		}
		else if (a == 1)
		{
			mSpringState = eSpringState::right_norm;
		}
			direction = a;
	}
	Spring::Spring()
		: direction(0)
	{
		SetName(L"Spring");
	}
	Spring::~Spring()
	{
	}
	void Spring::Initialize()
	{
		mAnimator = AddComponent<Animator>();
		mCollider = AddComponent<Collider>();
		mTr = GetComponent<Transform>();
		Image* spring = Resources::Load<Image>(L"spring", L"..\\Resources\\object\\spring.bmp");
		mAnimator->CreateAnimation(L"up_norm", spring, Vector2::Zero, 3, 4, 1, Vector2::Zero, 0.1f);
		mAnimator->CreateAnimation(L"up_used", spring, Vector2(32,0), 3, 4, 2, Vector2::Zero, 0.1f);
		mAnimator->CreateAnimation(L"right_norm", spring, Vector2(0, 32), 3, 4, 1, Vector2::Zero, 0.1f);
		mAnimator->CreateAnimation(L"right_used", spring, Vector2(32, 32), 3, 4, 2, Vector2::Zero, 0.1f);
		mAnimator->CreateAnimation(L"left_norm", spring, Vector2(0, 64), 3, 4, 1, Vector2::Zero, 0.1f);
		mAnimator->CreateAnimation(L"left_used", spring, Vector2(32, 64), 3, 4, 2, Vector2::Zero, 0.1f);
		

		sSpring = Resources::Load<Sound>(L"spring", L"..\\Resources\\sound\\sonic_spring.wav");


		mTr->SetScale(Vector2(2.5f, 2.5f));

		if (direction == 0)
		{
			mSpringState = eSpringState::up_norm;
		}
		else if (direction == 1)
		{
			mSpringState = eSpringState::right_norm;
		}
		if (direction == 2)
		{
			mSpringState = eSpringState::left_norm;
		}

		GameObject::Initialize();

	}
	void Spring::Update()
	{
		GameObject::Update();

		switch (mSpringState)
		{
		case sg::Spring::eSpringState::up_norm:
			Spring::up_norm();
			break;
		case sg::Spring::eSpringState::up_use:
			Spring::up_use();
			break;
		case sg::Spring::eSpringState::right_norm:
			Spring::right_norm();
			break;
		case sg::Spring::eSpringState::right_use:
			Spring::right_use();
			break;
		case sg::Spring::eSpringState::left_norm:
			Spring::left_norm();
			break;
		case sg::Spring::eSpringState::left_use:
			Spring::left_use();
			break;
		}
	}
	void Spring::Render(HDC hdc)
	{
		GameObject::Render(hdc);

	}
	void Spring::Release()
	{
		GameObject::Release();

	}
	void Spring::OnCollisionEnter(Collider* other)
	{
		Sonic* sonic = dynamic_cast<Sonic*>(other->GetOwner());
		sSpring->Play(false);
		mUse = true;
		if (mSpringState == eSpringState::up_norm
			|| mSpringState == eSpringState::up_use)
		{
			mSpringState = eSpringState::up_use;
		}
		if (mSpringState == eSpringState::right_norm
			|| mSpringState == eSpringState::right_use)
		{
			mSpringState = eSpringState::right_use;
		}
		if (mSpringState == eSpringState::left_norm
			|| mSpringState == eSpringState::left_use)
		{
			mSpringState = eSpringState::left_use;
		}
	}
	void Spring::OnCollisionStay(Collider* other)
	{
	}
	void Spring::OnCollisionExit(Collider* other)
	{
		mUse = false;
		mAnimator->Reset();
	}
	void Spring::up_norm()
	{
		mCollider->SetSize(Vector2(40.0f, 5.0f));
		mCollider->SetCenter(Vector2(25.0f, 45.0f));
		mAnimator->Play(L"up_norm", false);
	}
	void Spring::up_use()
	{
		mAnimator->Play(L"up_used", false);
			if (mAnimator->IsComplete())
			{
				mAnimator->Reset();
				mSpringState = eSpringState::up_norm;
			}
	}
	void Spring::right_norm()
	{
		mCollider->SetSize(Vector2(5.0f, 40.0f));
		mCollider->SetCenter(Vector2(45.0f, 25.0f));

		mAnimator->Play(L"right_norm", true);
	}
	void Spring::right_use()
	{
		mAnimator->Play(L"right_used", false);

			if (mAnimator->IsComplete())
			{
				mAnimator->Reset();
				mSpringState = eSpringState::right_norm;
			}
	}
	void Spring::left_norm()
	{
		mCollider->SetSize(Vector2(5.0f, 40.0f));
		mCollider->SetCenter(Vector2(35.0f, 25.0f));

		mAnimator->Play(L"left_norm", true);
	}
	void Spring::left_use()
	{
		mAnimator->Play(L"left_used", false);

		if (mAnimator->IsComplete())
		{
			mAnimator->Reset();
			mSpringState = eSpringState::left_norm;
		}
	}
}