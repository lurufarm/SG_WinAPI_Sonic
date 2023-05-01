#include "sgBomberboom.h"

#include "sgSonic.h"
#include "sgBomber.h"

#include "sgImage.h"
#include "sgResources.h"
#include "sgTime.h"
#include "sgSound.h"

#include "sgTransform.h"
#include "sgAnimator.h"
#include "sgCollider.h"
#include "sgRigidbody.h"

namespace sg
{
	Bomberbomb::Bomberbomb()
		: mTime(0.0f)
		, mDown(false)
	{
		SetName(L"Bomberboom");
	}
	Bomberbomb::~Bomberbomb()
	{
	}

	void Bomberbomb::Initialize()
	{
		mTr = GetComponent<Transform>();
		mAni = AddComponent<Animator>();
		mCol = AddComponent<Collider>();
		//mRb = AddComponent<Rigidbody>();
		Image* bomb = Resources::Load<Image>(L"bomb", L"..\\Resources\\enemies\\bomber_bomb.bmp");
		mAni->CreateAnimation(L"bomb", bomb, Vector2::Zero, 13, 2, 1, Vector2::Zero, 0.1);
		mAni->CreateAnimation(L"bomb_explosion", bomb, Vector2(0.0f, 86.0f), 13, 2, 13, Vector2::Zero, 0.1);

		mTr->SetScale(Vector2(2.5f, 2.5f));

		mAni->Play(L"bomb", true);
		mCol->SetCenter(Vector2(45.0f, 145.0f));
		mCol->SetSize(Vector2(30.0f, 60.0f));
		//mRb->SetMass(1.0);
		//mRb->SetGravity(Vector2(1000, 800));
		//mRb->SetGround(true);
		mDown = false;

		sExp = Resources::Load<Sound>(L"Exp", L"..\\Resources\\sound\\explosion.wav");

		GameObject::Initialize();
	}
	
	void Bomberbomb::Update()
	{
		GameObject::Update();

		Vector2 pos = mTr->GetPos();


		if (mDown)
		{
			//pos.x += 300 * Time::DeltaTime();
			pos.y += 800.0f * Time::DeltaTime();
			mTr->SetPos(pos);
		}
		else
		{
			if (pos.y < 730)
			{
				pos.y += 50.0f * Time::DeltaTime();
				mTr->SetPos(pos);
			}
			else if (pos.y > 730)
			{
				pos.y = 730;
			}
			pos.x += 550 * Time::DeltaTime();
			mTr->SetPos(pos);

		}
		
		if (pos.y + 215 >= 1315.0f)
		{
			mAni->Play(L"bomb_explosion", false);
			mCol->SetCenter(Vector2(-1000000, -1000000));
			if (mAni->GetAniIndex(L"bomb_explosion") == 1)
			{
				sExp->Play(false);
			}
			if (mAni->IsComplete())
			{
				object::Destroy(this);
			}
		}

	}
	void Bomberbomb::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void Bomberbomb::Release()
	{
		GameObject::Release();
	}
	void Bomberbomb::OnCollisionEnter(Collider* other)
	{
		Sonic* sonic = dynamic_cast<Sonic*>(other->GetOwner());

		sonic->SetSonicState(Sonic::eSonicState::hurt_right);
	}
	void Bomberbomb::OnCollisionStay(Collider* other)
	{
	}
	void Bomberbomb::OnCollisionExit(Collider* other)
	{
	}
}