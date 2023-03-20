#include "sgSonic.h"
#include "sgRhinobot.h"
#include "sgRing.h"

#include <random>
#include <algorithm>
#include "sgTime.h"
#include "sgInput.h"
#include "sgEnums.h"
#include "sgSceneManager.h"
#include "sgResources.h"
#include "sgTransform.h"
#include "sgAnimator.h"
#include "sgCollider.h"
#include "sgScene.h"
#include "sgObject.h"
#include "sgRigidbody.h"
#include "sgCamera.h"

namespace sg
{
	int Sonic::mRings = 0;

	Sonic::Sonic()
		: mBoredTime(0.0f)
		, mAbility(0.0f)
		, mLife(3)
	{
	}

	Sonic::~Sonic()
	{
	}

	void Sonic::Initialize()
	{
		mCollider = AddComponent<Collider>();
		mBoredTime = 0.0f;
		Camera::SetTarget(this);
		Image* idle1 = Resources::Load<Image>(L"Sonic_idle_right", L"..\\Resources\\sonic\\sonic_idle_right.bmp");
		Image* idle2 = Resources::Load<Image>(L"Sonic_idle_left", L"..\\Resources\\sonic\\sonic_idle_left.bmp");
		Image* bored = Resources::Load<Image>(L"Sonic_idle_bored", L"..\\Resources\\sonic\\sonic_idle2.bmp");
		Image* walk = Resources::Load<Image>(L"Sonic_walk", L"..\\Resources\\sonic\\sonic_walk.bmp");
		Image* LookUpAndCrouch = Resources::Load<Image>(L"Sonic_LookUpAndCrouch", L"..\\Resources\\sonic\\sonic_LookUpAndCrouch.bmp");
		Image* run_left = Resources::Load<Image>(L"Sonic_run_left", L"..\\Resources\\sonic\\sonic_run.left.bmp");
		Image* run_right = Resources::Load<Image>(L"Sonic_run_right", L"..\\Resources\\sonic\\sonic_run_right.bmp");
		Image* skid = Resources::Load<Image>(L"Sonic_skid", L"..\\Resources\\sonic\\sonic_skid.bmp");
		Image* jump = Resources::Load<Image>(L"Sonic_jump", L"..\\Resources\\sonic\\sonic_jump.bmp");
		Image* jump2 = Resources::Load<Image>(L"Sonic_jump2", L"..\\Resources\\sonic\\sonic_jump2.bmp");
		Image* spindash = Resources::Load<Image>(L"Sonic_spindash", L"..\\Resources\\sonic\\sonic_spindash2.bmp");
		Image* hurt = Resources::Load<Image>(L"Sonic_hurt", L"..\\Resources\\sonic\\sonic_hurt.bmp");
		Image* death = Resources::Load<Image>(L"Sonic_death", L"..\\Resources\\sonic\\death.bmp");

		Transform* tr = GetComponent<Transform>();
		tr->SetScale(Vector2(2.5f, 2.5f));

		mAnimator->CreateAnimation(L"Sonic_idle_left", idle2, Vector2::Zero, 1, 1, 1, Vector2::Zero, 0.1);
		mAnimator->CreateAnimation(L"Sonic_idle_right", idle1, Vector2::Zero, 1, 1, 1, Vector2::Zero, 0.1);
		mAnimator->CreateAnimation(L"Sonic_idle_bored", bored, Vector2::Zero, 12, 1, 12, Vector2::Zero, 0.2);
		mAnimator->CreateAnimation(L"Sonic_walk_left", walk, Vector2(0.0f, 40.0f), 8, 2, 8, Vector2::Zero, 0.1);
		mAnimator->CreateAnimation(L"Sonic_walk_right", walk, Vector2::Zero, 8, 2, 8, Vector2::Zero, 0.1);
		mAnimator->CreateAnimation(L"Sonic_lookup_left", LookUpAndCrouch, Vector2(120.0f,0.0f), 4, 2, 2, Vector2::Zero, 0.1);
		mAnimator->CreateAnimation(L"Sonic_lookup_right", LookUpAndCrouch, Vector2::Zero, 4, 2, 2, Vector2::Zero, 0.1);
		mAnimator->CreateAnimation(L"Sonic_crouch_left", LookUpAndCrouch, Vector2(120.0f, 41.0f), 4, 2, 2, Vector2::Zero, 0.1);
		mAnimator->CreateAnimation(L"Sonic_crouch_right", LookUpAndCrouch, Vector2(0.0f, 41.0f), 4, 2, 2, Vector2::Zero, 0.1);
		mAnimator->CreateAnimation(L"Sonic_run_left", run_left, Vector2::Zero, 4, 1, 4, Vector2::Zero, 0.1);
		mAnimator->CreateAnimation(L"Sonic_run_right", run_right, Vector2::Zero, 4, 1, 4, Vector2::Zero, 0.1);
		mAnimator->CreateAnimation(L"Sonic_skid_left", skid, Vector2::Zero, 4, 2, 4, Vector2::Zero, 0.08);
		mAnimator->CreateAnimation(L"Sonic_skid_right", skid, Vector2(0,38), 4, 2, 4, Vector2::Zero, 0.08);
		mAnimator->CreateAnimation(L"Sonic_jump_left", jump, Vector2(0, 40), 8, 2, 8, Vector2::Zero, 0.03);
		mAnimator->CreateAnimation(L"Sonic_jump_right", jump, Vector2::Zero, 8, 2, 8, Vector2::Zero, 0.03);
		mAnimator->CreateAnimation(L"Sonic_jump2_left", jump2, Vector2(0,48), 8, 2, 6, Vector2::Zero, 0.02);
		mAnimator->CreateAnimation(L"Sonic_jump2_right", jump2, Vector2::Zero, 8, 2, 6, Vector2::Zero, 0.02);
		mAnimator->CreateAnimation(L"Sonic_spindash_left", spindash, Vector2(0, 39), 9, 2, 9, Vector2::Zero, 0.03);
		mAnimator->CreateAnimation(L"Sonic_spindash_right", spindash, Vector2(0, 0), 9, 2, 9, Vector2::Zero, 0.03);
		mAnimator->CreateAnimation(L"Sonic_hurt_left", hurt, Vector2(0, 32), 4, 2, 4, Vector2::Zero, 0.1);
		mAnimator->CreateAnimation(L"Sonic_hurt_right", hurt, Vector2::Zero, 4, 2, 4, Vector2::Zero, 0.1);
		mAnimator->CreateAnimation(L"Sonic_death", death, Vector2::Zero, 1, 1, 1, Vector2::Zero, 0.1);

		mAnimator->Play(L"Sonic_idle_right", true);
		mCollider->SetCenter(Vector2::Zero);

		mRigidbody->SetMass(0.3);
		mRigidbody->SetFriction(200.0f);
		mRigidbody->SetVelocity(Vector2(100.f,100.f));
		mSonicState = eSonicState::idle_right;

		GameObject::Initialize();
	}
		
