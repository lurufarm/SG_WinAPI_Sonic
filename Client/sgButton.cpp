#include "sgButton.h"
#include "sgKnuckles.h"

#include "sgImage.h"
#include "sgResources.h"

#include "sgTransform.h"
#include "sgAnimator.h"
#include "sgCollider.h"


namespace sg
{
	Button::Button()
		: mPush(false)
	{
	}
	Button::~Button()
	{
	}
	void Button::Initialize()
	{
		mTr = GetComponent<Transform>();
		mAni = AddComponent<Animator>();
		mCol = AddComponent<Collider>();
		
		Image* button = Resources::Load<Image>(L"button", L"..\\Resources\\object\\button.bmp");
		mAni->CreateAnimation(L"button_norm", button, Vector2(0, 0), 2, 1, 1, Vector2::Zero, 1);
		mAni->CreateAnimation(L"button_pushed", button, Vector2(32, 0), 2, 1, 1, Vector2::Zero, 1);

		mTr->SetScale(Vector2(2.5f, 2.5f));
		mCol->SetSize(Vector2(20, 20));
		mCol->SetCenter(Vector2(30, 0));
		GameObject::Initialize();
	}
	void Button::Update()
	{
		GameObject::Update();

		if (mPush == false)
		{
			mAni->Play(L"button_norm", true);
			mCol->SetCenter(Vector2::Zero);
		}
		else
		{
			mAni->Play(L"button_pushed", true);
			mCol->SetCenter(Vector2(30, 20));

		}

	}
	void Button::Render(HDC hdc)
	{
		GameObject::Render(hdc);

	}
	void Button::Release()
	{
		GameObject::Release();

	}
	void Button::OnCollisionEnter(Collider* other)
	{
		mPush = true;
	}
	void Button::OnCollisionStay(Collider* other)
	{
		mPush = true;
	}
	void Button::OnCollisionExit(Collider* other)
	{
	}
}