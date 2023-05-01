#include "sgMapWater3.h"

#include "sgTime.h"
#include "sgInput.h"
#include "sgSceneManager.h"
#include "sgResources.h"
#include "sgTransform.h"
#include "sgAnimator.h"

namespace sg
{
	MapWater3::MapWater3()
	{
	}
	MapWater3::~MapWater3()
	{
	}
	void MapWater3::Initialize()
	{
		mAnimator = AddComponent<Animator>();
		Image* backgroundwater3 = Resources::Load<Image>(L"backgroundwater3", L"..\\Resources\\map\\MapObjects(back_water3).bmp");
		mAnimator->CreateAnimation(L"backgroundwater3_ani", backgroundwater3, Vector2::Zero, 3, 1, 3, Vector2::Zero, 0.15);
		mAnimator->Play(L"backgroundwater3_ani", true);

		GameObject::Initialize();
	}
	void MapWater3::Update()
	{
		GameObject::Update();
	}
	void MapWater3::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void MapWater3::Release()
	{
		GameObject::Release();
	}
}