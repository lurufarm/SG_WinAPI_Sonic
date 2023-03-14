#include "sgTitlesonic.h"

#include "sgTime.h"
#include "sgSceneManager.h"
#include "sgInput.h"
#include "sgResources.h"
#include "sgTransform.h"
#include "sgAnimator.h"
#include "sgScene.h"
#include "sgObject.h"



namespace sg
{
	Titlesonic::Titlesonic()
	{
	}
	Titlesonic::~Titlesonic()
	{
	}
	void Titlesonic::Initialize()
	{
		Image* intro_sonic = Resources::Load<Image>(L"intro_sonic", L"..\\Resources\\intro\\intro_sonic.bmp");
		Transform* tr = GetComponent<Transform>();
		mAnimator = AddComponent<Animator>();
		tr->SetScale(Vector2(3.5f, 3.5f));

		mAnimator->CreateAnimation(L"intro_sonic_ani", intro_sonic, Vector2::Zero, 8, 1, 8, Vector2::Zero, 0.13);
		mAnimator->Play(L"intro_sonic_ani", true);

		GameObject::Initialize();
	}
	void Titlesonic::Update()
	{
		GameObject::Update();
	}
	void Titlesonic::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void Titlesonic::Release()
	{
		GameObject::Release();
	}
}