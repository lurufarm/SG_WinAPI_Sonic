#include "sgRhinobot.h"
#include "sgSonic.h"
#include "sgTestGround.h"

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

extern sg::Ground* ground;

namespace sg
{
	Rhinobot::Rhinobot()
		: mTime(0.0f)
		, mAbility(2.0f)
	{
		this->SetName(L"Rhinobot");
	}
	Rhinobot::~Rhinobot()
	{
	}
	void Rhinobot::Initialize()
	{
		mAnimator = AddComponent<Animator>();
		mCollider = AddComponent<Collider>();
		mRigidbody = AddComponent<Rigidbody>();
		Image* rhinoidle = Resources::Load<Image>(L"rhinobot_idle", L"..\\Resources\\enemies\\rhinobot_idle.bmp");
		Image* rhinoidle2 = Resources::Load<Image>(L"rhinobot_idle2", L"..\\Resources\\enemies\\rhinobot_idle2.bmp");
		Image* rhinomove = Resources::Load<Image>(L"rhinobot_move", L"..\\Resources\\enemies\\rhinobot_move.bmp");
		Image* boom = Resources::Load<Image>(L"animal_boom", L"..\\Resources\\animals\\boom.bmp");

		sMove = Resources::Load<Sound>(L"rhino_s_move", L"..\\Resources\\sound\\enemy_rhinobot_move.wav");
		sDeath = Resources::Load<Sound>(L"enemy_s_death", L"..\\Resources\\sound\\enemy_death.wav");
		sBoom = Resources::Load<Sound>(L"enemy_s_boom", L"..\\Resources\\sound\\sonic_getitem.wav");
		mAnimator->CreateAnimation(L"rhinobot_idle_left", rhinoidle, Vector2::Zero, 5, 2, 5, Vector2::Zero, 0.15);
		mAnimator->CreateAnimation(L"rhinobot_idle_right", rhinoidle, Vector2(0, 27), 5, 2, 5, Vector2::Zero, 0.15);
		mAnimator->CreateAnimation(L"rhinobot_idle2_left", rhinoidle2, Vector2::Zero, 6, 2, 6, Vector2::Zero, 0.15);
		mAnimator->CreateAnimation(L"rhinobot_idle2_right", rhinoidle2, Vector2(0,29), 6, 2, 6, Vector2::Zero, 0.15);
		mAnimator->CreateAnimation(L"rhinobot_move_left", rhinomove, Vector2(0, 27), 1, 2, 1, Vector2::Zero, 0.15);
		mAnimator->CreateAnimation(L"rhinobot_move_right", rhinomove, Vector2::Zero, 1, 2, 1, Vector2::Zero, 0.15);
		mAnimator->CreateAnimation(L"animal_boom", boom, Vector2::Zero, 5, 1, 5, Vector2::Zero, 0.1);


		Transform* tr = GetComponent<Transform>();
		tr->SetScale(Vector2(2.5f, 2.5f));
		mOriginPos = tr->GetPos();
		mRigidbody->SetMass(1.0f);
		mRhinoState = eRhinoState::idle_left;

		GameObject::Initialize();

	}
	void Rhinobot::Update()
	{
		GameObject::Update();
		switch (mRhinoState)
		{
		case sg::Rhinobot::eRhinoState::idle_left:
			idle_left();
			break;
		case sg::Rhinobot::eRhinoState::idle_right:
			idle_right();
			break;
		case sg::Rhinobot::eRhinoState::move_left:
			move_left();
			break;
		case sg::Rhinobot::eRhinoState::move_right:
			move_right();
			break;
		case sg::Rhinobot::eRhinoState::death:
			death();
			break;
		}
	}
	void Rhinobot::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void Rhinobot::Release()
	{
		GameObject::Release();
	}
	void Rhinobot::OnCollisionEnter(Collider* other)
	{
		Sonic* sonic = dynamic_cast<Sonic*>(other->GetOwner());
		if (sonic == nullptr)
			return;

		if (sonic->GetSonicState() == Sonic::eSonicState::jump_left
			|| sonic->GetSonicState() == Sonic::eSonicState::jump_right
			|| sonic->GetSonicState() == Sonic::eSonicState::jump2_left
			|| sonic->GetSonicState() == Sonic::eSonicState::jump2_right
			|| sonic->GetSonicState() == Sonic::eSonicState::spindash_left
			|| sonic->GetSonicState() == Sonic::eSonicState::spindash_right
			|| sonic->GetSonicState() == Sonic::eSonicState::rolling_left
			|| sonic->GetSonicState() == Sonic::eSonicState::rolling_right)
		{
			sBoom->Play(false);
			mRhinoState = eRhinoState::death;
			Vector2 velocity = sonic->GetComponent<Rigidbody>()->GetVelocity();
			velocity.y = -400.0f;
			sonic->GetComponent<Rigidbody>()->SetVelocity(velocity);
			sonic->GetComponent<Rigidbody>()->SetGround(false);
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
	void Rhinobot::OnCollisionStay(Collider* other)
	{
	}
	void Rhinobot::OnCollisionExit(Collider* other)
	{
	}
	void Rhinobot::idle_left()
	{
		mCollider->SetCenter(Vector2(20.0f, 0.0f));
		mCollider->SetSize(Vector2(120, 70));
		mAnimator->Play(L"rhinobot_idle_left", false);
		if (mAnimator->IsComplete())
		{
			mAnimator->Reset();
			mRhinoState = eRhinoState::move_left;
		};
	}
	void Rhinobot::idle_right()
	{
		mAnimator->Play(L"rhinobot_idle_right", false);
		if (mAnimator->IsComplete())
		{
			mAnimator->Reset();
			mRhinoState = eRhinoState::move_right;
		}
	}
	void Rhinobot::move_left()
	{
		
		Transform* tr = GetComponent<Transform>();
		Vector2 rhinomove = tr->GetPos();
		rhinomove.x -= 200.0f * Time::DeltaTime();
		tr->SetPos(rhinomove);
		if (fabs(mSonic->GetComponent<Transform>()->GetPos().x - rhinomove.x) <= 500
			&& fabs(mSonic->GetComponent<Transform>()->GetPos().y - rhinomove.y) <= 200)
		{
			if (mAnimator->GetAniIndex(L"rhinobot_idle2_left") == 1)
			{
				sMove->Play(false);
			}
		}
		mAnimator->Play(L"rhinobot_move_right", true);
		if (rhinomove.x <= mOriginPos.x - 300)
		{
			mAnimator->Play(L"rhinobot_idle2_left", false);
			if (mAnimator->IsComplete())
			{
				mAnimator->Reset();
				mRhinoState = eRhinoState::idle_right;
			}
		}
	}
	void Rhinobot::move_right()
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 rhinomove = tr->GetPos();
		if (fabs(mSonic->GetComponent<Transform>()->GetPos().x - rhinomove.x) <= 500
			&& fabs(mSonic->GetComponent<Transform>()->GetPos().y - rhinomove.y) <= 200)
		{
			if (mAnimator->GetAniIndex(L"rhinobot_idle2_right") == 1)
			{
				sMove->Play(false);
			}
		}
		mAnimator->Play(L"rhinobot_move_left", true);
		rhinomove.x += 200.0f * Time::DeltaTime();
		tr->SetPos(rhinomove);
		if (rhinomove.x >= mOriginPos.x + 300)
		{
			mAnimator->Play(L"rhinobot_idle2_right", false);
			if (mAnimator->IsComplete())
			{
				mAnimator->Reset();
				mRhinoState = eRhinoState::idle_left;
			}
		}
	}
	void Rhinobot::death()
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