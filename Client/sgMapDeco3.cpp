#include "sgMapDeco3.h"

#include "sgTime.h"
#include "sgInput.h"
#include "sgSceneManager.h"
#include "sgResources.h"
#include "sgTransform.h"
#include "sgAnimator.h"

namespace sg
{
	MapDeco3::MapDeco3()
	{
	}
	MapDeco3::~MapDeco3()
	{
	}
	void MapDeco3::Initialize()
	{
		Animator* animator = AddComponent<Animator>();
		Image* mapdeco3 = Resources::Load<Image>(L"mapdeco3", L"..\\Resources\\map\\mapdeco.bmp");
		animator->CreateAnimation(L"mapdeco3_ani", mapdeco3, Vector2(0, 96), 14, 4, 7, Vector2::Zero, 0.08);
		Transform* tr = GetComponent<Transform>();
		tr->SetScale(Vector2(2.5f, 2.5f));
		animator->Play(L"mapdeco3_ani", true);

		GameObject::Initialize();
	}
	void MapDeco3::Update()
	{
		GameObject::Update();
	}
	void MapDeco3::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void MapDeco3::Release()
	{
		GameObject::Release();
	}
}