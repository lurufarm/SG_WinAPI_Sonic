#include "sgEnemyEffect.h"
#include "sgMiniboss.h"
#include "sgLastboss.h"
#include "sgSonic.h"

#include "sgImage.h"
#include "sgResources.h"
#include "sgTime.h"

#include "sgTransform.h"
#include "sgAnimator.h"
#include "sgCollider.h"
#include "sgCollisionManager.h"
#include "sgRigidbody.h"

namespace sg
{
	EnemyEffect::EnemyEffect()
		: mTime(0.0f)
		, mMB(nullptr)
	{
		SetName(L"EnemyEFfect");
	}
	EnemyEffect::~EnemyEffect()
	{
	}
	void EnemyEffect::Initialize()
	{
		mTr = GetComponent<Transform>();
		mAni = AddComponent<Animator>();
		mCol = AddComponent<Collider>();

		Image* MB_attack = Resources::Load<Image>(L"mb_attack", L"..\\Resources\\enemies\\MBattack.bmp");
		Image* MB_explosion = Resources::Load<Image>(L"mb_exp", L"..\\Resources\\enemies\\MBexplosion.bmp");
		Image* explosion = Resources::Load<Image>(L"explosion", L"..\\Resources\\enemies\\explosion.bmp");
		Image* nothing = Resources::Load<Image>(L"nothing2", L"..\\Resources\\enemies\\bloominator.bmp");
		mAni->CreateAnimation(L"mba_left", MB_attack, Vector2::Zero, 13, 2, 13, Vector2::Zero, 0.1);
		mAni->CreateAnimation(L"mba_right", MB_attack, Vector2(0.0f, 45.0f), 13, 2, 13, Vector2::Zero, 0.1);
		mAni->CreateAnimation(L"mb_exp", MB_explosion, Vector2::Zero, 30, 1, 30, Vector2::Zero, 0.1);
		mAni->CreateAnimation(L"explosion", explosion, Vector2::Zero, 7, 1, 7, Vector2::Zero, 0.05);
		mAni->CreateAnimation(L"nothing2", nothing, Vector2(38.0f, 0.0f), 4, 2, 1, Vector2::Zero, 0.1);

		mEEState = eEEState::None;

		mTr->SetScale(Vector2(2.5f, 2.5f));

		GameObject::Initialize();
	}
	void EnemyEffect::Update()
	{
		GameObject::Update();

		switch (mEEState)
		{
		case sg::EnemyEffect::eEEState::None:
			None();
			break;
		case sg::EnemyEffect::eEEState::MBA_left:
			MBA_left();
			break;
		case sg::EnemyEffect::eEEState::MBA_right:
			MBA_right();
			break;
		case sg::EnemyEffect::eEEState::MBA_explosion:
			MBA_explosion();
			break;
		case sg::EnemyEffect::eEEState::explosion:
			explosion();
			break;
		}
	}
	void EnemyEffect::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void EnemyEffect::Release()
	{
		GameObject::Release();
	}
	void EnemyEffect::OnCollisionEnter(Collider* other)
	{
		Sonic* sonic = dynamic_cast<Sonic*>(other->GetOwner());

		if (other->GetOwner() == nullptr)
			return;

		if (sonic->mFlame == false)
		{
			if (sonic->GetComponent<Transform>()->GetPos().x <=
				this->GetComponent<Transform>()->GetPos().x
				&& sonic->GetHurt() == false)
			{
				sonic->SetSonicState(Sonic::eSonicState::hurt_right);
			}
			else if (sonic->GetComponent<Transform>()->GetPos().x >
				this->GetComponent<Transform>()->GetPos().x
				&& sonic->GetHurt() == false)
			{
				sonic->SetSonicState(Sonic::eSonicState::hurt_left);
			}
		}
	}
	void EnemyEffect::OnCollisionStay(Collider* other)
	{
	}
	void EnemyEffect::OnCollisionExit(Collider* other)
	{
	}
	void EnemyEffect::None()
	{
		mAni->Play(L"nothing2", true);
	}
	void EnemyEffect::MBA_left()
	{
		mCol->SetSize(Vector2(375.0f, 90.0));
		mCol->SetCenter(Vector2(40.0f, 0.0f));
		Vector2 MBpos = mMB->GetComponent<Transform>()->GetPos();
		mTr->SetPos(Vector2(MBpos.x - 300, MBpos.y + 80));
		mAni->Play(L"mba_left", false);

		if (mAni->IsComplete())
		{
			mEEState = eEEState::None;
			mAni->Reset();
		}
	}
	void EnemyEffect::MBA_right()
	{
		mCol->SetSize(Vector2(375.0f, 90.0));
		mCol->SetCenter(Vector2(-80.0f,0.0f));
		Vector2 MBpos = mMB->GetComponent<Transform>()->GetPos();
		mTr->SetPos(Vector2(MBpos.x + 300, MBpos.y + 80));
		mAni->Play(L"mba_right", false);

		if (mAni->IsComplete())
		{
			mEEState = eEEState::None;
			mAni->Reset();
		}
	}
	void EnemyEffect::MBA_explosion()
	{
		if (SceneManager::GetActiveScene2() == eSceneType::Play && mMB != nullptr)
		{
			mTr->SetPos(mMB->GetComponent<Transform>()->GetPos());
			mTr->SetScale(Vector2(5.0f, 5.0f));
			mAni->Play(L"mb_exp", false);
			if (mAni->IsComplete())
			{
				mEEState = eEEState::None;
			}
		}
		else if (SceneManager::GetActiveScene2() == eSceneType::Play && mLB != nullptr)
		{
			mTr->SetPos(mLB->GetComponent<Transform>()->GetPos());
			mTr->SetScale(Vector2(5.0f, 5.0f));
			mAni->Play(L"mb_exp", false);
			if (mAni->IsComplete())
			{
				mEEState = eEEState::None;
			}
		}
	
		

	}
	void EnemyEffect::explosion()
	{
		mTr->SetPos(Vector2(19100.0f, 2300.0f));
		mTr->SetScale(Vector2(3.0f, 3.0f));
		mAni->Play(L"explosion", true);
		mTime += Time::DeltaTime();

		if (mTime > 7.0f)
		{
			mEEState = eEEState::None;
			mTime = 0.0f;
		}
	}
}