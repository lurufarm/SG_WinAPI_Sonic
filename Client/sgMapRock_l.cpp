#include "sgMapRock_l.h"
#include "sgSonic.h"

#include "sgTime.h"
#include "sgSceneManager.h"
#include "sgImage.h"
#include "sgResources.h"
#include "sgObject.h"
#include "sgGroundMgr.h"
#include "sgSound.h"

#include "sgTransform.h"
#include "sgAnimator.h"
#include "sgCollider.h"


namespace sg
{
	MapRock_l::MapRock_l()
	{
		SetName(L"MapRock_l");
	}
	MapRock_l::~MapRock_l()
	{
	}
	void MapRock_l::Initialize()
	{
		mAnimator = AddComponent<Animator>();
		mCollider = AddComponent<Collider>();
		mTr = GetComponent<Transform>();
		mTr->SetScale(Vector2(2.5f, 2.5f));

		Image* rock_norm = Resources::Load<Image>(L"rock_norm", L"..\\Resources\\object\\rock.bmp");
		Image* rock_broken = Resources::Load<Image>(L"rock_broken", L"..\\Resources\\object\\brokenrock.bmp");

		mAnimator->CreateAnimation(L"rock_norm", rock_norm, Vector2::Zero, 1, 1, 1, Vector2::Zero, 1.0f);
		mAnimator->CreateAnimation(L"rock_broken", rock_broken, Vector2::Zero, 9, 1, 9, Vector2::Zero, 0.3f);

		mCollider->SetSize(Vector2(120, 197.5));

		mRocklState = eRocklState::norm;

		sBreaking = Resources::Load<Sound>(L"Breakingsound", L"..\\Resources\\sound\\object_crash.wav");

		GameObject::Initialize();
	}
	void MapRock_l::Update()
	{
		GameObject::Update();
		switch (mRocklState)
		{
		case sg::MapRock_l::eRocklState::norm:
			Norm();
			break;
		case sg::MapRock_l::eRocklState::broken:
			Broken();
			break;

		}
	}
	void MapRock_l::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void MapRock_l::Release()
	{
		GameObject::Release();
	}

	void MapRock_l::OnCollisionEnter(Collider* other)
	{

		mUse = true;
		Sonic* sonic = dynamic_cast<Sonic*>(other->GetOwner());
		Vector2 mypos = this->GetComponent<Transform>()->GetPos();
		Vector2 spos = sonic->GetComponent<Transform>()->GetPos();
		if (sonic->GetSonicState() == Sonic::eSonicState::rolling_right
			|| sonic->GetSonicState() == Sonic::eSonicState::rolling_left)
		{
			sBreaking->Play(false);
			mRocklState = MapRock_l::eRocklState::broken;
		}
		
		if (spos.y + 122 < mypos.y)
		{	
			mOn = true;
		}
		else
		{
			mOn = false;
		}
	}
	void MapRock_l::OnCollisionStay(Collider* other)
	{
		Sonic* sonic = dynamic_cast<Sonic*>(other->GetOwner());
		Vector2 mypos = this->GetComponent<Transform>()->GetPos();
		Vector2 spos = sonic->GetComponent<Transform>()->GetPos();

		if (spos.y + 122 < mypos.y)
		{
			mOn = true;
		}
		else
		{
			mOn = false;
		}
	}
	void MapRock_l::OnCollisionExit(Collider* other)
	{
		mUse = false;
		mOn = false;
	}
	void MapRock_l::Norm()
	{
		mAnimator->Play(L"rock_norm", true);
	}
	void MapRock_l::Broken()
	{
		mCollider->SetCenter(Vector2(-1234123, 1234123));
		mAnimator->Play(L"rock_broken", false);

		if (mAnimator->IsComplete())
		{
			object::Destroy(this);
		}
	}
}