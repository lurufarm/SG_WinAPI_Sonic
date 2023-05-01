#include "sgZone1.h"
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
	Zone1::Zone1()
		:mTime(0.0f)
	{
		this->SetName(L"Zone1");
	}
	Zone1::~Zone1()
	{
	}
	void Zone1::Initialize()
	{
		mzone = Resources::Load<Image>(L"zone", L"..\\Resources\\fade\\zone.bmp");
		mAnimator = AddComponent<Animator>();
		mAnimator->CreateAnimation(L"zone_", mzone, Vector2::Zero, 1, 1, 1, Vector2::Zero, 5);
		mAnimator->Play(L"zone_", false);
		Transform* rctr = GetComponent<Transform>();
		Vector2 rctr_pos = rctr->GetPos();
		rctr->SetScale(Vector2(0.4f, 0.4f));
		if (SceneManager::GetActiveScene2() == eSceneType::Play)
		{
			rctr->SetPos(Vector2(1410, 2430));
		}
		else
		{
			rctr->SetPos(Vector2(1200, 1830));
		}


		mfadestate = efade::start;

		GameObject::Initialize();
	}
	void Zone1::Update()
	{
		switch (mfadestate)
		{
		case sg::Zone1::efade::start:
			Start();
			break;
		case sg::Zone1::efade::stay:
			Stay();
			break;
		case sg::Zone1::efade::exit:
			Exit();
			break;
		}
		GameObject::Update();
	}
	void Zone1::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void Zone1::Release()
	{
		GameObject::Release();

	}
	void Zone1::Start()
	{
		Transform* rctr = GetComponent<Transform>();
		Vector2 rctr_pos = rctr->GetPos();

		if (SceneManager::GetActiveScene2() == eSceneType::Play)
		{
			if (rctr_pos.x > 710)
			{
				rctr_pos.x -= 1200.0f * Time::DeltaTime();
				rctr->SetPos(rctr_pos);
			}

			if (rctr_pos.x <= 710)
			{
				mfadestate = efade::stay;
				rctr_pos.x = 710;
				rctr->SetPos(rctr_pos);
			}
		}
		else
		{
			if (rctr_pos.x > 500)
			{
				rctr_pos.x -= 1200.0f * Time::DeltaTime();
				rctr->SetPos(rctr_pos);
			}

			if (rctr_pos.x <= 500)
			{
				mfadestate = efade::stay;
				rctr_pos.x = 500;
				rctr->SetPos(rctr_pos);
			}
		}

	}
	void Zone1::Stay()
	{
		Transform* rctr = GetComponent<Transform>();
		Vector2 rctr_pos = rctr->GetPos();
		mTime += Time::DeltaTime();
		if (mTime >= 0.4f)
		{
			mfadestate = efade::exit;
		}
	}
	void Zone1::Exit()
	{
		mTime = 0.0f;
		Transform* rctr = GetComponent<Transform>();
		Vector2 rctr_pos = rctr->GetPos();
		rctr_pos.x += 1200.0f * Time::DeltaTime();
		rctr->SetPos(rctr_pos);
		if (rctr_pos.x > 2410)
		{
			object::Destroy(this);
		}
	}
}