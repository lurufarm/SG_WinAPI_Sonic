#include "sgMapDeco2.h"

#include "sgTime.h"
#include "sgInput.h"
#include "sgSceneManager.h"
#include "sgResources.h"
#include "sgTransform.h"
#include "sgAnimator.h"

namespace sg
{
	MapDeco2::MapDeco2()
	{
	}
	MapDeco2::~MapDeco2()
	{
	}
	void MapDeco2::Initialize()
	{
		Animator* animator = AddComponent<Animator>();
		Image* mapdeco2 = Resources::Load<Image>(L"mapdeco2", L"..\\Resources\\map\\mapdeco.bmp");
		animator->CreateAnimation(L"mapdeco2_ani", mapdeco2, Vector2(0, 48), 14, 4, 10, Vector2::Zero, 0.08);
		Transform* tr = GetComponent<Transform>();
		tr->SetScale(Vector2(2.5f, 2.5f));
		animator->Play(L"mapdeco2_ani", true);

		GameObject::Initialize();
	}
	void MapDeco2::Update()
	{
		GameObject::Update();
	}
	void MapDeco2::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void MapDeco2::Release()
	{
		GameObject::Release();
	}
}