#include "sgMiniboss.h"
#include "sgEnemyEffect.h"
#include "sgSonic.h"
#include "sgScenechange.h"

#include "sgImage.h"
#include "sgResources.h"
#include "sgTime.h"
#include "sgSound.h"
#include "sgCollisionManager.h"

#include "sgTransform.h"
#include "sgAnimator.h"
#include "sgCollider.h"
#include "sgRigidbody.h"

namespace sg
{
	Miniboss::Miniboss()
		: hp(10)
		, mPlayer(nullptr)
		, mMeffect(nullptr)
		, mUp(false)
		, mDir(false)
		, mDeath(false)
		, mTime(0.0f)
	{
		SetName(L"Miniboss");
	}
	Miniboss::~Miniboss()
	{
	}
	void Miniboss::Initialize()
	{
		mAni = AddComponent<Animator>();
		mCol= AddComponent<Collider>();
		mTr = GetComponent<Transform>();
		Image* miniboss = Resources::Load<Image>(L"miniboss", L"..\\Resources\\enemies\\miniboss.bmp");
		mAni->CreateAnimation(L"mb_idle_left", miniboss, Vector2::Zero, 12, 5, 2, Vector2::Zero, 0.05);
		mAni->CreateAnimation(L"mb_idle_right", miniboss, Vector2(0.0f, 200.0f), 12, 5, 2, Vector2::Zero, 0.05);
		mAni->CreateAnimation(L"mb_attack_left", miniboss, Vector2(0.0f, 100.0f), 12, 5, 12, Vector2::Zero, 0.05);
		mAni->CreateAnimation(L"mb_attack_right", miniboss, Vector2(0.0f, 300.0f), 12, 5, 12, Vector2::Zero, 0.05);
		mAni->CreateAnimation(L"mb_attacked_left", miniboss, Vector2(0.0f, 400.0f), 12, 5, 1, Vector2::Zero, 0.05);
		mAni->CreateAnimation(L"mb_attacked_right", miniboss, Vector2(100.0f, 400.0f), 12, 5, 1, Vector2::Zero, 0.05);
		mTr->SetScale(Vector2(2.5f, 2.5f));
		mAni->Play(L"mb_idle_left", true);
		mCol->SetSize(Vector2(160.0f, 145.0f));
		mCol->SetCenter(Vector2(42.5f, 65.0f));
		mMBState = eMBState::idle;
		mMeffect = object::Instantiate<EnemyEffect>(eLayerType::mEffect, eSceneType::Play);
		mMeffect->SetTarget(this);

		sAttacked = Resources::Load<Sound>(L"boss_attacked", L"..\\Resources\\sound\\boss_attacked.wav");
		sExp = Resources::Load<Sound>(L"boss_explosion", L"..\\Resources\\sound\\boss_explosion.wav");

		GameObject::Initialize();
	}
	void Miniboss::Update()
	{
		GameObject::Update();

		if (hp <= 0)
		{
			mMBState = eMBState::death;
		}

		switch (mMBState)
		{
		case sg::Miniboss::eMBState::idle:
			idle();
			break;
		case sg::Miniboss::eMBState::move_up:
			move_up();
			break;
		case sg::Miniboss::eMBState::move:
			move();
			break;
		case sg::Miniboss::eMBState::attack:
			attack();
			break;
		case sg::Miniboss::eMBState::attacked:
			attacked();
			break;
		case sg::Miniboss::eMBState::death:
			death();
			break;
		}
	}
	void Miniboss::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void Miniboss::Release()
	{
		GameObject::Release();
	}
	void Miniboss::OnCollisionEnter(Collider* other)
	{
		Sonic* sonic = dynamic_cast<Sonic*>(other->GetOwner());

		if (sonic->GetSonicState() == Sonic::eSonicState::jump_left
			|| sonic->GetSonicState() == Sonic::eSonicState::jump_right
			|| sonic->GetSonicState() == Sonic::eSonicState::jump2_left
			|| sonic->GetSonicState() == Sonic::eSonicState::jump2_right)
		{
			hp--;
			mMBState = eMBState::attacked;
			Vector2 velocity = sonic->GetComponent<Rigidbody>()->GetVelocity();
			velocity.y = -400.0f;
			sonic->GetComponent<Rigidbody>()->SetVelocity(velocity);
		}
		else if (sonic->GetComponent<Transform>()->GetPos().x <=
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
	void Miniboss::OnCollisionStay(Collider* other)
	{
	}
	void Miniboss::OnCollisionExit(Collider* other)
	{
	}
	void Miniboss::idle()
	{
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::mEffect, false);
		Vector2 mbpos = mTr->GetPos();

		if (mPlayer->GetComponent<Transform>()->GetPos().x > mbpos.x + 80)
		{
			mAni->Play(L"mb_idle_right", true);
		}
		else
		{
			mAni->Play(L"mb_idle_left", true);
		}
		if (hp % 3 == 0)
		{
			mMBState = eMBState::attack;
		}
	}
	void Miniboss::move_up()
	{
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::mEffect, false);
		Vector2 mbpos = mTr->GetPos();

		if (mUp == false)
		{
			mbpos.y -= 200.0f * Time::DeltaTime();
			mTr->SetPos(mbpos);
			if (mbpos.y < 1730) {
				mMBState = eMBState::move;
				mUp = true;
			}
		}
		else if (mUp) // 아래로 이동
		{
			mbpos.y += 200.0f * Time::DeltaTime();
			mTr->SetPos(mbpos);
			if (mbpos.y >= 2000)
			{
				mMBState = eMBState::attack;
			}
			if (mDir)
			{
				mDir = false;
			}
			else
			{
				mDir = true;
			}
		}
	}
	void Miniboss::move()
	{
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::mEffect, false);
		Vector2 mbpos = mTr->GetPos();

