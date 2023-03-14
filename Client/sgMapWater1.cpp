#include "sgMapWater1.h"

#include "sgTime.h"
#include "sgInput.h"
#include "sgSceneManager.h"
#include "sgResources.h"
#include "sgTransform.h"
#include "sgAnimator.h"

namespace sg
{
	MapWater1::MapWater1()
	{
	}
	MapWater1::~MapWater1()
	{
	}
	void MapWater1::Initialize()
	{
		mAnimator = AddComponent<Animator>();
		Image* backgroundwater1 = Resources::Load<Image>(L"backgroundwater1", L"..\\Resources\\map\\MapObjects(back_water1)1.bmp");
		mAnimator->CreateAnimation(L"backgroundwater1_ani", backgroundwater1, Vector2::Zero, 3, 1, 3, Vector2::Zero, 0.15);
		mAnimator->Play(L"backgroundwater1_ani", true);

		GameObject::Initialize();
	}
	void MapWater1::Update()
	{
		GameObject::Update();
	}
	void MapWater1::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void MapWater1::Release()
	{
		GameObject::Release();
	}
}