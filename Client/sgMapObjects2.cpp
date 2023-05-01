#include "sgMapObjects2.h"

#include "sgImage.h"
#include "sgTime.h"
#include "sgResources.h"

#include "sgAnimator.h"
#include "sgTransform.h"

namespace sg
{
	MapObjects2::MapObjects2()
		: mAninum(0)
	{
		SetName(L"MapObjects2");
	}
	MapObjects2::MapObjects2(int a)
		: mAninum(a)
	{
		SetName(L"MapObjects2");
	}
	MapObjects2::~MapObjects2()
	{
	}
	void MapObjects2::Initialize()
	{
		mAni = AddComponent<Animator>();
		mTr = GetComponent<Transform>();
		map2[0] = Resources::Load<Image>(L"stage2_1", L"..\\Resources\\map2\\img1.bmp");
		map2[1] = Resources::Load<Image>(L"stage2_2", L"..\\Resources\\map2\\img2.bmp");
		map2[2] = Resources::Load<Image>(L"stage2_3", L"..\\Resources\\map2\\img3.bmp");
		map2[3] = Resources::Load<Image>(L"stage2_4", L"..\\Resources\\map2\\img4.bmp");
		map2[4] = Resources::Load<Image>(L"stage2_5", L"..\\Resources\\map2\\img5.bmp");
		map2[5] = Resources::Load<Image>(L"stage2_6", L"..\\Resources\\map2\\img6.bmp");
		map2[6] = Resources::Load<Image>(L"stage2_7", L"..\\Resources\\map2\\img7.bmp");

		mAni->CreateAnimation(L"stage2_1", map2[0], Vector2::Zero, 6, 1, 6, Vector2::Zero, 0.1);
		mAni->CreateAnimation(L"stage2_2", map2[1], Vector2::Zero, 6, 1, 6, Vector2::Zero, 0.1);
		mAni->CreateAnimation(L"stage2_3", map2[2], Vector2::Zero, 6, 1, 6, Vector2::Zero, 0.1);
		mAni->CreateAnimation(L"stage2_4", map2[3], Vector2::Zero, 6, 1, 6, Vector2::Zero, 0.1);
		mAni->CreateAnimation(L"stage2_5", map2[4], Vector2::Zero, 6, 1, 6, Vector2::Zero, 0.1);
		mAni->CreateAnimation(L"stage2_6", map2[5], Vector2::Zero, 6, 1, 6, Vector2::Zero, 0.1);
		mAni->CreateAnimation(L"stage2_7", map2[6], Vector2::Zero, 6, 1, 6, Vector2::Zero, 0.1);

		GameObject::Initialize();
	}
	void MapObjects2::Update()
	{
		GameObject::Update();

		switch (mAninum)
		{
		case 0:
			mTr->SetPos(Vector2::Zero);
			mAni->Play(L"stage2_1", true);	
			break;
		case 1:
			mTr->SetPos(Vector2(4568, 0));
			mAni->Play(L"stage2_2", true);
			break;
		case 2:
			mTr->SetPos(Vector2(9136, 0));
			mAni->Play(L"stage2_3", true);
			break;
		case 3:
			mTr->SetPos(Vector2(13704, 0));
			mAni->Play(L"stage2_4", true);
			break;
		case 4:
			mTr->SetPos(Vector2(18272, 0));
			mAni->Play(L"stage2_5", true);
			break;
		case 5:
			mTr->SetPos(Vector2(20864, 0));
			mAni->Play(L"stage2_6", true);
			break;
		case 6:
			mTr->SetPos(Vector2(25432, 0));
			mAni->Play(L"stage2_7", true);
			break;
		}

	}
	void MapObjects2::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void MapObjects2::Release()
	{
		GameObject::Release();
	}
}