#include "sgWater.h"
#include "sgSonic.h"
#include "sgWatersplash.h"

#include "sgImage.h"
#include "sgResources.h"
#include "sgCamera.h"

#include "sgTransform.h"
#include "sgAnimator.h"
#include "sgCollider.h"
#include "sgRigidbody.h"

namespace sg
{

	Water::Water()
		: mScale(Vector2(1600, 500))
	{
		SetName(L"Water");
	}
	Water::Water(Vector2 scale, Vector2 pos)
		: mScale(scale)
		, mWaterPos(pos)
	{
		SetName(L"Water");
	}
	Water::~Water()
	{
	}
	void Water::Initialize()
	{
		mWater = Image::Create(L"Water", mScale.x, mScale.y, RGB(0, 45, 141));
		mTr = GetComponent<Transform>();
		mCol = AddComponent<Collider>();
		mAni = AddComponent<Animator>();
		mCol->SetSize(mScale);
		mCol->SetCenter(mWaterPos);

		GameObject::Initialize();
	}
	void Water::Update()
	{
		GameObject::Update();
		mWater = Image::Create(L"Water", mScale.x, mScale.y, RGB(0, 45, 141));

	}
	void Water::Render(HDC hdc)
	{
		GameObject::Render(hdc);

		BLENDFUNCTION func = {};
		func.BlendOp = AC_SRC_OVER;
		func.BlendFlags = 0;
		func.AlphaFormat = 0;
		func.SourceConstantAlpha = 120;

		Vector2 pos = Camera::CalculatePos(Vector2::Zero);

		AlphaBlend(hdc, static_cast<int>(pos.x) + mWaterPos.x, static_cast<int>(pos.y) + mWaterPos.y,
			mWater->GetWidth(), mWater->GetHeight(),
			mWater->GetHdc(), 0, 0,
			mWater->GetWidth(), mWater->GetHeight(),func);
	}
	void Water::Release()
	{
		GameObject::Release();
	}
	void Water::OnCollisionEnter(Collider* other)
	{
		Sonic* sonic = dynamic_cast<Sonic*>(other->GetOwner());

		if (other->GetOwner() == sonic) {
			sonic->GetComponent<Rigidbody>()->SetMass(0.5);
			sonic->mFlame = false;
			sonic->mThunder = false;
			object::Instantiate<Watersplash>(Vector2(sonic->GetComponent<Collider>()->GetPos()), eLayerType::ForeObject, SceneManager::GetActiveScene2());
		}
	}
	void Water::OnCollisionStay(Collider* other)
	{
		//Sonic* sonic = dynamic_cast<Sonic*>(other->GetOwner());
		//sonic->GetComponent<Rigidbody>()->SetMass(0.5);
		//sonic->mFlame = false;
		//sonic->mThunder = false;
	}
	void Water::OnCollisionExit(Collider* other)
	{
		Sonic* sonic = dynamic_cast<Sonic*>(other->GetOwner());

		if (other->GetOwner() == sonic) {
			sonic->GetComponent<Rigidbody>()->SetMass(0.3);
			object::Instantiate<Watersplash>(Vector2(sonic->GetComponent<Collider>()->GetPos()), eLayerType::ForeObject, SceneManager::GetActiveScene2());
		}
	}
}