#include "sgEndST.h"

#include "sgImage.h"
#include "sgResources.h"
#include "sgTime.h"

#include "sgTransform.h"
#include "sgAnimator.h"

namespace sg
{
	EndST::EndST()
		: mBool(false)
	{
		SetName(L"EndST");
	}
	EndST::~EndST()
	{
	}
	void EndST::Initialize()
	{
		mTr = GetComponent<Transform>();
		mAni = AddComponent<Animator>();

		Image* ST = Resources::Load<Image>(L"ST", L"..\\Resources\\ending\\sonicandtails.bmp");

		mAni->CreateAnimation(L"ST_1", ST, Vector2::Zero, 2, 4, 2, Vector2::Zero, 0.1);
		mAni->CreateAnimation(L"ST_2", ST, Vector2(0, 48), 2, 4, 2, Vector2::Zero, 0.1);
		mAni->CreateAnimation(L"ST_3", ST, Vector2(0, 96), 2, 4, 2, Vector2::Zero, 0.1);
		mAni->CreateAnimation(L"ST_4", ST, Vector2(0, 144), 2, 4, 2, Vector2::Zero, 0.1);

		mTr->SetScale(Vector2(2.5f, 2.5f));

		GameObject::Initialize();
	}
	void EndST::Update()
	{
		GameObject::Update();

		Vector2 pos = mTr->GetPos();

		if (pos.x < 500 && mBool == false)
		{
			mAni->Play(L"ST_1", true);
			pos.x += 100 * Time::DeltaTime();
			mTr->SetPos(pos);
		}
		else if (pos.x > 500 && pos.x < 650 && mBool == false)
		{
			mAni->Play(L"ST_2", true);
			pos.x += 100 * Time::DeltaTime();
			mTr->SetPos(pos);
		}
		else if (pos.x > 650 && pos.x < 900 && mBool == false)
		{
			mAni->Play(L"ST_3", true);
			pos.x += 100 * Time::DeltaTime();
			mTr->SetPos(pos);
		}
		if (pos.x > 900 && mBool == false)
		{
			mBool = true;
		}
		if (mBool)
		{
			mAni->Play(L"ST_4", true);
			pos.x -= 60 * Time::DeltaTime();
			mTr->SetPos(pos);
		}
		if (mBool && pos.x < -400)
		{
			mBool = false;
		}
	}
	void EndST::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void EndST::Release()
	{
		GameObject::Release();
	}
}