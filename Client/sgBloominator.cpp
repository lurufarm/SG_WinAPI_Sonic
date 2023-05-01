#include "sgBloominator.h"
#include "sgBloomBullet.h"
#include "sgSonic.h"

#include "sgTime.h"
#include "sgScene.h"
#include "sgImage.h"
#include "sgObject.h"
#include "sgResources.h"
#include "sgSound.h"
#include "sgCollisionManager.h"


#include "sgAnimator.h"
#include "sgCollider.h"
#include "sgRigidbody.h"
#include "sgTransform.h"

namespace sg
{
	Bloominator::Bloominator()
		: mTime(0.0f)
		, mAbility(2.0f)
		, mbShoot(false)
	{
		this->SetName(L"Bloominator");
	}
	Bloominator::~Bloominator()
	{
	}
	void Bloominator::Initialize()
	{
		Image* bloom = Resources::Load<Image>(L"bloom", L"..\\Resources\\enemies\\bloominator.bmp");
		Image* boom = Resources::Load<Image>(L"animal_boom", L"..\\Resources\\animals\\boom.bmp");

		mAnimator->CreateAnimation(L"bloom_idle", bloom, Vector2::Zero, 4, 2, 1, Vector2::Zero, 0.15);
		mAnimator->CreateAnimation(L"bloom_shoot", bloom, Vector2(0, 54), 4, 2, 4, Vector2::Zero, 0.15);
		mAnimator->CreateAnimation(L"animal_boom", boom, Vector2::Zero, 5, 1, 5, Vector2::Zero, 0.1);

		mBloomState = eBloomState::idle();
		Transform* tr = GetComponent<Transform>();
		tr->SetScale(Vector2(2.5f, 2.5f));
		mRigidbody->SetMass(1.0);
		mRigidbody->SetGround(true);

		sBullet = Resources::Load<Sound>(L"enemy_bullet", L"..\\Resources\\sound\\enemy_bullet.wav");
		sDeath = Resources::Load<Sound>(L"enemy_s_death", L"..\\Resources\\sound\\enemy_death.wav");
		sBoom = Resources::Load<Sound>(L"enemy_s_boom", L"..\\Resources\\sound\\sonic_getitem.wav");

		GameObject::Initialize();

	}
	void Bloominator::Update()
	{
		GameObject::Update();

		switch (mBloomState)
		{
		case sg::Bloominator::eBloomState::idle:
			idle();
			break;
		case sg::Bloominator::eBloomState::shoot:
			shoot();
			break;
		//case sg::Bloominator::eBloomState::shoot_right:
		//	shoot_right();
		//	break;
		case sg::Bloominator::eBloomState::death:
			death();
			break;
		}
	}
	void Bloominator::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void Bloominator::Release()
	{
		GameObject::Release();
	}
	void Bloominator::OnCollisionEnter(Collider* other)
	{
		Sonic* sonic = dynamic_cast<Sonic*>(other->GetOwner());
		if (sonic == nullptr)
			return;

		if (sonic->mAbility > this->mAbility
			|| sonic->GetSonicState() == Sonic::eSonicState::jump_left
			|| sonic->GetSonicState() == Sonic::eSonicState::jump_right
			|| sonic->GetSonicState() == Sonic::eSonicState::jump2_left
			|| sonic->GetSonicState() == Sonic::eSonicState::jump2_right
			|| sonic->GetSonicState() == Sonic::eSonicState::spindash_left
			|| sonic->GetSonicState() == Sonic::eSonicState::spindash_right
			|| sonic->GetSonicState() == Sonic::eSonicState::rolling_left
			|| sonic->GetSonicState() == Sonic::eSonicState::rolling_right)
		{
			sBoom->Play(false);
			mBloomState = eBloomState::death;
			Vector2 velocity = sonic->GetComponent<Rigidbody>()->GetVelocity();
			velocity.y = -400.0f;
			sonic->GetComponent<Rigidbody>()->SetVelocity(velocity);
		}
		else if (sonic->GetComponent<Transform>()->GetPos().x <=
			this->GetComponent<Transform>()->GetPos().x
			&& (sonic->mAbility <= this->mAbility
			&& sonic->GetSonicState() != Sonic::eSonicState::jump_left
			&& sonic->GetSonicState() != Sonic::eSonicState::jump_right
			&& sonic->GetSonicState() != Sonic::eSonicState::jump2_left
			&& sonic->GetSonicState() != Sonic::eSonicState::jump2_right
			&& sonic->GetSonicState() != Sonic::eSonicState::spindash_left
			&& sonic->GetSonicState() != Sonic::eSonicState::spindash_right
			&& sonic->GetSonicState() != Sonic::eSonicState::rolling_left
			&& sonic->GetSonicState() != Sonic::eSonicState::rolling_right))
		{
			if (sonic->GetHurt() == false)
			{
				sonic->SetSonicState(Sonic::eSonicState::hurt_right);
			}
		}
		else if (sonic->GetComponent<Transform>()->GetPos().x >
			this->GetComponent<Transform>()->GetPos().x
			&& (sonic->mAbility <=  this->mAbility
				&& sonic->GetSonicState() != Sonic::eSonicState::jump_left
				&& sonic->GetSonicState() != Sonic::eSonicState::jump_right
				&& sonic->GetSonicState() != Sonic::eSonicState::jump2_left
				&& sonic->GetSonicState() != Sonic::eSonicState::jump2_right
				&& sonic->GetSonicState() != Sonic::eSonicState::spindash_left
				&& sonic->GetSonicState() != Sonic::eSonicState::spindash_right
				&& sonic->GetSonicState() != Sonic::eSonicState::rolling_left
				&& sonic->GetSonicState() != Sonic::eSonicState::rolling_right))
		{
			if (sonic->GetHurt() == false)
			{
				sonic->SetSonicState(Sonic::eSonicState::hurt_left);
			}
		}
	}
	void Bloominator::OnCollisionStay(Collider* other)
	{
	}
	void Bloominator::OnCollisionExit(Collider* other)
	{
	}
	void Bloominator::idle()
	{
		mCollider->SetCenter(Vector2(15.0f, 0.0f));
		mCollider->SetSize(Vector2(70.0f, 130.0f));
		mAnimator->Play(L"bloom_idle", false);
		mTime += Time::DeltaTime();
		if (mTime >= 3.0f)
		{
			mBloomState = eBloomState::shoot;
			mTime = 0.0;
		}
	}

