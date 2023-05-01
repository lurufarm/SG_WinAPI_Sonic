#include "sgWall.h"
#include "sgSonic.h"

#include "sgTransform.h"
#include "sgCollider.h"

namespace sg
{
	Wall::Wall()
	{
	}
	Wall::~Wall()
	{
	}
	void Wall::Initialize()
	{
		mTr = GetComponent<Transform>();
		mCollider = AddComponent<Collider>();

		//mCollider->SetSize(Vector2(20000, 4280));
		GameObject::Initialize();
	}
	void Wall::Update()
	{
		GameObject::Update();

		Sonic* sonic = GetSonic();
		if (sonic->GetComponent<Transform>()->GetPos().x >= 18110)
		{
			mCollider->SetSize(Vector2(1100.0f, 800.0f));
			mCollider->SetCenter(Vector2(18110.0f, 2230.0f));
		}

	}
	void Wall::Render(HDC hdc)
	{
		GameObject::Render(hdc);

	}
	void Wall::Release()
	{
		GameObject::Release();
	}
	void Wall::OnCollisionEnter(Collider* other)
	{
	}
	void Wall::OnCollisionStay(Collider* other)
	{
	}
	void Wall::OnCollisionExit(Collider* other)
  	{
		Sonic* sonic = dynamic_cast<Sonic*>(other->GetOwner());
		Vector2 sonpos = sonic->GetComponent<Transform>()->GetPos();
		if (sonic->GetSonicState() != Sonic::eSonicState::death)
		{
			sonic->GetComponent<Transform>()->SetPos(sonpos);
		}
	}
}