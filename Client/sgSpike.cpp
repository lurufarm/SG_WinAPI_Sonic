#include "sgSpike.h"
#include "sgSonic.h"

#include "sgImage.h"
#include "sgSound.h"
#include "sgResources.h"

#include "sgTransform.h"
#include "sgAnimator.h"
#include "sgCollider.h"
#include "sgRigidbody.h"

namespace sg
{
	Spike::Spike()
		: mSpikeState(eSpikeState::up)
	{
		SetName(L"Spike");
	}
	Spike::~Spike()
	{
	}
	void Spike::Initialize()
	{
		mTr = GetComponent<Transform>();
		mAni = AddComponent<Animator>();
		mCol = AddComponent<Collider>();
		mTr->SetScale(Vector2(2.5f, 2.5f));
		
		Image* spike = Resources::Load<Image>(L"spike", L"..\\Resources\\enemies\\spike.bmp");

		mAni->CreateAnimation(L"spike_1", spike, Vector2::Zero, 4, 1, 1, Vector2::Zero, 1);
		mAni->CreateAnimation(L"spike_2", spike, Vector2(32.0f, 0.0f), 4, 1, 1, Vector2::Zero, 1);
		mAni->CreateAnimation(L"spike_3", spike, Vector2(64.0f, 0.0f), 4, 1, 1, Vector2::Zero, 1);
		mAni->CreateAnimation(L"spike_4", spike, Vector2(96.0f, 0.0f), 4, 1, 1, Vector2::Zero, 1);
		
		mCol->SetSize(Vector2(80.0f, 80.0f));

		sSpike = Resources::Load<Sound>(L"s_spike", L"..\\Resources\\sound\\sonic_spiked.wav");

		GameObject::Initialize();
	}
	void Spike::Update()
	{
		GameObject::Update();

		switch (mSpikeState)
		{
		case sg::Spike::eSpikeState::up:
			mAni->Play(L"spike_1", true);
			break;
		case sg::Spike::eSpikeState::right:
			mAni->Play(L"spike_2", true);
			break;
		case sg::Spike::eSpikeState::left:
			mAni->Play(L"spike_3", true);
			break;
		case sg::Spike::eSpikeState::down:
			mAni->Play(L"spike_4", true);
			break;
		}

	}
	void Spike::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void Spike::Release()
	{
		GameObject::Release();
	}
	void Spike::OnCollisionEnter(Collider* other)
	{
		Sonic* sonic = dynamic_cast<Sonic*>(other->GetOwner());
		Transform* str = sonic->GetComponent<Transform>();
		Collider* scol = sonic->GetComponent<Collider>();
		Rigidbody* srb = sonic->GetComponent<Rigidbody>();
		Vector2 spos = str->GetPos();
		Vector2 scolpos = scol->GetPos();
		Vector2 srbvel = srb->GetVelocity();

		Vector2 mycolpos = mCol->GetPos();

		if (mSpikeState == eSpikeState::up)
		{
			if (mycolpos.y - (scolpos.y + 122) < 0 && mycolpos.y - (scolpos.y + 122) > -50
				&& ((mycolpos.x < spos.x + 32.5 && mycolpos.x + 80 > spos.x + 32.5) || (mycolpos.x < spos.x + 92.5 && mycolpos.x + 80 > spos.x + 92.5))
				&& sonic->GetHurt() == false)
			{
				if (mycolpos.x + 40 <= spos.x + 62.5)
				{
					sSpike->Play(false);
					sonic->SetSonicState(Sonic::eSonicState::hurt_left);
				}
				else
				{
					sSpike->Play(false);
					sonic->SetSonicState(Sonic::eSonicState::hurt_right);
				}
			}
			else if (fabs(mycolpos.y + 80 - (scolpos.y + 122)) < 50
				&& ((mycolpos.x + 80 <= spos.x + 32.5) || (mycolpos.x <= spos.x + 92.5)))
			{
				if (mycolpos.x + 40 < spos.x + 62.5) // 캐릭터가 오른쪽
				{
					float x = spos.x + 42.5;
					while (x < mycolpos.x + 80)
					{
						spos.x += 1;
						x += 1;
						str->SetPos(spos);
					}
				}
				else if (mycolpos.x + 40 > spos.x + 62.5) //캐릭터가 왼쪽
				{
					float x = spos.x + 82.5;
					while (x > mycolpos.x)
					{
						spos.x -= 1;
						x -= 1;
						str->SetPos(spos);
					}
				}
			}
		}
		if (mSpikeState == eSpikeState::right)
		{
			if (mycolpos.y >= scolpos.y + 90 && mycolpos.x < scolpos.x && mycolpos.x + 80 > scolpos.x)
			{
				spos.y -= 1;
				str->SetPos(spos);
				srb->SetGround(true);
				mUse = true;
			}
			if (mycolpos.x + 80 >= scolpos.x 
				&& mycolpos.y + 80 < scolpos.y + 94
				&& sonic->GetHurt() == false)
			{
				sonic->SetSonicState(Sonic::eSonicState::hurt_left);
			}
		}
		if (mSpikeState == eSpikeState::left)
		{
			if (mycolpos.x <= scolpos.x + 50 
				&& mycolpos.y <= scolpos.y + 94
				&& sonic->GetHurt() == false)
			{
				sonic->SetSonicState(Sonic::eSonicState::hurt_right);
			}
			else if (mycolpos.y >= scolpos.y + 94)
			{
				mUse = true;
			}
		}
		if (mSpikeState == eSpikeState::down)
		{
			if (mycolpos.y + 80 >= scolpos.y 
				&& (mycolpos.x < scolpos.x + 27.5 && mycolpos.x + 80 > scolpos.x + 27.5)
				&& sonic->GetHurt() == false)
			{
				if (mycolpos.x + 40 <= scolpos.x + 27.5)
				{
					sonic->SetSonicState(Sonic::eSonicState::hurt_left);
				}
				else
				{
					sonic->SetSonicState(Sonic::eSonicState::hurt_right);
				}
			}
			else
			{
				if (mycolpos.x + 40 < scolpos.x + 27.5)
				{
					spos.x += 1;
					str->SetPos(spos);
					srbvel.x = 0;
					srb->SetVelocity(srbvel);

				}
				else if (mycolpos.x + 40 > scolpos.x)
				{
					spos.x -= 1;
					str->SetPos(spos);
					srbvel.x = 0;
					srb->SetVelocity(srbvel);

				}
			}
		}


	}
	void Spike::OnCollisionStay(Collider* other)
	{
		Sonic* sonic = dynamic_cast<Sonic*>(other->GetOwner());
		Transform* str = sonic->GetComponent<Transform>();
		Collider* scol = sonic->GetComponent<Collider>();
		Rigidbody* srb = sonic->GetComponent<Rigidbody>();
		Vector2 spos = str->GetPos();
		Vector2 scolpos = scol->GetPos();
		Vector2 srbvel = srb->GetVelocity();

		Vector2 mycolpos = mCol->GetPos();

		if (mSpikeState == eSpikeState::up)
		{
			if (mycolpos.y - (scolpos.y + 122) < 0 && mycolpos.y - (scolpos.y + 122) > -50
				&& ((mycolpos.x < spos.x + 32.5 && mycolpos.x + 80 > spos.x + 32.5) || (mycolpos.x < spos.x + 92.5 && mycolpos.x + 80 > spos.x + 92.5))
				&& sonic->GetHurt() == false)
			{
				if (mycolpos.x + 40 <= spos.x + 62.5)
				{
					sSpike->Play(false);
					sonic->SetSonicState(Sonic::eSonicState::hurt_left);
				}
				else
				{
					sSpike->Play(false);
					sonic->SetSonicState(Sonic::eSonicState::hurt_right);
				}
			}
			else if (fabs(mycolpos.y + 80 - (scolpos.y + 122)) < 50
				&& ((mycolpos.x + 80 <= spos.x + 32.5) || (mycolpos.x <= spos.x + 92.5)))
			{
				if (mycolpos.x + 40 < spos.x + 62.5) // 캐릭터가 오른쪽
				{
					float x = spos.x + 42.5;
					while (x < mycolpos.x + 80)
					{
						spos.x += 1;
						x += 1;
						str->SetPos(spos);
					}
				}
				else if (mycolpos.x + 40 > spos.x + 62.5) //캐릭터가 왼쪽
				{
					float x = spos.x + 82.5;

					while (x > mycolpos.x)
					{
						spos.x -= 1;
						x -= 1;
						str->SetPos(spos);
					}
				}
			}
		}
		if (mSpikeState == eSpikeState::right)
		{
			if (mycolpos.y >= scolpos.y + 90 && mycolpos.x < scolpos.x && mycolpos.x + 80 > scolpos.x)
			{
				spos.y -= 1;
				str->SetPos(spos);
				srb->SetGround(true);
				mUse = true;
			}
			if (mycolpos.x + 80 >= scolpos.x
				&& mycolpos.y + 80 < scolpos.y + 94
				&& sonic->GetHurt() == false)
			{
				sonic->SetSonicState(Sonic::eSonicState::hurt_left);
			}
		}
		if (mSpikeState == eSpikeState::left)
		{
			if (mycolpos.x <= scolpos.x + 50
				&& mycolpos.y <= scolpos.y + 94
				&& sonic->GetHurt() == false)
			{
				sonic->SetSonicState(Sonic::eSonicState::hurt_right);
			}
			else if (mycolpos.y >= scolpos.y + 94)
			{
				mUse = true;
			}
		}
		if (mSpikeState == eSpikeState::down)
		{
			if (mycolpos.y + 80 >= scolpos.y
				&& (mycolpos.x < scolpos.x + 27.5 && mycolpos.x + 80 > scolpos.x + 27.5)
				&& sonic->GetHurt() == false)
			{
				if (mycolpos.x + 40 <= scolpos.x + 27.5)
				{
					sonic->SetSonicState(Sonic::eSonicState::hurt_left);
				}
				else
				{
					sonic->SetSonicState(Sonic::eSonicState::hurt_right);
				}
			}
			else
			{
				if (mycolpos.x + 40 < scolpos.x + 27.5)
				{
					spos.x += 1;
					str->SetPos(spos);
					srbvel.x = 0;
					srb->SetVelocity(srbvel);

				}
				else if (mycolpos.x + 40 > scolpos.x)
				{
					spos.x -= 1;
					str->SetPos(spos);
					srbvel.x = 0;
					srb->SetVelocity(srbvel);

				}
			}
		}


	}
	void Spike::OnCollisionExit(Collider* other)
	{
		mUse = false;
	}
}