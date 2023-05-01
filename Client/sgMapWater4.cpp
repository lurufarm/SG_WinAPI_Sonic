#include "sgMapWater4.h"

#include "sgTime.h"
#include "sgInput.h"
#include "sgSceneManager.h"
#include "sgResources.h"
#include "sgTransform.h"
#include "sgAnimator.h"

namespace sg
{
	MapWater4::MapWater4()
	{
	}
	MapWater4::~MapWater4()
	{
	}
	void MapWater4::Initialize()
	{
		mAnimator = AddComponent<Animator>();
		Image* backgroundwater4 = Resources::Load<Image>(L"backgroundwater4", L"..\\Resources\\map\\MapObjects(back_water4).bmp");
		mAnimator->CreateAnimation(L"backgroundwater4_ani", backgroundwater4, Vector2::Zero, 4, 1, 4, Vector2::Zero, 0.15);
		Transform* tr = GetComponent<Transform>();
		tr->SetScale(Vector2(2.5f, 2.5f));
		mAnimator->Play(L"backgroundwater4_ani", true);

		GameObject::Initialize();
	}
	void MapWater4::Update()
	{
		GameObject::Update();
	}
	void MapWater4::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void MapWater4::Release()
	{
		GameObject::Release();
	}
}