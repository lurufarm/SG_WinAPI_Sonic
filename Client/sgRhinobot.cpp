#include "sgRhinobot.h"
#include "sgSonic.h"

#include "sgTime.h"
#include "sgScene.h"
#include "sgImage.h"
#include "sgObject.h"
#include "sgResources.h"
#include "sgAnimator.h"
#include "sgCollider.h"
#include "sgRigidbody.h"
#include "sgTransform.h"
#include "sgCollisionManager.h"

namespace sg
{
	Rhinobot::Rhinobot()
		: mTime(0.0f)
		, mAbility(2.0f)
	{
	}
	Rhinobot::~Rhinobot()
	{
	}
	void Rhinobot::Initialize()
	{
		Image* rhinoidle = Resources::Load<Image>(L"rhinobot_idle", L"..\\Resources\\enemies\\rhinobot_idle.bmp");
		Image* rhinomove = Resources::Load<Image>(L"rhinobot_move", L"..\\Resources\\enemies\\rhinobot_move.bmp");
	
		mAnimator->CreateAnimation(L"rhinobot_idle_left", rhinoidle, Vector2::Zero, 5, 2, 5, Vector2::Zero, 0.1);
		mAnimator->CreateAnimation(L"rhinobot_idle_right", rhinoidle, Vector2(0, 27), 5, 2, 5, Vector2::Zero, 0.1);
		mAnimator->CreateAnimation(L"rhinobot_move_left", rhinomove, Vector2(0, 27), 1, 2, 1, Vector2::Zero, 0.1);
		mAnimator->CreateAnimation(L"rhinobot_move_right", rhinomove, Vector2::Zero, 1, 2, 1, Vector2::Zero, 0.1);

		Transform* tr = GetComponent<Transform>();
		tr->SetScale(Vector2(2.5f, 2.5f));

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
			object::Destroy(this);

			Vector2 velocity = sonic->GetComponent<Rigidbody>()->GetVelocity();
			velocity.y -= 1000.0f;
			sonic->GetComponent<Rigidbody>()->SetVelocity(velocity);
		}
		else if (sonic->GetComponent<Transform>()->GetPos().x <=
			this->GetComponent<Transform>()->GetPos().x)
		{
			sonic->SetSonicState(Sonic::eSonicState::hurt_right);
		}
		else if (sonic->GetComponent<Transform>()->GetPos().x >
			this->GetComponent<Transform>()->GetPos().x)
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
		mTime += Time::DeltaTime();
		if (mTime >= 5.0f)
		{
			mAnimator->Play(L"rhinobot_idle_left", false);
			if (mAnimator->IsComplete())
			{
				mAnimator->Reset();
				mTime = 0.0f;
			}
		}
	}
	void Rhinobot::idle_right()
	{
		mAnimator->Play(L"rhinobot_idle_right", true);
		mTime += Time::DeltaTime();
		if (mTime >= 5.0f)
		{
			mAnimator->Play(L"rhinobot_idle_right", false);
			if (mAnimator->IsComplete())
			{
				mAnimator->Reset();
				mTime = 0.0f;
			}
		}
	}
	void Rhinobot::move_left()
	{
	}
	void Rhinobot::move_right()
	{
	}
	void Rhinobot::death()
	{
	}
}