#include "sgTestGround.h"
#include "sgCollider.h"
#include "sgSonic.h"
#include "sgRhinobot.h"
#include "sgRing.h"
#include "sgRigidbody.h"
#include "sgTransform.h"

namespace sg
{
	Ground::Ground()
	{
	}

	Ground::~Ground()
	{
	}

	void Ground::Initialize()
	{
		mCollider = AddComponent<Collider>();
		mCollider->SetSize(Vector2(200000.0f, 50.0f));
		GameObject::Initialize();
	}

	void Ground::Update()
	{
		GameObject::Update();
	}

	void Ground::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void Ground::Release()
	{
	}

	void Ground::OnCollisionEnter(Collider* other)
	{
		Sonic* sonic = dynamic_cast<Sonic*>(other->GetOwner());
		if (sonic == nullptr)
			return;

		Rigidbody* rb = sonic->GetComponent<Rigidbody>();
		rb->SetGround(true);

		Collider* sonicCol = sonic->GetComponent<Collider>();
		Vector2 sonicPos = sonicCol->GetPos();

		Collider* groundCol = this->GetComponent<Collider>();
		Vector2 groundPos = groundCol->GetPos();

		float fLen = fabs(sonicPos.y - groundPos.y);
		float fSize = (sonicCol->GetSize().y / 2.0f) + (groundCol->GetSize().y / 2.0f);
		
		if (fLen < fSize)
		{
			Transform* sonTr = sonic->GetComponent<Transform>();
			Transform* grTr = this->GetComponent<Transform>();

			Vector2 sonPos = sonTr->GetPos();
			Vector2 grPos = grTr->GetPos();

			sonPos.y -= (fSize - fLen) - 1.0f;
			sonTr->SetPos(sonPos);
		}

		if (sonic->GetSonicState() == Sonic::eSonicState::death)
		{
			rb->SetGround(false);
		}

		//Rhinobot* rhino = dynamic_cast<Rhinobot*>(other->GetOwner());
		//if (rhino == nullptr)
		//	return;

		//Rigidbody* rrb = rhino->GetComponent<Rigidbody>();
		//rrb->SetGround(true);

		//Collider* rhinoCol = rhino->GetComponent<Collider>();
		//Vector2 rhinoPos = rhinoCol->GetPos();

		//groundCol = this->GetComponent<Collider>();
		//groundPos = groundCol->GetPos();

		//fLen = fabs(rhinoPos.y - groundPos.y);
		//fSize = (rhinoCol->GetSize().y / 2.0f) + (groundCol->GetSize().y / 2.0f);

		//if (fLen < fSize)
		//{
		//	Transform* rhiTr = rhino->GetComponent<Transform>();
		//	Transform* grTr = this->GetComponent<Transform>();

		//	Vector2 rhiPos = rhiTr->GetPos();
		//	Vector2 grPos = grTr->GetPos();

		//	rhiPos.y -= (fSize - fLen) - 1.0f;
		//	rhiTr->SetPos(rhiPos);
		//}

	}

	void Ground::OnCollisionStay(Collider* other)
	{

	}

	void Ground::OnCollisionExit(Collider* other)
	{
		Sonic* sonic = dynamic_cast<Sonic*>(other->GetOwner());
		if (sonic == nullptr)
			return;

		Rigidbody* rb = sonic->GetComponent<Rigidbody>();
		rb->SetGround(false);

	}

}
