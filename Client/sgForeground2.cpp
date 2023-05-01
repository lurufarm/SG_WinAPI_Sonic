#include "sgForeground2.h"

#include "sgImage.h"
#include "sgResources.h"

#include "sgTransform.h"
#include "sgAnimator.h"



namespace sg
{
	void Foreground2::Initialize()
	{
		mTr = GetComponent<Transform>();
		fg = Resources::Load<Image>(L"fg2", L"..\\Resources\\map2\\foreground1.bmp");
		Image* tree = Resources::Load<Image>(L"trees", L"..\\Resources\\map2\\tree.bmp");
		mAni = AddComponent<Animator>();
		mAni->CreateAnimation(L"foreground2", fg, Vector2::Zero, 6, 1, 6, Vector2::Zero, 0.1);
		mAni->CreateAnimation(L"trees", tree, Vector2::Zero, 6, 1, 6, Vector2::Zero, 0.1);
		mAniN = false;

		GameObject::Initialize();
	}
	void Foreground2::Update()
	{
		GameObject::Update();

		if (mAniN == false)
		{
			mTr->SetScale(Vector2(1.0f, 1.0f));
			mAni->Play(L"foreground2", true);
		}
		else
		{
			mTr->SetScale(Vector2(2.5f, 2.5f));
			mAni->Play(L"trees", true);
		}
	}
	void Foreground2::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void Foreground2::Release()
	{
		GameObject::Release();
	}
}