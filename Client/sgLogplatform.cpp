#include "sgLogplatform.h"
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
	Logplatform::Logplatform()
		: mPlayer(nullptr)
	{
		SetName(L"Logplatform");
	}
	Logplatform::~Logplatform()
	{
	}
	void Logplatform::Initialize()
	{
		Image* logp = Resources::Load<Image>(L"logp", L"..\\Resources\\map\\logplatform.bmp");
		Animator* animator = AddComponent<Animator>();
		animator->CreateAnimation(L"logp", logp, Vector2::Zero, 4, 1, 4, Vector2::Zero, 0.1);
		animator->Play(L"logp", true);

		Transform* tr = GetComponent<Transform>();
		tr->SetScale(Vector2(2.5f, 2.5f));

		mCol = AddComponent<Collider>();
		mCol->SetSize(Vector2(115.0f, 10.0f));
		mCol->SetCenter(Vector2(22,21));

		GameObject::Initialize();

	}
	void Logplatform::Update()
	{
		GameObject::Update();
		Transform* thistr = GetComponent<Transform>();
		Vector2 thispos = thistr->GetPos();
		thispos.y += 100 * Time::DeltaTime();
		thistr->SetPos(thispos);
		if (SceneManager::GetActiveScene2() == eSceneType::Play)
		{
			if (thispos.y >= 3160.0f)
			{
				thispos.y = 1750.0f;
				thistr->SetPos(thispos);
			}
		}
		else
		{
			if (thispos.y >= 2400.0f)
			{
				thispos.y = 1315.0f;
				thistr->SetPos(thispos);
			}
		}
	}
	void Logplatform::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void Logplatform::Release()
	{
		GameObject::Release();
	}
	void Logplatform::OnCollisionEnter(Collider* other)
	{
		Sonic* sonic = dynamic_cast<Sonic*>(other->GetOwner());

		if (sonic->GetComponent<Collider>()->GetPos().y <= this->GetComponent<Collider>()->GetPos().y + 19)
		{
			mUse = true;
		}
	}
	void Logplatform::OnCollisionStay(Collider* other)
	{

	}
	void Logplatform::OnCollisionExit(Collider* other)
	{
		Sonic* sonic = dynamic_cast<Sonic*>(other->GetOwner());
		if (sonic == nullptr)
			return;

		Rigidbody* sonicrb = sonic->GetComponent<Rigidbody>();
		//sonicrb->SetGround(false);
		mUse = false;
	}
}