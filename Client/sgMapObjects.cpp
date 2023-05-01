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
		mapObjectImage[4] = Resources::Load<Image>(L"mapobject5", L"..\\Resources\\map\\MapObjects(back)5.bmp");

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
		GameObject::Render(hdc);

		Vector2 cpos = Camera::CalculatePos(Vector2::Zero);

		for (int i = 0; i < 4; i++)
		{
			Vector2 pos = Vector2((i * 4735), 0) + cpos;

			TransparentBlt(hdc, static_cast<int>(pos.x), static_cast<int>(pos.y),
				mapObjectImage[i]->GetWidth(), mapObjectImage[i]->GetHeight(),
				mapObjectImage[i]->GetHdc(), 0, 0,
				mapObjectImage[i]->GetWidth(), mapObjectImage[i]->GetHeight(), RGB(255, 0, 255));
		}

		Vector2 pos = Vector2(18850, 0) + cpos;
		TransparentBlt(hdc, static_cast<int>(pos.x), static_cast<int>(pos.y),
			mapObjectImage[4]->GetWidth(), mapObjectImage[4]->GetHeight(),
			mapObjectImage[4]->GetHdc(), 0, 0,
			mapObjectImage[4]->GetWidth(), mapObjectImage[4]->GetHeight(), RGB(255, 0, 255));
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