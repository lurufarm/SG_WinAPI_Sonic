#include "sgRope.h"
#include "sgSonic.h"

#include "sgImage.h"
#include "sgResources.h"
#include "sgTime.h"
#include "sgInput.h"

#include "sgTransform.h"
#include "sgAnimator.h"
#include "sgCollider.h"
#include "sgRigidbody.h"


namespace sg
{
	Rope::Rope()
		: mTime(0.0f)
		, index(0)
	{
		SetName(L"Rope");
	}
	Rope::~Rope()
	{
	}
	void Rope::Initialize()
	{
		mAnimator = AddComponent<Animator>();
		mCollider = AddComponent<Collider>();
		Image* rope = Resources::Load<Image>(L"ropeimag", L"..\\Resources\\object\\rope.bmp");
		mAnimator->CreateAnimation(L"rope_ani", rope, Vector2::Zero, 24, 1, 24, Vector2::Zero, 0.15);
		Transform* tr = GetComponent<Transform>();
		tr->SetScale(Vector2(2.5f, 2.5f));
		mAnimator->Play(L"rope_ani", true);
		colpos = Vector2(300, 320);
		mCollider->SetSize(Vector2(50.0f, 10.0f));
		mCollider->SetCenter(colpos);
		index = 0;
		
		GameObject::Initialize();
	}
	void Rope::Update()
	{
		GameObject::Update();

		mTime += Time::DeltaTime();

		float duration = 0.15f;
		int index = mAnimator->GetAniIndex(L"rope_ani");


			switch (index)
			{
			case 0:
				mTime = 0;
				colpos.x = math::Lerp(300.0f, 375.0f, mTime / duration);
				colpos.y = math::Lerp(318.0f, 308.0f, mTime / duration);
				break;
			case 1:
				mTime = 0;
				colpos.x = math::Lerp(375.0f, 440.0f, mTime / duration);
				colpos.y = math::Lerp(308.0f, 275.0f, mTime / duration);
				break;
			case 2:
				mTime = 0;
				colpos.x = math::Lerp(440.0f, 502.0f, mTime / duration);
				colpos.y = math::Lerp(275.0f, 228.0f, mTime / duration);
				break;
		case 3:
			mTime = 0;
			colpos.x = math::Lerp(502.0f, 552.0f, mTime / duration);
			colpos.y = math::Lerp(228.0f, 173.0f, mTime / duration);
			break;
		case 4:
			mTime = 0;
			colpos.x = math::Lerp(552.0f, 577.0f, mTime / duration);
			colpos.y = math::Lerp(173.0f, 103.0f, mTime / duration);
			break;
		case 5:
			mTime = 0;
			colpos.x = math::Lerp(577.0f, 590.0f, mTime / duration);
			colpos.y = math::Lerp(103.0f, 28.0f, mTime / duration);
			break;
		case 6:
			mTime = 0;
			colpos.x = math::Lerp(590.0f, 577.0f, mTime / duration);
			colpos.y = math::Lerp(28.0f, 103.0f, mTime / duration);
			break;
		case 7:
			mTime = 0;
			colpos.x = math::Lerp(577.0f, 552.0f, mTime / duration);
			colpos.y = math::Lerp(103.0f, 173.0f, mTime / duration);
			break;
		case 8:
			mTime = 0;
			colpos.x = math::Lerp(552.0f, 502.0f, mTime / duration);
			colpos.y = math::Lerp(173.0f, 228.0f, mTime / duration);
			break;
		case 9:
			mTime = 0;
			colpos.x = math::Lerp(502.0f, 440.0f, mTime / duration);
			colpos.y = math::Lerp(228.0f, 275.0f, mTime / duration);
			break;
		case 10:
			mTime = 0;
			colpos.x = math::Lerp(440.0f, 375.0f, mTime / duration);
			colpos.y = math::Lerp(275.0f, 308.0f, mTime / duration);
			break;
		case 11:
			mTime = 0;
			colpos.x = math::Lerp(375.0f, 300.0f, mTime / duration);
			colpos.y = math::Lerp(308.0f, 318.0f, mTime / duration);
			break;
		case 12:
			mTime = 0;
			colpos.x = math::Lerp(300.0f, 217.0f, mTime / duration);
			colpos.y = math::Lerp(318.0f, 308.0f, mTime / duration);
			break;
		case 13:
			mTime = 0;
			colpos.x = math::Lerp(217.0f, 150.0f, mTime / duration);
			colpos.y = math::Lerp(308.0f, 275.0f, mTime / duration);
			break;
		case 14:
			mTime = 0;
			colpos.x = math::Lerp(150.0f, 90.0f, mTime / duration);
			colpos.y = math::Lerp(275.0f, 228.0f, mTime / duration);
			break;
		case 15:
			mTime = 0;
			colpos.x = math::Lerp(90.0f, 45.0f, mTime / duration);
			colpos.y = math::Lerp(228.0f, 173.0f, mTime / duration);
			break;
		case 16:
			mTime = 0;
			colpos.x = math::Lerp(45.0f,  15.0f, mTime / duration);
			colpos.y = math::Lerp(173.0f, 103.0f, mTime / duration);
			break;
		case 17:
			mTime = 0;
			colpos.x = math::Lerp(15.0f,  7.0f, mTime / duration);
			colpos.y = math::Lerp(103.0f, 28.0f, mTime / duration);
			break;
		case 18:
			mTime = 0;
			colpos.x = math::Lerp(7.0f,  15.0f, mTime / duration);
			colpos.y = math::Lerp(28.0f, 103.0f, mTime / duration);
			break;
		case 19:
			mTime = 0;
			colpos.x = math::Lerp(15.0f,  45.0f, mTime / duration);
			colpos.y = math::Lerp(103.0f, 173.0f, mTime / duration);
		case 20:
			mTime = 0;
			colpos.x = math::Lerp(45.0f,  90.0f, mTime / duration);
			colpos.y = math::Lerp(173.0f, 228.0f, mTime / duration);
			break;
		case 21:
			mTime = 0;
			colpos.x = math::Lerp(90.0f,  150.0f, mTime / duration);
			colpos.y = math::Lerp(228.0f, 275.0f, mTime / duration);
			break;
		case 22:
			mTime = 0;
			colpos.x = math::Lerp(150.0f, 217.0f, mTime / duration);
			colpos.y = math::Lerp(275.0f, 308.0f, mTime / duration);
			break;	
		case 23:
			mTime = 0;
			colpos.x = math::Lerp(217.0f, 300.0f, mTime / duration);
			colpos.y = math::Lerp(308.0f, 318.0f, mTime / duration);
			break;
		
		}

		mCollider->SetCenter(colpos);
	}
	void Rope::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void Rope::Release()
	{
		GameObject::Release();
	}
	void Rope::OnCollisionEnter(Collider* other)
	{
		mUse = true;
	}
	void Rope::OnCollisionStay(Collider* other)
	{
	}
	void Rope::OnCollisionExit(Collider* other)
	{
		Sonic* sonic = dynamic_cast<Sonic*>(other->GetOwner());
		mUse = false;
		sonic->GetComponent<Rigidbody>()->SetGround(false);
		Rope::Initialize();
	}
}