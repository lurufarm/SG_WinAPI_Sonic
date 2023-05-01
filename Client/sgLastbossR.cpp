#include "sgLastbossR.h"
#include "sgLastboss.h"

#include "sgImage.h"
#include "sgResources.h"
#include "sgTime.h"
#include "sgObject.h"

#include "sgTransform.h"
#include "sgAnimator.h"

namespace sg
{
	LastbossR::LastbossR()
	{
	}
	LastbossR::~LastbossR()
	{
	}
	void LastbossR::Initialize()
	{
		mTr = GetComponent<Transform>();
		mAni = AddComponent<Animator>();

		Image* lastboss = Resources::Load<Image>(L"lastboss", L"..\\Resources\\enemies\\lastboss.bmp");
		mAni->CreateAnimation(L"lb_idle_left", lastboss, Vector2(111, 0), 4, 7, 1, Vector2::Zero, 0.1);
		mAni->CreateAnimation(L"lb_idle_right", lastboss, Vector2::Zero, 4, 7, 1, Vector2::Zero, 0.1);

		mTr->SetScale(Vector2(2.5f, 2.5f));

		GameObject::Initialize();
	}
	void LastbossR::Update()
	{
		GameObject::Update();

		Vector2 mPos = mTr->GetPos();

		if (mLB == nullptr)
		{
			mTr->SetScale(Vector2(1, 1));
			mAni->Play(L"lb_idle_right", true);
			mPos.x += 1300 * Time::DeltaTime();
			mTr->SetPos(mPos);
		}
		else if (mLB->mDir)
		{
			mAni->Play(L"lb_idle_left", true);
			mPos.x -= 200.0f * Time::DeltaTime();
			mTr->SetPos(mPos);
		}
		else if (mLB->mDir == false)
		{
			mAni->Play(L"lb_idle_right", true);
			mPos.x += 200.0f * Time::DeltaTime();
			mTr->SetPos(mPos);
		}
	}
	void LastbossR::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void LastbossR::Release()
	{
		GameObject::Release();
	}
}