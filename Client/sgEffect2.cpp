#include "sgEffect2.h"
#include "sgEffect.h"
#include "sgSonic.h"

#include "sgImage.h"
#include "sgResources.h"
#include "sgObject.h"

#include "sgAnimator.h"
#include "sgTransform.h"

namespace sg
{
	bool Effect2::mFlame = false;

	Effect2::Effect2()
		: mEffect(nullptr)
		, mTarget(nullptr)
	{
	}
	Effect2::~Effect2()
	{
	}
	void Effect2::Initialize()
	{
		mAni = AddComponent<Animator>();
		mTr = GetComponent<Transform>();
		Image* effect = Resources::Load<Image>(L"effect", L"..\\Resources\\object\\effect.bmp");
		mAni->CreateAnimation(L"fire2_idle", effect, Vector2(0.0f, 144.0f), 18, 4, 18, Vector2::Zero, 0.05);
		mAni->CreateAnimation(L"nothing", effect, Vector2(576.0f, 48.0f), 18, 4, 1, Vector2::Zero, 1);
		mTr->SetScale(Vector2(2.5f, 2.5f));
		mTr->SetPos(Vector2::Zero);

		GameObject::Initialize();

	}
	void Effect2::Update()
	{
		GameObject::Update();
		mTr->SetPos(Vector2(mTarget->GetComponent<Transform>()->GetPos().x, mTarget->GetComponent<Transform>()->GetPos().y + 10));

		switch (mFlame)
		{
		case false:
			mAni->Play(L"nothing", false);
			break;
		case true:
			mAni->Play(L"fire2_idle", true);
			break;
		}

		if (mEffect == nullptr)
			return;
		else if (mEffect->GetEffectState() == Effect::eEffectState::Fire_dash)
		{
			mFlame = false;
		}
		else if (mEffect->GetEffectState() == Effect::eEffectState::Flame)
		{
			mFlame = true;
		}
		else if (mEffect->GetEffectState() == Effect::eEffectState::None)
		{
			mFlame = false;
		}


	}
	void Effect2::Render(HDC hdc)
	{
		GameObject::Render(hdc);

	}
	void Effect2::Release()
	{
		GameObject::Release();

	}
	void Effect2::OnCollisionEnter(Collider* other)
	{
	}
	void Effect2::OnCollisionStay(Collider* other)
	{
	}
	void Effect2::OnCollisionExit(Collider* other)
	{
	}
}