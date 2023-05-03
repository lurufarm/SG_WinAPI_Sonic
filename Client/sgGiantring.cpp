#include "sgGiantring.h"

#include "sgImage.h"
#include "sgResources.h"
#include "sgSound.h"

#include "sgTransform.h"
#include "sgAnimator.h"
#include "sgCollider.h"

namespace sg
{
	Giantring::Giantring()
	{
	}
	Giantring::~Giantring()
	{
	}
	void Giantring::Initialize()
	{
		mAni = AddComponent<Animator>();
		mCol = AddComponent<Collider>();
		Transform* tr = GetComponent<Transform>();

		Image* GR = Resources::Load<Image>(L"giantring", L"..\\Resources\\object\\giantring.bmp");
		Image* GR2 = Resources::Load<Image>(L"giantring2", L"..\\Resources\\object\\giantring2.bmp");

		mAni->CreateAnimation(L"giantring", GR, Vector2::Zero, 4, 1, 4, Vector2::Zero, 0.1);
		mAni->CreateAnimation(L"giantring2", GR2, Vector2::Zero, 7, 1, 7, Vector2::Zero, 0.01);
		sRing = Resources::Load<Sound>(L"s_giantring", L"..\\Resources\\sound\\sonic_getgiantring.wav");
		mAni->Play(L"giantring", true);

		tr->SetScale(Vector2(2.5f, 2.5f));
		
		mCol->SetSize(Vector2(160.0f, 160.0f));

		GameObject::Initialize();
	}
	void Giantring::Update()
	{
		GameObject::Update();
	}
	void Giantring::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void Giantring::Release()
	{
		GameObject::Release();
	}
	void Giantring::OnCollisionEnter(Collider* other)
	{
		sRing->Play(false);
		mAni->Play(L"giantring2", false);
		if (mAni->IsComplete())
		{
			object::Destroy(this);
		}

	}
	void Giantring::OnCollisionStay(Collider* other)
	{
		if (mAni->IsComplete())
		{
			object::Destroy(this);
		}
	}
	void Giantring::OnCollisionExit(Collider* other)
	{
		if (mAni->IsComplete())
		{
			object::Destroy(this);
		}
	}
}