	void Sonic::Update()
	{
		GameObject::Update();

		switch (mSonicState)
		{
		case sg::Sonic::eSonicState::idle_left:
			idle_left();
			break;
		case sg::Sonic::eSonicState::idle_right:
			idle_right();
			break;
		//case sg::Sonic::eSonicState::idle_bored:
		//	idle_bored();
		//	break;
		case sg::Sonic::eSonicState::walk_left:
			walk_left();
			break;
		case sg::Sonic::eSonicState::walk_right:
			walk_right();
			break;
		case sg::Sonic::eSonicState::lookup_left:
			lookup_left();
			break;
		case sg::Sonic::eSonicState::lookup_right:
			lookup_right();
			break;
		case sg::Sonic::eSonicState::crouch_left:
			crouch_left();
			break;
		case sg::Sonic::eSonicState::crouch_right:
			crouch_right();
			break;
		case sg::Sonic::eSonicState::run_left:
			run_left();
			break;
		case sg::Sonic::eSonicState::run_right:
			run_right();
			break;
		case sg::Sonic::eSonicState::jump_left:
			jump_left();
			break;
		case sg::Sonic::eSonicState::jump_right:
			jump_right();
			break;
		case sg::Sonic::eSonicState::jump2_left:
			jump2_left();
			break;
		case sg::Sonic::eSonicState::jump2_right:
			jump2_right();
			break;
		case sg::Sonic::eSonicState::spindash_left:
			spindash_left();
			break;
		case sg::Sonic::eSonicState::spindash_right:
			spindash_right();
			break;
		case sg::Sonic::eSonicState::rolling_left:
			rolling_left();
			break;
		case sg::Sonic::eSonicState::rolling_right:
			rolling_right();
			break;
		case sg::Sonic::eSonicState::skid_left:
			skid_left();
			break;
		case sg::Sonic::eSonicState::skid_right:
			skid_right();
			break;
		case sg::Sonic::eSonicState::hurt_left:
			hurt_left();
			break;
		case sg::Sonic::eSonicState::hurt_right:
			hurt_right();
			break;
		case sg::Sonic::eSonicState::death:
			death();
			break;
		}
		if (mRings > 0)
		{
			mAbility = 1;
		}
		if (mRings == 0)
		{
			mAbility = 0;
		}
		if (mRings > 100)
		{
			mRings -= 100;
			mLife++;
		}

	}
	void Sonic::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void Sonic::Release()
	{
		GameObject::Release();
	}

