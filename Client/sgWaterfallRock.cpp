#include "sgWaterfallRock.h"

#include "sgImage.h"
#include "sgResources.h"

#include "sgTransform.h"
#include "sgAnimator.h"
#include "sgCollider.h"

namespace sg
{
	WaterfallRock::WaterfallRock()
	{
		SetName(L"WFR");
	}
	WaterfallRock::~WaterfallRock()
	{
	}
	void WaterfallRock::Initialize()
	{
		mTr = GetComponent<Transform>();
		mAni = AddComponent<Animator>();
		mCol = AddComponent<Collider>();

		Image* WFR = Resources::Load<Image>(L"WFR", L"..\\Resources\\map2\\waterfallrock.bmp");

		mAni->CreateAnimation(L"WFR", WFR, Vector2::Zero, 2, 1, 2, Vector2::Zero, 0.1);
		mAni->Play(L"WFR", true);

		mTr->SetScale(Vector2(2.5f, 2.5f));
		mCol->SetCenter(Vector2(21, 21));
		mCol->SetSize(Vector2(160, 20));

		GameObject::Initialize();
	}
	void WaterfallRock::Update()
	{
		GameObject::Update();
	}
	void WaterfallRock::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void WaterfallRock::Release()
	{
		GameObject::Release();
	}
	void WaterfallRock::OnCollisionEnter(Collider* other)
	{
		mUse = true;
	}
	void WaterfallRock::OnCollisionStay(Collider* other)
	{
	}
	void WaterfallRock::OnCollisionExit(Collider* other)
	{
		mUse = false;
	}
}