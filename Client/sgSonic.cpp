#include "sgSonic.h"
#include "sgRhinobot.h"
#include "sgBloominator.h"
#include "sgBloomBullet.h"
#include "sgMiniboss.h"
#include "sgCaterkiller.h"
#include "sgEnemyEffect.h"
#include "sgRing.h"
#include "sgGiantring.h"
#include "sgRope.h"
#include "sgSpring.h"
#include "sgMapRock_l.h"
#include "sgMovingTerrain.h"
#include "sgBreakingterrain.h"
#include "sgLogplatform.h"
#include "sgTestGround.h"
#include "sgPlayScene.h"
#include "sgItem.h"


#include <random>
#include <algorithm>
#include "sgTime.h"
#include "sgInput.h"
#include "sgSound.h"
#include "sgResources.h"
#include "sgScene.h"
#include "sgSceneManager.h"
#include "sgCollisionManager.h"
#include "sgObject.h"
#include "sgCamera.h"

#include "sgTransform.h"
#include "sgAnimator.h"
#include "sgCollider.h"
#include "sgRigidbody.h"

extern sg::Ground* ground;
extern sg::Sonic* mSonic;
extern sg::Sonic* mSonic2;

namespace sg
{
	int Sonic::mRings = 0;
	int Sonic::mAbility = 0;
	int Sonic::mLife = 3;
	bool Sonic::mFlame = false;
	bool Sonic::mThunder = false;
	bool Sonic::mWater = false;
	//Effect* Sonic::mEffect = nullptr;
	//Effect2* Sonic::mEffect2 = nullptr;

	Sonic::Sonic()
		: mTime(0.0f)
		, mHurtTime(0.0f)
		, mbHurt(false)
		, mSonicVelocity(Vector2::Zero)
		, mR(false)
		, mLimitVel(0.0)
		, mResetPos(Vector2::Zero)
	{
		SetName(L"Sonic");
	}
	Sonic::~Sonic()
	{
	}

