#include "sgBackground_sea.h"

#include "sgTime.h"
#include "sgInput.h"
#include "sgSceneManager.h"
#include "sgResources.h"
#include "sgTransform.h"
#include "sgAnimator.h"

namespace sg
{
	Backgroundsea::Backgroundsea()
	{
		this->SetName(L"Background_sea");
	}
	Backgroundsea::~Backgroundsea()
	{
	}
	void Backgroundsea::Initialize()

	{
		Animator* animator = AddComponent<Animator>();
		Image* backgroundseaImage = Resources::Load<Image>(L"background_sea_image", L"..\\Resources\\map\\Background_sea.bmp");
		animator->CreateAnimation(L"background_sea", backgroundseaImage, Vector2::Zero, 8, 1, 8, Vector2::Zero, 0.15);
		Transform* tr = GetComponent<Transform>();
		tr->SetScale(Vector2(2.5f, 2.5f));
		animator->Play(L"background_sea", true);

		GameObject::Initialize();
	}
	void Backgroundsea::Update()
	{
		GameObject::Update();
	}
	void Backgroundsea::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void Backgroundsea::Release()
	{
		GameObject::Release();
	}
}