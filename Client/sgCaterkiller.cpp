#include "sgCaterkiller.h"
#include "sgSonic.h"

#include "sgTime.h"
#include "sgImage.h"
#include "sgObject.h"
#include "sgResources.h"
#include "sgSound.h"

#include "sgTransform.h"
#include "sgAnimator.h"
#include "sgCollider.h"
#include "sgRigidbody.h"

namespace sg
{
	Caterkiller::Caterkiller()
	{
	}
	Caterkiller::~Caterkiller()
	{
	}
	void Caterkiller::Initialize()
	{
		Transform* tr = GetComponent<Transform>();
		mAni = AddComponent<Animator>();
		mCol = AddComponent<Collider>();

		Image* ck = Resources::Load<Image>(L"caterkiller", L"..\\Resources\\enemies\\caterkiller.bmp");
		Image* boom = Resources::Load<Image>(L"animal_boom", L"..\\Resources\\animals\\boom.bmp");

		mAni->CreateAnimation(L"animal_boom", boom, Vector2::Zero, 5, 1, 5, Vector2::Zero, 0.1);

		mAni->CreateAnimation(L"ck_move_left", ck, Vector2::Zero, 23, 4, 23, Vector2::Zero, 0.2);
		mAni->CreateAnimation(L"ck_move_right", ck, Vector2(0, 51), 23, 4, 23, Vector2::Zero, 0.2);
		mAni->CreateAnimation(L"ck_turn_left", ck, Vector2(0, 102), 23, 4, 17, Vector2::Zero, 0.2);
		mAni->CreateAnimation(L"ck_turn_right", ck, Vector2(0, 153), 23, 4, 17, Vector2::Zero, 0.2);
		mAni->Play(L"ck_move_left", true);

		mOriginPos = tr->GetPos();
		tr->SetScale(Vector2(2.5f, 2.5f));

		mCol->SetSize(Vector2(187.5f, 80.0f));
		mCol->SetCenter(Vector2(0, 30));

		sDeath = Resources::Load<Sound>(L"enemy_s_death", L"..\\Resources\\sound\\enemy_death.wav");
		sBoom = Resources::Load<Sound>(L"enemy_s_boom", L"..\\Resources\\sound\\sonic_getitem.wav");

		GameObject::Initialize();
	}
	void Caterkiller::Update()
	{
		GameObject::Update();

		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();

		if (mCKState == eCKState::move_left && pos.x <= mOriginPos.x - 200)
		{
			mCKState = eCKState::turn_right;
		}
		else if (mCKState == eCKState::move_right && pos.x >= mOriginPos.x + 200)
		{
			mCKState = eCKState::turn_left;
		}


		switch (mCKState)
		{
		case sg::Caterkiller::eCKState::move_left:
			move_left();
			break;
		case sg::Caterkiller::eCKState::move_right:
			move_right();
			break;
		case sg::Caterkiller::eCKState::turn_left:
			turn_left();
			break;
		case sg::Caterkiller::eCKState::turn_right:
			turn_right();
			break;
		case sg::Caterkiller::eCKState::death:
			death();
			break;
		}

	}
	void Caterkiller::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void Caterkiller::Release()
	{
		GameObject::Release();
	}
	void Caterkiller::OnCollisionEnter(Collider* other)
	{
		Sonic* sonic = dynamic_cast<Sonic*>(other->GetOwner());
		Transform* tr = GetComponent<Transform>();

		if (other->GetOwner() == sonic)
		{
			if (mAni->GetAniIndex(L"ck_move_left") == 10
				|| mAni->GetAniIndex(L"ck_move_left") == 11
				|| mAni->GetAniIndex(L"ck_move_left") == 12
				|| mAni->GetAniIndex(L"ck_move_left") == 13
				|| mAni->GetAniIndex(L"ck_move_left") == 14
				|| mAni->GetAniIndex(L"ck_move_left") == 15
				|| mAni->GetAniIndex(L"ck_move_left") == 16
				|| mAni->GetAniIndex(L"ck_move_left") == 17
				|| mAni->GetAniIndex(L"ck_move_right") == 10
				|| mAni->GetAniIndex(L"ck_move_right") == 11
				|| mAni->GetAniIndex(L"ck_move_right") == 12
				|| mAni->GetAniIndex(L"ck_move_right") == 13
				|| mAni->GetAniIndex(L"ck_move_right") == 14
				|| mAni->GetAniIndex(L"ck_move_right") == 15
				|| mAni->GetAniIndex(L"ck_move_right") == 16
				|| mAni->GetAniIndex(L"ck_move_right") == 17)
			{
				if (other->GetPos().x > tr->GetPos().x)
				{
					sonic->SetSonicState(Sonic::eSonicState::hurt_right);
				}
				else
				{
					sonic->SetSonicState(Sonic::eSonicState::hurt_left);
				}
			}
			else if (sonic->GetSonicState() == Sonic::eSonicState::rolling_left
				|| sonic->GetSonicState() == Sonic::eSonicState::rolling_right
				|| sonic->GetSonicState() == Sonic::eSonicState::jump_left
				|| sonic->GetSonicState() == Sonic::eSonicState::jump_right
				|| sonic->GetSonicState() == Sonic::eSonicState::jump2_left
				|| sonic->GetSonicState() == Sonic::eSonicState::jump2_right)
			{
				sBoom->Play(false);
				mCKState = eCKState::death;
				Vector2 velocity = sonic->GetComponent<Rigidbody>()->GetVelocity();
				velocity.y = -400.0f;
				sonic->GetComponent<Rigidbody>()->SetVelocity(velocity);
				sonic->GetComponent<Rigidbody>()->SetGround(false);
			}
		}

	}
	void Caterkiller::OnCollisionStay(Collider* other)
	{
	}
	void Caterkiller::OnCollisionExit(Collider* other)
	{
	}
	void Caterkiller::move_left()
	{
		mAni->Play(L"ck_move_left", true);
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();
		pos.x -= 50.0f * Time::DeltaTime();
		tr->SetPos(pos);
	}
	void Caterkiller::move_right()
	{
		mAni->Play(L"ck_move_right", true);
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();
		pos.x += 50.0f * Time::DeltaTime();
		tr->SetPos(pos);
	}
	void Caterkiller::turn_left()
	{
		mAni->Play(L"ck_turn_left", false);
		if (mAni->IsComplete())
		{
			mCKState = eCKState::move_left;
			mAni->Reset();
		}
	}
	void Caterkiller::turn_right()
	{
		mAni->Play(L"ck_turn_right", false);
		if (mAni->IsComplete())
		{
			mCKState = eCKState::move_right;
			mAni->Reset();
		}
	}
	void Caterkiller::death()
	{
		mAni->Play(L"animal_boom", false);
		sDeath->Play(false);

		if (mAni->IsComplete())
		{
			object::Destroy(this);
		}
	}
}