		if (mDir && mUp) // 왼쪽 위에 있을 때 오른쪽으로 이동
		{
			mAni->Play(L"mb_idle_right", true);
			mbpos.x += 200.0f * Time::DeltaTime();
			mTr->SetPos(mbpos);
			if (mbpos.x > 18910)
			{
				mMBState = eMBState::move_up;
			}
		}
		else if (mDir == false && mUp) // 오른쪽 위에 있을 때 왼쪽으로 이동
		{
			mAni->Play(L"mb_idle_left", true);
			mbpos.x -= 200.0f * Time::DeltaTime();
			mTr->SetPos(mbpos);

			if (mbpos.x < 18160)
			{
				mMBState = eMBState::move_up;
			}
		}
	}
	void Miniboss::attack()
	{
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::mEffect, true);

		Vector2 mbpos = mTr->GetPos();
		if (mbpos.x > 18910)
		{
			mAni->Play(L"mb_attack_left", false);
			mMeffect->SetEEState(EnemyEffect::eEEState::MBA_left);
		}
		else if (mbpos.x < 18910)
		{
			mAni->Play(L"mb_attack_right", false);
			mMeffect->SetEEState(EnemyEffect::eEEState::MBA_right);
		}

		if (mAni->IsComplete())
		{
			mMBState = eMBState::idle;
			mUp = false;
			mAni->Reset();
		}
	}
	void Miniboss::attacked()
	{
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::mEffect, false);
		Vector2 mbpos = mTr->GetPos();
		sAttacked->Play(false);
		if (mPlayer->GetComponent<Transform>()->GetPos().x < mbpos.x)
		{
			mAni->Play(L"mb_attacked_right", false);
		}
		else
		{
			mAni->Play(L"mb_attacked_left", false);
		}

		if (mAni->IsComplete())
		{
			mMBState = eMBState::idle;
			mAni->Reset();
		}

		if (hp % 4 == 0)
		{
			if (mDir)
			{
				mAni->Play(L"mb_idle_right", true);
			}
			else
			{
				mAni->Play(L"mb_idle_left", true);
			}
			mMBState = eMBState::move_up;
		}
		if (hp % 3 == 0)
		{
			mMBState = eMBState::attack;
		}

	}
	void Miniboss::death()
	{
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::mEffect, false);
		Vector2 mbpos = mTr->GetPos();
		if (mbpos.x < 19410 && mDeath == false) 
		{
			mMeffect->SetEEState(EnemyEffect::eEEState::MBA_explosion);
			mbpos.x += 300.0f * Time::DeltaTime();
			mTr->SetPos(mbpos);
		}
		mTime += Time::DeltaTime();
		if (mDeath == false)
		{
			sExp->Play(false);
			Scenechange* sc = object::Instantiate<Scenechange>(eLayerType::ForeObject, eSceneType::Play);
			mDeath = true;
		}
		if (mTime >= 3.0f)
		{
			SceneManager::LoadScene(eSceneType::Play2);
		}
	}

}