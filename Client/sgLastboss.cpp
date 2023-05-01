#include "sgLastboss.h"
#include "sgLastbossR.h"
#include "sgSonic.h"
#include "sgLBEffect.h"
#include "sgEnemyEffect.h"

#include "sgImage.h"
#include "sgResources.h"
#include "sgTime.h"
#include "sgObject.h"
#include "sgSound.h"

#include "sgTransform.h"
#include "sgAnimator.h"
#include "sgCollider.h"
#include "sgRigidbody.h"
#include "sgCollisionManager.h"


namespace sg
{
	Lastboss::Lastboss()
		: hp(10)
		, mTime(0.0f)
		, mPlayer(nullptr)
		, mDir(false)
		, mLayerChange(false)
		, mAttack_log(false)
		, mAttack(0)
		, mdAttack(false)
		, mStart(false)
		, mLBr(nullptr)
		, mLBrb(false)
	{
		SetName(L"Lastboss");
	}
	Lastboss::~Lastboss()
	{
	}
	void Lastboss::Initialize()
	{
		mTr = GetComponent<Transform>();
		mAni = AddComponent<Animator>();
		mCol = AddComponent<Collider>();

		Image* lastboss = Resources::Load<Image>(L"lastboss", L"..\\Resources\\enemies\\lastboss.bmp");
		mAni->CreateAnimation(L"lb_idle_left", lastboss, Vector2(111, 0), 4, 7, 1, Vector2::Zero, 0.1);
		mAni->CreateAnimation(L"lb_idle_right", lastboss, Vector2::Zero, 4, 7, 1, Vector2::Zero, 0.1);
		mAni->CreateAnimation(L"lb_attacked_left", lastboss, Vector2(111, 91), 4, 7, 2, Vector2::Zero, 0.1);
		mAni->CreateAnimation(L"lb_attacked_right", lastboss, Vector2(0, 91), 4, 7, 2, Vector2::Zero, 0.1);
		mAni->CreateAnimation(L"lb_wet_left", lastboss, Vector2(0, 273), 4, 7, 4, Vector2::Zero, 0.13);
		mAni->CreateAnimation(L"lb_wet_right", lastboss, Vector2(0, 182), 4, 7, 4, Vector2::Zero, 0.13);
		mAni->CreateAnimation(L"lb_attack_left", lastboss, Vector2(0, 364), 4, 7, 3, Vector2::Zero, 0.2);
		mAni->CreateAnimation(L"lb_attack_right", lastboss, Vector2(0, 455), 4, 7, 3, Vector2::Zero, 0.2);
		mAni->CreateAnimation(L"lb_death_left", lastboss, Vector2(111, 546), 4, 7, 1, Vector2::Zero, 0.1);
		mAni->CreateAnimation(L"lb_death_right", lastboss, Vector2(0, 546), 4, 7, 1, Vector2::Zero, 0.1);
		Image* nothing = Resources::Load<Image>(L"nothing", L"..\\Resources\\enemies\\bloominator.bmp");
		mAni->CreateAnimation(L"nothing", nothing, Vector2(38.0f, 0.0f), 4, 2, 1, Vector2::Zero, 0.1);
		
		mTr->SetScale(Vector2(2.5f, 2.5f));
		mCol->SetCenter(Vector2(57.5f, 75.0f));
		mCol->SetSize(Vector2(165.0f, 150.0f));

		sCL = Resources::Load<Sound>(L"boss_splash", L"..\\Resources\\sound\\lb_changelayer.wav");
		sAttack = Resources::Load<Sound>(L"boss_attack", L"..\\Resources\\sound\\enemy_bullet.wav");
		sAttacked = Resources::Load<Sound>(L"boss_attacked", L"..\\Resources\\sound\\boss_attacked.wav");
		sExp = Resources::Load<Sound>(L"boss_explosion", L"..\\Resources\\sound\\boss_explosion.wav");

		mLBState = eLBState::idle();
		
		GameObject::Initialize();
	}
	void Lastboss::Update()
	{
		GameObject::Update();

		if (hp <= 0)
		{
			mLBState = eLBState::death;
		}

		switch (mLBState)
		{
		case sg::Lastboss::eLBState::idle:
			idle();
			break;
		case sg::Lastboss::eLBState::move_norm:
			move_norm();
			break;
		case sg::Lastboss::eLBState::changelayer:
			changelayer();
			break;
		case sg::Lastboss::eLBState::attack_log:
			attack_log();
			break;
		case sg::Lastboss::eLBState::attack_player:
			attack_player();
			break;
		case sg::Lastboss::eLBState::death:
			death();
			break;
		}
	}
	void Lastboss::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void Lastboss::Release()
	{
		GameObject::Release();
	}
	void Lastboss::OnCollisionEnter(Collider* other)
	{
		Sonic* sonic = dynamic_cast<Sonic*>(other->GetOwner());
		Vector2 sonpos = sonic->GetComponent<Transform>()->GetPos();

		if (sonpos.x > mTr->GetPos().x &&
			(sonic->GetSonicState() == Sonic::eSonicState::jump_left
				|| sonic->GetSonicState() == Sonic::eSonicState::jump_right
				|| sonic->GetSonicState() == Sonic::eSonicState::jump2_left
				|| sonic->GetSonicState() == Sonic::eSonicState::jump_right))
		{
			sAttacked->Play(false);
			hp--;
			mAni->Play(L"lb_attacked_left", false);
			Vector2 velocity = sonic->GetComponent<Rigidbody>()->GetVelocity();
			velocity.y = -400.0f;
			sonic->GetComponent<Rigidbody>()->SetVelocity(velocity);

		}
		else if (sonpos.x < mTr->GetPos().x &&
			(sonic->GetSonicState() == Sonic::eSonicState::jump_left
				|| sonic->GetSonicState() == Sonic::eSonicState::jump_right
				|| sonic->GetSonicState() == Sonic::eSonicState::jump2_left
				|| sonic->GetSonicState() == Sonic::eSonicState::jump_right))
		{
			sAttacked->Play(false);
			hp--;
			mAni->Play(L"lb_attacked_right", false);
			Vector2 velocity = sonic->GetComponent<Rigidbody>()->GetVelocity();
			velocity.y = -400.0f;
			sonic->GetComponent<Rigidbody>()->SetVelocity(velocity);

		}
		else if (sonpos.x > mTr->GetPos().x && sonic->mFlame == false && sonic->GetHurt() == false)
		{
			sonic->SetSonicState(Sonic::eSonicState::hurt_left);
		}
		else if (sonpos.x < mTr->GetPos().x && sonic->mFlame == false && sonic->GetHurt() == false)
		{
			sonic->SetSonicState(Sonic::eSonicState::hurt_right);

		}
		if (mAni->IsComplete())
		{
			mAni->Reset();
		}

	}
	void Lastboss::OnCollisionStay(Collider* other)
	{
	}
	void Lastboss::OnCollisionExit(Collider* other)
	{
	}
	void Lastboss::idle()
	{
		Transform* pTr = mPlayer->GetComponent<Transform>();
		Vector2 pPos = pTr->GetPos();
		Vector2 mPos = mTr->GetPos();

		if (pPos.x + 62.5 < mPos.x + 138.75)
		{
			mAni->Play(L"lb_idle_left", true);
		}
		else
		{
			mAni->Play(L"lb_idle_right", true);
		}

		if (mAttack_log == false && mStart)
		{
			mLBState = eLBState::attack_log;
		}
	}
	void Lastboss::move_norm()
	{
		Vector2 mPos = mTr->GetPos();
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Boss, false);

