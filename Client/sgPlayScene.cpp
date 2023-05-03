#include "sgPlayScene.h"
#include "sgSonic.h"
#include "sgWall.h"
#include "sgMiniboss.h"
#include "sgRhinobot.h"
#include "sgBloominator.h"
#include "sgCaterkiller.h"
#include "sgSpike.h"
#include "sgBackground.h"
#include "sgBackground_middle.h"
#include "sgBackground_middle2.h"
#include "sgBackground_sea.h"
#include "sgMapObjects.h"
#include "sgForeground.h"
#include "sgMovingTerrain.h"
#include "sgBreakingterrain.h"
#include "sgLogplatform.h"
#include "sgMapWater1.h"
#include "sgMapWater2.h"
#include "sgMapWater3.h"
#include "sgMapWater4.h"
#include "sgMapDeco1.h"
#include "sgMapDeco2.h"
#include "sgMapDeco3.h"
#include "sgMapDeco4.h"
#include "sgWater.h"
#include "sgRing.h"
#include "sgGiantring.h"
#include "sgRope.h"
#include "sgSpring.h"
#include "sgMapRock_l.h"
#include "sgItem.h"
#include "sgEffect.h"
#include "sgEffect2.h"
#include "sgRedcard.h"
#include "sgZone1.h"
#include "sgAct1.h"
#include "sgTestGround.h"
#include "sgPlayUI.h"
#include "sgScenechange.h"

#include "sgApplication.h"
#include "sgTime.h"
#include "sgInput.h"
#include "sgSceneManager.h"
#include "sgCollisionManager.h"
#include "sgImage.h"
#include "sgResources.h"
#include "sgTransform.h"
#include "sgCamera.h"
#include "sgObject.h"
#include "sgSound.h"

sg::Ground* ground;
sg::Sonic* mSonic;

extern sg::Application application;

