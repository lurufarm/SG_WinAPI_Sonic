#include "sgScenechange.h"

#include "sgTime.h"
#include "sgImage.h"
#include "sgResources.h"
#include "sgSceneManager.h"
#include "sgObject.h"
#include "sgSound.h"

#include "sgTransform.h"
#include "sgAnimator.h"

namespace sg
{
	Scenechange::Scenechange()
	{
	}
	Scenechange::~Scenechange()
	{
	}
	void Scenechange::Initialize()
	{
		mAni = AddComponent<Animator>();
		mTr = GetComponent<Transform>();
		mTr->SetScale(Vector2(2.8f, 2.8f));
		Image* scenechange = Resources::Load<Image>(L"scenechange", L"..\\Resources\\enemies\\scenechangefire.bmp");
		sSC = Resources::Load<Sound>(L"SC", L"..\\Resources\\sound\\explosion.wav");
		sSC->Play(false);
		mAni->CreateAnimation(L"scenechange", scenechange, Vector2::Zero, 2, 1, 2, Vector2::Zero, 0.3);
		mAni->Play(L"scenechange", true);
		if (SceneManager::GetActiveScene2() == eSceneType::Play)
		{
			mTr->SetPos(Vector2(17910, 2430));
		}
		else {
			mTr->SetPos(Vector2(-100.0f, 1000.0f));
		}
		GameObject::Initialize();
	}
	void Scenechange::Update()
	{
		GameObject::Update();

		Vector2 pos = mTr->GetPos();
		pos.y -= 500.0f * Time::DeltaTime();
		mTr->SetPos(pos);

		if (pos.y <= -2000.0f)
		{
			object::Destroy(this);
		}

	}
	void Scenechange::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void Scenechange::Release()
	{
		GameObject::Release();
	}
}