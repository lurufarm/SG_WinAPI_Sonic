#include "sgBloomBullet.h"
#include "sgSonic.h"
#include "sgTestGround.h"

#include "sgTime.h"
#include "sgSceneManager.h"
#include "sgTransform.h"
#include "sgAnimator.h"
#include "sgRigidbody.h"
#include "sgCollider.h"
#include "sgResources.h"
#include "sgImage.h"
#include "sgObject.h"

namespace sg
{
	BloomBullet::BloomBullet()
		: mTime(0.0f)
	{
		this->SetName(L"BloomBullet");
	}
	BloomBullet::~BloomBullet()
	{
	}
	void BloomBullet::Initialize()
	{
		mState = GameObject::eState::Active;
		Image* bullet = Resources::Load<Image>(L"Bloombullet", L"..\\Resources\\enemies\\bloominator_bullet.bmp");
		mAnimator->CreateAnimation(L"bullet", bullet, Vector2::Zero, 1, 1, 1, Vector2::Zero, 0.1);
		Transform* tr = GetComponent<Transform>();
		tr->SetScale(Vector2(2.5f, 2.5f));
		mRigidbody->SetMass(0.1);
		mRigidbody->SetGround(false);
		mAnimator->Play(L"bullet", false);
		mCollider->SetSize(Vector2(40.0f, 40.0f));

		GameObject::Initialize();
	}
	void BloomBullet::Update()
	{
		GameObject::Update();

		Transform* tr = GetComponent<Transform>();
		//Vector2 dir = Vector2(500.0, 500.0f);
		//dir.Nomalize();	
		mTime += Time::DeltaTime();
		if (/*mTime >= 3.0f ||*/ mRigidbody->GetGround() == true)
		{
			object::Destroy(this);
		}
	}
	void BloomBullet::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void BloomBullet::Release()
	{
		GameObject::Release();
	}
	void BloomBullet::OnCollisionEnter(Collider* other)
	{
		Sonic* sonic = dynamic_cast<Sonic*>(other->GetOwner());
		if (sonic == nullptr)
			return;

		if (sonic->GetComponent<Transform>()->GetPos().x <=
			this->GetComponent<Transform>()->GetPos().x)
		{
			if (sonic->GetHurt() == false)
			{
				sonic->SetSonicState(Sonic::eSonicState::hurt_right);
			}
		}
		else if (sonic->GetComponent<Transform>()->GetPos().x >
			this->GetComponent<Transform>()->GetPos().x)
		{
			if (sonic->GetHurt() == false)
			{
				sonic->SetSonicState(Sonic::eSonicState::hurt_left);
			}
		}

	}
	void BloomBullet::OnCollisionStay(Collider* other)
	{

	}
	void BloomBullet::OnCollisionExit(Collider* other)
	{
		
	}
}