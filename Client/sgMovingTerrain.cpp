#include "sgMovingTerrain.h"
#include "sgSonic.h"

#include "sgImage.h"
#include "sgResources.h"
#include "sgTime.h"
#include "sgInput.h"
#include "sgGroundMgr.h"

#include "sgTransform.h"
#include "sgAnimator.h"
#include "sgCollider.h"
#include "sgRigidbody.h"

namespace sg
{
	MovingTerrain::MovingTerrain()
		: mUpDown(false)
	{
		SetName(L"MovTerr");
	}
	MovingTerrain::~MovingTerrain()
	{
	}

	void MovingTerrain::Initialize()
	{
		Image* movterr = Resources::Load<Image>(L"movterr", L"..\\Resources\\map\\MovingTerrain.bmp");
		Image* movterr2 = Resources::Load<Image>(L"movterr2", L"..\\Resources\\map2\\movingterrain_2.bmp");
		Animator* animator = AddComponent<Animator>();
		animator->CreateAnimation(L"movterr", movterr, Vector2::Zero, 1, 1, 1, Vector2::Zero, 1);
		animator->CreateAnimation(L"movterr2", movterr2, Vector2::Zero, 6, 1, 6, Vector2::Zero, 1);


		if (SceneManager::GetActiveScene2() == eSceneType::Play)
		{
			animator->Play(L"movterr", true);
		}
		else
		{
			animator->Play(L"movterr2", true);
		}

		Transform* tr = GetComponent<Transform>();
		mFirstPos = tr->GetPos();
		tr->SetScale(Vector2(2.5f, 2.5f));
		
		mCol = AddComponent<Collider>();
		mCol->SetSize(Vector2(160.0f, 10.0f));
		mCol->SetCenter(Vector2::Zero);

		GameObject::Initialize();

	}
	void MovingTerrain::Update()
	{
		GameObject::Update();
		Transform* thistr = GetComponent<Transform>();
		Vector2 thispos = thistr->GetPos();
		Vector2 range = Vector2(0.0f, 400.0f);


		if (mUpDown == false)
		{
			thispos.y += 100.0f * Time::DeltaTime();
			thistr->SetPos(thispos);
			if (thistr->GetPos().y > mFirstPos.y + range.y)
				mUpDown = true;
		}
		if (mUpDown == true)
		{
			thispos.y -= 100.0f * Time::DeltaTime();
			thistr->SetPos(thispos);
			if (thistr->GetPos().y < mFirstPos.y - range.y)
				mUpDown = false;
		}
	}
	void MovingTerrain::Render(HDC hdc)
	{
		GameObject::Render(hdc);

	}
	void MovingTerrain::Release()
	{
		GameObject::Release();

	}
	void MovingTerrain::OnCollisionEnter(Collider* other)
	{
		Sonic* sonic= dynamic_cast<Sonic*>(other->GetOwner());

		if (/*sonic->GetComponent<Collider>()->GetPos().y + 123 <= this->GetComponent<Collider>()->GetPos().y + 19*/other->GetOwner() == sonic)
		{
			mUse = true;
			//ColPosControl(sonic->GetComponent<Collider>(), this);
		}
	}
	void MovingTerrain::OnCollisionStay(Collider* other)
	{

	}
	void MovingTerrain::OnCollisionExit(Collider* other)
	{
		Sonic* sonic = dynamic_cast<Sonic*>(other->GetOwner());
		if (sonic == nullptr)
			return;

		//Rigidbody* sonicrb = sonic->GetComponent<Rigidbody>();
		//sonicrb->SetGround(false);
		mUse = false;
	}
}