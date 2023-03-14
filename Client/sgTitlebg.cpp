#include "sgTitlebg.h"
#include "sgTime.h"
#include "sgInput.h"
#include "sgSceneManager.h"
#include "sgResources.h"
#include "sgTransform.h"
#include "sgAnimator.h"
#include "sgObject.h"


namespace sg
{
	Titlebg::Titlebg()
	{
	}
	Titlebg::~Titlebg()
	{
	}
	void Titlebg::Initialize()
	{
		Image* intro_bg = Resources::Load<Image>(L"intro_bg", L"..\\Resources\\intro\\intro_bg.bmp");
		Transform* tr = GetComponent<Transform>();
		tr->SetScale(Vector2(3.5f, 3.5f));
		mAnimator = AddComponent<Animator>();
		mAnimator->CreateAnimation(L"intro_bg_ani", intro_bg, Vector2::Zero, 6, 1, 6, Vector2::Zero, 0.3);
		mAnimator->Play(L"intro_bg_ani", true);

		GameObject::Initialize();
	}
	void Titlebg::Update()
	{
		GameObject::Update();
	}
	void Titlebg::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void Titlebg::Release()
	{
		GameObject::Release();
	}
}