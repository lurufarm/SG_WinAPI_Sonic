#include "sgMapObjects.h"
#include "sgTime.h"
#include "sgInput.h"
#include "sgSceneManager.h"
#include "sgResources.h"
#include "sgTransform.h"
#include "sgCamera.h"
#include "sgCollider.h"
#include "sgRigidbody.h"
#include "sgSonic.h"

#include "sgApplication.h"
extern sg::Application application;

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

		//mCollider = AddComponent<Collider>();
		//mCollider->SetSize(Vector2(16000, 1000));
		//mCollider->SetCenter(Vector2(1000, 3520));

		GameObject::Initialize();
		
	}
	void MapObjects::Update()
	{
		Transform* tr = GetComponent<Transform>();
		tr->SetPos(Camera::GetCameraPos());
		GameObject::Update();
	}
	void MapObjects::Render(HDC hdc)
	{
		//GameObject::Render(hdc);

		//Vector2 pos, cpos;

		//pos = GetComponent<Transform>()->GetPos();
		//cpos = Camera::CalculatePos(pos);
		//gpos = Camera::GetCameraPos();

		//if (gpos.x < 4735)
		//{
		//	int x = static_cast<int>(cpos.x - mapObjectImage[0]->GetWidth() / 2.0f); // 카메라 위치에서 이미지 너비의 반을 빼서 X 좌표 계산
		//	int y = static_cast<int>(cpos.y - mapObjectImage[0]->GetHeight() / 2.0f); // 카메라 위치에서 이미지 높이의 반을 빼서 Y 좌표 계산
		//	TransparentBlt(hdc, x - 1278, y - 1370, pos.x, pos.y,
		//		mapObjectImage[0]->GetHdc(), 0, 0, pos.x, pos.y, RGB(255, 0, 255));
		//}

		//for (size_t i = 0; i < 4; i++)
		//{


		//	//cpos.x -= application.GetWidth() / 2;
		//	//cpos.y -= application.GetHeight() / 2;
		//	//pos.x -= application.GetWidth() / 2;
		//	//pos.y -= application.GetHeight() / 2;

		//	int x = static_cast<int>(cpos.x - mapObjectImage[i]->GetWidth() / 2.0f); // 카메라 위치에서 이미지 너비의 반을 빼서 X 좌표 계산
		//	int y = static_cast<int>(cpos.y - mapObjectImage[i]->GetHeight() / 2.0f); // 카메라 위치에서 이미지 높이의 반을 빼서 Y 좌표 계산

		//	TransparentBlt(hdc, x - 1278 + (i * 4735), y - 1370, pos.x, pos.y,
		//		mapObjectImage[i]->GetHdc(), 0, 0, pos.x, pos.y, RGB(255, 0, 255));
		//}
					//TransparentBlt(hdc, cpos.x, cpos.y, application.GetWidth(), application.GetHeight(),
			//	mapObjectImage[i]->GetHdc(), pos.x - 1278, pos.y - 1370, application.GetWidth(), application.GetHeight(), RGB(255, 0, 255));
	
		GameObject::Render(hdc);

		Vector2 cpos = Camera::CalculatePos(Vector2::Zero);

		for (int i = 0; i < 4; i++)
		{
			Vector2 pos = Vector2((i * 4735), 0) + cpos;

			TransparentBlt(hdc, static_cast<int>(pos.x)+1090, static_cast<int>(pos.y)+770,
				mapObjectImage[i]->GetWidth(), mapObjectImage[i]->GetHeight(),
				mapObjectImage[i]->GetHdc(), 0, 0,
				mapObjectImage[i]->GetWidth(), mapObjectImage[i]->GetHeight(), RGB(255, 0, 255));
		}

	
	}

	void MapObjects::Release()
	{	
		GameObject::Release();
	}
	void MapObjects::OnCollisionEnter(Collider* other)
	{
	}
	void MapObjects::OnCollisionStay(Collider* other)
	{
	}
	void MapObjects::OnCollisionExit(Collider* other)
	{
	}
}