	void Sonic::OnCollisionEnter(Collider* other)
	{
		Ring* ring = dynamic_cast<Ring*>(other->GetOwner());
		if (other->GetOwner() == ring)
		{
			GetRing();
		}
	}

	void Sonic::OnCollisionStay(Collider* other)
	{
	}

	void Sonic::OnCollisionExit(Collider* other)
	{
	}

	void Sonic::idle_left()
	{
		mAnimator->Play(L"Sonic_idle_left", true);
		mCollider->SetSize(Vector2(40.0f, 93.75f));
		mCollider->SetCenter(Vector2(15.0f, 3.0f));
		Vector2 Velocity = mRigidbody->GetVelocity();
		mRigidbody->SetVelocity(Vector2(Velocity.x * 0.9, Velocity.y));

		mBoredTime += Time::DeltaTime();
		if (mBoredTime >= 5.0f)
		{
			mAnimator->Play(L"Sonic_idle_bored", false);
			if (mAnimator->IsComplete())
			{
				mAnimator->Reset();
				mBoredTime = 0.0f;
			}
		}
		if (Input::GetKeyDown(eKeyCode::Left)
			|| Input::GetKey(eKeyCode::Left))
		{
			mSonicState = eSonicState::walk_left;
		}
		if (Input::GetKeyDown(eKeyCode::Right)
			|| Input::GetKey(eKeyCode::Right))
		{
			mSonicState = eSonicState::walk_right;
		}
		if (Input::GetKeyDown(eKeyCode::Up))
		{
			mSonicState = eSonicState::lookup_left;
		}
		if (Input::GetKeyDown(eKeyCode::Down))
		{
			mSonicState = eSonicState::crouch_left;
		}
		if (Input::GetKeyDown(eKeyCode::Space))
		{
			Vector2 velocity = mRigidbody->GetVelocity();
			velocity.y -= 650.0f;
			mRigidbody->SetVelocity(velocity);
			mRigidbody->SetGround(false);
			mSonicState = eSonicState::jump_left;
		}
	}
	void Sonic::idle_right()
	{
		mAnimator->Play(L"Sonic_idle_right", true);
		mCollider->SetSize(Vector2(40.0f, 93.75f));
		mCollider->SetCenter(Vector2(25.0f, 3.0f));
		Vector2 Velocity = mRigidbody->GetVelocity();
		mRigidbody->SetVelocity(Vector2(Velocity.x * 0.9, Velocity.y));

		mBoredTime += Time::DeltaTime();
		if (mBoredTime >= 5.0f)
		{
			mAnimator->Play(L"Sonic_idle_bored", false);
			if (mAnimator->IsComplete())
			{
				mAnimator->Reset();
				mBoredTime = 0.0f;
			}
		}
		if (Input::GetKeyDown(eKeyCode::Left)
			|| Input::GetKey(eKeyCode::Left))
		{
			mSonicState = eSonicState::walk_left;
		}
		if (Input::GetKeyDown(eKeyCode::Right)
			|| Input::GetKey(eKeyCode::Right))
		{
			mSonicState = eSonicState::walk_right;
		}
		if (Input::GetKeyDown(eKeyCode::Up))
		{
			mSonicState = eSonicState::lookup_right;
		}
		if (Input::GetKeyDown(eKeyCode::Down))
		{
			mSonicState = eSonicState::crouch_right;
		}
		if (Input::GetKeyDown(eKeyCode::Space))
		{
			Vector2 velocity = mRigidbody->GetVelocity();
			velocity.y -= 650.0f;
			mRigidbody->SetVelocity(velocity);
			mRigidbody->SetGround(false);
			mSonicState = eSonicState::jump_right;
		}

	}
	void Sonic::idle_bored()
	{
	//	mBoredTime = 0.0f;
	//	mCollider->SetSize(Vector2(55.0f, 93.75f));
	//	mCollider->SetCenter(Vector2(25.0f, 3.0f));
	//	mAnimator->Play(L"Sonic_idle_bored", true);
	//	if (mAnimator->IsComplete() == false)
	//	{
	//		mSonicState = eSonicState::idle_right;
	//	}
	//	if (Input::GetKey(eKeyCode::Left))
	//	{
	//		mSonicState = eSonicState::walk_left;
	//	}
	//	if (Input::GetKey(eKeyCode::Right))
	//	{
	//		mSonicState = eSonicState::walk_right;
	//	}
	//	if (Input::GetKeyDown(eKeyCode::Space))
	//	{
	//		Vector2 velocity = mRigidbody->GetVelocity();
	//		velocity.y -= 650.0f;
	//		mRigidbody->SetVelocity(velocity);
	//		mRigidbody->SetGround(false);
	//		mSonicState = eSonicState::jump_right;
	//	}
	}
	void Sonic::walk_left()
	{
		mAnimator->Play(L"Sonic_walk_left", true);
		mCollider->SetSize(Vector2(55.0f, 93.75f));
		mCollider->SetCenter(Vector2(25.0f, 3.0f));

		if (Input::GetKeyUp(eKeyCode::Left))
		{
			mSonicState = eSonicState::idle_left;
		}
		if (Input::GetKeyDown(eKeyCode::Right))
		{
			Vector2 Velocity = mRigidbody->GetVelocity();
			mRigidbody->SetVelocity(Vector2(Velocity.x * 0.005, Velocity.y));
			mSonicState = eSonicState::walk_right;
		}
		if (mRigidbody->GetVelocity().x <= -300.0f
			&& Input::GetKey(eKeyCode::Right))
		{
				mSonicState = eSonicState::skid_left;
		}
		if (Input::GetKey(eKeyCode::Left))
		{
			mRigidbody->AddForce(Vector2(-100.0f, 0.0f));
			if (mRigidbody->GetVelocity().x <= -500.0f)
			{
				mSonicState = eSonicState::run_left;
			}
		}

		if (Input::GetKeyDown(eKeyCode::Space))
		{
			Vector2 velocity = mRigidbody->GetVelocity();
			velocity.y -= 650.0f;
			mRigidbody->SetVelocity(velocity);
			mRigidbody->SetGround(false);
			mSonicState = eSonicState::jump_left;
		}
	}
	void Sonic::walk_right()
	{
		mAnimator->Play(L"Sonic_walk_right", true);
		mCollider->SetSize(Vector2(55.0f, 93.75f));
		mCollider->SetCenter(Vector2(30.0f, 3.0f));

		if (Input::GetKeyUp(eKeyCode::Right))
		{
			mSonicState = eSonicState::idle_right;
		}
		if (Input::GetKeyDown(eKeyCode::Left))
		{
			Vector2 Velocity = mRigidbody->GetVelocity();
			mRigidbody->SetVelocity(Vector2(Velocity.x * 0.005, Velocity.y));
			mSonicState = eSonicState::walk_left;
		}
		if (mRigidbody->GetVelocity().x >= 300.0f
			&& Input::GetKey(eKeyCode::Left))
		{
			mSonicState = eSonicState::skid_right;
		}
		if (Input::GetKey(eKeyCode::Right))
		{
			mRigidbody->AddForce(Vector2(100.0f, 0.0f));
			if (mRigidbody->GetVelocity().x >= 500.0f)
			{
				mSonicState = eSonicState::run_right;
			}
		}
		if (Input::GetKeyDown(eKeyCode::Space))
		{
			Vector2 velocity = mRigidbody->GetVelocity();
			velocity.y -= 650.0f;
			mRigidbody->SetVelocity(velocity);
			mRigidbody->SetGround(false);
			mSonicState = eSonicState::jump_right;
		}
	}
	void Sonic::run_left()
	{
		mAnimator->Play(L"Sonic_run_left", true);
		mCollider->SetSize(Vector2(60.f, 93.75f));
		mCollider->SetCenter(Vector2(-20.0f, 3.0f));

		if (Input::GetKey(eKeyCode::Left))
			mRigidbody->AddForce(Vector2(-100.0f, 0.0f));

		if (Input::GetKeyUp(eKeyCode::Left))
		{
			mSonicState = eSonicState::idle_left;
		}
		if (Input::GetKeyDown(eKeyCode::Right))
		{
			mSonicState = eSonicState::skid_left;
		}
		if (Input::GetKeyDown(eKeyCode::Space))
		{
			Vector2 velocity = mRigidbody->GetVelocity();
			velocity.y -= 650.0f;
			mRigidbody->SetVelocity(velocity);
			mRigidbody->SetGround(false);
			mSonicState = eSonicState::jump_left;
		}
		if (mRigidbody->GetVelocity().x >= -600.0f)
		{
			mSonicState = eSonicState::walk_left;
		}
	}
	void Sonic::run_right()
	{
		mAnimator->Play(L"Sonic_run_right", true);
		mCollider->SetSize(Vector2(60.0f, 93.75f));
		mCollider->SetCenter(Vector2(55.0f, 3.0f));

		if (Input::GetKey(eKeyCode::Right))
			mRigidbody->AddForce(Vector2(100.0f, 0.0f));
		if (Input::GetKeyUp(eKeyCode::Right))
		{
			mSonicState = eSonicState::idle_right;
		}
		if (Input::GetKeyDown(eKeyCode::Left))
		{
			mSonicState = eSonicState::skid_right;
		}
		if (Input::GetKeyDown(eKeyCode::Space))
		{
			Vector2 velocity = mRigidbody->GetVelocity();
			velocity.y -= 650.0f;
			mRigidbody->SetVelocity(velocity);
			mRigidbody->SetGround(false);
			mSonicState = eSonicState::jump_right;
		}
		if (mRigidbody->GetVelocity().x <= 600.0f)
		{
			mSonicState = eSonicState::walk_right;
		}
	}
	void Sonic::jump_left()
	{
		mAnimator->Play(L"Sonic_jump_left", true);
		if (Input::GetKeyDown(eKeyCode::Space))
		{
			mAnimator->Play(L"Sonic_jump2_left", false);
			if (mAnimator->IsComplete())
				mSonicState = eSonicState::jump2_left;
		}
		if (Input::GetKey(eKeyCode::Left))
		{
			mRigidbody->AddForce(Vector2(-100.0f, 0.0f));
		}
		if (Input::GetKey(eKeyCode::Right))
		{
			mRigidbody->AddForce(Vector2(100.0f, 0.0f));
		}
		if (mRigidbody->GetGround() == true
			&& Input::GetKey(eKeyCode::Left))
		{
			mSonicState = eSonicState::walk_left;
		}
		if (mRigidbody->GetGround() == true
			&& Input::GetKey(eKeyCode::Right))
		{
			mSonicState = eSonicState::walk_right;
		}
		if (mRigidbody->GetGround() == true
			&& Input::GetKeyState(eKeyCode::Left) == eKeyState::None
			&& Input::GetKeyState(eKeyCode::Right) == eKeyState::None)
		{
			mSonicState = eSonicState::idle_left;
		}
	}
	void Sonic::jump_right()
	{
		mAnimator->Play(L"Sonic_jump_right", true);

		if (Input::GetKeyDown(eKeyCode::Space))
		{
			mAnimator->Play(L"Sonic_jump2_right", false);
			if (mAnimator->IsComplete())
				mSonicState = eSonicState::jump2_right;
		}
		if (Input::GetKey(eKeyCode::Left))
		{
			mRigidbody->AddForce(Vector2(-100.0f, 0.0f));
		}
		if (Input::GetKey(eKeyCode::Right))
		{
			mRigidbody->AddForce(Vector2(100.0f, 0.0f));
		}
		if (mRigidbody->GetGround() == true
			&& Input::GetKey(eKeyCode::Left))
		{
			mSonicState = eSonicState::walk_left;
		}
		if (mRigidbody->GetGround() == true
			&& Input::GetKey(eKeyCode::Right))
		{
			mSonicState = eSonicState::walk_right;
		}
		if (mRigidbody->GetGround() == true
			&& Input::GetKeyState(eKeyCode::Left) == eKeyState::None
			&& Input::GetKeyState(eKeyCode::Right) == eKeyState::None)
		{
			mSonicState = eSonicState::idle_right;
		}
	}
	void Sonic::jump2_left()
	{
			if (Input::GetKey(eKeyCode::Left))
			{
				mRigidbody->AddForce(Vector2(-100.0f, 0.0f));
			}
			if (Input::GetKey(eKeyCode::Right))
			{
				mRigidbody->AddForce(Vector2(100.0f, 0.0f));
			}
			if (mRigidbody->GetGround() == true
				&& Input::GetKey(eKeyCode::Left))
			{
				mSonicState = eSonicState::walk_left;
			}
			if (mRigidbody->GetGround() == true
				&& Input::GetKey(eKeyCode::Right))
			{
				mSonicState = eSonicState::walk_right;
			}
			if (mRigidbody->GetGround() == true)
			{
				mSonicState = eSonicState::idle_left;
			}
	}
	void Sonic::jump2_right()
	{
			if (Input::GetKey(eKeyCode::Left))
			{
				mRigidbody->AddForce(Vector2(-100.0f, 0.0f));
			}
			if (Input::GetKey(eKeyCode::Right))
			{
				mRigidbody->AddForce(Vector2(100.0f, 0.0f));
			}
			if (mRigidbody->GetGround() == true
				&& Input::GetKey(eKeyCode::Left))
			{
				mSonicState = eSonicState::walk_left;
			}
			if (mRigidbody->GetGround() == true
				&& Input::GetKey(eKeyCode::Right))
			{
				mSonicState = eSonicState::walk_right;
			}
			if (mRigidbody->GetGround() == true)
			{
				mSonicState = eSonicState::idle_right;
			}
	}
	void Sonic::spindash_left()
	{
		mRigidbody->SetVelocity(Vector2::Zero);
		mCollider->SetSize(Vector2(55.0f, 93.75f));
		mCollider->SetCenter(Vector2(30.0f, 3.0f));
		mAnimator->Play(L"Sonic_spindash_left", true);
		if (Input::GetKeyDown(eKeyCode::Space))
		{
			mAnimator->Play(L"Sonic_spindash_left", true);
		}
		if (Input::GetKeyUp(eKeyCode::Down))
		{
			mRigidbody->AddForce(Vector2(-20000.0f, 0.0f));
			mSonicState = eSonicState::rolling_left;
		}
	}
	void Sonic::spindash_right()
  	{
		mRigidbody->SetVelocity(Vector2::Zero);
		mAnimator->Play(L"Sonic_spindash_right", true);
 		if (Input::GetKeyDown(eKeyCode::Space))
		{
			mAnimator->Play(L"Sonic_spindash_right", true);
		}
		if (Input::GetKeyUp(eKeyCode::Down))
		{
			mRigidbody->AddForce(Vector2(20000.0f, 0.0f));
			mSonicState = eSonicState::rolling_right;
		}
	}
	void Sonic::rolling_left()
	{
		mAnimator->Play(L"Sonic_jump_left", true);
		if (Input::GetKeyDown(eKeyCode::Space))
		{
			
			Vector2 velocity = mRigidbody->GetVelocity();
			velocity.y -= 650.0f;
			velocity.x *= 0.3;
			mRigidbody->SetVelocity(velocity);
			mRigidbody->SetGround(false);
			mSonicState = eSonicState::jump_left;
		}
		if (Input::GetKeyDown(eKeyCode::Right)
			|| Input::GetKey(eKeyCode::Right))
		{
			Vector2 velocity = mRigidbody->GetVelocity();
			velocity.x = 0.7 * velocity.x;
			mRigidbody->SetVelocity(velocity);
			if (mRigidbody->GetVelocity().x >= -100.0f)
				mSonicState = eSonicState::idle_right;
		}
			if (mRigidbody->GetVelocity().x >= 100.0f)
				mSonicState = eSonicState::idle_left;
	}
	void Sonic::rolling_right()
	{
		mAnimator->Play(L"Sonic_jump_right", true);
		if (Input::GetKeyDown(eKeyCode::Space))
		{
			Vector2 velocity = mRigidbody->GetVelocity();
			velocity.y -= 650.0f;
			velocity.x *= 0.3;
			mRigidbody->SetVelocity(velocity);
			mRigidbody->SetGround(false);
			mSonicState = eSonicState::jump_right;
		}
		if (Input::GetKeyDown(eKeyCode::Left)
			|| Input::GetKey(eKeyCode::Left))
		{
			Vector2 velocity = mRigidbody->GetVelocity();
			velocity.x = 0.7 * velocity.x;
			mRigidbody->SetVelocity(velocity);
		if(mRigidbody->GetVelocity().x <= 100.0f)
			mSonicState = eSonicState::idle_left;
		}
		if (mRigidbody->GetVelocity().x <= 100.0f)
			mSonicState = eSonicState::idle_right;

	}
	void Sonic::skid_left()
	{
		mAnimator->Play(L"Sonic_skid_right", false);
		Vector2 Velocity = mRigidbody->GetVelocity();
		mRigidbody->SetVelocity(Vector2(Velocity.x * 0.005, Velocity.y));

		if (Input::GetKey(eKeyCode::Right)
			&& mAnimator->IsComplete())
		{
			mSonicState = eSonicState::walk_right;
		}
		if (Input::GetKey(eKeyCode::Left)\
			&& mAnimator->IsComplete())
		{
			mSonicState = eSonicState::walk_left;
		}
		if (Input::GetKeyDown(eKeyCode::Space))
		{
			Vector2 velocity = mRigidbody->GetVelocity();
			velocity.y -= 650.0f;

			mRigidbody->SetVelocity(velocity);
			mRigidbody->SetGround(false);
			mSonicState = eSonicState::jump_left;
		}
	}
	void Sonic::skid_right()
	{
		mAnimator->Play(L"Sonic_skid_left", false);
	
		Vector2 Velocity = mRigidbody->GetVelocity();
		mRigidbody->SetVelocity(Vector2(Velocity.x * 0.005, Velocity.y));

		if (Input::GetKey(eKeyCode::Left)
			&& mAnimator->IsComplete())
		{
			mSonicState = eSonicState::walk_left;
		}
		if (Input::GetKey(eKeyCode::Right)
			&& mAnimator->IsComplete())
		{
			mSonicState = eSonicState::walk_right;
		}
		if (Input::GetKeyDown(eKeyCode::Space))
		{
			Vector2 velocity = mRigidbody->GetVelocity();
			velocity.y -= 650.0f;

			mRigidbody->SetVelocity(velocity);
			mRigidbody->SetGround(false);
			mSonicState = eSonicState::jump_right;

		}
	}
	void Sonic::hurt_left()
	{
		mRings;
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_real_distribution<float> x_distribution(50.0f, 80.0f);
		std::uniform_real_distribution<float> y_distribution(-100.0f, -50.0f);
		std::uniform_real_distribution<float> spredx_distribution(-500.0f, 500.0f);
		std::uniform_real_distribution<float> spredy_distribution(-500.0f, 0.0f);

		Transform* tr = GetComponent<Transform>();
		Vector2 spos = tr->GetPos();
		Vector2 genrings;
		genrings.x = x_distribution(gen);
		genrings.y = y_distribution(gen);
		Vector2 spreadrings;
		spreadrings.x = spredx_distribution(gen);
		spreadrings.y = spredy_distribution(gen);
		for (size_t i = 0; i < mRings; i++)
		{
			Ring* ring = object::Instantiate<Ring>(genrings + spos, eLayerType::Ring, eSceneType::Play);
			Rigidbody* ringrigid = ring->AddComponent<Rigidbody>();
			ringrigid->SetMass(1.0f);
			ringrigid->SetVelocity(spreadrings);
			ringrigid->SetGround(false);
			ring->SetRingState(Ring::eRingState::rigid);
		}
		if (this->mAbility == 0)
		{
			mSonicState = eSonicState::death;
		}
		if (mAnimator->IsComplete() == false)
		{
			mAnimator->Play(L"Sonic_hurt_left", false);
			Vector2 velocity;
			velocity.y -= 250.0f;
			velocity.x += 300.0f;
			mRigidbody->SetVelocity(velocity);
			mRigidbody->SetGround(false);
		}
		if (mAnimator->IsComplete() || mRigidbody->GetGround() == true)
		{
			mRings = 0;
			mAnimator->Reset();
			mSonicState = eSonicState::idle_left;
		}
	}
	void Sonic::hurt_right()
	{
		mRings;
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_real_distribution<float> x_distribution(50.0f, 80.0f);
		std::uniform_real_distribution<float> y_distribution(-100.0f, -50.0f);
		std::uniform_real_distribution<float> spredx_distribution(-500.0f, 500.0f);
		std::uniform_real_distribution<float> spredy_distribution(-500.0f, 0.0f);

		Transform* tr = GetComponent<Transform>();
		Vector2 spos = tr->GetPos();
		Vector2 genrings;
		genrings.x = x_distribution(gen);
		genrings.y = y_distribution(gen);
		Vector2 spreadrings;
		spreadrings.x = spredx_distribution(gen);
		spreadrings.y = spredy_distribution(gen);

		int maxRingCount = 100;  // 최대 생성 가능한 링 개수

		for (int i = 0; i < min(maxRingCount, mRings); i++)

		{
			Ring* ring = object::Instantiate<Ring>(genrings + spos, eLayerType::Ring, eSceneType::Play);
			Rigidbody* ringrigid = ring->AddComponent<Rigidbody>();
			ringrigid->SetMass(1.0f);
			ringrigid->SetVelocity(spreadrings);
			ringrigid->SetGround(false);
			ring->SetRingState(Ring::eRingState::rigid);
		}

		if (this->mAbility == 0)
		{
			mSonicState = eSonicState::death;
		}
		mAnimator->Play(L"Sonic_hurt_right", false);
		if (mAnimator->IsComplete() == false)
		{
			Vector2 velocity;
			velocity.y -= 200.0f;
			velocity.x -= 300.0f;
			mRigidbody->SetVelocity(velocity);
			mRigidbody->SetGround(false);
		}
		if (mAnimator->IsComplete() || mRigidbody->GetGround() == true)
		{
			mRings = 0;
			mAnimator->Reset();
			mSonicState = eSonicState::idle_right;
		}
	}
	void Sonic::death()
	{
		Camera::SetTarget(nullptr);
		Transform* tr = GetComponent<Transform>();
		mSonicPos = tr->GetPos();
		mBoredTime += Time::DeltaTime();
		mAnimator->Play(L"Sonic_death", false);
		mCollider->SetSize(Vector2::Zero);
		if (mAnimator->IsComplete() == false)
		{
			Vector2 sonicvel = mRigidbody->GetVelocity();
			sonicvel.y -= 200.0f;
			sonicvel.x = 0.0;
			mRigidbody->SetVelocity(sonicvel);
			mRigidbody->SetGround(false);
		}
		if (mLife > 0 && mBoredTime >= 5.0f)
		{
			mLife--;
			tr->SetPos(Vector2(1500.0f, 3410.0f));
			Sonic::Sonic::Initialize();
		};


	}
	void Sonic::crouch_left()
	{
		mAnimator->Play(L"Sonic_crouch_left", false);
		mCollider->SetSize(Vector2(55.0f, 60.0f));
		mCollider->SetCenter(Vector2(10.0f, 40.0f));
		if (Input::GetKeyUp(eKeyCode::Down))
		{
			mAnimator->Reset();
			mSonicState = eSonicState::idle_left;
		}
		if (Input::GetKeyDown(eKeyCode::Space))
		{
			mAnimator->Reset();
			mSonicState = eSonicState::spindash_left;
		}
	}
	void Sonic::crouch_right()
	{
		mAnimator->Play(L"Sonic_crouch_right", false);
		mCollider->SetSize(Vector2(55.0f, 60.0f));
		mCollider->SetCenter(Vector2(38.0f, 40.0f));
		if (Input::GetKeyUp(eKeyCode::Down))
		{
			mAnimator->Reset();
			mSonicState = eSonicState::idle_right;
		}
		if (Input::GetKeyDown(eKeyCode::Space))
		{
			mAnimator->Reset();
			mSonicState = eSonicState::spindash_right;
		}
	}
	void Sonic::lookup_left()
	{
		mAnimator->Play(L"Sonic_lookup_left", false);
		mCollider->SetSize(Vector2(40.0f, 93.75f));
		mCollider->SetCenter(Vector2(15.0f, 10.0f));

		if (Input::GetKeyUp(eKeyCode::Up))
		{
			mAnimator->Reset();
			mSonicState = eSonicState::idle_left;
		}
		if (Input::GetKeyDown(eKeyCode::Space))
		{
			mAnimator->Reset();
			Vector2 velocity = mRigidbody->GetVelocity();
			velocity.y -= 650.0f;

			mRigidbody->SetVelocity(velocity);
			mRigidbody->SetGround(false);
			mSonicState = eSonicState::jump_left;
		}
	}
	void Sonic::lookup_right()
	{
		mAnimator->Play(L"Sonic_lookup_right", false);
	
		mCollider->SetSize(Vector2(40.0f, 93.75f));
		mCollider->SetCenter(Vector2(25.0f, 10.0f));

		if (Input::GetKeyUp(eKeyCode::Up))
		{
			mAnimator->Reset();
			mSonicState = eSonicState::idle_right;
		}
		if (Input::GetKeyDown(eKeyCode::Space))
		{
			mAnimator->Reset();
			Vector2 velocity = mRigidbody->GetVelocity();
			velocity.y -= 650.0f;

			mRigidbody->SetVelocity(velocity);
			mRigidbody->SetGround(false);
			mSonicState = eSonicState::jump_right;
		}
	}

}
