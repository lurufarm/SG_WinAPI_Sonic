#include "sgPlayScene2.h"
#include "sgSonic.h"
#include "sgKnuckles.h"
#include "sgForeground2.h"
#include "sgBackground2.h"
#include "sgMapObjects2.h"
#include "sgMapDeco5.h"
#include "sgScenechange.h"
#include "sgGround2.h"
#include "sgPlayUI.h"

#include "sgBomber.h";
#include "sgLastboss.h"
#include "sgLastbossR.h"
#include "sgRhinobot.h"
#include "sgBloominator.h"
#include "sgCaterkiller.h"

#include "sgRedcard.h"
#include "sgAct1.h"
#include "sgZone1.h"

#include "sgLogbridge.h"
#include "sgLogplatform.h"
#include "sgMovingTerrain.h"
#include "sgBreakingterrain.h"
#include "sgSpring.h"
#include "sgButton.h"
#include "sgWater.h"

#include "sgTime.h"
#include "sgObject.h"
#include "sgInput.h"
#include "sgImage.h"
#include "sgResources.h"
#include "sgCamera.h"
#include "sgApplication.h"
#include "sgSound.h"

#include "sgSceneManager.h"
#include "sgCollisionManager.h"
#include "sgTransform.h"
#include "sgRigidbody.h"


sg::Sonic* mSonic2;
extern sg::Application application;

