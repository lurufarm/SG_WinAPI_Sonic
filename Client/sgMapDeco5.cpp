#include "sgMapDeco5.h"

#include "sgTime.h"
#include "sgInput.h"
#include "sgResources.h"

#include "sgTransform.h"
#include "sgAnimator.h"

namespace sg
{
	MapDeco5::MapDeco5()
		: mNumber(false)
	{
	}
	MapDeco5::~MapDeco5()
	{
	}
	void MapDeco5::Initialize()
	{
		mAni = AddComponent<Animator>();
		Image* mapdeco5 = Resources::Load<Image>(L"mapdeco5", L"..\\Resources\\map2\\mapdeco.bmp");
		mAni->CreateAnimation(L"mapdeco5_ani_1", mapdeco5, Vector2(0, 0), 12, 2, 12, Vector2::Zero, 0.08);
		mAni->CreateAnimation(L"mapdeco5_ani_2", mapdeco5, Vector2(0, 48), 12, 2, 10, Vector2::Zero, 0.08);
		Transform* tr = GetComponent<Transform>();
		tr->SetScale(Vector2(2.5f, 2.5f));

		GameObject::Initialize();
	}
	void MapDeco5::Update()
	{
		GameObject::Update();

		if (mNumber == false)
		{
			mAni->Play(L"mapdeco5_ani_1", true);
		}
		else
		{
			mAni->Play(L"mapdeco5_ani_2", true);
		}
	}
	void MapDeco5::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void MapDeco5::Release()
	{
		GameObject::Release();
	}
}