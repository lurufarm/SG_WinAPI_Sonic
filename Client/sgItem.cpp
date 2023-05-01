#include "sgItem.h"
#include "sgSonic.h"
#include "sgEffect.h"
#include "sgEffect2.h"

#include "sgImage.h"
#include "sgResources.h"
#include "sgObject.h"
#include "sgSound.h"

#include "sgAnimator.h"
#include "sgTransform.h"
#include "sgCollider.h"
#include "sgRigidbody.h"

namespace sg
{
	Item::Item()
		: mBroken(false)
	{
		SetName(L"Item");
	}
	Item::Item(int a)
	{
		SetName(L"Item");
		if (a == 0)
		{
			mItemState = eItemState::Ring;
		}
		else if (a == 1)
		{
			mItemState = eItemState::Flame;
		}
		else if (a == 2)
		{
			mItemState = eItemState::Thunder;
		}
		else if (a == 3)
		{
			mItemState = eItemState::Water;
		}
		else if (a == 4)
		{
			mItemState = eItemState::Life;
		}
		
	}
	Item::~Item()
	{
	}
	void Item::Initialize()
	{
		mBroken = false;
		if (mBroken == false)
		{
			mCol = AddComponent<Collider>();
		}
		mAni = AddComponent<Animator>();
		mTr = GetComponent<Transform>();
		Image* item = Resources::Load<Image>(L"item", L"..\\Resources\\object\\item.bmp");
		Image* boom = Resources::Load<Image>(L"boom_", L"..\\Resources\\animals\\boom.bmp");
		mAni->CreateAnimation(L"item_life", item, Vector2::Zero, 6, 1, 1, Vector2::Zero, 1);
		mAni->CreateAnimation(L"item_broken", item, Vector2(28, 0), 6, 1, 1, Vector2::Zero, 1);
		mAni->CreateAnimation(L"item_ring", item, Vector2(56, 0), 6, 1, 1, Vector2::Zero, 1);
		mAni->CreateAnimation(L"item_fire", item, Vector2(84, 0), 6, 1, 1, Vector2::Zero, 1);
		mAni->CreateAnimation(L"item_thunder", item, Vector2(112, 0), 6, 1, 1, Vector2::Zero, 1);
		mAni->CreateAnimation(L"item_water", item, Vector2(140, 0), 6, 1, 1, Vector2::Zero, 1);
		mAni->CreateAnimation(L"boom", boom, Vector2::Zero, 5, 1, 5, Vector2::Zero, 0.1);

		mTr->SetScale(Vector2(2.5f, 2.5f));
		mCol->SetSize(Vector2(10.0f, 80.0f));
		mCol->SetCenter(Vector2(30.0f, 0.0f));
		//mItemState = eItemState::Ring;

		sItem = Resources::Load<Sound>(L"item", L"..\\Resources\\sound\\sonic_getitem.wav");

		GameObject::Initialize();

	}
	void Item::Update()
	{
		GameObject::Update();

		switch (mItemState)
		{
		case sg::Item::eItemState::Life:
			Life();
			break;
		case sg::Item::eItemState::Ring:
			Ring();
			break;
		case sg::Item::eItemState::Flame:
			Flame();
			break;
		case sg::Item::eItemState::Thunder:
			Thunder();
			break;
		case sg::Item::eItemState::Water:
			Water();
			break;
		case sg::Item::eItemState::Broken:
			Broken();
			break;
		}
	}
	void Item::Render(HDC hdc)
	{
		GameObject::Render(hdc);

	}
	void Item::Release()
	{
		GameObject::Release();

	}

	void Item::OnCollisionEnter(Collider* other)
	{
		Sonic* sonic = dynamic_cast<Sonic*>(other->GetOwner());

		if (other->GetOwner() == nullptr)
			return;

		if ((sonic->GetSonicState() == Sonic::eSonicState::rolling_left
			|| sonic->GetSonicState() == Sonic::eSonicState::rolling_right
			|| sonic->GetSonicState() == Sonic::eSonicState::jump_left
			|| sonic->GetSonicState() == Sonic::eSonicState::jump_right
			|| sonic->GetSonicState() == Sonic::eSonicState::jump2_left
			|| sonic->GetSonicState() == Sonic::eSonicState::jump2_right)
			&& mItemState != eItemState::Broken)
		{
			sItem->Play(false);
			mAni->Play(L"boom", false);
			mBroken = true;
		}

		
	}
	void Item::OnCollisionStay(Collider* other)
	{
		Sonic* sonic = dynamic_cast<Sonic*>(other->GetOwner());

		if (other->GetOwner() == nullptr)
			return;

		if ((sonic->GetSonicState() == Sonic::eSonicState::rolling_left
			|| sonic->GetSonicState() == Sonic::eSonicState::rolling_right
			|| sonic->GetSonicState() == Sonic::eSonicState::jump_left
			|| sonic->GetSonicState() == Sonic::eSonicState::jump_right
			|| sonic->GetSonicState() == Sonic::eSonicState::jump2_left
			|| sonic->GetSonicState() == Sonic::eSonicState::jump2_right)
			&& mItemState != eItemState::Broken)
		{
			sItem->Play(false);
			mItemState = eItemState::Broken;
		}
	}
	void Item::OnCollisionExit(Collider* other)
	{
		Sonic* sonic = dynamic_cast<Sonic*>(other->GetOwner());
		if (other->GetOwner() == nullptr)
			return;

		if ((sonic->GetSonicState() == Sonic::eSonicState::rolling_left
			|| sonic->GetSonicState() == Sonic::eSonicState::rolling_right
			|| sonic->GetSonicState() == Sonic::eSonicState::jump_left
			|| sonic->GetSonicState() == Sonic::eSonicState::jump_right
			|| sonic->GetSonicState() == Sonic::eSonicState::jump2_left
			|| sonic->GetSonicState() == Sonic::eSonicState::jump2_right)
			&& mItemState != eItemState::Broken)
		{
			mItemState = eItemState::Broken;
		}
	}
	void Item::Life()
	{
		mAni->Play(L"item_life", false);
	}
	void Item::Ring()
	{
		mAni->Play(L"item_ring", false);
	}
	void Item::Flame()
	{
		mAni->Play(L"item_fire", false);
	}
	void Item::Thunder()
	{
		mAni->Play(L"item_thunder", false);
	}
	void Item::Water()
	{
		mAni->Play(L"item_water", false);
	}
	void Item::Broken()
	{
		mAni->Play(L"item_broken", true);
		mCol->SetCenter(Vector2(-10000, -10000));
	}
}