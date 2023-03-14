#include "sgSonic.h"
#include "sgTime.h"
#include "sgInput.h"
#include "sgSceneManager.h"
#include "sgResources.h"
#include "sgTransform.h"
#include "sgAnimator.h"
#include "sgCollider.h"
#include "sgScene.h"
#include "sgObject.h"
#include "sgRigidbody.h"

namespace sg
{
	Sonic::Sonic()
		: mBoredTime(0.0f)
	{
	}

	Sonic::~Sonic()
	{
	}

	void Sonic::Initialize()
	{
		//mAnimator = AddComponent<Animator>();
		Transform* tr = GetComponent<Transform>();
		Image* mImage_idle1 = Resources::Load<Image>(L"Sonic_idle_right", L"..\\Resources\\sonic\\sonic_idle_right.bmp");
		Image* mImage_idle2 = Resources::Load<Image>(L"Sonic_idle_left", L"..\\Resources\\sonic\\sonic_idle_left.bmp");
		Image* mImage_bored = Resources::Load<Image>(L"Sonic_idle_bored", L"..\\Resources\\sonic\\sonic_idle2.bmp");
		Image* mImage_walk = Resources::Load<Image>(L"Sonic_walk", L"..\\Resources\\sonic\\sonic_walk.bmp");
		Image* mImage_LookUpAndCrouch = Resources::Load<Image>(L"Sonic_LookUpAndCrouch", L"..\\Resources\\sonic\\sonic_LookUpAndCrouch.bmp");
		Image* mImage_run_left = Resources::Load<Image>(L"Sonic_run_left", L"..\\Resources\\sonic\\sonic_run.left.bmp");
		Image* mImage_run_right = Resources::Load<Image>(L"Sonic_run_right", L"..\\Resources\\sonic\\sonic_run_right.bmp");
		Image* mImage_skid = Resources::Load<Image>(L"mImage_skid", L"..\\Resources\\sonic\\sonic_skid.bmp");


		tr->SetScale(Vector2(2.5f, 2.5f));
		mAnimator->CreateAnimation(L"Sonic_idle_left", mImage_idle2, Vector2::Zero, 1, 1, 1, Vector2::Zero, 0.1);
		mAnimator->CreateAnimation(L"Sonic_idle_right", mImage_idle1, Vector2::Zero, 1, 1, 1, Vector2::Zero, 0.1);
		mAnimator->CreateAnimation(L"Sonic_idle_bored", mImage_bored, Vector2::Zero, 12, 1, 12, Vector2::Zero, 0.2);
		mAnimator->CreateAnimation(L"Sonic_walk_left", mImage_walk, Vector2(0.0f, 40.0f), 8, 2, 8, Vector2::Zero, 0.1);
		mAnimator->CreateAnimation(L"Sonic_walk_right", mImage_walk, Vector2::Zero, 8, 2, 8, Vector2::Zero, 0.1);
		mAnimator->CreateAnimation(L"Sonic_lookup_left", mImage_LookUpAndCrouch, Vector2(120.0f,0.0f), 4, 2, 2, Vector2::Zero, 0.1);
		mAnimator->CreateAnimation(L"Sonic_lookup_right", mImage_LookUpAndCrouch, Vector2::Zero, 4, 2, 2, Vector2::Zero, 0.1);
		mAnimator->CreateAnimation(L"Sonic_crouch_left", mImage_LookUpAndCrouch, Vector2(120.0f, 41.0f), 4, 2, 2, Vector2::Zero, 0.1);
		mAnimator->CreateAnimation(L"Sonic_crouch_right", mImage_LookUpAndCrouch, Vector2(0.0f, 41.0f), 4, 2, 2, Vector2::Zero, 0.1);
		mAnimator->CreateAnimation(L"Sonic_run_left", mImage_run_left, Vector2::Zero, 4, 1, 4, Vector2::Zero, 0.1);
		mAnimator->CreateAnimation(L"Sonic_run_right", mImage_run_right, Vector2::Zero, 4, 1, 4, Vector2::Zero, 0.1);
		mAnimator->CreateAnimation(L"Sonic_skid_left", mImage_skid, Vector2::Zero, 4, 2, 4, Vector2::Zero, 0.15);
		mAnimator->CreateAnimation(L"Sonic_skid_right", mImage_skid, Vector2(0,38), 4, 2, 4, Vector2::Zero, 0.15);

		mAnimator->Play(L"Sonic_idle_right", true);

		Collider* collider = AddComponent<Collider>();
		collider->SetCenter(Vector2::Zero);

		mRigidbody = AddComponent<Rigidbody>();
		mRigidbody->SetMass(1.0f);

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
		case sg::Sonic::eSonicState::idle_bored:
			idle_bored();
			break;
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
		case sg::Sonic::eSonicState::skid_left:
			skid_left();
			break;
		case sg::Sonic::eSonicState::skid_right:
			skid_right();
			break;
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
		Collider* collider = GetComponent<Collider>();
		collider->SetSize(Vector2(40.0f, 93.75f));
		collider->SetCenter(Vector2(15.0f, 3.0f));

		mBoredTime += Time::DeltaTime();
		if (mBoredTime >= 3.0f)
		{
			mSonicState = eSonicState::idle_bored;
			mBoredTime = 0.0f;
		}


		if (Input::GetKeyDown(eKeyCode::Left))
		{
			mSonicState = eSonicState::walk_left;
			mAnimator->Play(L"Sonic_walk_left", true);
		}
		if (Input::GetKeyDown(eKeyCode::Right))
		{
			mSonicState = eSonicState::walk_right;
			mAnimator->Play(L"Sonic_walk_right", true);
		}
		if (Input::GetKeyDown(eKeyCode::Up))
		{
			mSonicState = eSonicState::lookup_left;
			mAnimator->Play(L"Sonic_lookup_left", true);
		}
		if (Input::GetKeyDown(eKeyCode::Down))
		{
			mSonicState = eSonicState::crouch_left;
			mAnimator->Play(L"Sonic_crouch_left", true);
		}
	}
	void Sonic::idle_right()
	{
		mAnimator->Play(L"Sonic_idle_right", true);
		Collider* collider = GetComponent<Collider>();
		collider->SetSize(Vector2(40.0f, 93.75f));
		collider->SetCenter(Vector2(25.0f, 3.0f));

		mBoredTime += Time::DeltaTime();
		if (mBoredTime >= 3.0f)
		{
			mSonicState = eSonicState::idle_bored;
			mBoredTime = 0.0f;
		}


		if (Input::GetKeyDown(eKeyCode::Left))
		{
			mSonicState = eSonicState::walk_left;
			mAnimator->Play(L"Sonic_walk_left", true);
		}
		if (Input::GetKeyDown(eKeyCode::Right))
		{
			mSonicState = eSonicState::walk_right;
			mAnimator->Play(L"Sonic_walk_right", true);
		}
		if (Input::GetKeyDown(eKeyCode::Up))
		{
			mSonicState = eSonicState::lookup_right;
			mAnimator->Play(L"Sonic_lookup_right", true);
		}
		if (Input::GetKeyDown(eKeyCode::Down))
		{
			mSonicState = eSonicState::crouch_right;
			mAnimator->Play(L"Sonic_crouch_left", true);
		}
	}
	void Sonic::idle_bored()
	{
		Transform* tr = GetComponent<Transform>();
		mAnimator->Play(L"Sonic_idle_bored", true);
		Collider* collider = GetComponent<Collider>();
		collider->SetSize(Vector2(55.0f, 93.75f));
		collider->SetCenter(Vector2(25.0f, 3.0f));


		if (Input::GetKeyUp(eKeyCode::Left))
		{
			mSonicState = eSonicState::idle_left;
			mAnimator->Play(L"Sonic_idle_left", true);
		}
		if (Input::GetKeyDown(eKeyCode::Right))
		{
			mSonicState = eSonicState::walk_right;
			mAnimator->Play(L"Sonic_walk_right", true);
		}
	}
	void Sonic::walk_left()
	{
		Transform* tr = GetComponent<Transform>();
		mSonicPos = tr->GetPos();
		Collider* collider = GetComponent<Collider>();
		collider->SetSize(Vector2(55.0f, 93.75f));
		collider->SetCenter(Vector2(25.0f, 3.0f));

		if (Input::GetKeyUp(eKeyCode::Left))
		{
			mSonicState = eSonicState::idle_left;
			mAnimator->Play(L"Sonic_idle_left", true);
		}
		if (Input::GetKeyDown(eKeyCode::Right))
		{
			mSonicState = eSonicState::walk_right;
			mAnimator->Play(L"Sonic_walk_right", true);
		}
		if (Input::GetKey(eKeyCode::Left))
			//mSonicPos.x -= 300.0f * Time::DeltaTime();
			mRigidbody->AddForce(Vector2(-300.0f, 0.0f));
		if (mRigidbody->GetVelocity().x <= -1000.0f
			&& mSonicState == eSonicState::walk_left)
		{
			mSonicState = eSonicState::run_left;
		}
		
		//tr->SetPos(mSonicPos);
		mAnimator->Play(L"Sonic_walk_left", true);

	}
	void Sonic::walk_right()
	{
		Transform* tr = GetComponent<Transform>();
		mSonicPos= tr->GetPos();
		Collider* collider = GetComponent<Collider>();
		collider->SetSize(Vector2(55.0f, 93.75f));
		collider->SetCenter(Vector2(30.0f, 3.0f));

		if (Input::GetKeyUp(eKeyCode::Right))
		{
			mSonicState = eSonicState::idle_right;
			mAnimator->Play(L"Sonic_idle_right", true);
		}
		if (Input::GetKeyDown(eKeyCode::Left))
		{
			mSonicState = eSonicState::walk_left;
			mAnimator->Play(L"Sonic_walk_left", true);
		}
		if(Input::GetKey(eKeyCode::Right))
			//mSonicPos.x += 300.0f * Time::DeltaTime();
			mRigidbody->AddForce(Vector2(300.0f, 0.0f));
		if (mRigidbody->GetVelocity().x >= 1000.0f 
			&& mSonicState == eSonicState::walk_right)
		{
			mSonicState = eSonicState::run_right;
		}
		
		
		//tr->SetPos(mSonicPos);
		mAnimator->Play(L"Sonic_walk_right", true);

	}
	void Sonic::run_left()
	{
		mAnimator->Play(L"Sonic_run_left", true);
		if (Input::GetKey(eKeyCode::Left))
			mRigidbody->AddForce(Vector2(-500.0f, 0.0f));
		if (Input::GetKeyUp(eKeyCode::Left))
		{
			mRigidbody->AddForce(Vector2(+5000, 0));
			mSonicState = eSonicState::idle_right;
		}
		if (Input::GetKeyDown(eKeyCode::Right))
		{
			mSonicState = eSonicState::skid_left;
			mRigidbody->AddForce(Vector2(80000.0f, 0.0f));
		}
	}
	void Sonic::run_right()
	{
		mAnimator->Play(L"Sonic_run_right", true);
		if (Input::GetKey(eKeyCode::Right))
			mRigidbody->AddForce(Vector2(500.0f, 0.0f));
		if (Input::GetKeyUp(eKeyCode::Right))
		{
			mRigidbody->AddForce(Vector2(-5000,0));
			mSonicState = eSonicState::idle_right;
		}
		if (Input::GetKeyDown(eKeyCode::Left))
		{
			mSonicState = eSonicState::skid_right;
			mRigidbody->AddForce(Vector2(-80000.0f, 0.0f));
		}
		
	}
	void Sonic::skid_left()
	{
		mAnimator->Play(L"Sonic_skid_right", true);
		mRigidbody->AddForce(Vector2(+10000.0f, 0.0f));
		if (Input::GetKey(eKeyCode::Right))
			mSonicState = eSonicState::walk_right;
		if (Input::GetKey(eKeyCode::Left))
			mSonicState = eSonicState::walk_left;
		if (Input::GetKeyUp(eKeyCode::Left)
			|| Input::GetKeyUp(eKeyCode::Right))
		{
			mSonicState = eSonicState::idle_left;
		}
	}
	void Sonic::skid_right()
	{
		mAnimator->Play(L"Sonic_skid_left", true);
		mRigidbody->AddForce(Vector2(-10000.0f, 0.0f));
		if (Input::GetKey(eKeyCode::Left))
			mSonicState = eSonicState::walk_right;
		if (Input::GetKey(eKeyCode::Right))
			mSonicState = eSonicState::walk_left;
		if (Input::GetKeyUp(eKeyCode::Left)
			|| Input::GetKeyUp(eKeyCode::Right))
		{
			mSonicState = eSonicState::idle_right;
		}
	}
	void Sonic::crouch_left()
	{
		if (Input::GetKeyUp(eKeyCode::Down))
		{
			mSonicState = eSonicState::idle_left;
		}
		mAnimator->Play(L"Sonic_crouch_left", false);
		Collider* collider = GetComponent<Collider>();
		collider->SetSize(Vector2(55.0f, 60.0f));
		collider->SetCenter(Vector2(10.0f, 40.0f));
	}
	void Sonic::crouch_right()
	{

		if (Input::GetKeyUp(eKeyCode::Down))
		{
			mSonicState = eSonicState::idle_right;
		}
		mAnimator->Play(L"Sonic_crouch_right", false);
		Collider* collider = GetComponent<Collider>();
		collider->SetSize(Vector2(55.0f, 60.0f));
		collider->SetCenter(Vector2(38.0f, 40.0f));
	}
	void Sonic::lookup_left()
	{
		if (Input::GetKeyUp(eKeyCode::Up))
		{
			mSonicState = eSonicState::idle_left;
		}
		mAnimator->Play(L"Sonic_lookup_left", false);
		Collider* collider = GetComponent<Collider>();
		collider->SetSize(Vector2(40.0f, 93.75f));
		collider->SetCenter(Vector2(15.0f, 10.0f));
	}
	void Sonic::lookup_right()
	{
		if (Input::GetKeyUp(eKeyCode::Up))
		{
			mSonicState = eSonicState::idle_right;
		}
		mAnimator->Play(L"Sonic_lookup_right", false);
		Collider* collider = GetComponent<Collider>();
		collider->SetSize(Vector2(40.0f, 93.75f));
		collider->SetCenter(Vector2(25.0f, 10.0f));
	}
}