	void Sonic::Initialize()
	{
		mTime = 0.0f;
		Image* sonicimg = Resources::Load<Image>(L"Sonic", L"..\\Resources\\sonic\\sonic.bmp"); 
		Image* jump2 = Resources::Load<Image>(L"Sonic_jump2", L"..\\Resources\\sonic\\sonic_jump2.bmp");
		Image* spindash = Resources::Load<Image>(L"Sonic_spindash", L"..\\Resources\\sonic\\sonic_spindash2.bmp");
		Transform* tr = GetComponent<Transform>();
		tr->SetScale(Vector2(2.5f, 2.5f));
		mAnimator = AddComponent<Animator>();
		mCollider = AddComponent<Collider>();
		mRigidbody = AddComponent<Rigidbody>();

		sJump = Resources::Load<Sound>(L"Sonic_s_jump", L"..\\Resources\\sound\\sonic_jump.wav");
		sJump2 = Resources::Load<Sound>(L"Sonic_s_jump2", L"..\\Resources\\sound\\sonic_double-jump.wav");
		sSpin = Resources::Load<Sound>(L"Sonic_s_spin", L"..\\Resources\\sound\\sonic_spindash.wav");
		sHurt = Resources::Load<Sound>(L"Sonic_s_hurt", L"..\\Resources\\sound\\sonic_hurt.wav");
		sDeath = Resources::Load<Sound>(L"Sonic_s_death", L"..\\Resources\\sound\\sonic_death.wav");
		sGrap = Resources::Load<Sound>(L"Sonic_s_grap", L"..\\Resources\\sound\\sonic_grap.wav");
		sSkid = Resources::Load<Sound>(L"Sonic_s_skid", L"..\\Resources\\sound\\sonic_skid.wav");
		sJump_water = Resources::Load<Sound>(L"Sonic_s_jump_water", L"..\\Resources\\sound\\sonic_waterjump.wav");
		sJump_thunder = Resources::Load<Sound>(L"Sonic_s_jump_thunder", L"..\\Resources\\sound\\sonic_electric-double-jump.wav");
		sJump_flame = Resources::Load<Sound>(L"Sonic_s_jump_flame", L"..\\Resources\\sound\\sonic_flame-dash.wav");
		sGetring = Resources::Load<Sound>(L"Sonic_s_getring", L"..\\Resources\\sound\\sonic_getring.wav");
		sLosering =  Resources::Load<Sound>(L"Sonic_s_losering", L"..\\Resources\\sound\\sonic_ring-lose.wav");


		mAnimator->CreateAnimation(L"Sonic_idle_left", sonicimg, Vector2(0, 50), 16, 20, 1, Vector2::Zero, 0.1);
		mAnimator->CreateAnimation(L"Sonic_idle_right", sonicimg, Vector2(0, 0), 16, 20, 1, Vector2::Zero, 0.1);
		mAnimator->CreateAnimation(L"Sonic_idle_bored", sonicimg, Vector2(0, 100), 16, 20, 12, Vector2::Zero, 0.15);
		mAnimator->CreateAnimation(L"Sonic_walk_left", sonicimg, Vector2(0, 150), 16, 20, 8, Vector2::Zero, 0.1);
		mAnimator->CreateAnimation(L"Sonic_walk_right", sonicimg, Vector2(0, 200), 16, 20, 8, Vector2::Zero, 0.1);
		mAnimator->CreateAnimation(L"Sonic_run_left", sonicimg, Vector2(0,250), 16, 20, 4, Vector2::Zero, 0.1);
		mAnimator->CreateAnimation(L"Sonic_run_right", sonicimg, Vector2(0,300), 16, 20, 4, Vector2::Zero, 0.1);
		mAnimator->CreateAnimation(L"Sonic_lookup_left", sonicimg, Vector2(100,350), 16, 20, 2, Vector2::Zero, 0.1);
		mAnimator->CreateAnimation(L"Sonic_lookup_right", sonicimg, Vector2(0,350), 16, 20, 2, Vector2::Zero, 0.1);
		mAnimator->CreateAnimation(L"Sonic_crouch_left", sonicimg, Vector2(100, 400), 16, 20, 2, Vector2::Zero, 0.1);
		mAnimator->CreateAnimation(L"Sonic_crouch_right", sonicimg, Vector2(0, 400), 16, 20, 2, Vector2::Zero, 0.1);
		mAnimator->CreateAnimation(L"Sonic_skid_left", sonicimg, Vector2(0,550), 16, 20, 4, Vector2::Zero, 0.08);
		mAnimator->CreateAnimation(L"Sonic_skid_right", sonicimg, Vector2(0,600), 16, 20, 4, Vector2::Zero, 0.08);
		mAnimator->CreateAnimation(L"Sonic_jump_left", sonicimg, Vector2(0, 450), 16, 20, 8, Vector2::Zero, 0.03);
		mAnimator->CreateAnimation(L"Sonic_jump_right", sonicimg, Vector2(0, 500), 16, 20, 8, Vector2::Zero, 0.03);
		mAnimator->CreateAnimation(L"Sonic_jump2_left", jump2, Vector2(0,48), 8, 2, 6, Vector2::Zero, 0.005);
		mAnimator->CreateAnimation(L"Sonic_jump2_right", jump2, Vector2::Zero, 8, 2, 6, Vector2::Zero, 0.005);
		mAnimator->CreateAnimation(L"Sonic_spindash_left", spindash, Vector2(0, 50), 9, 2, 9, Vector2::Zero, 0.03);
		mAnimator->CreateAnimation(L"Sonic_spindash_right", spindash, Vector2(0, 0), 9, 2, 9, Vector2::Zero, 0.03);
		mAnimator->CreateAnimation(L"Sonic_hurt_left", sonicimg, Vector2(0, 650), 16, 20, 4, Vector2::Zero, 0.15);
		mAnimator->CreateAnimation(L"Sonic_hurt_right", sonicimg, Vector2(0, 700), 16, 20, 4, Vector2::Zero, 0.15);
		mAnimator->CreateAnimation(L"Sonic_death", sonicimg, Vector2(0,750), 16, 20, 1, Vector2::Zero, 0.1);
		mAnimator->CreateAnimation(L"Sonic_hang_left", sonicimg, Vector2(0, 900), 16, 20, 4, Vector2::Zero, 0.25);
		mAnimator->CreateAnimation(L"Sonic_hang_right", sonicimg, Vector2(0, 950), 16, 20, 4, Vector2::Zero, 0.25);
		mAnimator->CreateAnimation(L"Sonic_spring_up", sonicimg, Vector2(50, 0), 16, 20, 12, Vector2::Zero, 0.1);
		mAnimator->CreateAnimation(L"Sonic_fall_down", sonicimg, Vector2(200, 700), 16, 20, 2, Vector2::Zero, 0.15);


		mRigidbody->SetMass(0.3);

		mLimitVel = 800.0f;

		mSonicState = eSonicState::idle_right;

		mEffect = object::Instantiate<Effect>(eLayerType::Effect, SceneManager::GetActiveScene2());
		mEffect2 = object::Instantiate<Effect2>(eLayerType::Effect2, SceneManager::GetActiveScene2());
		mEffect->SetTarget(this);
		mEffect2->SetTarget(this);
		mEffect2->SetEffect(mEffect);

		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Monster, true);
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::hideMonster, true);
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::RMonster, true);
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Boss, true);
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Ring, true);
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::hideObjects, true);
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::MapObjects, true);
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Item, true);
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Ground, true);
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::mEffect, true);
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Bullet, true);

		//mResetPos = tr->GetPos();

		GameObject::Initialize();
	}
	void Sonic::Update()
	{
		GameObject::Update();
		Transform* Tr = GetComponent<Transform>();

		if (SceneManager::GetActiveScene2() == eSceneType::Play)
		{
			if (Tr->GetPos().x < 6500)
			{
				mResetPos = Vector2(510, 2640);
			}
			else if (Tr->GetPos().x > 6500 && Tr->GetPos().x < 13440)
			{
				mResetPos = Vector2(6530, 2320);
			}
			else if (Tr->GetPos().x > 13400 && Tr->GetPos().x < 17100)
			{
				mResetPos = Vector2(12550, 2840);
			}
			else if (Tr->GetPos().x > 17100)
			{
				mResetPos = Vector2(17100, 2100);
			}
		}
		else
		{
			if (Tr->GetPos().x < 5150)
			{
				mResetPos = Vector2(300, 2000);
			}
			else if (Tr->GetPos().x > 5150 && Tr->GetPos().x < 8200)
			{
				mResetPos = Vector2(5380, 5380);
			}
			else if (Tr->GetPos().x > 8200 && Tr->GetPos().x < 22900)
			{
				mResetPos = Vector2(13300, 980);
			}
			else if (Tr->GetPos().x > 22900)
			{
				mResetPos = Vector2(23500, 980);
			}
		}
		mEffect->SetTarget(this);
		mEffect2->SetTarget(this);
		mEffect2->SetEffect(mEffect);

		mSonicVelocity = mRigidbody->GetVelocity();

		if (mSonicVelocity.x > 0
			&& Input::GetKey(eKeyCode::Left))
		{
			mSonicVelocity.x -= 50.0;
			mRigidbody->SetVelocity(mSonicVelocity);
		}
		if (mSonicVelocity.x < 0
			&& Input::GetKey(eKeyCode::Right))
		{
			mSonicVelocity.x += 50.0;
			mRigidbody->SetVelocity(mSonicVelocity);
		}


		if (Input::GetKeyDown(eKeyCode::Ctrl))
		{
			Sonic::SonicReset();
		}

		switch (mSonicState)
		{
		case sg::Sonic::eSonicState::idle_left:
			mWaterJump = false;
			idle_left();
			break;
		case sg::Sonic::eSonicState::idle_right:
			mWaterJump = false;
			idle_right();
			break;
		case sg::Sonic::eSonicState::walk_left:
			mWaterJump = false;
			mTime = 0.0;
			walk_left();
			break;
		case sg::Sonic::eSonicState::walk_right:
			mWaterJump = false;
			mTime = 0.0;
			walk_right();
			break;
		case sg::Sonic::eSonicState::lookup_left:
			mTime = 0.0;
			lookup_left();
			break;
		case sg::Sonic::eSonicState::lookup_right:
			mTime = 0.0;
			lookup_right();
			break;
		case sg::Sonic::eSonicState::crouch_left:
			mTime = 0.0;
			crouch_left();
			break;
		case sg::Sonic::eSonicState::crouch_right:
			mTime = 0.0;
			crouch_right();
			break;
		case sg::Sonic::eSonicState::run_left:
			mTime = 0.0;
			run_left();
			break;
		case sg::Sonic::eSonicState::run_right:
			mTime = 0.0;
			run_right();
			break;
		case sg::Sonic::eSonicState::jump_left:
			mTime = 0.0;
			jump_left();
			break;
		case sg::Sonic::eSonicState::jump_right:
			mTime = 0.0;
			jump_right();
			break;
		case sg::Sonic::eSonicState::jump2_left:
			mTime = 0.0;
			jump2_left();
			break;
		case sg::Sonic::eSonicState::jump2_right:
			mTime = 0.0;
			jump2_right();
			break;
		case sg::Sonic::eSonicState::spindash_left:
			mTime = 0.0;
			spindash_left();
			break;
		case sg::Sonic::eSonicState::spindash_right:
			mTime = 0.0;
			spindash_right();
			break;
		case sg::Sonic::eSonicState::rolling_left:
			mTime = 0.0;
			rolling_left();
			break;
		case sg::Sonic::eSonicState::rolling_right:
			mTime = 0.0;
			rolling_right();
			break;
		case sg::Sonic::eSonicState::skid_left:
			mTime = 0.0;
			skid_left();
			break;
		case sg::Sonic::eSonicState::skid_right:
			mTime = 0.0;
			skid_right();
			break;
		case sg::Sonic::eSonicState::hurt_left:
			mTime = 0.0;
			hurt_left();
			break;
		case sg::Sonic::eSonicState::hurt_right:
			mTime = 0.0;
			hurt_right();
			break;
		case sg::Sonic::eSonicState::death:
			
			death();
			break;
		case sg::Sonic::eSonicState::hang_left:
			mTime = 0.0;
			hang_left();
			break;
		case sg::Sonic::eSonicState::hang_right:
			mTime = 0.0;
			hang_right();
			break;
		case sg::Sonic::eSonicState::spring_up:
			mTime = 0.0;
			spring_up();
			break;
		case sg::Sonic::eSonicState::waterjump:
			mTime = 0.0;
			waterjump();
			break;
		case sg::Sonic::eSonicState::falldown:
			mTime = 0.0;
			falldown();
			break;
		}
		if (mRings > 0)
		{
			mAbility = 1;
		}
		if (mRings <= 0)
		{
			mAbility = 0;
		}
		if (mRings >= 100)
		{
			mRings -= 100;
			mLife++;
		}

		if (mWater || mFlame || mThunder)
		{
			CollisionManager::SetLayer(eLayerType::Effect, eLayerType::Bullet, true);
			CollisionManager::SetLayer(eLayerType::Player, eLayerType::Bullet, false);

		}
		else if (mWater == false && mFlame == false && mThunder == false)
		{
			CollisionManager::SetLayer(eLayerType::Player, eLayerType::Bullet, true);
			CollisionManager::SetLayer(eLayerType::Effect, eLayerType::Bullet, false);
			mEffect->SetEffectState(Effect::eEffectState::None);
			mEffect2->mFlame = false;
		}
		
		if (mLife <= 0)
		{
			 mTime+= Time::DeltaTime();

			 if (mTime >= 1.0f)
			 {
				 SceneManager::LoadScene(eSceneType::Ending);
				 mTime = 0;
			 }

		}
		if (mbHurt == true)
		{
			mHurtTime += Time::DeltaTime();

		}
		if (mHurtTime >= 2.0f)
		{
			mbHurt = false;
			mHurtTime = 0.0f;
		}

	}
	void Sonic::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void Sonic::Release()
	{
		GameObject::Release();
	}

	void Sonic::OnCollisionEnter(Collider* other)
	{
		Ring* ring = dynamic_cast<Ring*>(other->GetOwner());
		Giantring* Gring = dynamic_cast<Giantring*>(other->GetOwner());
		Rope* rope = dynamic_cast<Rope*>(other->GetOwner());
		MapRock_l* maprockl = dynamic_cast<MapRock_l*>(other->GetOwner());
		Spring* spring = dynamic_cast<Spring*>(other->GetOwner());
		Item* item = dynamic_cast<Item*>(other->GetOwner());
		Rhinobot* rhino = dynamic_cast<Rhinobot*>(other->GetOwner());
		Bloominator* bloom = dynamic_cast<Bloominator*>(other->GetOwner());
		BloomBullet* bullet = dynamic_cast<BloomBullet*>(other->GetOwner());
		Logplatform* logp = dynamic_cast<Logplatform*>(other->GetOwner());
		Breakingterrain* bterr = dynamic_cast<Breakingterrain*>(other->GetOwner());

		Transform* mytr = GetComponent<Transform>();
		Vector2 mypos = GetComponent<Transform>()->GetPos();
		Vector2 mycolpos = mCollider->GetPos();

		if (other->GetOwner() == nullptr)
		{
			return;
		}

		if (other->GetOwner() == ring)
		{
			mRings++;
		}
		
		if (other->GetOwner() == Gring)
		{
			mRings += 50;
		}

		if (other->GetOwner() == maprockl)
		{
			if (mSonicState != eSonicState::rolling_left
				&& mSonicState != eSonicState::rolling_right)
			{
				if (mypos.x + 62.5 > maprockl->GetComponent<Transform>()->GetPos().x + 60
					&& maprockl->mOn == false) // 캐릭터가 오른쪽
				{
					float x = mypos.x + 42.5;
					while (x < maprockl->GetComponent<Transform>()->GetPos().x + 120 && maprockl->mOn == false)
					{
						mypos.x += 1;
						x += 1;
						mytr->SetPos(mypos);
					}
				}
				else if (mypos.x + 62.5 < maprockl->GetComponent<Transform>()->GetPos().x + 60
					&& maprockl->mOn == false) // 캐릭터가 왼쪽
				{
					float x = mypos.x + 82.5;
					while (x > maprockl->GetComponent<Transform>()->GetPos().x && maprockl->mOn == false)
					{
						mypos.x -= 1;
						x -= 1;
						mytr->SetPos(mypos);
					}
				}
			}
		}

		if (other->GetOwner() == rope)
		{
			sGrap->Play(false);
			mSonicState = eSonicState::hang_right;
			mRigidbody->SetGround(true);
			mytr->SetPos(other->GetPos());
		}

		if (other->GetOwner() == logp)
		{

			Vector2 logppos = logp->GetComponent<Collider>()->GetPos();
			mytr->SetPos(Vector2(mypos.x, logppos.y - 100));

		}

		if (other->GetOwner() == spring)
		{
			if ((spring->GetState() == Spring::eSpringState::up_norm
				|| spring->GetState() == Spring::eSpringState::up_use)
				&& mSonicState != eSonicState::rolling_left
				&& mSonicState != eSonicState::rolling_right)
			{
				mRigidbody->SetGround(false);
				mSonicVelocity.y = -1050;
				mRigidbody->SetVelocity(mSonicVelocity);
				mRigidbody->SetGround(false);
				mSonicState = eSonicState::spring_up;
			}
			else if (spring->GetState() == Spring::eSpringState::right_norm
				|| spring->GetState() == Spring::eSpringState::right_use)
			{
				mSonicVelocity.x = -1000.0f;
				mSonicState = eSonicState::run_left;
				mRigidbody->SetVelocity(mSonicVelocity);
			}
			else if (spring->GetState() == Spring::eSpringState::left_norm
				|| spring->GetState() == Spring::eSpringState::left_use)
			{
				mSonicVelocity.x = +1000.0f;
				mSonicState = eSonicState::run_right;
				mRigidbody->SetVelocity(mSonicVelocity);
			}
		}

		if (other->GetOwner() == item
			&& (mSonicState == eSonicState::jump_left
			|| mSonicState == eSonicState::jump_right
			|| mSonicState == eSonicState::rolling_left
			|| mSonicState == eSonicState::rolling_right))
		{
			if (item->GetState() == Item::eItemState::Ring)
			{
				mRings += 10;
				mSonicVelocity.y = -300;
				mRigidbody->SetVelocity(mSonicVelocity);
			}
			else if (other->GetOwner() == item
				&& item->GetState() == Item::eItemState::Life)
			{
				mLife++;
				mSonicVelocity.y = -300;
				mRigidbody->SetVelocity(mSonicVelocity);
			}
			else if (other->GetOwner() == item
				&& item->GetState() == Item::eItemState::Flame)
			{
				Sound* sFlameShield = Resources::Load<Sound>(L"s_thunderhield", L"..\\Resources\\sound\\sonic_flame-shield.wav");
				sFlameShield->Play(false);
				mThunder = false;
				mWater = false;
				mFlame = true;
				mEffect->SetEffectState(Effect::eEffectState::Flame);
				mEffect2->mFlame = true;
				mSonicVelocity.y = -300;
				mRigidbody->SetVelocity(mSonicVelocity);
			}
			else if (other->GetOwner() == item
				&& item->GetState() == Item::eItemState::Thunder)
			{
				Sound* ThunderShield = Resources::Load<Sound>(L"s_flameshield", L"..\\Resources\\sound\\sonic_electric-shield.wav");
				ThunderShield->Play(false);
				mThunder = true;
				mWater = false;
				mFlame = false;
				mEffect->SetEffectState(Effect::eEffectState::Thunder);
				mEffect2->mFlame = false;
				mSonicVelocity.y = -300;
				mRigidbody->SetVelocity(mSonicVelocity);
			}
			else if (other->GetOwner() == item
				&& item->GetState() == Item::eItemState::Water)
			{
				Sound* WaterShield = Resources::Load<Sound>(L"s_watershield", L"..\\Resources\\sound\\sonic_water-shield.wav");
				WaterShield->Play(false);
				mThunder = false;
				mWater = true;
				mFlame = false;
				mEffect->SetEffectState(Effect::eEffectState::Water);
				mEffect2->mFlame = false;
				mSonicVelocity.y = -300;
				mRigidbody->SetVelocity(mSonicVelocity);
			}
		}
		else if (other->GetOwner() == item)
		{
			mSonicVelocity.x = 0;
			mRigidbody->SetVelocity(mSonicVelocity);

			if (mypos.x + 100 > item->GetComponent<Transform>()->GetPos().x + 70) // 내가 오른쪽
			{
				mypos.x += 3;
				mytr->SetPos(mypos);
			}
			if (mypos.x + 20 < item->GetComponent<Transform>()->GetPos().x) // 내가 왼쪽
			{
				mypos.x -= 3;
				mytr->SetPos(mypos);
			}
		}

	
	}
	void Sonic::OnCollisionStay(Collider* other)
	{
		Transform* mytr = GetComponent<Transform>();
		Vector2 mypos = mytr->GetPos();
		Vector2 mycolpos = mCollider->GetPos();
		MapRock_l* maprockl = dynamic_cast<MapRock_l*>(other->GetOwner());
		Rope* rope = dynamic_cast<Rope*>(other->GetOwner());
		MovingTerrain* movter = dynamic_cast<MovingTerrain*>(other->GetOwner());
		Logplatform* logp = dynamic_cast<Logplatform*>(other->GetOwner());
		Item* item = dynamic_cast<Item*>(other->GetOwner());
		Spring* spring = dynamic_cast<Spring*>(other->GetOwner());



		if (other->GetOwner() == rope)
		{
			mytr->SetPos(other->GetPos());
		}
		
		if (other->GetOwner() == maprockl)
		{
			if (mSonicState != eSonicState::rolling_left
				&& mSonicState != eSonicState::rolling_right)
			{
				if (mypos.x + 62.5 > maprockl->GetComponent<Transform>()->GetPos().x + 60
					&& maprockl->mOn == false) // 캐릭터가 오른쪽
				{
					float x = mypos.x + 42.5;
					while (x < maprockl->GetComponent<Transform>()->GetPos().x + 120 && maprockl->mOn == false)
					{
						mypos.x += 1;
						x += 1;
						mytr->SetPos(mypos);
					}
				}
				else if (mypos.x + 62.5 < maprockl->GetComponent<Transform>()->GetPos().x + 60
					&& maprockl->mOn == false) // 캐릭터가 왼쪽
				{
					float x = mypos.x + 82.5;
					while (x > maprockl->GetComponent<Transform>()->GetPos().x && maprockl->mOn == false)
					{
						mypos.x -= 1;
						x -= 1;
						mytr->SetPos(mypos);
					}
				}
			}
		}

		if (other->GetOwner() == movter)
		{
			if (movter->mUpDown == true)
			{
				mypos.y -= 100.0f * Time::DeltaTime();
				mytr->SetPos(mypos);
			}
			else
			{
   				Vector2 moveterpos = movter->GetComponent<Collider>()->GetPos();
				mytr->SetPos(Vector2(mypos.x, moveterpos.y - 100));
			}
		}

		if (other->GetOwner() == logp)
		{
			Vector2 logppos = logp->GetComponent<Collider>()->GetPos();
			mytr->SetPos(Vector2(mypos.x, logppos.y - 100));
		}

		if (other->GetOwner() == item)
		{
			//mSonicVelocity.x = 0;
			//mRigidbody->SetVelocity(mSonicVelocity);

			if (mypos.x + 100 > item->GetComponent<Transform>()->GetPos().x + 70) // 내가 오른쪽
			{
				mypos.x += 3;
				mytr->SetPos(mypos);
			}
			if (mypos.x + 20 < item->GetComponent<Transform>()->GetPos().x) // 내가 왼쪽
			{
				mypos.x -= 3;
				mytr->SetPos(mypos);
			}
		}
	}
	void Sonic::OnCollisionExit(Collider* other)
	{
		MapRock_l* maprockl = dynamic_cast<MapRock_l*>(other->GetOwner());
		MovingTerrain* movter = dynamic_cast<MovingTerrain*>(other->GetOwner());
		Logplatform* logp = dynamic_cast<Logplatform*>(other->GetOwner());
		Ground* ground = dynamic_cast<Ground*>(other->GetOwner());
		Rope* rope = dynamic_cast<Rope*>(other->GetOwner());
		Spring* spring = dynamic_cast<Spring*>(other->GetOwner());
		Breakingterrain* bterr = dynamic_cast<Breakingterrain*>(other->GetOwner());

		Transform* mytr = GetComponent<Transform>();
		Vector2 mypos = mytr->GetPos();
		Vector2 myvel = mRigidbody->GetVelocity();


		if (other->GetOwner() == movter
			|| other->GetOwner() == maprockl
			|| other->GetOwner() == ground
			|| other->GetOwner() == bterr
			|| other->GetOwner() == logp)
		{
			mRigidbody->SetGround(false);
		}
		//if (other->GetOwner() == rope)
		//{
		//		mRigidbody->SetGround(false);
		//		other->GetOwner()->mUse = false;
		//}

		if (other->GetOwner() == spring)
		{
			if ((spring->GetState() == Spring::eSpringState::up_norm
				|| spring->GetState() == Spring::eSpringState::up_use)
				&& mSonicState != eSonicState::rolling_left
				&& mSonicState != eSonicState::rolling_right)
			{
				mRigidbody->SetGround(false);
				mSonicVelocity.y = -1050;
				mRigidbody->SetVelocity(mSonicVelocity);
				mRigidbody->SetGround(false);
				mSonicState = eSonicState::spring_up;
			}
			else if (spring->GetState() == Spring::eSpringState::right_norm
				|| spring->GetState() == Spring::eSpringState::right_use)
			{
				mSonicVelocity.x = -1000.0f;
				mSonicState = eSonicState::run_left;
				mRigidbody->SetVelocity(mSonicVelocity);
			}
		}

	}

	void Sonic::SonicReset()
	{
		Transform* Tr = GetComponent<Transform>();
		Tr->SetPos(mResetPos);
		
		mTime = 0.0f;
		mRigidbody->SetMass(0.3);
		mRigidbody->SetFriction(250);
		mLimitVel = 800.0f;
		mSonicState = eSonicState::idle_right;

		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Monster, true);
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::hideMonster, true);
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::RMonster, true);
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Boss, true);
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Ring, true);
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::hideObjects, true);
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::MapObjects, true);
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Item, true);
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Ground, true);
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::mEffect, true);
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Bullet, true);

		Camera::SetTarget(this);

	}

	void Sonic::idle_left()
	{
		mR = false;
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();
		mAnimator->Play(L"Sonic_idle_left", true);
		mCollider->SetSize(Vector2(45.0f, 93.75f));
		mCollider->SetCenter(Vector2(40.0f, 30.0f));
		mRigidbody->SetVelocity(Vector2(mSonicVelocity.x * 0.9f, mSonicVelocity.y));

		mTime += Time::DeltaTime();
		if (mTime >= 5.0f)
		{
			mAnimator->Play(L"Sonic_idle_bored", false);
			if (mAnimator->IsComplete())
			{
				mAnimator->Reset();
				mTime = 0.0f;
			}
		}
		if ((Input::GetKeyDown(eKeyCode::Left)
			|| Input::GetKey(eKeyCode::Left)))
		{
			mSonicState = eSonicState::walk_left;
		}
		if ((Input::GetKeyDown(eKeyCode::Right)
			|| Input::GetKey(eKeyCode::Right)))
		{
			mSonicState = eSonicState::walk_right;
		}
		if (Input::GetKeyDown(eKeyCode::Up))
		{
			mSonicState = eSonicState::lookup_left;
		}
		if (Input::GetKeyDown(eKeyCode::Down))
		{
			mSonicState = eSonicState::crouch_left;
		}
		if (Input::GetKeyDown(eKeyCode::Space))
		{
			sJump->Play(false);
			mSonicVelocity.y -= 650.0f;
			mRigidbody->SetVelocity(mSonicVelocity);
			mRigidbody->SetGround(false);
			mSonicState = eSonicState::jump_left;
		}
		tr->SetPos(pos);

	}
	void Sonic::idle_right()
	{
		mR = false;
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();

		mAnimator->Play(L"Sonic_idle_right", true);
		mCollider->SetSize(Vector2(40.0f, 93.75f));
		mCollider->SetCenter(Vector2(45.0f, 30.0f));
		mRigidbody->SetVelocity(Vector2(mSonicVelocity.x * 0.9f, mSonicVelocity.y));

		mTime += Time::DeltaTime();
		if (mTime >= 5.0f)
		{
			mAnimator->Play(L"Sonic_idle_bored", false);
			if (mAnimator->IsComplete())
			{
				mAnimator->Reset();
				mTime = 0.0f;
			}
		}
		if ((Input::GetKeyDown(eKeyCode::Left)
			|| Input::GetKey(eKeyCode::Left)))
		{
			mSonicState = eSonicState::walk_left;
		}
		if ((Input::GetKeyDown(eKeyCode::Right)
			|| Input::GetKey(eKeyCode::Right)))
		{
			mSonicState = eSonicState::walk_right;
		}
		if (Input::GetKeyDown(eKeyCode::Up))
		{
			mSonicState = eSonicState::lookup_right;
		}
		if (Input::GetKeyDown(eKeyCode::Down))
		{
			mSonicState = eSonicState::crouch_right;
		}
		if (Input::GetKeyDown(eKeyCode::Space))
		{
			sJump->Play(false);
			mSonicVelocity.y -= 650.0f;
			mRigidbody->SetVelocity(mSonicVelocity);
			mRigidbody->SetGround(false);
			mSonicState = eSonicState::jump_right;
		}
		tr->SetPos(pos);
	}
	void Sonic::walk_left()
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();

		mAnimator->Play(L"Sonic_walk_left", true);
		mCollider->SetSize(Vector2(55.0f, 93.75f));
		mCollider->SetCenter(Vector2(40.0f, 30.0f));

		if (Input::GetKeyUp(eKeyCode::Left))
		{
			mSonicState = eSonicState::idle_left;
		}
		if (Input::GetKeyDown(eKeyCode::Right))
		{
			mRigidbody->SetVelocity(Vector2(mSonicVelocity.x * 0.005, mSonicVelocity.y));
			mSonicState = eSonicState::walk_right;
		}
		if (Input::GetKey(eKeyCode::Left)
			&& mRigidbody->GetGround() == true)
		{
			float vellength = mSonicVelocity.Length();
			mRigidbody->SetVelocity(Vector2(mSonicVelocity.x, ground->GetFrontPos().y * vellength));
			mRigidbody->AddForce(Vector2(-100.0f, 0.0f));
			if (mRigidbody->GetVelocity().x <= -400.0f)
			{
				mSonicState = eSonicState::run_left;
			}
		}

		if (Input::GetKey(eKeyCode::Left)
			&& mRigidbody->GetGround() == false)
		{
			mRigidbody->AddForce(Vector2(-100.0f, 0.0f));
		}

		if (Input::GetKeyDown(eKeyCode::Space))
		{
			sJump->Play(false);
			mSonicVelocity.y -= 650.0f;
			mRigidbody->SetVelocity(mSonicVelocity);
			mRigidbody->SetGround(false);
			mSonicState = eSonicState::jump_left;
		}
		tr->SetPos(pos);

	}
	void Sonic::walk_right()
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();

		mAnimator->Play(L"Sonic_walk_right", true);
		mCollider->SetSize(Vector2(55.0f, 93.75f));
		mCollider->SetCenter(Vector2(45.0f, 30.0f));

		if (Input::GetKeyUp(eKeyCode::Right))
		{
			mSonicState = eSonicState::idle_right;
		}
		if (Input::GetKeyDown(eKeyCode::Left))
		{
			mRigidbody->SetVelocity(Vector2(mSonicVelocity.x * 0.005, mSonicVelocity.y));
			mSonicState = eSonicState::walk_left;
		}


		if (Input::GetKey(eKeyCode::Right)
			&& mRigidbody->GetGround() == true)
		{
			if (mRigidbody->GetGrabity() == Vector2(0, 800))
			{
				float vellength = mSonicVelocity.Length();
				mRigidbody->SetVelocity(Vector2(mSonicVelocity.x, ground->GetFrontPos().y * vellength));
				mRigidbody->AddForce(Vector2(100.0f, 0.0f));
			}
			else if (mRigidbody->GetGrabity() == Vector2(0, -1))
			{
				float vellength = mSonicVelocity.Length();
				mRigidbody->SetVelocity(Vector2(mSonicVelocity.x, ground->GetFrontPos().y * vellength));
				mRigidbody->AddForce(Vector2(100.0f, 0.0f));
			}

			if (mRigidbody->GetVelocity().x >= 400.0f)
			{
				mSonicState = eSonicState::run_right;
			}

		}

		if (Input::GetKey(eKeyCode::Right)
			&& mRigidbody->GetGround() == false)
		{
			mRigidbody->AddForce(Vector2(100.0f, 0.0f));
		}
		if (Input::GetKeyDown(eKeyCode::Space))
		{
			sJump->Play(false);
			float jumpvel = -650;
			mRigidbody->SetVelocity(Vector2(mSonicVelocity.x, jumpvel));
			mRigidbody->SetGround(false);
			mSonicState = eSonicState::jump_right;
		}
		tr->SetPos(pos);

	}
	void Sonic::run_left()
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();

		mAnimator->Play(L"Sonic_run_left", true);
		mCollider->SetSize(Vector2(60.f, 93.75f));
		mCollider->SetCenter(Vector2(40.0f, 30.0f));
		if (mRigidbody->GetVelocity().x < -mLimitVel)
		{
			mSonicVelocity.x = -mLimitVel;
			mRigidbody->SetVelocity(mSonicVelocity);
		}
		if (Input::GetKey(eKeyCode::Left)
			&& mRigidbody->GetGround() == true)
		{
			float vellength = mSonicVelocity.Length();
			mRigidbody->SetVelocity(Vector2(mSonicVelocity.x, ground->GetFrontPos().y * vellength));
			mRigidbody->AddForce(Vector2(-100.0f, 0.0f));
		}

		if (Input::GetKeyUp(eKeyCode::Left))
		{
			mSonicState = eSonicState::idle_left;
		}
		if (Input::GetKeyDown(eKeyCode::Right))
		{
			sSkid->Play(false);
			mSonicState = eSonicState::skid_left;
		}
		if (Input::GetKeyDown(eKeyCode::Space))
		{
			sJump->Play(false);
			float jumpvel = -650.0f;
			mRigidbody->SetVelocity(Vector2(mSonicVelocity.x, jumpvel));
			mRigidbody->SetGround(false);
			mSonicState = eSonicState::jump_left;
		}
		if (mRigidbody->GetVelocity().x >= -400.0f)
		{
			mSonicState = eSonicState::walk_left;
		}
		tr->SetPos(pos);

	}
	void Sonic::run_right()
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();

		mAnimator->Play(L"Sonic_run_right", true);
		mCollider->SetSize(Vector2(60.0f, 93.75f));
		mCollider->SetCenter(Vector2(45.0f, 30.0f));
		
		if (mRigidbody->GetVelocity().x > mLimitVel)
		{
			mSonicVelocity.x = mLimitVel;
			mRigidbody->SetVelocity(mSonicVelocity);
		}
		if (Input::GetKey(eKeyCode::Right)
			&& mRigidbody->GetGround() == true)
		{
			float vellength = mSonicVelocity.Length();
			mRigidbody->SetVelocity(Vector2(mSonicVelocity.x, ground->GetFrontPos().y * vellength));
			mRigidbody->AddForce(Vector2(100.0f, 0.0f));
		}
		if (Input::GetKeyUp(eKeyCode::Right))
		{
			mSonicState = eSonicState::idle_right;
		}
		if (Input::GetKeyDown(eKeyCode::Left))
		{
			sSkid->Play(false);
			mSonicState = eSonicState::skid_right;
		}
		if (Input::GetKeyDown(eKeyCode::Space))
		{
			sJump->Play(false);
			float jumpvel = -650.0f;
			mRigidbody->SetVelocity(Vector2(mSonicVelocity.x, jumpvel));
			mRigidbody->SetGround(false);
			mSonicState = eSonicState::jump_left;
		}
		if (mRigidbody->GetVelocity().x <= 400.0f)
		{
			mSonicState = eSonicState::walk_right;
		}
		tr->SetPos(pos);

	}
	void Sonic::jump_left()
	{
		mCollider->SetSize(Vector2(80, 80));
		mCollider->SetCenter(Vector2(25.0f, 50.0f));

		mAnimator->Play(L"Sonic_jump_left", true);
		if (Input::GetKeyDown(eKeyCode::Space)
			&& mFlame == true)
		{
			mAnimator->Play(L"Sonic_jump_left", true);
			sJump_flame->Play(false);
			mSonicVelocity.x = -700;
			mRigidbody->SetVelocity(mSonicVelocity);
			mSonicState = eSonicState::jump2_left;

		}
		else if (Input::GetKeyDown(eKeyCode::Space)
			&& mThunder == true)
		{
			mAnimator->Play(L"Sonic_jump_left", true);
			sJump_thunder->Play(false);
			mSonicVelocity.y -= 400;
			mRigidbody->SetVelocity(mSonicVelocity);
			mSonicState = eSonicState::jump2_left;

		}
		else if (Input::GetKeyDown(eKeyCode::Space)
			&& mWater == true)
		{
			sJump_water->Play(false);
			mSonicState = eSonicState::waterjump;
		}
		else if (Input::GetKeyDown(eKeyCode::Space))
		{
			sJump2->Play(false);
			mAnimator->Play(L"Sonic_jump2_left", false);
			mSonicState = eSonicState::jump2_right;
		}

		if (Input::GetKey(eKeyCode::Left))
		{
			mRigidbody->AddForce(Vector2(-100.0f, 0.0f));
		}
		if (Input::GetKey(eKeyCode::Right))
		{
			mRigidbody->AddForce(Vector2(100.0f, 0.0f));
			mSonicState = eSonicState::jump_right;
		}
		if (mRigidbody->GetGround() == true
			&& Input::GetKey(eKeyCode::Left))
		{
			mSonicState = eSonicState::walk_left;
		}
		if (mRigidbody->GetGround() == true
			&& Input::GetKey(eKeyCode::Right))
		{
			mSonicState = eSonicState::walk_right;
		}
		if (mRigidbody->GetGround() == true
			&& Input::GetKeyState(eKeyCode::Left) == eKeyState::None
			&& Input::GetKeyState(eKeyCode::Right) == eKeyState::None)
		{
			mSonicState = eSonicState::idle_left;
		}
		if (mRigidbody->GetGround() == true
			&& (Input::GetKey(eKeyCode::Down)
			|| Input::GetKeyDown(eKeyCode::Down)))
		{
			mSonicState = eSonicState::crouch_left;
		}

	}
	void Sonic::jump_right()
	{
		mCollider->SetSize(Vector2(80, 80));
		mCollider->SetCenter(Vector2(25.0f, 50.0f));
		mAnimator->Play(L"Sonic_jump_right", true);

		if (Input::GetKeyDown(eKeyCode::Space)
			&& mFlame == true)
		{
			mAnimator->Play(L"Sonic_jump_right", true);
			sJump_flame->Play(false);
			mSonicVelocity.x = 700;
			mRigidbody->SetVelocity(mSonicVelocity);
			mSonicState = eSonicState::jump2_right;
		}
		else if (Input::GetKeyDown(eKeyCode::Space)
			&& mThunder == true)
		{
			mAnimator->Play(L"Sonic_jump_right", true);
			sJump_thunder->Play(false);
			mSonicVelocity.y -= 400;
			mRigidbody->SetVelocity(mSonicVelocity);
			mSonicState = eSonicState::jump2_right;
		}
		else if (Input::GetKeyDown(eKeyCode::Space)
			&& mWater == true)
		{
			sJump_water->Play(false);
			mSonicState = eSonicState::waterjump;
		}
		else if (Input::GetKeyDown(eKeyCode::Space))
		{
			sJump2->Play(false);
			mAnimator->Play(L"Sonic_jump2_right", false);
			mSonicState = eSonicState::jump2_right;
		}

		if (Input::GetKey(eKeyCode::Left))
		{
			mRigidbody->AddForce(Vector2(-100.0f, 0.0f));
			mSonicState = eSonicState::jump_left;
		}
		if (Input::GetKey(eKeyCode::Right))
		{
			mRigidbody->AddForce(Vector2(100.0f, 0.0f));
		}
		if (mRigidbody->GetGround() == true
			&& Input::GetKey(eKeyCode::Left))
		{
			mSonicState = eSonicState::walk_left;
		}
		if (mRigidbody->GetGround() == true
			&& Input::GetKey(eKeyCode::Right))
		{
			mSonicState = eSonicState::walk_right;
		}
		if (mRigidbody->GetGround() == true
			&& Input::GetKeyState(eKeyCode::Left) == eKeyState::None
			&& Input::GetKeyState(eKeyCode::Right) == eKeyState::None)
		{
			mSonicState = eSonicState::idle_right;
		}
		if (mRigidbody->GetGround() == true
			&& (Input::GetKey(eKeyCode::Down)
			|| Input::GetKeyDown(eKeyCode::Down)))
		{
			mSonicState = eSonicState::crouch_right;
		}
	}
	void Sonic::jump2_left()
	{
		if (mAnimator->IsComplete())
		{
			mAnimator->Reset();
			mAnimator->Play(L"Sonic_jump_left", true);
		}
		if (Input::GetKey(eKeyCode::Left))
		{
			mRigidbody->AddForce(Vector2(-100.0f, 0.0f));
		}
		if (Input::GetKey(eKeyCode::Right))
		{
			mRigidbody->AddForce(Vector2(100.0f, 0.0f));
		}
		if (mRigidbody->GetGround() == true
			&& Input::GetKey(eKeyCode::Left))
		{
			mSonicState = eSonicState::walk_left;
		}
		if (mRigidbody->GetGround() == true
			&& Input::GetKey(eKeyCode::Right))
		{
			mSonicState = eSonicState::walk_right;
		}
		if (mRigidbody->GetGround() == true)
		{
			mSonicState = eSonicState::idle_left;
		}
	}
	void Sonic::jump2_right()
	{
		if (mAnimator->IsComplete())
		{	
			mAnimator->Reset();
			mAnimator->Play(L"Sonic_jump_right", true);
		}
		if (Input::GetKey(eKeyCode::Left))
		{
			mRigidbody->AddForce(Vector2(-100.0f, 0.0f));
		}
		if (Input::GetKey(eKeyCode::Right))
		{
			mRigidbody->AddForce(Vector2(100.0f, 0.0f));
		}
		if (mRigidbody->GetGround() == true
			&& Input::GetKey(eKeyCode::Left))
		{
			mSonicState = eSonicState::walk_left;
		}
		if (mRigidbody->GetGround() == true
			&& Input::GetKey(eKeyCode::Right))
		{
			mSonicState = eSonicState::walk_right;
		}
		if (mRigidbody->GetGround() == true)
		{
			mSonicState = eSonicState::idle_right;
		}
	}
	void Sonic::spindash_left()
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();
		mCollider->SetSize(Vector2(70, 65));
		mCollider->SetCenter(Vector2(0.0f, 60.0f));
		mRigidbody->SetVelocity(Vector2::Zero);
		mAnimator->Play(L"Sonic_spindash_left", true);

		if (Input::GetKeyDown(eKeyCode::Space))
		{
			sSpin->Play(false);
			mAnimator->Play(L"Sonic_spindash_left", true);
		}
		if (Input::GetKeyUp(eKeyCode::Down))
		{
			float vellength = mSonicVelocity.Length();
			mRigidbody->SetVelocity(Vector2(-1000.0f, 0.0f) + (ground->GetFrontPos() * vellength * 0.2f));
			mSonicState = eSonicState::rolling_left;
		}
		tr->SetPos(pos);
	}
	void Sonic::spindash_right()
  	{
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();
		mCollider->SetSize(Vector2(70, 65));
		mCollider->SetCenter(Vector2(65.0f, 60.0f));
		mRigidbody->SetVelocity(Vector2::Zero);
		mAnimator->Play(L"Sonic_spindash_right", true);
 		if (Input::GetKeyDown(eKeyCode::Space))
		{
			sSpin->Play(false);
			mAnimator->Play(L"Sonic_spindash_right", true);
		}
		if (Input::GetKeyUp(eKeyCode::Down))
		{
			float vellength = mSonicVelocity.Length();
			mRigidbody->SetVelocity(Vector2(1000.0f, 0.0f) + (ground->GetFrontPos() * vellength * 0.2f));
			mSonicState = eSonicState::rolling_right;
		}
		tr->SetPos(pos);
	}
	void Sonic::rolling_left()
	{
		mAnimator->Play(L"Sonic_jump_left", true);
		mCollider->SetSize(Vector2(80, 80));
		mCollider->SetCenter(Vector2(25.0f, 50.0f));
		mSonicVelocity.x += 1;
		mRigidbody->SetVelocity(mSonicVelocity);
		if (Input::GetKeyDown(eKeyCode::Space))
		{
			sJump->Play(false);
			mSonicVelocity.y -= 650.0f;
			mRigidbody->SetVelocity(mSonicVelocity);
			mRigidbody->SetGround(false);
			mSonicState = eSonicState::jump_left;
		}
		if (Input::GetKey(eKeyCode::Right)
			&& mRigidbody->GetGround() == true)
		{
			mSonicVelocity.x = 0.7 * mSonicVelocity.x;
			mRigidbody->SetVelocity(mSonicVelocity);
		}
			if (mRigidbody->GetVelocity().x >= 80.0f)
				mSonicState = eSonicState::idle_left;

		if (mRigidbody->GetGround() == false)
		{
			if (Input::GetKey(eKeyCode::Left))
			{
				mRigidbody->AddForce(Vector2(-50.0f, 0.0f));
			}
			else if (Input::GetKey(eKeyCode::Right))
			{
				mRigidbody->AddForce(Vector2(50.0f, 0.0f));
			}
		}

	}
	void Sonic::rolling_right()
	{

		mCollider->SetSize(Vector2(80, 80));
		mCollider->SetCenter(Vector2(25.0f, 50.0f));
		mSonicVelocity.x -= 5;
		mRigidbody->SetVelocity(mSonicVelocity);
		mAnimator->Play(L"Sonic_jump_right", true);
		if (Input::GetKeyDown(eKeyCode::Space))
		{
			sJump->Play(false);
			mSonicVelocity.y -= 650.0f;
			mRigidbody->SetVelocity(mSonicVelocity);
			mRigidbody->SetGround(false);
			mSonicState = eSonicState::jump_right;
		}
		if (Input::GetKey(eKeyCode::Left)
			&& mRigidbody->GetGround() == true)
		{
			mSonicVelocity.x = 0.7 * mSonicVelocity.x;
			mRigidbody->SetVelocity(mSonicVelocity);
		}
		if(mRigidbody->GetVelocity().x <= 80.0f)
			mSonicState = eSonicState::idle_right;

		if (mRigidbody->GetGround() == false)
		{
			if (Input::GetKey(eKeyCode::Left))
			{
				mRigidbody->AddForce(Vector2(-50.0f, 0.0f));
			}
			else if (Input::GetKey(eKeyCode::Right))
			{
				mRigidbody->AddForce(Vector2(50.0f, 0.0f));
			}
		}

	}
	void Sonic::skid_left()
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();
		mCollider->SetSize(Vector2(60.f, 93.75f));
		mCollider->SetCenter(Vector2(40.0f, 30.0f));

		mAnimator->Play(L"Sonic_skid_right", false);
		mSonicVelocity = mRigidbody->GetVelocity();
		mRigidbody->SetVelocity(Vector2(mSonicVelocity.x * 0.005, mSonicVelocity.y));

		if (Input::GetKey(eKeyCode::Right)
			&& mAnimator->IsComplete())
		{
			mSonicState = eSonicState::walk_right;
		}
		if (Input::GetKey(eKeyCode::Left)\
			&& mAnimator->IsComplete())
		{
			mSonicState = eSonicState::walk_left;
		}
		if (Input::GetKeyDown(eKeyCode::Space))
		{
			sJump->Play(false);
			mSonicVelocity = mRigidbody->GetVelocity();
			mSonicVelocity.y -= 650.0f;

			mRigidbody->SetVelocity(mSonicVelocity);
			mRigidbody->SetGround(false);
			mSonicState = eSonicState::jump_left;
		}
		if (mAnimator->IsComplete())
		{
			mAnimator->Reset();
			mSonicState = eSonicState::idle_left;
		}
		tr->SetPos(pos);
	}
	void Sonic::skid_right()
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();
		mCollider->SetSize(Vector2(60.f, 93.75f));
		mCollider->SetCenter(Vector2(45.0f, 30.0f));

		mAnimator->Play(L"Sonic_skid_left", false);
	
		mSonicVelocity = mRigidbody->GetVelocity();
		mRigidbody->SetVelocity(Vector2(mSonicVelocity.x * 0.005, mSonicVelocity.y));

		if (Input::GetKey(eKeyCode::Left)
			&& mAnimator->IsComplete())
		{
			mSonicState = eSonicState::walk_left;
		}
		if (Input::GetKey(eKeyCode::Right)
			&& mAnimator->IsComplete())
		{
			mSonicState = eSonicState::walk_right;
		}
		if (Input::GetKeyDown(eKeyCode::Space))
		{
			sJump->Play(false);
			Vector2 velocity = mRigidbody->GetVelocity();
			velocity.y -= 650.0f;

			mRigidbody->SetVelocity(velocity);
			mRigidbody->SetGround(false);
			mSonicState = eSonicState::jump_right;
		}
		if (mAnimator->IsComplete())
		{
			mAnimator->Reset();
			mSonicState = eSonicState::idle_right;
		}
		tr->SetPos(pos);
	}
	void Sonic::hurt_left()
	{
		mAnimator->Play(L"Sonic_hurt_left", false);
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();

		if ((mFlame || mThunder || mWater) && mbHurt == false)
		{
			sHurt->Play(false);
			mFlame = false;
			mThunder = false;
			mWater = false;
			mbHurt = true;
			mEffect->SetEffectState(Effect::eEffectState::None);
		}
		else if (mAbility <= 0 && mFlame == false && mThunder == false && mWater == false && mR == false && mbHurt == false)
		{
			sDeath->Play(false);
			mSonicState = eSonicState::death;
			mbHurt = true;
		}
		else if (mAbility > 0 && mFlame == false && mThunder == false && mWater == false && mR == false && mbHurt == false)
		{
			sHurt->Play(false);
			sLosering->Play(false);
			std::random_device rd;
			std::mt19937 gen(rd());
			std::uniform_real_distribution<float> x_distribution(50.0f, 80.0f);
			std::uniform_real_distribution<float> y_distribution(-100.0f, -50.0f);
			std::uniform_real_distribution<float> spredx_distribution(-500.0f, 500.0f);
			std::uniform_real_distribution<float> spredy_distribution(-500.0f, 0.0f);

			Transform* tr = GetComponent<Transform>();
			Vector2 spos = tr->GetPos();
			Vector2 genrings;
			Vector2 spreadrings;
			for (int i = 0; i < mRings; i++)
			{
				genrings.x = x_distribution(gen);
				genrings.y = y_distribution(gen);
				spreadrings.x = spredx_distribution(gen);
				spreadrings.y = spredy_distribution(gen);

				Ring* ring = object::Instantiate<Ring>(genrings + spos, eLayerType::Ring, eSceneType::Play);
				Rigidbody* ringrigid = ring->AddComponent<Rigidbody>();
				ringrigid->SetMass(1.0f);
				ringrigid->SetVelocity(spreadrings);
				ringrigid->SetGround(false);
				ring->SetRingState(Ring::eRingState::rigid);
			}
			mRings = 0;
			mR = true;
			mbHurt = true;
		}

		if (mAnimator->IsComplete() == false)
		{
			mRigidbody->SetGround(false);
			mSonicVelocity.y = -200.0f;
			mSonicVelocity.x = 300.0f;
			mRigidbody->SetVelocity(mSonicVelocity);
			mRigidbody->SetGround(false);

		}
		if (mAnimator->IsComplete())
		{
			mAnimator->Reset();
			mSonicState = eSonicState::idle_left;
		}
		tr->SetPos(pos);
	}
	void Sonic::hurt_right()
	{
		mAnimator->Play(L"Sonic_hurt_right", false);
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();
		if ((mFlame || mThunder || mWater) && mbHurt == false)
		{
			sHurt->Play(false);
			mFlame = false;
			mThunder = false;
			mWater = false;
			mbHurt = true;
			mEffect->SetEffectState(Effect::eEffectState::None);
		}
		else if (mAbility == 0 && mFlame == false && mThunder == false && mWater == false && mR == false && mbHurt == false)
		{
			sDeath->Play(false);
			mSonicState = eSonicState::death;
			mbHurt = true;
		}

		else if (mAbility > 0 && mFlame == false && mThunder == false && mWater == false && mR == false && mbHurt == false)
		{
			sLosering->Play(false);
			std::random_device rd;
			std::mt19937 gen(rd());
			std::uniform_real_distribution<float> x_distribution(50.0f, 80.0f);
			std::uniform_real_distribution<float> y_distribution(-100.0f, -50.0f);
			std::uniform_real_distribution<float> spredx_distribution(-500.0f, 500.0f);
			std::uniform_real_distribution<float> spredy_distribution(-500.0f, 0.0f);

			Transform* tr = GetComponent<Transform>();
			Vector2 spos = tr->GetPos();
			Vector2 genrings;
			Vector2 spreadrings;
			for (int i = 0; i < mRings; i++)
			{
				genrings.x = x_distribution(gen);
				genrings.y = y_distribution(gen);
				spreadrings.x = spredx_distribution(gen);
				spreadrings.y = spredy_distribution(gen);

				Ring* ring = object::Instantiate<Ring>(genrings + spos, eLayerType::Ring, SceneManager::GetActiveScene2());
				Rigidbody* ringrigid = ring->AddComponent<Rigidbody>();
				ringrigid->SetMass(1.0f);
				ringrigid->SetVelocity(spreadrings);
				ringrigid->SetGround(false);
				ring->SetRingState(Ring::eRingState::rigid);
			}
			mRings = 0;
			mR = true;
			mbHurt = true;
		}

		if (mAnimator->IsComplete() == false)
		{
			mRigidbody->SetGround(false);
			mSonicVelocity.y = -200.0f;
			mSonicVelocity.x = -300.0f;
			mRigidbody->SetVelocity(mSonicVelocity);
			mRigidbody->SetGround(false);
		}
		if (mAnimator->IsComplete())
		{
			mAnimator->Reset();
			mSonicState = eSonicState::idle_right;
		}
	}
	void Sonic::death()
	{
		Transform* Tr = GetComponent<Transform>();

		mResetPos = Tr->GetPos();

		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Monster, false);
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::hideMonster, false);
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::RMonster, false);
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Boss, false);
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Ring, false);
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::hideObjects, false);
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::MapObjects, false);
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Item, false);
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Ground, false);
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::mEffect, false);
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Bullet, false);
		mbHurt = true;
		mAnimator->Play(L"Sonic_death", false);
		mCollider->SetSize(Vector2::Zero);
		if (mAnimator->IsComplete() == false)
		{
			Camera::SetTarget(nullptr);
			mSonicVelocity.y -= 130.0f;
			mSonicVelocity.x = 0.0;
			mRigidbody->SetVelocity(mSonicVelocity);
			mRigidbody->SetGround(false);
		}
		mTime += Time::DeltaTime();
		if (mLife > 0 && mTime > 3.0f)
		{
			mLife--;
			mTime = 0.0f;
			Sonic::SonicReset();
		};
	}
	void Sonic::hang_left()
	{
		mAnimator->Play(L"Sonic_hang_left", true);
		mCollider->SetCenter(Vector2(40, 0));
		mCollider->SetSize(Vector2(45, 93.5));

		if (Input::GetKeyDown(eKeyCode::Space))
		{
			sJump->Play(false);

			mSonicVelocity.y -= 650.0f;
			mRigidbody->SetVelocity(mSonicVelocity);
			mRigidbody->SetGround(false);
			mSonicState = eSonicState::jump_left;
		}
		if (Input::GetKey(eKeyCode::Left)
			&& Input::GetKeyDown(eKeyCode::Space))
		{
			sJump->Play(false);
			mSonicVelocity.y -= 650.0f;
			mSonicVelocity.x -= 200.0f;
			mRigidbody->SetVelocity(mSonicVelocity);
			mRigidbody->SetGround(false);
			mSonicState = eSonicState::jump_left;
		}

		if (Input::GetKeyDown(eKeyCode::Right))
		{
			mSonicState = eSonicState::hang_right;
		}

	}
	void Sonic::hang_right()
	{
		mAnimator->Play(L"Sonic_hang_right", true);
		mCollider->SetCenter(Vector2(40, 0));
		mCollider->SetSize(Vector2(45, 93.5));
		
		if (Input::GetKeyDown(eKeyCode::Space))
		{
			sJump->Play(false);
			mSonicVelocity.y -= 650.0f;
			mRigidbody->SetVelocity(mSonicVelocity);
			mRigidbody->SetGround(false);
			mSonicState = eSonicState::jump_right;
		}

		if (Input::GetKey(eKeyCode::Right)
			&& Input::GetKeyDown(eKeyCode::Space))
		{
			sJump->Play(false);
			mSonicVelocity.y -= 650.0f;
			mSonicVelocity.x += 200.0f;
			mRigidbody->SetVelocity(mSonicVelocity);
			mRigidbody->SetGround(false);
			mSonicState = eSonicState::jump_left;
		}
		if (Input::GetKeyDown(eKeyCode::Left))
		{
			mSonicState = eSonicState::hang_left;
		}
	}
	void Sonic::spring_up()
	{
		mAnimator->Play(L"Sonic_spring_up", false);

		if (Input::GetKey(eKeyCode::Left))
		{
			mRigidbody->AddVelocity(Vector2(-30.0f, 0.0f));
		}
		if (Input::GetKey(eKeyCode::Right))
		{
			mRigidbody->AddVelocity(Vector2(30.0f, 0.0f));
		}
		if (mAnimator->IsComplete())
		{
			mSonicState = eSonicState::walk_right;
			mAnimator->Reset(); 
		}
		if (mRigidbody->GetGround() == true)
		{
			mSonicState = eSonicState::idle_right;
			mAnimator->Reset();
		}
	}
	void Sonic::waterjump()
	{
		mAnimator->Play(L"Sonic_jump_right", true);

		if (mRigidbody->GetGround() == false && mWaterJump == false && mWater)
		{
			mSonicVelocity.y += 800;
			mRigidbody->SetVelocity(mSonicVelocity);
			mWaterJump = true;
		}
		else if (Input::GetKeyDown(eKeyCode::Space)
			&& mWater)
		{
			mSonicVelocity.y += 800;
			mRigidbody->SetVelocity(mSonicVelocity);
			mSonicState = eSonicState::jump_right;
			mWaterJump = true;
		}
		if (mWaterJump == true && mRigidbody->GetGround() == true && mWater)
		{
			mWaterJump = false;
			mSonicState = eSonicState::idle_right;
		}
		if (Input::GetKey(eKeyCode::Right)
			|| Input::GetKeyDown(eKeyCode::Right)
			&& mWater)
		{
			mWaterJump = false;
			mRigidbody->AddVelocity(Vector2(50.0f, 0.0f));
			mSonicState = eSonicState::walk_right;
		}
		else if (Input::GetKey(eKeyCode::Left)
			|| Input::GetKeyDown(eKeyCode::Left)
			&& mWater)
		{
			mWaterJump = false;
			mRigidbody->AddVelocity(Vector2(-50.0f, 0.0f));
			mSonicState = eSonicState::walk_left;
		}

	}
	void Sonic::falldown()
	{
		mAnimator->Play(L"Sonic_fall_down", true);
	}
	void Sonic::crouch_left()
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();

		mAnimator->Play(L"Sonic_crouch_left", false);
		mCollider->SetSize(Vector2(60, 60));
		mCollider->SetCenter(Vector2(20.0f, 60.0f));
		if (Input::GetKeyUp(eKeyCode::Down))
		{
			mAnimator->Reset();
			mSonicState = eSonicState::idle_left;
		}
		if (Input::GetKeyDown(eKeyCode::Space))
		{
			sSpin->Play(false);
			mAnimator->Reset();
			mSonicState = eSonicState::spindash_left;
		}
		tr->SetPos(pos);
	}
	void Sonic::crouch_right()
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();

		mAnimator->Play(L"Sonic_crouch_right", false);
		mCollider->SetSize(Vector2(60, 60));
		mCollider->SetCenter(Vector2(55.0f, 60.0f));
		if (Input::GetKeyUp(eKeyCode::Down))
		{
			mAnimator->Reset();
			mSonicState = eSonicState::idle_right;
		}
		if (Input::GetKeyDown(eKeyCode::Space))
		{
			sSpin->Play(false);
			mAnimator->Reset();
			mSonicState = eSonicState::spindash_right;
		}
		tr->SetPos(pos);
	}
	void Sonic::lookup_left()
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();

		mAnimator->Play(L"Sonic_lookup_left", false);
		mCollider->SetSize(Vector2(45.f, 93.75f));
		mCollider->SetCenter(Vector2(45.0f, 30.0f));

		if (Input::GetKeyUp(eKeyCode::Up))
		{
			mAnimator->Reset();
			mSonicState = eSonicState::idle_left;
		}
		if (Input::GetKeyDown(eKeyCode::Space))
		{
			sJump->Play(false);
			mAnimator->Reset();
			mSonicVelocity.y -= 650.0f;
			mRigidbody->SetVelocity(mSonicVelocity);
			mRigidbody->SetGround(false);
			mSonicState = eSonicState::jump_left;
		}
		tr->SetPos(pos);
	}
	void Sonic::lookup_right()
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();

		mAnimator->Play(L"Sonic_lookup_right", false);
	
		mCollider->SetSize(Vector2(45.f, 93.75f));
		mCollider->SetCenter(Vector2(40.0f, 30.0f));

		if (Input::GetKeyUp(eKeyCode::Up))
		{
			mAnimator->Reset();
			mSonicState = eSonicState::idle_right;
		}
		if (Input::GetKeyDown(eKeyCode::Space))
		{
			sJump->Play(false);
			mAnimator->Reset();
			mSonicVelocity.y -= 650.0f;
			mRigidbody->SetVelocity(mSonicVelocity);
			mRigidbody->SetGround(false);
			mSonicState = eSonicState::jump_right;
		}
		tr->SetPos(pos);
	}

}
