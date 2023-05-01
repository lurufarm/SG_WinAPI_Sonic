#include "sgForeground.h"

#include "sgImage.h"
#include "sgResources.h"
#include "sgCamera.h"

#include "sgTransform.h"

namespace sg
{
	Foreground::Foreground()
	{
	}
	Foreground::~Foreground()
	{
	}
	void Foreground::Initialize()
	{
		mTr = GetComponent<Transform>();
		fg = Resources::Load<Image>(L"fg", L"..\\Resources\\map\\foreground.bmp");

		GameObject::Initialize();
	}
	void Foreground::Update()
	{
		GameObject::Update();
	}
	void Foreground::Render(HDC hdc)
	{
		GameObject::Render(hdc);
		Vector2 pos = Camera::CalculatePos(Vector2::Zero);

		TransparentBlt(hdc, static_cast<int>(pos.x), static_cast<int>(pos.y),
			fg->GetWidth(), fg->GetHeight(),
			fg->GetHdc(), 0, 0,
			fg->GetWidth(), fg->GetHeight(), RGB(255, 0, 255));
	}
	void Foreground::Release()
	{
		GameObject::Release();
	}
}