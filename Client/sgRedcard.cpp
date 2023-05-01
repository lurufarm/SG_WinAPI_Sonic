#include "sgRedcard.h"
#include "sgTransform.h"
#include "sgApplication.h"
#include "sgTime.h"
#include "sgInput.h"
#include "sgSceneManager.h"
#include "sgResources.h"
#include "sgCamera.h"
#include "sgObject.h"

namespace sg
{
	Redcard::Redcard()
		:mTime(0.0f)
	{
		this->SetName(L"Redcard");
	}
	Redcard::~Redcard()
	{
	}
	void Redcard::Initialize()
	{
		mredcard = Resources::Load<Image>(L"redcard", L"..\\Resources\\fade\\redcard.bmp");
		//mzone = Resources::Load<Image>(L"zone", L"..\\Resources\\fade\\zone.bmp");
		//mact = Resources::Load<Image>(L"act", L"..\\Resources\\fade\\act.bmp");
		mAnimator = AddComponent<Animator>();
		mAnimator->CreateAnimation(L"redcard_", mredcard, Vector2::Zero, 1, 1, 1, Vector2::Zero, 5);
		mAnimator->Play(L"redcard_", false);
		Transform* rctr = GetComponent<Transform>();
		rctr->SetScale(Vector2(0.5f, 0.5f));
		if (SceneManager::GetActiveScene2() == eSceneType::Play)
		{
			rctr->SetPos(Vector2(410, 1230));
		}
		else
		{
			rctr->SetPos(Vector2(200, 230));
		}


		mfadestate = efade::start;

		GameObject::Initialize();
	}
	void Redcard::Update()
	{
		switch (mfadestate)
		{
		case sg::Redcard::efade::start:
			Start();
			break;
		case sg::Redcard::efade::stay:
			Stay();
			break;
		case sg::Redcard::efade::exit:
			Exit();
			break;
		}
		GameObject::Update();
	}
	void Redcard::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void Redcard::Release()
	{
		GameObject::Release();

	}
	void Redcard::Start()
	{
			Transform* rctr = GetComponent<Transform>();
			Vector2 rctr_pos = rctr->GetPos();

		if (SceneManager::GetActiveScene2() == eSceneType::Play)
		{
			if (rctr_pos.y < 2030)
			{
				rctr_pos.y += 1600.0f * Time::DeltaTime();
				rctr->SetPos(rctr_pos);
			}

			if (rctr_pos.y >= 2030)
			{
				mfadestate = efade::stay;
				rctr_pos.y = 2030;
				rctr->SetPos(rctr_pos);
			}
		}
		else
		{
			if (rctr_pos.y < 1430)
			{
				rctr_pos.y += 1600.0f * Time::DeltaTime();
				rctr->SetPos(rctr_pos);
			}

			if (rctr_pos.y >= 1430)
			{
				mfadestate = efade::stay;
				rctr_pos.y = 1430;
				rctr->SetPos(rctr_pos);
			}
		}
	}
	void Redcard::Stay()
	{
		Transform* rctr = GetComponent<Transform>();
		Vector2 rctr_pos = rctr->GetPos();
		mTime += Time::DeltaTime();
		if (mTime >= 1.f)
		{
			mfadestate = efade::exit;
		}
	}
	void Redcard::Exit()
	{
		mTime = 0.0f;
		Transform* rctr = GetComponent<Transform>();
		Vector2 rctr_pos = rctr->GetPos();
			rctr_pos.y -= 1600.0f * Time::DeltaTime();
			rctr->SetPos(rctr_pos);
			if (rctr_pos.y < -770)
			{
				object::Destroy(this);
			}
	}
}