	void Bloominator::shoot()
	{
		Transform* tr = GetComponent<Transform>();
		if (mbShoot == false && mSonic->GetComponent<Transform>()->GetPos().x > tr->GetPos().x)
		{
			mAnimator->Play(L"bloom_shoot", false);
			Vector2 BloomPos = tr->GetPos();
			mLeftBullet = object::Instantiate<BloomBullet>(BloomPos, eLayerType::Bullet, SceneManager::GetActiveScene2());
			if (fabs(mSonic->GetComponent<Transform>()->GetPos().x - BloomPos.x) <= 500
				&& fabs(mSonic->GetComponent<Transform>()->GetPos().y - BloomPos.y) <= 200)
			{
				sBullet->Play(false);
			}
			Rigidbody* bulletrb = mLeftBullet->GetComponent<Rigidbody>();
			bulletrb->SetVelocity(Vector2(200.0f, -500.0f));
		}
		else if (mbShoot == false && mSonic->GetComponent<Transform>()->GetPos().x < tr->GetPos().x)
		{
			mAnimator->Play(L"bloom_shoot", false);
			Vector2 BloomPos = tr->GetPos();
			mLeftBullet = object::Instantiate<BloomBullet>(BloomPos, eLayerType::Bullet, SceneManager::GetActiveScene2());
			if (fabs(mSonic->GetComponent<Transform>()->GetPos().x - BloomPos.x) <= 500
				&& fabs(mSonic->GetComponent<Transform>()->GetPos().y - BloomPos.y) <= 200)
			{
				sBullet->Play(false);
			}			
			Rigidbody* bulletrb = mLeftBullet->GetComponent<Rigidbody>();
			bulletrb->SetVelocity(Vector2(-200.0f, -500.0f));
		}
			mbShoot = true;
		if (mbShoot == true)
		{
			mBloomState = eBloomState::idle;
			mAnimator->Reset();
			mbShoot = false;
		}
	}
	void Bloominator::death()
	{
		sDeath->Play(false);
		mAnimator->Play(L"animal_boom", false);
		if (mAnimator->IsComplete())
		{
			object::Destroy(this);
			mAnimator->Reset();
		}
	}
}