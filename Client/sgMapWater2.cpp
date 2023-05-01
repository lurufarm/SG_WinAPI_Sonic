#include "sgMapWater2.h"

#include "sgTime.h"
#include "sgInput.h"
#include "sgSceneManager.h"
#include "sgResources.h"
#include "sgTransform.h"
#include "sgAnimator.h"

namespace sg
{
	MapWater2::MapWater2()
	{
	}
	MapWater2::~MapWater2()
	{
	}
	void MapWater2::Initialize()
	{
		mAnimator = AddComponent<Animator>();
		Image* backgroundwater1 = Resources::Load<Image>(L"backgroundwater2", L"..\\Resources\\map\\MapObjects(back_water2).bmp");
		mAnimator->CreateAnimation(L"backgroundwater2_ani", backgroundwater1, Vector2::Zero, 3, 1, 3, Vector2::Zero, 0.15);
		mAnimator->Play(L"backgroundwater2_ani", true);

		GameObject::Initialize();
	}
	void MapWater2::Update()
	{
		GameObject::Update();
	}
	void MapWater2::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void MapWater2::Release()
	{
		GameObject::Release();
	}
}