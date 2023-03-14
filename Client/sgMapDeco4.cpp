#include "sgMapDeco4.h"

#include "sgTime.h"
#include "sgInput.h"
#include "sgSceneManager.h"
#include "sgResources.h"
#include "sgTransform.h"
#include "sgAnimator.h"

namespace sg
{
	MapDeco4::MapDeco4()
	{
	}
	MapDeco4::~MapDeco4()
	{
	}
	void MapDeco4::Initialize()
	{
		Animator* animator = AddComponent<Animator>();
		Image* mapdeco4 = Resources::Load<Image>(L"mapdeco4", L"..\\Resources\\map\\mapdeco.bmp");
		animator->CreateAnimation(L"mapdeco4_ani", mapdeco4, Vector2(0, 144), 14, 4, 7, Vector2::Zero, 0.08);
		Transform* tr = GetComponent<Transform>();
		tr->SetScale(Vector2(2.5f, 2.5f));
		animator->Play(L"mapdeco4_ani", true);

		GameObject::Initialize();
	}
	void MapDeco4::Update()
	{
		GameObject::Update();
	}
	void MapDeco4::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void MapDeco4::Release()
	{
		GameObject::Release();
	}
}