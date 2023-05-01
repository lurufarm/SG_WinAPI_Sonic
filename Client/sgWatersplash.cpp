#include "sgWatersplash.h"

#include "sgImage.h"
#include "sgResources.h"
#include "sgObject.h"
#include "sgSound.h"

#include "sgTransform.h"
#include "sgAnimator.h"


namespace sg
{
	Watersplash::Watersplash()
	{
	}
	Watersplash::~Watersplash()
	{
	}
	void Watersplash::Initialize()
	{
		mTr = GetComponent<Transform>();
		mAni = AddComponent<Animator>();
		Sound* swatersplash = Resources::Load<Sound>(L"water_splash", L"..\\Resources\\sound\\lb_changelayer.wav");
		Image* watersplash = Resources::Load<Image>(L"watersplash", L"..\\Resources\\map\\watersplash.bmp");
		mAni->CreateAnimation(L"watersplash", watersplash, Vector2::Zero, 7, 1, 7, Vector2::Zero, 0.05);
		mAni->Play(L"watersplash", false);
		swatersplash->Play(false);
		GameObject::Initialize();

	}
	void Watersplash::Update()
	{
		GameObject::Update();

		if (mAni->IsComplete())
		{
			object::Destroy(this);
		}

	}
	void Watersplash::Render(HDC hdc)
	{
		GameObject::Render(hdc);

	}
	void Watersplash::Release()
	{

		GameObject::Release();
	}
}