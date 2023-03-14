#include "sgTitletitle.h"
#include "sgSceneManager.h"
#include "sgResources.h"
#include "sgTransform.h"
#include "sgObject.h"


namespace sg
{
	Titletitle::Titletitle()
	{
	}
	Titletitle::~Titletitle()
	{
	}
	void Titletitle::Initialize()
	{
		GameObject::Initialize();
		mtitletitle = Resources::Load<Image>(L"titletitle", L"..\\Resources\\intro\\intro_title.bmp");

	}
	void Titletitle::Update()
	{
		GameObject::Update();
	}
	void Titletitle::Render(HDC hdc)
	{
		GameObject::Render(hdc);
		TransparentBlt(hdc, 100, 470, mtitletitle->GetWidth()*3.5, mtitletitle->GetHeight()*3.5,
			mtitletitle->GetHdc(), 0, 0, mtitletitle->GetWidth(), mtitletitle->GetHeight(), RGB(255, 0, 255));
	}
	void Titletitle::Release()
	{
		GameObject::Release();
	}
}