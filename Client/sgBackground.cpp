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

		Vector2 pos;
		pos.x = backgroundImage->GetWidth();
		pos.y = backgroundImage->GetHeight();

		Vector2 cPos = Camera::CalculatePos(pos); // 카메라 위치 계산

		int x = static_cast<int>(cPos.x - backgroundImage->GetWidth() / 2.0f); // 카메라 위치에서 이미지 너비의 반을 빼서 X 좌표 계산
		int y = static_cast<int>(cPos.y - backgroundImage->GetHeight() / 2.0f); // 카메라 위치에서 이미지 높이의 반을 빼서 Y 좌표 계산

		for (size_t i = 0; i < 17500; i+=3500)
		{
		TransparentBlt(hdc, x+i, y-949, backgroundImage->GetWidth(), backgroundImage->GetHeight(),
			backgroundImage->GetHdc(), 0, 0, backgroundImage->GetWidth(), backgroundImage->GetHeight(), RGB(255, 0, 255));
		}
		//Image* background_middle2 = Resources::Load<Image>(L"background", L"..\\Resources\\map\\Background_middle2.bmp");

		//TransparentBlt(hdc, x , 2800, background_middle2->GetWidth(), background_middle2->GetHeight(),
		//	background_middle2->GetHdc(), 0, 0, background_middle2->GetWidth(), background_middle2->GetHeight(), RGB(255, 0, 255));

	}
	void Background::Release()
	{
		GameObject::Release();
	}
}