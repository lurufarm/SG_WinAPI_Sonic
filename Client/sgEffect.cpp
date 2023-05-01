#include "sgEffect.h"
#include "sgSonic.h"
#include "sgRhinobot.h"
#include "sgBloominator.h"
#include "sgBloomBullet.h"
#include "sgWater.h"

#include "sgImage.h"
#include "sgResources.h"
#include "sgObject.h"
#include "sgInput.h"

#include "sgAnimator.h"
#include "sgTransform.h"
#include "sgCollider.h"
#include "sgCollisionManager.h"
#include "sgRigidbody.h"

namespace sg
{
	Effect::eEffectState Effect::mEffectState = Effect::eEffectState::None;
	//Animator* Effect::mAni = nullptr;
	
	Effect::Effect()
		: mTarget(nullptr)
	{
		SetName(L"Effect");
	}
	Effect::~Effect()
	{
	}


	void Effect::Initialize()
	{
		mAni = AddComponent<Animator>();
		mTr = GetComponent<Transform>();
		mCol = AddComponent<Collider>();

		Image* effect = Resources::Load<Image>(L"effect", L"..\\Resources\\object\\effect.bmp");
		Image* effect_space = Resources::Load<Image>(L"effect_spa", L"..\\Resources\\object\\effect2.bmp");

		mAni->CreateAnimation(L"water_idle", effect, Vector2::Zero, 18, 4, 18, Vector2::Zero, 0.05);
		mAni->CreateAnimation(L"thunder_idle", effect, Vector2(0.0f, 48.0f), 18, 4, 12, Vector2::Zero, 0.05);
		mAni->CreateAnimation(L"fire1_idle", effect, Vector2(0.0f, 96.0f), 18, 4, 18, Vector2::Zero, 0.05);
		mAni->CreateAnimation(L"nothing", effect, Vector2(576.0f, 48.0f), 18, 4, 1, Vector2::Zero, 1);
		mAni->CreateAnimation(L"water_spa", effect_space, Vector2::Zero, 6, 3, 6, Vector2::Zero, 0.05);
		mAni->CreateAnimation(L"fire1_spa_right", effect_space, Vector2(0.0f, 48.0f), 6, 3, 6, Vector2::Zero, 0.01);
		mAni->CreateAnimation(L"fire1_spa_left", effect_space, Vector2(0.0f, 96.0f), 6, 3, 6, Vector2::Zero, 0.05);
		mTr->SetScale(Vector2(2.5f, 2.5f));

		mEffectState = eEffectState::None;

		//mCol->SetCenter(mTr->GetPos());

		GameObject::Initialize();
	}
	void Effect::Update()
	{
		GameObject::Update();
		mCol->SetSize(Vector2(120.0f, 120.0f));
		mTr->SetPos(Vector2(mTarget->GetComponent<Transform>()->GetPos().x, mTarget->GetComponent<Transform>()->GetPos().y + 15));

		Vector2 test = mTr->GetPos();


		switch (mEffectState)
		{
		case sg::Effect::eEffectState::None:
			None();
			break;
		case sg::Effect::eEffectState::Flame:
			Flame();
			break;
		case sg::Effect::eEffectState::Fire_dash:
			Fire_dash();
			break;
		case sg::Effect::eEffectState::Thunder:
			Thunder();
			break;
		case sg::Effect::eEffectState::Water:
			Water();
			break;
		case sg::Effect::eEffectState::WaterJump:
			WaterJump();
			break;
		}



	}
	void Effect::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void Effect::Release()
	{
		GameObject::Release();
	}
	void Effect::OnCollisionEnter(Collider* other)
	{
		Rhinobot* rhino = dynamic_cast<Rhinobot*>(other->GetOwner());
		Bloominator* bloom = dynamic_cast<Bloominator*>(other->GetOwner());
		BloomBullet* bullet = dynamic_cast<BloomBullet*>(other->GetOwner());
		class Water* water = dynamic_cast<class Water*>(other->GetOwner());

		if (other->GetOwner() == nullptr)
			return;

		if (other->GetOwner() == bullet)
		{
			Vector2 bulletvel = bullet->GetComponent<Rigidbody>()->GetVelocity();
			Vector2 normal = mCol->GetNormal(other);
			Vector2 normal2 = -normal;
			Vector2 reflectvel = ((-bulletvel) + normal * 2 * math::Dot(bulletvel, normal2));
			bullet->GetComponent<Rigidbody>()->SetVelocity(reflectvel);
		}
		else if (other->GetOwner() == bloom
			|| other->GetOwner() == rhino)
		{
			mEffectState = eEffectState::None;
		}

		if (other->GetOwner() == water
			&& (mEffectState == eEffectState::Flame
			|| mEffectState == eEffectState::Thunder))
		{
			mEffectState = eEffectState::None;
		}

	}
	void Effect::OnCollisionStay(Collider* other)
	{

	}
	void Effect::OnCollisionExit(Collider* other)
	{
	}
	void Effect::None()
	{
		mAni->Play(L"nothing", false);
	}
	void Effect::Flame()
	{
		mAni->Play(L"fire1_idle", true);
		if (mTarget->GetSonicState() == Sonic::eSonicState::jump2_left || mTarget->GetSonicState() == Sonic::eSonicState::jump2_right)
		{
			mEffectState = eEffectState::Fire_dash;
		}
	}
	void Effect::Thunder()
	{
		mAni->Play(L"thunder_idle", true);
	}
	void Effect::Water()
	{
		mAni->Play(L"water_idle", true);

		if (mTarget->GetSonicState() == Sonic::eSonicState::waterjump) {
			if (Input::GetKeyDown(eKeyCode::Space))
			{
				mEffectState = eEffectState::WaterJump;
			}
		}

	}
	void Effect::Fire_dash()
	{
		if (mTarget->GetSonicState() == Sonic::eSonicState::jump2_left)
		{
			mAni->Play(L"fire1_spa_left", false);
			if (mAni->IsComplete())
			{
				mTarget->SetSonicState(Sonic::eSonicState::jump_left);
				mAni->Reset();
				mEffectState = eEffectState::Flame;
			}
		}
		else if (mTarget->GetSonicState() == Sonic::eSonicState::jump2_right)
		{
			mAni->Play(L"fire1_spa_right", false);
			if (mAni->IsComplete())
			{
				mTarget->SetSonicState(Sonic::eSonicState::jump_right);
				mAni->Reset();
				mEffectState = eEffectState::Flame;
			}
		}
		
	}
	void Effect::WaterJump()
	{
		mTr->SetPos(Vector2(mTarget->GetComponent<Transform>()->GetPos().x - 30, mTarget->GetComponent<Transform>()->GetPos().y + 15));
		mAni->Play(L"water_spa", false);
		if (mAni->IsComplete())
		{
			mAni->Reset();
			mEffectState = eEffectState::Water;
		}
	}
}