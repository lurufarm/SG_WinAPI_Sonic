#include "sgBreakingterrain.h"
#include "sgSonic.h"

#include "sgImage.h"
#include "sgResources.h"
#include "sgTime.h"
#include "sgSound.h"

#include "sgTransform.h"
#include "sgAnimator.h"
#include "sgCollider.h"



namespace sg
{
	Breakingterrain::Breakingterrain()
		: mTime(0.0f)
		, mDir(false)
		, mOn(false)
	{
		SetName(L"Breakingterrain");
	}
	Breakingterrain::~Breakingterrain()
	{
	}
	void Breakingterrain::Initialize()
	{
		mCol = AddComponent<Collider>();
		mAni = AddComponent<Animator>();

		// ¿À¸¥ÂÊ
		Image* Breakingterrain1 = Resources::Load<Image>(L"stable1", L"..\\Resources\\map\\stable_terrain.bmp");
		Image* Breakingterrain2 = Resources::Load<Image>(L"stable2", L"..\\Resources\\map2\\stable_terrain.bmp");
		Image* Breakingterrain3 = Resources::Load<Image>(L"Breakingterrain1", L"..\\Resources\\map\\breaking_terrain.bmp");
		Image* Breakingterrain4 = Resources::Load<Image>(L"Breakingterrain2", L"..\\Resources\\map2\\breaking_terrain.bmp");
		mAni->CreateAnimation(L"stable1", Breakingterrain1, Vector2::Zero, 1, 1, 1, Vector2::Zero, 0.1);
		mAni->CreateAnimation(L"stable2", Breakingterrain2, Vector2::Zero, 6, 1, 6, Vector2::Zero, 0.1);
		mAni->CreateAnimation(L"Breakingterrain1", Breakingterrain3, Vector2::Zero, 5, 1, 5, Vector2::Zero, 0.1);
		mAni->CreateAnimation(L"Breakingterrain2", Breakingterrain4, Vector2::Zero, 5, 1, 5, Vector2::Zero, 0.1);

		// ¿ÞÂÊ
		Image* Breakingterrain5 = Resources::Load<Image>(L"stable1_left", L"..\\Resources\\map\\stable_terrain2.bmp");
		Image* Breakingterrain6 = Resources::Load<Image>(L"stable2_left", L"..\\Resources\\map2\\stable_terrain2.bmp");
		Image* Breakingterrain7 = Resources::Load<Image>(L"Breakingterrain1_left", L"..\\Resources\\map\\breaking_terrain2.bmp");
		Image* Breakingterrain8 = Resources::Load<Image>(L"Breakingterrain2_left", L"..\\Resources\\map2\\breaking_terrain2.bmp");
		mAni->CreateAnimation(L"stable1_left", Breakingterrain5, Vector2::Zero, 1, 1, 1, Vector2::Zero, 0.1);
		mAni->CreateAnimation(L"stable2_left", Breakingterrain6, Vector2::Zero, 6, 1, 6, Vector2::Zero, 0.1);
		mAni->CreateAnimation(L"Breakingterrain1_left", Breakingterrain7, Vector2::Zero, 5, 1, 5, Vector2::Zero, 0.1);
		mAni->CreateAnimation(L"Breakingterrain2_left", Breakingterrain8, Vector2::Zero, 5, 1, 5, Vector2::Zero, 0.1);

		sBreaking = Resources::Load<Sound>(L"Breakingsound", L"..\\Resources\\sound\\object_crash.wav");
		
		Transform* tr = GetComponent<Transform>();
		tr->SetScale(Vector2(2.5f, 2.5f));

		mCol->SetSize(Vector2(240.0f, 20.0f));
		mCol->SetCenter(Vector2::Zero);

		GameObject::Initialize();
	}
	void Breakingterrain::Update()
	{
		GameObject::Update();

		if (SceneManager::GetActiveScene2() == eSceneType::Play && mDir == false)
		{
			mAni->Play(L"stable1", true);
			mPlay = true;
		}
		else if (SceneManager::GetActiveScene2() == eSceneType::Play && mDir)
		{
			mAni->Play(L"stable1_left", true);
			mPlay = true;
		}
		else if (SceneManager::GetActiveScene2() == eSceneType::Play2 && mDir == false)
		{
			mAni->Play(L"stable2", true);
			mPlay = false;
		}
		else if (SceneManager::GetActiveScene2() == eSceneType::Play2 && mDir)
		{
			mAni->Play(L"stable2_left", true);
			mPlay = false;
		}
		if (mOn)
		{
			mTime += Time::DeltaTime();
		}


		if (mTime >= 0.3)
		{
			if (mPlay && mDir == false)
			{
				mAni->Play(L"Breakingterrain1", false);
			}
			else if (mPlay == false && mDir == false)
			{
				mAni->Play(L"Breakingterrain2", false);
			}
			else if (mPlay && mDir)
			{
				mAni->Play(L"Breakingterrain1_left", false);
			}
			else if (mPlay == false && mDir)
			{
				mAni->Play(L"Breakingterrain2_left", false);
			}
			if (mAni->IsComplete())
			{
				sBreaking->Play(false);
				object::Destroy(this);
			}
		}

	}
	void Breakingterrain::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void Breakingterrain::Release()
	{
		GameObject::Release();
	}
	void Breakingterrain::OnCollisionEnter(Collider* other)
	{
		mUse = true;
		mOn = true;
	}
	void Breakingterrain::OnCollisionStay(Collider* other)
	{
	
	}
	void Breakingterrain::OnCollisionExit(Collider* other)

	{	
		mUse = false;

	}
}