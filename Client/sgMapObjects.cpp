#include "sgMapObjects.h"
#include "sgTime.h"
#include "sgInput.h"
#include "sgSceneManager.h"
#include "sgResources.h"
#include "sgTransform.h"
#include "sgCamera.h"

namespace sg
{
	MapObjects::MapObjects()
	{
	}
	MapObjects::~MapObjects()
	{
	}
	void MapObjects::Initialize()
	{
		mapObjectImage[0] = Resources::Load<Image>(L"mapobject1", L"..\\Resources\\map\\MapObjects(back)1.bmp");
		mapObjectImage[1] = Resources::Load<Image>(L"mapobject2", L"..\\Resources\\map\\MapObjects(back)2.bmp");
		mapObjectImage[2] = Resources::Load<Image>(L"mapobject3", L"..\\Resources\\map\\MapObjects(back)3.bmp");
		mapObjectImage[3] = Resources::Load<Image>(L"mapobject4", L"..\\Resources\\map\\MapObjects(back)4.bmp");

		GameObject::Initialize();
		
	}
	void MapObjects::Update()
	{
		GameObject::Update();
	}
	void MapObjects::Render(HDC hdc)
	{
		GameObject::Render(hdc);


		Vector2 pos;
		
		for (size_t i = 0; i < 4; i++)
		{

		pos.x = mapObjectImage[i]->GetWidth();
		pos.y = mapObjectImage[i]->GetHeight();

		Vector2 cPos = Camera::CalculatePos(pos); // 카메라 위치 계산

		int x = static_cast<int>(cPos.x - mapObjectImage[i]->GetWidth() / 2.0f); // 카메라 위치에서 이미지 너비의 반을 빼서 X 좌표 계산
		int y = static_cast<int>(cPos.y - mapObjectImage[i]->GetHeight() / 2.0f); // 카메라 위치에서 이미지 높이의 반을 빼서 Y 좌표 계산

		//TransparentBlt(hdc, x-8380, y-1370, pos.x, pos.y,
		//	mapObjectImage->GetHdc(), 0, 0, mapObjectImage->GetWidth(), mapObjectImage->GetHeight(), RGB(255, 0, 255));
		TransparentBlt(hdc, x - 1278 + (i * 4735), y - 1370, pos.x, pos.y,
			mapObjectImage[i]->GetHdc(), 0, 0, pos.x, pos.y, RGB(255, 0, 255));
		}

	}
	void MapObjects::Release()
	{	
		GameObject::Release();
	}
}