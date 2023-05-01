#include "sgLBEffect.h"
#include "sgSonic.h"
#include "sgLastboss.h"
#include "sgLogbridge.h"

#include "sgImage.h"
#include "sgResources.h"
#include "sgTime.h"

#include "sgTransform.h"
#include "sgAnimator.h"
#include "sgCollider.h"


namespace sg
{
	LBEffect::LBEffect(eLBE a)
		: mLBEState(a)
	{
		SetName(L"LBEffect");
	}
	LBEffect::~LBEffect()
	{
	}
	void LBEffect::Initialize()
	{
		mTr = GetComponent<Transform>();
		mAni = AddComponent<Animator>();
		mCol = AddComponent<Collider>();

		Image* lbe_attack = Resources::Load<Image>(L"lbe_attack", L"..\\Resources\\enemies\\lastboss_attack.bmp");
		Image* lbe_attack2 = Resources::Load<Image>(L"lbe_attack2", L"..\\Resources\\enemies\\lastboss_attack2.bmp");
		Image* lbe_Splash = Resources::Load<Image>(L"lbe_splash", L"..\\Resources\\enemies\\lastboss_splash.bmp");

		Image* lbe_explosion = Resources::Load<Image>(L"mb_exp", L"..\\Resources\\enemies\\MBexplosion.bmp");

		Image* nothing = Resources::Load<Image>(L"nothing", L"..\\Resources\\enemies\\bloominator.bmp");
		mAni->CreateAnimation(L"lbe_attack", lbe_attack2, Vector2::Zero, 4, 1, 4, Vector2::Zero, 0.1);
		mAni->CreateAnimation(L"lbe_attack_left1", lbe_attack, Vector2::Zero, 4, 4, 4, Vector2::Zero, 0.1);
		mAni->CreateAnimation(L"lbe_attack_left2", lbe_attack, Vector2(0, 37), 4, 4, 4, Vector2::Zero, 0.1);
		mAni->CreateAnimation(L"lbe_attack_right1", lbe_attack, Vector2(0, 74), 4, 4, 4, Vector2::Zero, 0.1);
		mAni->CreateAnimation(L"lbe_attack_right2", lbe_attack, Vector2(0, 111), 4, 4, 4, Vector2::Zero, 0.1);
		mAni->CreateAnimation(L"lbe_splash", lbe_Splash, Vector2::Zero, 4, 1, 4, Vector2::Zero, 0.1);
		mAni->CreateAnimation(L"lbe_exp", lbe_explosion, Vector2::Zero, 30, 1, 30, Vector2::Zero, 0.1);

		mAni->CreateAnimation(L"nothing", nothing, Vector2(38.0f, 0.0f), 4, 2, 1, Vector2::Zero, 0.1);

		mTr->SetScale(Vector2(2.5f, 2.5f));

		GameObject::Initialize();
	}
	void LBEffect::Update()
	{
		GameObject::Update();

		switch (mLBEState)
		{
		case sg::LBEffect::eLBE::splash:
			splash();
			break;
		case sg::LBEffect::eLBE::fire:
			fire();
			break;
		case sg::LBEffect::eLBE::fire2:
			fire2();
			break;
		case sg::LBEffect::eLBE::explosion:
			explosion();
			break;
		}
	}
	void LBEffect::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void LBEffect::Release()
	{
		GameObject::Release();
	}
	void LBEffect::OnCollisionEnter(Collider* other)
	{
		Sonic* sonic = dynamic_cast<Sonic*>(other->GetOwner());
		Logbridge* lob = dynamic_cast<Logbridge*>(other->GetOwner());

		if (sonic != nullptr)
		{
			Vector2 sonpos = sonic->GetComponent<Transform>()->GetPos();
			if (sonpos.x > mTr->GetPos().x && sonic->mFlame == false && sonic->GetHurt() == false)
			{
				sonic->SetSonicState(Sonic::eSonicState::hurt_left);
			}
			else if (sonpos.x < mTr->GetPos().x && sonic->mFlame == false && sonic->GetHurt() == false)
			{
				sonic->SetSonicState(Sonic::eSonicState::hurt_right);
			}
		}
	}
	void LBEffect::OnCollisionStay(Collider* other)
	{
	}
	void LBEffect::OnCollisionExit(Collider* other)
	{
	}
	void LBEffect::splash()
	{
		mCol->SetCenter(Vector2(-9999999, -999999));
		mAni->Play(L"lbe_splash", false);

		if (mAni->IsComplete())
		{
			object::Destroy(this);
		}
	}
	void LBEffect::fire()
	{
		Vector2 pos = mTr->GetPos();

		if (mTarget->mDir)
		{
			mAni->Play(L"lbe_attack_left1", true);
			mCol->SetCenter(Vector2(50, 48));
			mCol->SetSize(Vector2(55, 33));
			pos.x -= 200.0f * Time::DeltaTime();
			pos.y += 200.0f * Time::DeltaTime();
			mTr->SetPos(pos);

			if (pos.y >= 1260)
			{
				mAni->Play(L"lbe_attack_left2", true);
				mCol->SetCenter(Vector2(0, 35));
				mCol->SetSize(Vector2(100, 26));
				pos.x -= 200.0f * Time::DeltaTime();
				pos.y -= 200.0f * Time::DeltaTime();
				mTr->SetPos(pos);
				if (pos.x < 27000)
				{
					object::Destroy(this);
				}
			}
		}
		else if (mTarget->mDir == false)
		{
			mAni->Play(L"lbe_attack_right1", true);
			mCol->SetCenter(Vector2(140, 48));
			mCol->SetSize(Vector2(55, 33));
			pos.x += 200.0f * Time::DeltaTime();
			pos.y += 200.0f * Time::DeltaTime();
			mTr->SetPos(pos);

			if (pos.y >= 1260)
			{
				mAni->Play(L"lbe_attack_right2", true);
				mCol->SetCenter(Vector2(90	, 35));
				mCol->SetSize(Vector2(100, 26));
				pos.x += 200.0f * Time::DeltaTime();
				pos.y -= 200.0f * Time::DeltaTime();
				mTr->SetPos(pos);
				if (pos.x > 29000)
				{
					object::Destroy(this);
				}
			}
		}
	}
	void LBEffect::fire2()
	{
		Vector2 pos = mTr->GetPos();

		mAni->Play(L"lbe_attack", true);
		mCol->SetCenter(Vector2(0, 87.5));
		mCol->SetSize(Vector2(55, 25));
		pos.y += 200.0f * Time::DeltaTime();
		mTr->SetPos(pos);
	}
	void LBEffect::explosion()
	{	
		mTr->SetScale(Vector2(4, 4));
		mAni->Play(L"lbe_exp", false);
		if (mAni->IsComplete() == false)
		{
			mTr->SetPos(mTarget->GetComponent<Transform>()->GetPos());
		}

		if (mAni->IsComplete())
		{
			object::Destroy(this);
		}
	}
}