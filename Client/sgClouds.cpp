#include "sgClouds.h"

#include "sgImage.h"
#include "sgTime.h"
#include "sgResources.h"

#include "sgTransform.h"
#include "sgAnimator.h"


namespace sg
{
	Clouds::Clouds(int a)
	{
		if (a == 1)
		{
			mCNumber = eCNumber::Cloud1;
		}
		else if (a == 2)
		{
			mCNumber = eCNumber::Cloud2;
		}
		else if (a == 3)
		{
			mCNumber = eCNumber::Cloud3;
		}
		else if (a == 4)
		{
			mCNumber = eCNumber::Cloud4;
		}
	}
	Clouds::~Clouds()
	{
	}
	void Clouds::Initialize()
	{
		mTr = GetComponent<Transform>();
		mAni = AddComponent<Animator>();

		Image* c1 = Resources::Load<Image>(L"cloud_1", L"..\\Resources\\map\\cloud_1.bmp");
		Image* c2 = Resources::Load<Image>(L"cloud_2", L"..\\Resources\\map\\cloud_2.bmp");
		Image* c3 = Resources::Load<Image>(L"cloud_3", L"..\\Resources\\map\\cloud_3.bmp");
		Image* c4 = Resources::Load<Image>(L"cloud_4", L"..\\Resources\\map\\cloud_4.bmp");
		mAni->CreateAnimation(L"cloud_1", c1, Vector2::Zero, 1, 1, 1, Vector2::Zero, 1);
		mAni->CreateAnimation(L"cloud_2", c2, Vector2::Zero, 1, 1, 1, Vector2::Zero, 1);
		mAni->CreateAnimation(L"cloud_3", c3, Vector2::Zero, 1, 1, 1, Vector2::Zero, 1);
		mAni->CreateAnimation(L"cloud_4", c4, Vector2::Zero, 1, 1, 1, Vector2::Zero, 1);

		GameObject::Initialize();
	}
	void Clouds::Update()
	{
		GameObject::Update();


		Vector2 pos = mTr->GetPos();
		float speed = static_cast<float>(rand() % 30 + 5);
		pos.x -= speed * Time::DeltaTime();
		mTr->SetPos(pos);

		switch (mCNumber)
		{
		case sg::Clouds::eCNumber::Cloud1:
			mAni->Play(L"cloud_1", true);
			break;
		case sg::Clouds::eCNumber::Cloud2:
			mAni->Play(L"cloud_2", true);
			break;
		case sg::Clouds::eCNumber::Cloud3:
			mAni->Play(L"cloud_3", true);
			break;
		case sg::Clouds::eCNumber::Cloud4:
			mAni->Play(L"cloud_4", true);
			break;
		}
	}
	void Clouds::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void Clouds::Release()
	{
		GameObject::Release();
	}
}