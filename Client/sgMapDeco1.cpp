#include "sgMapDeco1.h"

#include "sgTime.h"
#include "sgInput.h"
#include "sgSceneManager.h"
#include "sgResources.h"
#include "sgTransform.h"
#include "sgAnimator.h"

namespace sg
{
	MapDeco1::MapDeco1()
	{
	}
	MapDeco1::~MapDeco1()
	{
	}
	void MapDeco1::Initialize()
	{
		Animator* animator = AddComponent<Animator>();
		Image* mapdeco1 = Resources::Load<Image>(L"mapdeco1", L"..\\Resources\\map\\mapdeco.bmp");
		animator->CreateAnimation(L"mapdeco1_ani", mapdeco1, Vector2::Zero, 14, 4, 14, Vector2::Zero, 0.15);
		Transform* tr = GetComponent<Transform>();
		tr->SetScale(Vector2(2.5f, 2.5f));
		animator->Play(L"mapdeco1_ani", true);

		GameObject::Initialize();
	}
	void MapDeco1::Update()
	{
		GameObject::Update();
	}
	void MapDeco1::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void MapDeco1::Release()
	{
		GameObject::Release();
	}
}