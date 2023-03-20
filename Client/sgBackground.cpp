#include "sgBackground.h"
#include "sgTime.h"
#include "sgInput.h"
#include "sgSceneManager.h"
#include "sgResources.h"
#include "sgTransform.h"
#include "sgCamera.h"

namespace sg
{
	Background::Background()
	{
	}
	Background::~Background()
	{
	}
	void Background::Initialize()
	{
		backgroundImage = Resources::Load<Image>(L"background", L"..\\Resources\\map\\Background1.bmp");		
		GameObject::Initialize();
	}
	void Background::Update()
	{
		GameObject::Update();
	}
	void Background::Render(HDC hdc)
	{
		GameObject::Render(hdc);

		//Vector2 pos;
		//pos.x = backgroundImage->GetWidth();
		//pos.y = backgroundImage->GetHeight();

		//Vector2 cPos = Camera::CalculatePos(pos); // ī�޶� ��ġ ���

		//int x = static_cast<int>(cPos.x - backgroundImage->GetWidth() / 2.0f); // ī�޶� ��ġ���� �̹��� �ʺ��� ���� ���� X ��ǥ ���
		//int y = static_cast<int>(cPos.y - backgroundImage->GetHeight() / 2.0f); // ī�޶� ��ġ���� �̹��� ������ ���� ���� Y ��ǥ ���

		//for (size_t i = 0; i < 17500; i+=3500)
		//{
		//TransparentBlt(hdc, x+i, y-949, backgroundImage->GetWidth(), backgroundImage->GetHeight(),
		//	backgroundImage->GetHdc(), 0, 0, backgroundImage->GetWidth(), backgroundImage->GetHeight(), RGB(255, 0, 255));
		//}


		Vector2 pos;
		pos.x = backgroundImage->GetWidth();
		pos.y = backgroundImage->GetHeight();

		Vector2 cPos = Camera::CalculatePos(pos); // ī�޶� ��ġ ���

		int x = static_cast<int>(cPos.x - backgroundImage->GetWidth() / 2.0f) % backgroundImage->GetWidth();
		int y = static_cast<int>(cPos.y - backgroundImage->GetHeight() / 2.0f);

		int x1 = x - backgroundImage->GetWidth();
		int x2 = x;

		TransparentBlt(hdc, x1, y - 949, backgroundImage->GetWidth(), backgroundImage->GetHeight(),
			backgroundImage->GetHdc(), 0, 0, backgroundImage->GetWidth(), backgroundImage->GetHeight(), RGB(255, 0, 255));

		TransparentBlt(hdc, x2, y - 949, backgroundImage->GetWidth(), backgroundImage->GetHeight(),
			backgroundImage->GetHdc(), 0, 0, backgroundImage->GetWidth(), backgroundImage->GetHeight(), RGB(255, 0, 255));

	}
	void Background::Release()
	{
		GameObject::Release();
	}
}