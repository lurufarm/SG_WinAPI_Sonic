#include "sgLogbridge.h"
#include "sgSonic.h"

#include "sgImage.h"
#include "sgResources.h"
#include "sgGroundMgr.h"
#include "sgSound.h"

#include "sgTransform.h"
#include "sgAnimator.h"
#include "sgCollider.h"

namespace sg
{
	Logbridge::Logbridge()
	{
		SetName(L"Logbridge");
	}
	Logbridge::~Logbridge()
	{
	}
	void Logbridge::Initialize()
	{
		mAni = AddComponent<Animator>();
		mCol = AddComponent<Collider>();

		Image* logbridge = Resources::Load<Image>(L"logb", L"..\\Resources\\object\\logbridge.bmp");
		
		mAni->CreateAnimation(L"logb_stable", logbridge, Vector2::Zero, 9, 3, 6, Vector2::Zero, 0.15);
		mAni->CreateAnimation(L"logb_burning", logbridge, Vector2(0, 128), 9, 3, 9, Vector2::Zero, 0.08);
		mAni->CreateAnimation(L"logb_breaking", logbridge, Vector2(0, 2568), 9, 3, 6, Vector2::Zero, 0.08);

		Transform* tr = GetComponent<Transform>();
		tr->SetScale(Vector2(2.5f, 2.5f));

		mAni->Play(L"logb_stable",true);
		sBreaking = Resources::Load<Sound>(L"Breakingsound", L"..\\Resources\\sound\\object_crash.wav");

		mCol->SetCenter(Vector2(60.0f, 60.0f));
		mCol->SetSize(Vector2(480.0f, 10.0f));
		
		GameObject::Initialize();
	}
	void Logbridge::Update()
	{
		GameObject::Update();
		if (mAni->GetAniIndex(L"logb_breaking") == 1 || mAni->GetAniIndex(L"logb_burning") == 1)
		{
			sBreaking->Play(false);
			mCol->SetCenter(Vector2(50000, 50000));
		}

	}
	void Logbridge::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void Logbridge::Release()
	{
		GameObject::Release();
	}
	void Logbridge::OnCollisionEnter(Collider* other)
	{
		Sonic* sonic = dynamic_cast<Sonic*>(other->GetOwner());
		LBEffect* lbe = dynamic_cast<LBEffect*>(other->GetOwner());

		if (other->GetOwner() == sonic)
		{
			mUse = true;
			ColPosControl(sonic->GetComponent<Collider>(), this);
		}

		if (other->GetOwner() == lbe)
		{
			mAni->Play(L"logb_burning", false);
			mUse = false;
		}

	}
	void Logbridge::OnCollisionStay(Collider* other)
	{
		Sonic* sonic = dynamic_cast<Sonic*>(other->GetOwner());

		if (other->GetOwner() == sonic)
		{
			mUse = true;
			ColPosControl(sonic->GetComponent<Collider>(), this);
		}
	}
	void Logbridge::OnCollisionExit(Collider* other)
	{
		Sonic* sonic = dynamic_cast<Sonic*>(other->GetOwner());

		if (other->GetOwner() == sonic)
		{
			mUse = false;
		}
	}
}