#include "sgBackground2.h"

#include "sgTime.h"
#include "sgInput.h"
#include "sgSceneManager.h"
#include "sgResources.h"
#include "sgCamera.h"
#include "sgObject.h"

#include "sgTransform.h"
#include "sgAnimator.h"

namespace sg
{
	Background2::Background2()
		: mTr(GetComponent<Transform>())
		, mPos(Vector2::Zero)
	{
		SetName(L"Background2");
	}
	Background2::~Background2()
	{
	}
	void Background2::Initialize()
	{
		mTr = GetComponent<Transform>();
		background2Image[0] = Resources::Load<Image>(L"background2_1", L"..\\Resources\\map2\\background2_1.bmp");
		background2Image[1] = Resources::Load<Image>(L"background2_2", L"..\\Resources\\map2\\background2_2.bmp");
		background2Image[2] = Resources::Load<Image>(L"background2_3", L"..\\Resources\\map2\\background2_3.bmp");

		mAni = AddComponent<Animator>();
		mAni->CreateAnimation(L"bg2_1", background2Image[0], Vector2::Zero, 6, 1, 6, Vector2::Zero, 0.1);
		mAni->CreateAnimation(L"bg2_2", background2Image[1], Vector2::Zero, 6, 1, 6, Vector2::Zero, 0.1);
		mAni->CreateAnimation(L"bg2_3", background2Image[2], Vector2::Zero, 6, 1, 6, Vector2::Zero, 0.1);

		mTr->SetScale(Vector2(0.5f, 0.5f));

		GameObject::Initialize();
	}
	void Background2::Update()
	{
		Vector2 cPos = Camera::GetCameraPos();
		switch (mBGState)
		{
		case sg::Background2::eBGState::bg1:
			mAni->Play(L"bg2_1", true);
			mTr->SetPos(Vector2(mPos.x + cPos.x * 0.3f, mPos.y + cPos.y - 750));
			if (cPos.x - 500 - (mPos.x + cPos.x * 0.3f + 1280) > 0)
			{
				mPos.x += 1280 * 2.0f;
			}
			if (cPos.x + 500 - (mPos.x + cPos.x * 0.3f) < 0)
			{
				mPos.x -= 1280 * 2.0f;
			}
			break;
		case sg::Background2::eBGState::bg2:
			mAni->Play(L"bg2_2", true);
			mTr->SetPos(Vector2(mPos.x + cPos.x * 0.8f, mPos.y + cPos.y - 750));
			if (cPos.x - (mPos.x + cPos.x * 0.8f + 1280) > 0)
			{
				mPos.x += 1280 * 2.0f;
			}
			if (cPos.x + 500 - (mPos.x + cPos.x * 0.8f) < 0)
			{
				mPos.x -= 1280 * 2.0f;
			}
			break;
		case sg::Background2::eBGState::bg3:
			mAni->Play(L"bg2_3", true);
			mTr->SetPos(Vector2(mPos.x + cPos.x * 0.5f, mPos.y + cPos.y - 750));
			if (cPos.x - (mPos.x + cPos.x * 0.5f + 1280) > 0)
			{
				mPos.x += 1280 * 2.0f;
			}
			if (cPos.x + 500 - (mPos.x + cPos.x * 0.5f) < 0)
			{
				mPos.x -= 1280 * 2.0f;
			}
			break;
		}

		GameObject::Update();
	}
	void Background2::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void Background2::Release()
	{
		GameObject::Release();
	}
}