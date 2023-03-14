#include "sgAct1.h"
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
	Act1::Act1()
		:mTime(0.0f)
	{
	}
	Act1::~Act1()
	{
	}
	void Act1::Initialize()
	{
		mact = Resources::Load<Image>(L"act", L"..\\Resources\\fade\\act.bmp");
		mAnimator = AddComponent<Animator>();
		mAnimator->CreateAnimation(L"act_", mact, Vector2::Zero, 1, 1, 1, Vector2::Zero, 5);
		mAnimator->Play(L"act_", false);
		Transform* rctr = GetComponent<Transform>();
		Vector2 rctr_pos = rctr->GetPos();
		rctr_pos.x = 2800;
		rctr_pos.y = 3450;
		rctr->SetScale(Vector2(0.4f, 0.4f));
		rctr->SetPos(rctr_pos);


		//mfadestate = efade::start;

		GameObject::Initialize();
	}
	void Act1::Update()
	{
		switch (mfadestate)
		{
		case sg::Act1::efade::start:
			Start();
			break;
		case sg::Act1::efade::stay:
			Stay();
			break;
		case sg::Act1::efade::exit:
			Exit();
			break;
		}
		GameObject::Update();
	}
	void Act1::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void Act1::Release()
	{
		GameObject::Release();

	}
	void Act1::Start()
	{
		Transform* rctr = GetComponent<Transform>();
		Vector2 rctr_pos = rctr->GetPos();

		if (rctr_pos.x > 2100)
		{
			rctr_pos.x -= 1500.0f * Time::DeltaTime();
			rctr->SetPos(rctr_pos);
		}

		if (rctr_pos.x <= 2100)
		{
			mfadestate = efade::stay;
			rctr_pos.x = 2100;
			rctr->SetPos(rctr_pos);
		}

	}
	void Act1::Stay()
	{
		Transform* rctr = GetComponent<Transform>();
		Vector2 rctr_pos = rctr->GetPos();
		mTime += Time::DeltaTime();
		if (mTime >= 0.8f)
		{
			mfadestate = efade::exit;
		}
	}
	void Act1::Exit()
	{
		mTime = 0.0f;
		Transform* rctr = GetComponent<Transform>();
		Vector2 rctr_pos = rctr->GetPos();
		rctr_pos.x += 1200.0f * Time::DeltaTime();
		rctr->SetPos(rctr_pos);
		if (rctr_pos.x > 3500)
		{
			object::Destroy(this);
		}
	}
}