#include "sgRing.h"
#include "sgSonic.h"

#include "sgTime.h"
#include "sgSceneManager.h"
#include "sgResources.h"
#include "sgTransform.h"
#include "sgAnimator.h"
#include "sgCollider.h"
#include "sgCollisionManager.h"
#include "sgObject.h"

namespace sg
{
	Ring::Ring()
	{
	}
	Ring::~Ring()
	{
	}
	void Ring::Initialize()
	{
		mAnimator = AddComponent<Animator>();
		mRingCollider = AddComponent<Collider>();
		mRingCollider->SetCenter(Vector2::Zero);
		mRingCollider->SetSize(Vector2(40.f, 40.f));
		Transform* tr = GetComponent<Transform>();
		tr->SetScale(Vector2(2.5f, 2.5f));
		Image* ring = Resources::Load<Image>(L"ring", L"..\\Resources\\object\\ring.bmp");
		mAnimator->CreateAnimation(L"ring_exist", ring, Vector2::Zero, 4, 2, 4, Vector2::Zero, 0.1);
		mAnimator->CreateAnimation(L"ring_nonex", ring, Vector2(0, 16), 4, 2, 4, Vector2::Zero, 0.01);
		mAnimator->Play(L"ring_exist", true);

		eRingState = eRingState::exist;

		GameObject::Initialize();




	}
	void Ring::Update()
	{
		switch (eRingState)
		{
		case Ring::eRingState::exist:
			Exist();
			break;
		case Ring::eRingState::nonexistent:
			Nonexistent();
			break;
		default:
			break;
		}

		GameObject::Update();

	}
	void Ring::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void Ring::Release()
	{
		GameObject::Release();
	}
	void Ring::OnCollisionEnter(Collider* other)
	{
	}
	void Ring::OnCollisionStay(Collider* other)
	{
		mAnimator->Play(L"ring_nonex", true);
		eRingState = eRingState::nonexistent;
	}
	void Ring::OnCollisionExit(Collider* other)
	{
	}
	void Ring::Exist()
	{
		mAnimator->Play(L"ring_exist", true);
	}
	void Ring::Nonexistent()
	{
		object::Destroy(this);
	}
}