		if (mLBrb == false)
		{
			mLBr = object::Instantiate<LastbossR>(mPos, eLayerType::hideObjects, eSceneType::Play2);
			mLBr->SetLB(this);
			mLBrb = true;
		}
		if (mDir == false)
		{
			mAni->Play(L"nothing", true);
			mCol->SetCenter(Vector2(-123123123, -123123123));

			mPos.x += 200.0f * Time::DeltaTime();
			mTr->SetPos(mPos);
			if (mPos.x >= 28720)
			{
				mDir = true;
				mLayerChange = true;
				mLBState = eLBState::changelayer;
			}
		}
		else
		{
			mAni->Play(L"nothing", true);
			mCol->SetCenter(Vector2(-123123123, -123123123));
				mPos.x -= 200.0f * Time::DeltaTime();
				mTr->SetPos(mPos);
			if (mPos.x <= 27750)
			{
				mDir = false;
				mLayerChange = true;
				mLBState = eLBState::changelayer;
			}
		}
	}
	void Lastboss::changelayer()
	{
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::mEffect, false);
		Vector2 pos = mTr->GetPos();
		mTime += Time::DeltaTime();
		if (mLBrb)
		{
			object::Destroy(mLBr);
			mLBrb = false;
		}

		if (mTime >= 1.5f)
		{
			if (mLayerChange)
			{

				if (mDir == false)
				{
					sCL->Play(false);
					object::LBEffectInstantiate(Vector2(pos.x + 20, pos.y - 20), eLayerType::mEffect, LBEffect::eLBE::splash);
					mCol->SetCenter(Vector2(57.5f, 75.0f));
					mAni->Play(L"lb_wet_left", false);
					if (mAni->IsComplete())
					{
						mAni->Reset();
						mLBState = eLBState::attack_player;
					}
				}
				else
				{
					sCL->Play(false);
					object::LBEffectInstantiate(Vector2(pos.x + 20, pos.y - 20), eLayerType::mEffect, LBEffect::eLBE::splash);
					mCol->SetCenter(Vector2(57.5f, 75.0f));
					mAni->Play(L"lb_wet_right", false);
					if (mAni->IsComplete())
					{
						mAni->Reset();
						mLBState = eLBState::attack_player;
					}
				}
			}
			else
			{
				Vector2 pos = mTr->GetPos();
				sCL->Play(false);
				object::LBEffectInstantiate(Vector2(pos.x + 20, pos.y - 20), eLayerType::mEffect, LBEffect::eLBE::splash);
				mLBState = eLBState::move_norm;
			}
			mTime = 0.0f;
		}
	}
	void Lastboss::attack_log()
	{
		mTime += Time::DeltaTime();
		Transform* pTr = mPlayer->GetComponent<Transform>();
		Vector2 pPos = pTr->GetPos();
		Vector2 mPos = mTr->GetPos();

		if (mAni->GetAniIndex(L"lb_attack_right") == 1 && mAttack_log == false)
		{
			sAttack->Play(false);
			LBEffect* fire = object::LBEffectInstantiate(Vector2(mPos.x + 110, mPos.y + 155), eLayerType::mEffect, LBEffect::eLBE::fire2);
			fire->SetTarget(this);
			mAttack_log = true;
		}

		if (mTime >= 1.5f)
		{

			mAni->Play(L"lb_attack_right", false);

			mTime = 0.0f;
		}
			if (mAni->IsComplete())
			{
				mAni->Reset();
				mLBState = eLBState::changelayer;
			}
	}
	void Lastboss::attack_player()
	{
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::mEffect, true);
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Boss, true);

		Transform* pTr = mPlayer->GetComponent<Transform>();
		Vector2 pPos = pTr->GetPos();
		Vector2 mPos = mTr->GetPos();
		if (mAni->GetAniIndex(L"lb_attack_left") == 1 && mdAttack == false)
		{
			LBEffect* fire = object::LBEffectInstantiate(Vector2(mPos.x + 110, mPos.y + 155), eLayerType::mEffect, LBEffect::eLBE::fire);
			sAttack->Play(false);
			fire->SetTarget(this);
			mAttack++;
			mdAttack = true;
		}
		else if (mAni->GetAniIndex(L"lb_attack_right") == 1 && mdAttack == false)
		{
			LBEffect* fire = object::LBEffectInstantiate(Vector2(mPos.x + 110, mPos.y + 155), eLayerType::mEffect, LBEffect::eLBE::fire);
			sAttack->Play(false);
			fire->SetTarget(this);
			mAttack++;
			mdAttack = true;
		}

		if (mAttack < 2)
		{
			mTime += Time::DeltaTime();

			if (mTime >= 1.5f) {

				if (mDir)
				{
					mAni->Play(L"lb_attack_left", false);
				}
				else
				{
					mAni->Play(L"lb_attack_right", false);
				}


				if (mAni->IsComplete())
				{
					mdAttack = false;
					mAni->Reset();
				}
				mTime = 0.0f;
			}
		}
		else
		{
			mAttack = 0;
			mLayerChange = false;
			mLBState = eLBState::changelayer;
		}
	}
	void Lastboss::death()
	{
		mAni->Play(L"lb_death_right", true);
		sExp->Play(false);
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::mEffect, false);
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Boss, false);
		Vector2 pos = mTr->GetPos();

		if (mLBrb == false)
		{
			LBEffect* exp = object::LBEffectInstantiate(Vector2(pos), eLayerType::mEffect, LBEffect::eLBE::explosion);
			exp->SetTarget(this);
			mLBrb = true;
		}
		pos.y += 200 * Time::DeltaTime();
		pos.x += 100 * Time::DeltaTime();
		mTr->SetPos(pos);
	}
}