namespace sg
{
	PlayScene2::PlayScene2()
		: mTime(0.0f)
		, mLBr(nullptr)
		, mKnuc(false)
	{
	}
	PlayScene2::~PlayScene2()
	{
	}
	void PlayScene2::Initialize()
	{
		mSonic2 = object::Instantiate<Sonic>(Vector2(300.0f, 1600.0f), eLayerType::Player, eSceneType::Play2);
		//Camera::SetTarget(mSonic2);
		mBG = Resources::Load<Sound>(L"PlayTheme2", L"..\\Resources\\sound\\music\\act2bg.wav");

		Background2* bg2_3 = object::Instantiate<Background2>(eLayerType::BG, eSceneType::Play2);
		Background2* bg2_1 = object::Instantiate<Background2>(eLayerType::BG, eSceneType::Play2);
		Background2* bg2_3_2 = object::Instantiate<Background2>(eLayerType::BG, eSceneType::Play2);
		Background2* bg2_2 = object::Instantiate<Background2>(eLayerType::BG, eSceneType::Play2);
		bg2_3->SetBG(Background2::eBGState::bg3, Vector2(-1000.0f,0.0f));
		bg2_1->SetBG(Background2::eBGState::bg1, Vector2(-1000.0f,140.0f));
		bg2_3_2->SetBG(Background2::eBGState::bg3, Vector2(-1000.0f, 1080.0f));
		bg2_2->SetBG(Background2::eBGState::bg2, Vector2(-1000.0f,1220.0f));
		Background2* bg2_3_3 = object::Instantiate<Background2>(eLayerType::BG, eSceneType::Play2);
		Background2* bg2_1_2 = object::Instantiate<Background2>(eLayerType::BG, eSceneType::Play2);
		Background2* bg2_3_4 = object::Instantiate<Background2>(eLayerType::BG, eSceneType::Play2);
		Background2* bg2_2_2 = object::Instantiate<Background2>(eLayerType::BG, eSceneType::Play2);
		bg2_3_3->SetBG(Background2::eBGState::bg3, Vector2(280.0f, 0.0f));
		bg2_1_2->SetBG(Background2::eBGState::bg1, Vector2(280.0f, 140.0f));
		bg2_3_4->SetBG(Background2::eBGState::bg3, Vector2(280.0f, 1080.0f));
		bg2_2_2->SetBG(Background2::eBGState::bg2, Vector2(280.0f, 1220.0f));
		Foreground2* fg = object::Instantiate<Foreground2>(Vector2(4400, 2530), eLayerType::ForeObject, eSceneType::Play2);
		mTrees = object::Instantiate<Foreground2>(Vector2(23587, 980), eLayerType::hideObjects, eSceneType::Play2);
		mTrees->mAniN = true;

		//----------------------------------- Map
		MapObjects2* mobj0 = object::MapObjects2Instantiate(Vector2(0, 0), eLayerType::MapObjects, eSceneType::Play2, 0);
		MapObjects2* mobj1 = object::MapObjects2Instantiate(Vector2(4568, 0), eLayerType::MapObjects, eSceneType::Play2, 1);
		MapObjects2* mobj2 = object::MapObjects2Instantiate(Vector2(9136, 0), eLayerType::MapObjects, eSceneType::Play2, 2);
		MapObjects2* mobj3 = object::MapObjects2Instantiate(Vector2(13704, 0), eLayerType::MapObjects, eSceneType::Play2, 3);
		MapObjects2* mobj4 = object::MapObjects2Instantiate(Vector2(18272, 0), eLayerType::MapObjects, eSceneType::Play2, 4);
		MapObjects2* mobj5 = object::MapObjects2Instantiate(Vector2(20864, 0), eLayerType::MapObjects, eSceneType::Play2, 5);
		MapObjects2* mobj6 = object::MapObjects2Instantiate(Vector2(25432, 0), eLayerType::MapObjects, eSceneType::Play2, 6);
		//----------------------------------- Map

		//----------------------------------- MapDeco
		MapDeco5* mdec1 = object::Instantiate<MapDeco5>(Vector2(240, 2011), eLayerType::MapDeco, eSceneType::Play2);
		mdec1->mNumber = true;
		MapDeco5* mdec2 = object::Instantiate<MapDeco5>(Vector2(520, 2011), eLayerType::MapDeco, eSceneType::Play2);
		MapDeco5* mdec3 = object::Instantiate<MapDeco5>(Vector2(4320, 3211), eLayerType::MapDeco, eSceneType::Play2);
		MapDeco5* mdec4 = object::Instantiate<MapDeco5>(Vector2(4642, 3131), eLayerType::MapDeco, eSceneType::Play2);
		MapDeco5* mdec5 = object::Instantiate<MapDeco5>(Vector2(6891, 2320), eLayerType::MapDeco, eSceneType::Play2);
		mdec5->mNumber = true;
		MapDeco5* mdec6 = object::Instantiate<MapDeco5>(Vector2(7291, 1120), eLayerType::MapDeco, eSceneType::Play2);
		mdec5->mNumber = true;
		MapDeco5* mdec7 = object::Instantiate<MapDeco5>(Vector2(12951, 1040), eLayerType::MapDeco, eSceneType::Play2);
		MapDeco5* mdec8 = object::Instantiate<MapDeco5>(Vector2(13595, 1040), eLayerType::MapDeco, eSceneType::Play2);
		MapDeco5* mdec9 = object::Instantiate<MapDeco5>(Vector2(13915, 1040), eLayerType::MapDeco, eSceneType::Play2);
		mdec8->mNumber = true;
		mdec9->mNumber = true;
		//----------------------------------- MapDeco

		//----------------------------------- Objects
		Water* water2 = object::WaterInstantiate(Vector2(6165.0f, 3910.0f), Vector2(645.0f, 500.0f), eLayerType::Water, eSceneType::Play2);

		Logplatform* logp1 = object::Instantiate<Logplatform>(Vector2(6110, 1315), eLayerType::MapObjects, eSceneType::Play2);
		Logplatform* logp2 = object::Instantiate<Logplatform>(Vector2(6110, 1543), eLayerType::MapObjects, eSceneType::Play2);
		Logplatform* logp3 = object::Instantiate<Logplatform>(Vector2(6110, 1771), eLayerType::MapObjects, eSceneType::Play2);
		Logplatform* logp4 = object::Instantiate<Logplatform>(Vector2(6110, 1999), eLayerType::MapObjects, eSceneType::Play2);
		Logplatform* logp5 = object::Instantiate<Logplatform>(Vector2(6110, 2227), eLayerType::MapObjects, eSceneType::Play2);
		Logplatform* logp6 = object::Instantiate<Logplatform>(Vector2(6110, 2455), eLayerType::MapObjects, eSceneType::Play2);
		Logplatform* logp7 = object::Instantiate<Logplatform>(Vector2(6110, 2683), eLayerType::MapObjects, eSceneType::Play2);
		Logplatform* logp8 = object::Instantiate<Logplatform>(Vector2(6110, 2911), eLayerType::MapObjects, eSceneType::Play2);
		Logplatform* logp9 = object::Instantiate<Logplatform>(Vector2(6110, 3139), eLayerType::MapObjects, eSceneType::Play2);
		Logplatform* logp10 = object::Instantiate<Logplatform>(Vector2(6110, 3367), eLayerType::MapObjects, eSceneType::Play2);

		Breakingterrain* bterr1 = object::Instantiate<Breakingterrain>(Vector2(3920, 2765), eLayerType::MapObjects, eSceneType::Play2);
		Breakingterrain* bterr2 = object::Instantiate<Breakingterrain>(Vector2(6160, 3700), eLayerType::MapObjects, eSceneType::Play2);
		Breakingterrain* bterr3 = object::Instantiate<Breakingterrain>(Vector2(6090, 2430), eLayerType::MapObjects, eSceneType::Play2);
		bterr3->SetDir(true);
		Breakingterrain* bterr4 = object::Instantiate<Breakingterrain>(Vector2(6410, 1310), eLayerType::MapObjects, eSceneType::Play2);
		bterr4->SetDir(true);
		//Camera::SetTarget(bterr4);


		Spring* spring1 = object::springInstantiate(Vector2(7370, 3090), eLayerType::hideObjects, eSceneType::Play2, 0);

		Logbridge* logb1 = object::Instantiate<Logbridge>(Vector2(27400.0f, 1265.0f), eLayerType::MapObjects, eSceneType::Play2);
		logb = object::Instantiate<Logbridge>(Vector2(28675.0f, -3000.0f), eLayerType::MapObjects, eSceneType::Play2);
		mButton = object::Instantiate<Button>(Vector2(29220.0f, 970.0f), eLayerType::Player, eSceneType::Play2);

		//----------------------------------- Monster
		Bloominator* bloom1 = object::Instantiate<Bloominator>(Vector2(7420.0f, 630.0f), eLayerType::hideMonster, eSceneType::Play2);
		bloom1->SetSonic(mSonic2);
		Caterkiller* ck1 = object::Instantiate<Caterkiller>(Vector2(7320.0f, 2380.0f), eLayerType::Monster, eSceneType::Play2);
		Caterkiller* ck2 = object::Instantiate<Caterkiller>(Vector2(6400.0f, 3930.0f), eLayerType::Monster, eSceneType::Play2);
		mLB = object::Instantiate<Lastboss>(Vector2(27500.0f, 1000.0f), eLayerType::Boss, eSceneType::Play2);
		mLB->SetPlayer(mSonic2);
		mBomber = object::Instantiate<Bomber>(Vector2(14000, -300), eLayerType::Boss, eSceneType::Play2);
		mBombermove = Resources::Load<Sound>(L"bomber", L"..\\Resources\\sound\\bomber_move.wav");
		mLBmove = Resources::Load<Sound>(L"LB_move-in-forest", L"..\\Resources\\sound\\lb_move-in-forest.wav");
		mLBBG = Resources::Load<Sound>(L"LBTheme", L"..\\Resources\\sound\\music\\lastboss.wav");
		Ground2* ground2 = object::Instantiate<Ground2>(eLayerType::Ground, eSceneType::Play2);
		ground2->SetPlayer(mSonic2);
		ground2->AddGameObject(logb1);
		ground2->AddGameObject(logb);
		ground2->AddGameObject(bterr1);
		ground2->AddGameObject(bterr2);
		ground2->AddGameObject(bterr3);
		ground2->AddGameObject(bterr4);
		ground2->AddGameObject(logp1);
		ground2->AddGameObject(logp2);
		ground2->AddGameObject(logp3);
		ground2->AddGameObject(logp4);
		ground2->AddGameObject(logp5);
		ground2->AddGameObject(logp6);
		ground2->AddGameObject(logp7);
		ground2->AddGameObject(logp8);
		ground2->AddGameObject(logp9);
		ground2->AddGameObject(logp10);
		ground2->AddSpring(spring1);

		//Camera::SetTarget(ck2);

		PlayUI* ui = object::Instantiate<PlayUI>(eLayerType::UI, eSceneType::Play2);
		ui->SetTarget(mSonic2);



	}
	void PlayScene2::Update()
	{
		if (Input::GetKeyDown(eKeyCode::ESC))
		{
			SceneManager::LoadScene(eSceneType::Ending);
		}

		if (mSonic2->GetComponent<Transform>()->GetPos().x > 14450.0f && mSonic2->GetComponent<Transform>()->GetPos().x < 21000.0f)
		{

			float time = 0.0f;
			int index1 = 0;
			int index2 = 0;

			mSonic2->mLimitVel = 600.0f;

			Vector2 Bpos = mBomber->GetComponent<Transform>()->GetPos();
			if (Bpos.y < 600)
			{
				mBombermove->Play(true);
				Bpos.y += 500 * Time::DeltaTime();
				Bpos.x += 800 * Time::DeltaTime();
				mBomber->GetComponent<Transform>()->SetPos(Bpos);
			}
			else if (Bpos.y >= 600 && Bpos.x < mSonic2->GetComponent<Transform>()->GetPos().x)
			{
				Bpos.x += 550 * Time::DeltaTime();
				mBomber->GetComponent<Transform>()->SetPos(Bpos);
				mBomber->mthrowBomb = true;
			}
		}
		else if ((mSonic2->GetComponent<Transform>()->GetPos().x >= 21000.0f))
		{
			mSonic2->mLimitVel = 800.0f;
			mBombermove->Stop(false);

			Vector2 Bpos = mBomber->GetComponent<Transform>()->GetPos();
			if (Bpos.y >= 500)
			{
				Bpos.y -= 100 * Time::DeltaTime();
				Bpos.x -= 80 * Time::DeltaTime();
				mBomber->GetComponent<Transform>()->SetPos(Bpos);
			}
			else if (Bpos.y < 0)
			{
				object::Destroy(mBomber);
			}

		}
		
		
		if ((mSonic2->GetComponent<Transform>()->GetPos().x >= 23000.0f && mLBrb == false))
		{
			mLBmove->Play(true);
			mLBr = object::Instantiate<LastbossR>(Vector2(22500.0f, 1100.0f), eLayerType::hideObjects, eSceneType::Play2);
			mLBrb = true;
			Vector2 mLBrpos = mLBr->GetComponent<Transform>()->GetPos();
		}

			Vector2 mTreespos = mTrees->GetComponent<Transform>()->GetPos();
		if (mSonic2->GetComponent<Transform>()->GetPos().x >= 23000.0f)
		{
			mTreespos.x += 200 * Time::DeltaTime();
			mTrees->GetComponent<Transform>()->SetPos(mTreespos);

		}
		if (mTreespos.x >= 24600)
		{
			mTreespos.x = 24600;
			mTrees->GetComponent<Transform>()->SetPos(mTreespos);
		}
		if (mSonic2->GetComponent<Transform>()->GetPos().x >= 27600.0f && mLB->mStart == false)
		{
			mLBmove->Stop(false);
			mBG->Stop(false);
			mLBBG->Play(true);
			object::Destroy(mLBr);
			mLB->mStart = true;
		}
		if (mLB->GetComponent<Transform>()->GetPos().y > 2000 && mLB->mStart == true)
		{
			mLBBG->Stop(false);
			mBG->Play(true);
			logb->GetComponent<Transform>()->SetPos(Vector2(28675.0f, 1265.0f));
			mLB->mStart = false;
		}
		if (mSonic2->GetComponent<Transform>()->GetPos().x >= 28775.0f && logb->GetComponent<Transform>()->GetPos().y > 1200.0f && mKnuc == false)
		{
			Knuckles* kn = object::Instantiate<Knuckles>(Vector2(29900, 880), eLayerType::Monster, eSceneType::Play2);
			mKnuc = true;
		}
		if (mButton->mPush)
		{
			logb->GetComponent<Animator>()->Play(L"logb_breaking", false);
			mSonic2->SetSonicState(Sonic::eSonicState::falldown);

			if (mSonic2->GetComponent<Transform>()->GetPos().y >= 2000)
			{
				Camera::SetTarget(nullptr);
				SceneManager::LoadScene(eSceneType::Ending);
			}
		}
		
		Scene::Update();

	}
	void PlayScene2::Render(HDC hdc)
	{
		Scene::Render(hdc);
	}
	void PlayScene2::Release()
	{
		Scene::Release();
	}
	void PlayScene2::OnEnter()
	{
		Camera::SetTarget(mSonic2);

		Scenechange* sc = object::Instantiate<Scenechange>(eLayerType::ForeObject, eSceneType::Play2);

		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Monster, true);
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::hideMonster, true);
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::RMonster, true);
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Boss, true);
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Ring, true);
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::hideObjects, true);
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::MapObjects, true);
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Water, true);
		CollisionManager::SetLayer(eLayerType::Effect, eLayerType::Water, true);
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Item, true);
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Ground, true);
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::mEffect, true);
		CollisionManager::SetLayer(eLayerType::Monster, eLayerType::Ground, true);
		CollisionManager::SetLayer(eLayerType::Ground, eLayerType::Bomb, true);
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Bullet, true);
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Bomb, true);
		CollisionManager::SetLayer(eLayerType::mEffect, eLayerType::MapObjects, true);


		Redcard* rc = object::Instantiate<Redcard>(eLayerType::UI, eSceneType::Play2);
		Zone1* zone1 = object::Instantiate<Zone1>(eLayerType::UI, eSceneType::Play2);
		Act1* act2 = object::Instantiate<Act1>(eLayerType::UI, eSceneType::Play2);

		mBG->Play(true);


		//Camera::SetTarget(mSonic2);


	}
	void PlayScene2::OnExit()
	{
		mBG->Stop(false);
		mLBBG->Stop(false);

	}
}