namespace sg
{
	PlayScene::PlayScene()
	{
	}
	PlayScene::~PlayScene()
	{
	}
	void PlayScene::Initialize()
	{
		mBG = Resources::Load<Sound>(L"PlayTheme", L"..\\Resources\\sound\\music\\act1bg.wav");
		mMBBG = Resources::Load<Sound>(L"MBTheme", L"..\\Resources\\sound\\music\\miniboss.wav");

		Wall* wall = object::Instantiate<Wall>(Vector2(-90.0f, -770.0f), eLayerType::hideObjects, eSceneType::Play);
		mSonic = object::Instantiate<Sonic>(Vector2(510.0f, 2640.0f), eLayerType::Player, eSceneType::Play);

		// background --------------------------------------------
		{ 
			GameObject* bg1 = object::Instantiate<Background>(eLayerType::BG, eSceneType::Play);
			Background_middle* bg2 = object::Instantiate<Background_middle>(eLayerType::BG, eSceneType::Play);
			bg2->SetSonic(mSonic);
			Background_middle2* bg3 = object::Instantiate<Background_middle2>(eLayerType::BG, eSceneType::Play);
			bg3->SetSonic(mSonic);
			for (size_t i = 0; i <= 14400; i += 576)
			{
				object::Instantiate<Backgroundsea>(Vector2(910 + i, 2157), eLayerType::BG, eSceneType::Play);
			}
			object::Instantiate<MapObjects>(eLayerType::MapObjects, eSceneType::Play);
			Water* water = object::WaterInstantiate(Vector2(10721, 3280), Vector2(1600, 500), eLayerType::Water, eSceneType::Play);
			//water->SetWaterScale(Vector2(100, 100));
			Foreground* fg = object::Instantiate<Foreground>(eLayerType::ForeObject, eSceneType::Play);

		}		

		// MapDeco --------------------------------------------
		{
			object::Instantiate<MapWater1>(Vector2(-40.5, 60), eLayerType::MapDeco, eSceneType::Play);
			object::Instantiate<MapWater2>(Vector2(11002, 60), eLayerType::MapDeco, eSceneType::Play);
			object::Instantiate<MapWater3>(Vector2(17040, 60), eLayerType::MapDeco, eSceneType::Play);
			object::Instantiate<MapWater4>(Vector2(17958, 2140), eLayerType::MapDeco, eSceneType::Play);
			object::Instantiate<MapWater4>(Vector2(18598, 2140), eLayerType::MapDeco, eSceneType::Play);
			object::Instantiate<MapDeco1>(Vector2(3275, 2781), eLayerType::MapDeco, eSceneType::Play);
			object::Instantiate<MapDeco2>(Vector2(3435, 2781), eLayerType::MapDeco, eSceneType::Play);
			object::Instantiate<MapDeco3>(Vector2(3920, 2782), eLayerType::MapDeco, eSceneType::Play);
			object::Instantiate<MapDeco4>(Vector2(4360, 2782), eLayerType::MapDeco, eSceneType::Play);
			MapDeco1* mdc1 = object::Instantiate<MapDeco1>(Vector2(5195, 2460), eLayerType::MapDeco, eSceneType::Play);
			MapDeco2* mdc2 = object::Instantiate<MapDeco2>(Vector2(5355, 2460), eLayerType::MapDeco, eSceneType::Play);
			MapDeco1* mdc3 = object::Instantiate<MapDeco1>(Vector2(7120, 3100), eLayerType::MapDeco, eSceneType::Play);
			MapDeco2* mdc4 = object::Instantiate<MapDeco2>(Vector2(7280, 3100), eLayerType::MapDeco, eSceneType::Play);
			MapDeco1* mdc5 = object::Instantiate<MapDeco1>(Vector2(8870, 1465), eLayerType::MapDeco, eSceneType::Play);
			MapDeco2* mdc6 = object::Instantiate<MapDeco2>(Vector2(9030, 1465), eLayerType::MapDeco, eSceneType::Play);
			MapDeco1* mdc7 = object::Instantiate<MapDeco1>(Vector2(12555, 2140), eLayerType::MapDeco, eSceneType::Play);
			MapDeco2* mdc8 = object::Instantiate<MapDeco2>(Vector2(12715, 2140), eLayerType::MapDeco, eSceneType::Play);
			MapDeco1* mdc9 = object::Instantiate<MapDeco1>(Vector2(12875, 3100), eLayerType::MapDeco, eSceneType::Play);
			MapDeco2* mdc10 = object::Instantiate<MapDeco2>(Vector2(13035, 3100), eLayerType::MapDeco, eSceneType::Play);
			MapDeco3* mdcf1 = object::Instantiate<MapDeco3>(Vector2(6480, 1620), eLayerType::MapDeco, eSceneType::Play);
			MapDeco3* mdcf2 = object::Instantiate<MapDeco3>(Vector2(7760, 2900), eLayerType::MapDeco, eSceneType::Play);
			MapDeco4* mdcf3 = object::Instantiate<MapDeco4>(Vector2(11080, 3220), eLayerType::MapDeco, eSceneType::Play);
			MapDeco4* mdcf4 = object::Instantiate<MapDeco4>(Vector2(13320, 1940), eLayerType::MapDeco, eSceneType::Play);
		}

		// Item ------------------------------------------------ 0 ring / 1 flame / 2 thunder / 3 water / 4 life

		Item* item_ring1 = object::itemInstantiate(Vector2(2890, 1790), eLayerType::Item, eSceneType::Play, 0);
		Item* item_ring2 = object::itemInstantiate(Vector2(2970, 1790), eLayerType::Item, eSceneType::Play, 0);
		Item* item_flame1= object::itemInstantiate(Vector2(8460, 1070), eLayerType::Item, eSceneType::Play, 1);
		Item* item_ring3 = object::itemInstantiate(Vector2(9680, 2300), eLayerType::Item, eSceneType::Play, 0);
		Item* item_water1 = object::itemInstantiate(Vector2(10750, 3300), eLayerType::Item, eSceneType::Play, 3);

		Item* item_ring4 = object::itemInstantiate(Vector2(13805, 3445), eLayerType::Item, eSceneType::Play, 0);
		Item* item_life1 = object::itemInstantiate(Vector2(13885, 3445), eLayerType::Item, eSceneType::Play, 4);
		Item* item_ring5 = object::itemInstantiate(Vector2(13965, 3445), eLayerType::Item, eSceneType::Play, 0);
		Item* item_ring6 = object::itemInstantiate(Vector2(14535, 1500), eLayerType::Item, eSceneType::Play, 0);
		Item* item_life2 = object::itemInstantiate(Vector2(16235, 2100), eLayerType::Item, eSceneType::Play, 4);


		//Item* item_test1 = object::itemInstantiate(Vector2(910, 2660), eLayerType::Item, eSceneType::Play, 0);
		//Item* item_test2 = object::itemInstantiate(Vector2(1060, 2660), eLayerType::Item, eSceneType::Play, 1);
		//Item* item_test3 = object::itemInstantiate(Vector2(1210, 2660), eLayerType::Item, eSceneType::Play, 2);
		//Item* item_test4 = object::itemInstantiate(Vector2(1460, 2660), eLayerType::Item, eSceneType::Play, 3);
		//Item* item_test5 = object::itemInstantiate(Vector2(1710, 2660), eLayerType::Item, eSceneType::Play, 4);


		// Ring --------------------------------------------
		{ 
			Giantring* Gring1 = object::Instantiate<Giantring>(Vector2(5540, 3030), eLayerType::Ring, eSceneType::Play);

			Ring* ring1 = object::Instantiate<Ring>(Vector2(2440, 2570), eLayerType::Ring, eSceneType::Play);
			Ring* ring2 = object::Instantiate<Ring>(Vector2(2510, 2570), eLayerType::Ring, eSceneType::Play);
			Ring* ring3 = object::Instantiate<Ring>(Vector2(2580, 2570), eLayerType::Ring, eSceneType::Play);

			Ring* ring4 = object::Instantiate<Ring>(Vector2(2760, 2630), eLayerType::Ring, eSceneType::Play);
			Ring* ring5 = object::Instantiate<Ring>(Vector2(2840, 2670), eLayerType::Ring, eSceneType::Play);
			Ring* ring6 = object::Instantiate<Ring>(Vector2(2920, 2710), eLayerType::Ring, eSceneType::Play);
			Ring* ring7 = object::Instantiate<Ring>(Vector2(3000, 2750), eLayerType::Ring, eSceneType::Play);
			Ring* ring8 = object::Instantiate<Ring>(Vector2(3080, 2790), eLayerType::Ring, eSceneType::Play);

			Ring* ring9 = object::Instantiate<Ring>(Vector2(3580, 2840), eLayerType::Ring, eSceneType::Play);
			Ring* ring10 = object::Instantiate<Ring>(Vector2(3650, 2800), eLayerType::Ring, eSceneType::Play);
			Ring* ring11 = object::Instantiate<Ring>(Vector2(3700, 2730), eLayerType::Ring, eSceneType::Play);

			Ring* ring12 = object::Instantiate<Ring>(Vector2(4410, 2680), eLayerType::Ring, eSceneType::Play);
			Ring* ring13 = object::Instantiate<Ring>(Vector2(4480, 2680), eLayerType::Ring, eSceneType::Play);
			Ring* ring14 = object::Instantiate<Ring>(Vector2(4550, 2680), eLayerType::Ring, eSceneType::Play);

			Ring* ring15 = object::Instantiate<Ring>(Vector2(5710, 1570), eLayerType::Ring, eSceneType::Play);
			Ring* ring16 = object::Instantiate<Ring>(Vector2(5780, 1570), eLayerType::Ring, eSceneType::Play);
			Ring* ring17 = object::Instantiate<Ring>(Vector2(5850, 1570), eLayerType::Ring, eSceneType::Play);

			Ring* ring18 = object::Instantiate<Ring>(Vector2(6090, 1790), eLayerType::Ring, eSceneType::Play);
			Ring* ring19 = object::Instantiate<Ring>(Vector2(6170, 1770), eLayerType::Ring, eSceneType::Play);
			Ring* ring20 = object::Instantiate<Ring>(Vector2(6250, 1750), eLayerType::Ring, eSceneType::Play);

			Ring* ring21 = object::Instantiate<Ring>(Vector2(7410, 3130), eLayerType::Ring, eSceneType::Play);
			Ring* ring22 = object::Instantiate<Ring>(Vector2(7490, 3090), eLayerType::Ring, eSceneType::Play);
			Ring* ring23 = object::Instantiate<Ring>(Vector2(7570, 3050), eLayerType::Ring, eSceneType::Play);

			Ring* ring24 = object::Instantiate<Ring>(Vector2(8200, 1330), eLayerType::Ring, eSceneType::Play);
			Ring* ring25 = object::Instantiate<Ring>(Vector2(8270, 1330), eLayerType::Ring, eSceneType::Play);
			Ring* ring26 = object::Instantiate<Ring>(Vector2(8340, 1330), eLayerType::Ring, eSceneType::Play);

			Ring* ring27 = object::Instantiate<Ring>(Vector2(10730, 2050), eLayerType::Ring, eSceneType::Play);
			Ring* ring28 = object::Instantiate<Ring>(Vector2(10810, 2050), eLayerType::Ring, eSceneType::Play);
			Ring* ring29 = object::Instantiate<Ring>(Vector2(10890, 2050), eLayerType::Ring, eSceneType::Play);

			Ring* ring30 = object::Instantiate<Ring>(Vector2(9830, 1840), eLayerType::Ring, eSceneType::Play);
			Ring* ring31 = object::Instantiate<Ring>(Vector2(9910, 1840), eLayerType::Ring, eSceneType::Play);
			Ring* ring32 = object::Instantiate<Ring>(Vector2(9990, 1840), eLayerType::Ring, eSceneType::Play);

			Ring* ring33 = object::Instantiate<Ring>(Vector2(13900, 3000), eLayerType::Ring, eSceneType::Play);
			Ring* ring34 = object::Instantiate<Ring>(Vector2(13900, 3070), eLayerType::Ring, eSceneType::Play);
			Ring* ring35 = object::Instantiate<Ring>(Vector2(13900, 3140), eLayerType::Ring, eSceneType::Play);

			Ring* ring36 = object::Instantiate<Ring>(Vector2(11730, 3440), eLayerType::Ring, eSceneType::Play);
			Ring* ring37 = object::Instantiate<Ring>(Vector2(11800, 3410), eLayerType::Ring, eSceneType::Play);
			Ring* ring38 = object::Instantiate<Ring>(Vector2(11870, 3380), eLayerType::Ring, eSceneType::Play);

			Ring* ring39 = object::Instantiate<Ring>(Vector2(14400, 2840), eLayerType::Ring, eSceneType::Play);
			Ring* ring40 = object::Instantiate<Ring>(Vector2(14470, 2840), eLayerType::Ring, eSceneType::Play);
			Ring* ring41 = object::Instantiate<Ring>(Vector2(14540, 2840), eLayerType::Ring, eSceneType::Play);

			Ring* ring42 = object::Instantiate<Ring>(Vector2(15430, 2835), eLayerType::Ring, eSceneType::Play);
			Ring* ring43 = object::Instantiate<Ring>(Vector2(15490, 2785), eLayerType::Ring, eSceneType::Play);
			Ring* ring44 = object::Instantiate<Ring>(Vector2(15540, 2720), eLayerType::Ring, eSceneType::Play);

			Ring* ring45 = object::Instantiate<Ring>(Vector2(13017, 1170), eLayerType::Ring, eSceneType::Play);
			Ring* ring46 = object::Instantiate<Ring>(Vector2(13087, 1170), eLayerType::Ring, eSceneType::Play);
			Ring* ring47 = object::Instantiate<Ring>(Vector2(13157, 1170), eLayerType::Ring, eSceneType::Play);
			Ring* ring48 = object::Instantiate<Ring>(Vector2(12987, 1230), eLayerType::Ring, eSceneType::Play);
			Ring* ring49 = object::Instantiate<Ring>(Vector2(13057, 1230), eLayerType::Ring, eSceneType::Play);
			Ring* ring50 = object::Instantiate<Ring>(Vector2(13127, 1230), eLayerType::Ring, eSceneType::Play);
			Ring* ring51 = object::Instantiate<Ring>(Vector2(13197, 1230), eLayerType::Ring, eSceneType::Play);

			Ring* ring52 = object::Instantiate<Ring>(Vector2(13800, 1335), eLayerType::Ring, eSceneType::Play);
			Ring* ring53 = object::Instantiate<Ring>(Vector2(13870, 1335), eLayerType::Ring, eSceneType::Play);
			Ring* ring54 = object::Instantiate<Ring>(Vector2(13940, 1335), eLayerType::Ring, eSceneType::Play);
			
			Ring* ring55 = object::Instantiate<Ring>(Vector2(14165, 1875), eLayerType::Ring, eSceneType::Play);
			Ring* ring56 = object::Instantiate<Ring>(Vector2(14215, 1735), eLayerType::Ring, eSceneType::Play);
			Ring* ring57 = object::Instantiate<Ring>(Vector2(14370, 1670), eLayerType::Ring, eSceneType::Play);
			Ring* ring58 = object::Instantiate<Ring>(Vector2(14535, 1735), eLayerType::Ring, eSceneType::Play);
			Ring* ring59 = object::Instantiate<Ring>(Vector2(14585, 1875), eLayerType::Ring, eSceneType::Play);

			Ring* ring60 = object::Instantiate<Ring>(Vector2(15855, 2525), eLayerType::Ring, eSceneType::Play);
			Ring* ring61 = object::Instantiate<Ring>(Vector2(15935, 2565), eLayerType::Ring, eSceneType::Play);
			Ring* ring62 = object::Instantiate<Ring>(Vector2(16015, 2605), eLayerType::Ring, eSceneType::Play);
			Ring* ring63 = object::Instantiate<Ring>(Vector2(16095, 2645), eLayerType::Ring, eSceneType::Play);
			Ring* ring64 = object::Instantiate<Ring>(Vector2(16175, 2685), eLayerType::Ring, eSceneType::Play);

		}

		// Monster --------------------------------------------
		Rhinobot* rhino1 = object::Instantiate<Rhinobot>(Vector2(5410, 2430), eLayerType::RMonster, eSceneType::Play);
		Rhinobot* rhino2 = object::Instantiate<Rhinobot>(Vector2(8300, 1450), eLayerType::RMonster, eSceneType::Play);
		Rhinobot* rhino3 = object::Instantiate<Rhinobot>(Vector2(13000, 2230), eLayerType::RMonster, eSceneType::Play);
		//Camera::SetTarget(mSonic);

		Bloominator* bloom1 = object::Instantiate<Bloominator>(Vector2(3330, 2400), eLayerType::hideMonster, eSceneType::Play);
		Bloominator* bloom2 = object::Instantiate<Bloominator>(Vector2(6810, 1580), eLayerType::Monster, eSceneType::Play);
		Bloominator* bloom3 = object::Instantiate<Bloominator>(Vector2(8450, 1130), eLayerType::hideMonster, eSceneType::Play);
		Bloominator* bloom4 = object::Instantiate<Bloominator>(Vector2(10450, 2210), eLayerType::Monster, eSceneType::Play);
		Bloominator* bloom5 = object::Instantiate<Bloominator>(Vector2(12605, 1730), eLayerType::hideMonster, eSceneType::Play);
		Bloominator* bloom6 = object::Instantiate<Bloominator>(Vector2(12930, 2580), eLayerType::hideMonster, eSceneType::Play);
		Caterkiller* ck1 = object::Instantiate<Caterkiller>(Vector2(11500, 3280), eLayerType::Monster, eSceneType::Play);
		Miniboss* miniboss = object::Instantiate<Miniboss>(Vector2(18910, 2000), eLayerType::Boss, eSceneType::Play);
		rhino1->SetSonic(mSonic);
		rhino2->SetSonic(mSonic);
		rhino3->SetSonic(mSonic);
		bloom1->SetSonic(mSonic);
		bloom2->SetSonic(mSonic);
		bloom3->SetSonic(mSonic);
		bloom4->SetSonic(mSonic);
		bloom5->SetSonic(mSonic);
		bloom6->SetSonic(mSonic);
		miniboss->SetPlayer(mSonic);

		Spike* spike1 = object::Instantiate<Spike>(Vector2(6040, 2425), eLayerType::hideMonster, eSceneType::Play);
		Spike* spike2 = object::Instantiate<Spike>(Vector2(6380, 2425), eLayerType::hideMonster, eSceneType::Play);
		Spike* spike3 = object::Instantiate<Spike>(Vector2(8940, 1510), eLayerType::hideMonster, eSceneType::Play);
		Spike* spike4 = object::Instantiate<Spike>(Vector2(9180, 1510), eLayerType::hideMonster, eSceneType::Play);
		Spike* spike5 = object::Instantiate<Spike>(Vector2(13960, 2460), eLayerType::hideMonster, eSceneType::Play);
		Spike* spike6 = object::Instantiate<Spike>(Vector2(14080, 2750), eLayerType::hideMonster, eSceneType::Play);
		Spike* spike7 = object::Instantiate<Spike>(Vector2(11365, 3460), eLayerType::hideMonster, eSceneType::Play);
		Spike* spike8 = object::Instantiate<Spike>(Vector2(11445, 3460), eLayerType::hideMonster, eSceneType::Play);
		Spike* spike9 = object::Instantiate<Spike>(Vector2(11525, 3460), eLayerType::hideMonster, eSceneType::Play);
		Spike* spike10 = object::Instantiate<Spike>(Vector2(16350, 2350), eLayerType::Monster, eSceneType::Play);
		Spike* spike11 = object::Instantiate<Spike>(Vector2(16840, 2683), eLayerType::Monster, eSceneType::Play);
		spike5->SetSpike(Spike::eSpikeState::down);
		spike10->SetSpike(Spike::eSpikeState::down);
		spike11->SetSpike(Spike::eSpikeState::down);

		// Ground
		{
			ground = object::Instantiate<Ground>(eLayerType::Ground, eSceneType::Play);
			MovingTerrain* movterr1 = object::Instantiate<MovingTerrain>(Vector2(3410, 2330), eLayerType::Ground, eSceneType::Play);
			MovingTerrain* movterr2 = object::Instantiate<MovingTerrain>(Vector2(5340, 1630), eLayerType::Ground, eSceneType::Play);
			Breakingterrain* bterr1 = object::Instantiate<Breakingterrain>(Vector2(9440, 1580), eLayerType::Ground, eSceneType::Play);
			Breakingterrain* bterr2 = object::Instantiate<Breakingterrain>(Vector2(11010, 2340), eLayerType::Ground, eSceneType::Play);
			Breakingterrain* bterr3 = object::Instantiate<Breakingterrain>(Vector2(11760, 2260), eLayerType::Ground, eSceneType::Play);

			bterr3->SetDir(true);

			Logplatform* logp1 = object::Instantiate<Logplatform>(Vector2(11400.0f, 1750.0f), eLayerType::Ground, eSceneType::Play);
			Logplatform* logp2 = object::Instantiate<Logplatform>(Vector2(11400.0f, 2012.5f), eLayerType::Ground, eSceneType::Play);
			Logplatform* logp3 = object::Instantiate<Logplatform>(Vector2(11400.0f, 2275.0f), eLayerType::Ground, eSceneType::Play);
			Logplatform* logp4 = object::Instantiate<Logplatform>(Vector2(11400.0f, 2537.5f), eLayerType::Ground, eSceneType::Play);
			Logplatform* logp5 = object::Instantiate<Logplatform>(Vector2(11400.0f, 2800.0f), eLayerType::Ground, eSceneType::Play);

		Rope* rope1 = object::Instantiate<Rope>(Vector2(6610, 2130), eLayerType::MapObjects, eSceneType::Play);
		Rope* rope2 = object::Instantiate<Rope>(Vector2(7410, 2130), eLayerType::MapObjects, eSceneType::Play);
		Rope* rope3 = object::Instantiate<Rope>(Vector2(8210, 2130), eLayerType::MapObjects, eSceneType::Play);
		Rope* rope4 = object::Instantiate<Rope>(Vector2(11980, 2475), eLayerType::MapObjects, eSceneType::Play);

		//Spring  --------------------------------------------
		Spring* spring1 = object::springInstantiate(Vector2(4730, 2580), eLayerType::hideObjects, eSceneType::Play, 1);
		Spring* spring2 = object::springInstantiate(Vector2(4150, 2660), eLayerType::hideObjects, eSceneType::Play, 0);
		Spring* spring3 = object::springInstantiate(Vector2(3970, 2310), eLayerType::hideObjects, eSceneType::Play, 0);
		Spring* spring4 = object::springInstantiate(Vector2(5260, 2130), eLayerType::hideObjects, eSceneType::Play, 0);
		Spring* spring5 = object::springInstantiate(Vector2(7760, 2990), eLayerType::hideObjects, eSceneType::Play, 1);
		Spring* spring6 = object::springInstantiate(Vector2(8080, 2890), eLayerType::hideObjects, eSceneType::Play, 1);
		Spring* spring7 = object::springInstantiate(Vector2(13800, 3480), eLayerType::MapObjects, eSceneType::Play, 0);
		Spring* spring8 = object::springInstantiate(Vector2(13880, 3480), eLayerType::MapObjects, eSceneType::Play, 0);
		Spring* spring9 = object::springInstantiate(Vector2(13960, 3480), eLayerType::MapObjects, eSceneType::Play, 0);
		Spring* spring10 = object::springInstantiate(Vector2(16350, 2280), eLayerType::MapObjects, eSceneType::Play, 0);
		Spring* spring11 = object::springInstantiate(Vector2(16840, 2603), eLayerType::MapObjects, eSceneType::Play, 0);
		Spring* spring12 = object::springInstantiate(Vector2(12245, 3300), eLayerType::MapObjects, eSceneType::Play, 0);
		Spring* spring13 = object::springInstantiate(Vector2(12260, 2180), eLayerType::MapObjects, eSceneType::Play, 0);
		Spring* spring14 = object::springInstantiate(Vector2(14240, 2830), eLayerType::hideObjects, eSceneType::Play, 2);
		Spring* spring15 = object::springInstantiate(Vector2(13600, 1880), eLayerType::hideObjects, eSceneType::Play, 0);


		//Rock --------------------------------------------
		MapRock_l* maprockl1 = object::Instantiate<MapRock_l>(Vector2(4130, 2680), eLayerType::hideObjects, eSceneType::Play);
		MapRock_l* maprockl2 = object::Instantiate<MapRock_l>(Vector2(8310, 2680), eLayerType::hideObjects, eSceneType::Play);
		MapRock_l* maprockl3 = object::Instantiate<MapRock_l>(Vector2(6360, 2950), eLayerType::hideObjects, eSceneType::Play);
		MapRock_l* maprockl4 = object::Instantiate<MapRock_l>(Vector2(9140, 2330), eLayerType::hideObjects, eSceneType::Play);
		MapRock_l* maprockl5 = object::Instantiate<MapRock_l>(Vector2(9340, 2280), eLayerType::hideObjects, eSceneType::Play);
		MapRock_l* maprockl6 = object::Instantiate<MapRock_l>(Vector2(9540, 2230), eLayerType::hideObjects, eSceneType::Play);
		MapRock_l* maprockl7 = object::Instantiate<MapRock_l>(Vector2(10760, 2150), eLayerType::MapObjects, eSceneType::Play);
		MapRock_l* maprockl8 = object::Instantiate<MapRock_l>(Vector2(12250, 2070), eLayerType::MapObjects, eSceneType::Play);
		MapRock_l* maprockl9 = object::Instantiate<MapRock_l>(Vector2(13860, 2760), eLayerType::hideObjects, eSceneType::Play);

			ground->SetPlayer(mSonic);
			ground->AddGameObject(movterr1);
			ground->AddGameObject(movterr2);
			ground->AddGameObject(maprockl1);
			ground->AddGameObject(maprockl2);
			ground->AddGameObject(maprockl3);
			ground->AddGameObject(maprockl4);
			ground->AddGameObject(maprockl5);
			ground->AddGameObject(maprockl6);
			ground->AddGameObject(maprockl7);
			ground->AddGameObject(maprockl8);
			ground->AddGameObject(maprockl9);
			ground->AddGameObject(rope1);
			ground->AddGameObject(rope2);
			ground->AddGameObject(rope3);
			ground->AddGameObject(rope4);
			ground->AddGameObject(logp1);
			ground->AddGameObject(logp2);
			ground->AddGameObject(logp3);
			ground->AddGameObject(logp4);
			ground->AddGameObject(logp5);
			ground->AddGameObject(bterr1);
			ground->AddGameObject(bterr2);
			ground->AddGameObject(bterr3);
			ground->AddSpring(spring2);
			ground->AddSpring(spring3);
			ground->AddSpring(spring4);
			ground->AddSpring(spring7);
			ground->AddSpring(spring8);
			ground->AddSpring(spring9);
			ground->AddSpring(spring10);
			ground->AddSpring(spring11);
			ground->AddSpring(spring12);
			ground->AddSpring(spring13);
			ground->AddSpring(spring15);


		}		
		mUI = object::Instantiate<PlayUI>(eLayerType::UI, eSceneType::Play);
		mUI->SetTarget(mSonic);

		mMB = false;
	}
	void PlayScene::Update()
	{
		if (Input::GetKeyDown(eKeyCode::ESC))
		{
			SceneManager::LoadScene(eSceneType::Play2);
		}

		//if (Input::GetKeyDown(eKeyCode::Ctrl))
		//{
		//	application.Initialize(application.GetHwnd());
		//}
		Vector2 sonicpos = mSonic->GetComponent<Transform>()->GetPos();
		if (sonicpos.x >= 18360 && mMB == false)
		{
			mBG->Stop(false);
			mMBBG->Play(false);
			mMB = true;
			Camera::SetTarget(nullptr);
		}

		if ((UINT)sonicpos.x % 20 == 0)
		{
			int CNum = rand() % 4 + 1;
			mClouds.push_back(object::CloudsInstantiate(sonicpos.x, CNum, eSceneType::Play));

		}
		if (mClouds.size() > 10)
		{
			mClouds.erase(mClouds.begin());
		}


		Scene::Update();
	}
	void PlayScene::Render(HDC hdc)
	{
		Scene::Render(hdc);
	}

	void PlayScene::Release()
	{
		Scene::Release();
	}
	void PlayScene::OnEnter()
	{
		mBG->Play(true);

		Camera::SetTarget(mSonic);
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
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Bullet, true);
	}
	void PlayScene::OnExit()
	{
		mBG->Stop(false);
		mMBBG->Stop(false);
	}
}