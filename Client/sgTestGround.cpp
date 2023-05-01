#include "sgTestGround.h"
#include "sgGroundMgr.h"

#include "sgSonic.h"
#include "sgMovingTerrain.h"
#include "sgBreakingterrain.h"
#include "sgLogplatform.h"
#include "sgMapRock_l.h"
#include "sgRhinobot.h"
#include "sgRing.h"
#include "sgSpring.h"
#include "sgRope.h"

#include "sgImage.h"
#include "sgResources.h"
#include "sgCamera.h"
#include "sgInput.h"
#include "sgLayer.h"

#include "sgRigidbody.h"
#include "sgTransform.h"
#include "sgCollider.h"
#include "sgAnimator.h"

#include "sgSceneManager.h"


#define earth RGB(127, 0, 255)
#define earth2 RGB(50, 127, 127)
#define air RGB(255, 0, 255)
#define firststep RGB(127, 127, 0)
#define secondstep RGB(0, 127, 0)

namespace sg
{
	Ground::Ground()
		: mbAble(false)
		, mOnOff(true)
		, mYellow(false)
		, mGreen(false)
		, mBlue(false)
		, mRed(false)
		, mFrontpos(Vector2::Zero)

	{
		this->SetName(L"Ground");
	}

	Ground::~Ground()
	{	
	}

	void Ground::Initialize()
	{
		mImage = Resources::Load<Image>(L"Ground_pixel", L"..\\Resources\\map\\pixel.bmp");

		mYellow = false;
		mGreen = false;
		mBlue = false;
		mRed = false;

		GameObject::Initialize();
	}

	void Ground::Update()
	{
		GameObject::Update();

		if (Input::GetKeyDown(eKeyCode::Ctrl)) // Ctrl 누르면 Render On/Off
		{
			if (mOnOff == true)
			{
				mOnOff = false;
			}
			else
			{
				mOnOff = true;
			}
		}

		Transform* playerTr = mPlayer->GetComponent<Transform>();
		Collider* playerCol = mPlayer->GetComponent<Collider>();
		Rigidbody* playerRb = mPlayer->GetComponent<Rigidbody>();
		Animator* playerAni = mPlayer->GetComponent<Animator>();

		Vector2 pos = playerTr->GetPos();
		Vector2 velocity = playerRb->GetVelocity();
		Vector2 force = playerRb->GetForce();
		Vector2 gravity;
		Vector2 accel = playerRb->GetAccel();
		Vector2 value = Vector2::Zero;

		COLORREF mynowcolor = mImage->GetPixel(pos.x + 62.5, pos.y + 90); // 내 몸
		COLORREF myupcolor = mImage->GetPixel(pos.x + 62.5, pos.y + 30);

		COLORREF myfootcolor = mImage->GetPixel(pos.x + 62.5, pos.y + 123); // 내 발
		COLORREF myfootupcolor = mImage->GetPixel(pos.x + 62.5, pos.y + 122); //내 발보다 위
		COLORREF myfootdowncolor = mImage->GetPixel(pos.x + 62.5, pos.y + 124); // 내 발보다 아래

		COLORREF myleftcolor = mImage->GetPixel(pos.x + 32.5, pos.y + 50); // 내 왼쪽
		COLORREF myleftupcolor = mImage->GetPixel(pos.x + 32.5, pos.y + 30); // 내 왼쪽 위
		COLORREF myleftleftcolor = mImage->GetPixel(pos.x + 12.5, pos.y + 50);

		COLORREF myrightcolor = mImage->GetPixel(pos.x + 92.5, pos.y + 50); // 내 오른쪽
		COLORREF myrightupcolor = mImage->GetPixel(pos.x + 92.5, pos.y + 30); // 내 오른쪽 위
		COLORREF myrightrightcolor = mImage->GetPixel(pos.x + 112.5, pos.y + 50);

		COLORREF yellowloop = RGB(255, 255, 0);
		COLORREF orangeloop = RGB(255, 255, 0);
		COLORREF blueloop = RGB(0, 0, 255);
		COLORREF greyloop = RGB(100, 100, 100);
		COLORREF redloop = RGB(80, 0, 0);
		COLORREF greenloop = RGB(127, 255, 0);
		//

		for (GameObject* mon : SceneManager::GetActiveScene()->GetGameObjects(eLayerType::RMonster))
		{
			if (mon == nullptr)
				return;

			Vector2 monpos = mon->GetComponent<Transform>()->GetPos();
			COLORREF monfoot = mImage->GetPixel(monpos.x + 60, monpos.y + 68);

			if (monfoot != air)
			{
				mon->GetComponent<Rigidbody>()->SetGround(true);
				value = Vector2(monpos.x + 60, monpos.y + 67);
				if (mImage->GetPixel(value.x, value.y) != air)
				{
					monpos.y -= 1;
					value.y -= 1;
					mon->GetComponent<Transform>()->SetPos(monpos);
				}
			}
			else
			{
				mon->GetComponent<Rigidbody>()->SetGround(false);
			}
		}
		for (GameObject* bullet : SceneManager::GetActiveScene()->GetGameObjects(eLayerType::Bullet))
		{
			if (bullet == nullptr)
				return;

			Vector2 bulletpos = bullet->GetComponent<Transform>()->GetPos();
			COLORREF bulletbottom = mImage->GetPixel(bulletpos.x + 20, bulletpos.y + 40);

			if (bulletbottom != air)
			{
				bullet->GetComponent<Rigidbody>()->SetGround(true);
			}
		}

		// --------------------------------------------- 플레이어의 발 아래, 머리 위, 옆이 땅일 때
		if (myfootdowncolor != air
			&& myfootdowncolor != NULL
			&& myfootdowncolor != blueloop
			&& myfootdowncolor != redloop
			&& myfootdowncolor != greyloop
			//&& myfootdowncolor != greenloop
			&& mPlayer->GetSonicState() != Sonic::eSonicState::death)  // 현재 서 있는 곳이 땅일 경우 땅으로 인식하기
		{
			playerRb->SetFriction(250);
			playerRb->SetGround(true);

			value = Vector2(pos.x + 62.5, pos.y + 122);
			while (mImage->GetPixel(value.x, value.y) != air
				&& mImage->GetPixel(value.x, value.y != NULL
				&& mImage->GetPixel(value.x, value.y) != blueloop
				&& mImage->GetPixel(value.x, value.y) != greenloop
				&& mImage->GetPixel(value.x, value.y) != redloop
				&& mImage->GetPixel(value.x, value.y) != greyloop
				&& mPlayer->GetSonicState() != Sonic::eSonicState::death))
			{
				pos.y -= 1;
				value.y -= 1;
				playerTr->SetPos(pos);
			}
			value = Vector2(pos.x + 62.5, pos.y + 122);
			while (mImage->GetPixel(value.x, value.y) == greenloop && mGreen == true)
			{
				pos.y -= 1;
				value.y -= 1;
				playerTr->SetPos(pos);
			}
			//while (mImage->GetPixel(value.x, value.y) == blueloop && mBlue == true)
			//{
			//	pos.y -= 1;
			//	value.y -= 1;
			//	playerTr->SetPos(pos);
			//}
		}
		if (myupcolor != air
			&& myupcolor != NULL
			&& myupcolor != greyloop
			&& myupcolor != redloop
			&& myupcolor != yellowloop
			&& myupcolor != greenloop
			&& myupcolor != blueloop
			&& mPlayer->GetSonicState() != Sonic::eSonicState::death)  // 내 머리가 땅일 경우 땅으로 인식하기
		{
			playerRb->SetGround(false);
			
			value = Vector2(pos.x + 62.5, pos.y + 20);
			while (mImage->GetPixel(value.x, value.y) != air
				&& mImage->GetPixel(value.x, value.y) != NULL
				&& mImage->GetPixel(value.x, value.y) != yellowloop
				&& mImage->GetPixel(value.x, value.y) != blueloop
				&& mImage->GetPixel(value.x, value.y) != greyloop
				&& mImage->GetPixel(value.x, value.y) != redloop
				&& mImage->GetPixel(value.x, value.y) != greenloop


				&& mPlayer->GetSonicState() != Sonic::eSonicState::death)
			{
				pos.y += 1;
				value.y += 1;
				playerTr->SetPos(pos);

			}

			//while (mImage->GetPixel(value.x, value.y) == blueloop)
			//{
			//	pos.x += 1;				
			//	value.x += 1;
			//	playerTr->SetPos(pos);
			//}
		}
		if (myleftcolor != air
			&& myleftcolor != NULL
			&& myleftcolor != greyloop
			&& myleftcolor != redloop
			&& myleftcolor != greenloop
			&& myleftcolor != blueloop
			&& mPlayer->GetSonicState() != Sonic::eSonicState::death);
		{
			value = Vector2(pos.x + 32.5, pos.y + 50);

			while (mImage->GetPixel(value.x, value.y) != air
				&& mImage->GetPixel(value.x, value.y) != NULL
				&& mImage->GetPixel(value.x, value.y) != RGB(0, 127, 0)
				&& mImage->GetPixel(value.x, value.y) != greyloop
				&& mImage->GetPixel(value.x, value.y) != redloop
				&& mImage->GetPixel(value.x, value.y) != yellowloop
				&& mImage->GetPixel(value.x, value.y) != blueloop
				&& mImage->GetPixel(value.x, value.y) != greenloop
				&& mPlayer->GetSonicState() != Sonic::eSonicState::death)
			{
				velocity.x = 0;
				playerRb->SetVelocity(velocity);
				pos.x += 1;
				value.x += 1;
				playerTr->SetPos(pos);
			}
			while (mImage->GetPixel(value.x, value.y) == yellowloop)

			{
				pos.y += 1;
				value.y += 1;
				playerTr->SetPos(pos);
			}
			while (mImage->GetPixel(value.x, value.y) == blueloop)
			{
				pos.x += 1;
				value.x += 1;
				playerTr->SetPos(pos);
			}
			while (mImage->GetPixel(value.x, value.y) == RGB(0, 127, 0))

			{
				pos.x += 1;
				value.x += 1;
				playerTr->SetPos(pos);
			}
		} 
  		if (myrightcolor != air
			&& myrightcolor != NULL
			&& myrightcolor != blueloop
			&& myrightcolor != greyloop
			&& myrightcolor != redloop
			&& myrightcolor != greenloop
			&& mPlayer->GetSonicState() != Sonic::eSonicState::death)// 내 오른쪽이 땅일 경우 땅으로 인식하기
		{
			value = Vector2(pos.x + 92.5, pos.y + 50);

			while (mImage->GetPixel(value.x, value.y) != air
				&& mImage->GetPixel(value.x, value.y) != NULL
				&& mImage->GetPixel(value.x, value.y) != RGB(0, 127, 0)
				&& mImage->GetPixel(value.x, value.y) != greyloop
				&& mImage->GetPixel(value.x, value.y) != redloop
				&& mImage->GetPixel(value.x, value.y) != yellowloop
				&& mImage->GetPixel(value.x, value.y) != blueloop
				&& mImage->GetPixel(value.x, value.y) != greenloop
				&& mPlayer->GetSonicState() != Sonic::eSonicState::death)
			{
				velocity.x = 0;
				playerRb->SetVelocity(velocity);
				pos.x -= 1;
				value.x -= 1;
				playerTr->SetPos(pos);
			}

			while (mImage->GetPixel(value.x, value.y) == yellowloop || mImage->GetPixel(value.x, value.y) == RGB(0, 127, 0))
			{
				pos.x -= 1;
				value.x -= 1;
				playerTr->SetPos(pos);
			}

		}

		// --------------------------------------------- 픽셀검사 후 방향벡터 설정
		if (playerRb->GetVelocity().x > 0.0f
			&& playerRb->GetGround() == true)
		{
			if (mPlayer->GetSonicState() == Sonic::eSonicState::run_left)
			{
				mPlayer->SetSonicState(Sonic::eSonicState::run_right);
			}
			else if (mPlayer->GetSonicState() == Sonic::eSonicState::rolling_left)
			{
				mPlayer->SetSonicState(Sonic::eSonicState::rolling_right);
			}

			for (size_t i = 0; i < 114; i++)
			{
				if (mImage->GetPixel(pos.x + 82.5, pos.y + 20 + i) != air
					&& mImage->GetPixel(pos.x + 82.5, pos.y + 20 + i) != NULL
					&& mImage->GetPixel(pos.x + 82.5, pos.y + 20 + i) != greyloop
					&& mImage->GetPixel(pos.x + 82.5, pos.y + 20 + i) != redloop
					&& mImage->GetPixel(pos.x + 82.5, pos.y + 20 + i) != yellowloop
					&& mImage->GetPixel(pos.x + 82.5, pos.y + 20 + i) != blueloop
					&& mImage->GetPixel(pos.x + 82.5, pos.y + 20 + i) != greenloop
					)
				{
					if (i > 94)
					{
						mFrontpos = Vector2(1, 1).Nomalize();
					}
					else
					{
						mFrontpos = Vector2(pos.x + 82.5, pos.y + 20 + i);
						mFrontpos.Nomalize();
					}
					break;
				}
			}
		}
		else if (playerRb->GetVelocity().x < 0.0f
			&& playerRb->GetGround() == true)
		{
			if (mPlayer->GetSonicState() == Sonic::eSonicState::run_right)
			{
				mPlayer->SetSonicState(Sonic::eSonicState::run_left);
			}
			else if (mPlayer->GetSonicState() == Sonic::eSonicState::rolling_right)
			{
				mPlayer->SetSonicState(Sonic::eSonicState::rolling_left);
			}
			for (size_t i = 0; i < 114; i++)
			{
				if (mImage->GetPixel(pos.x + 42.5, pos.y + 20 + i) != air
					&& mImage->GetPixel(pos.x + 42.5, pos.y + 20 + i) != NULL
					&& mImage->GetPixel(pos.x + 42.5, pos.y + 20 + i) != greyloop
					&& mImage->GetPixel(pos.x + 42.5, pos.y + 20 + i) != redloop
					&& mImage->GetPixel(pos.x + 42.5, pos.y + 20 + i) != yellowloop
					&& mImage->GetPixel(pos.x + 42.5, pos.y + 20 + i) != blueloop
					&& mImage->GetPixel(pos.x + 42.5, pos.y + 20 + i) != greenloop
					)
				{
					if (i > 94)
					{
						mFrontpos = Vector2(-1, 1).Nomalize();
					}
					else
					{
						mFrontpos = Vector2(pos.x + 42.5, pos.y + 20 + i);
						mFrontpos.Nomalize();
					}
					break;
				}
			}
		}
		// ---------------------------------------------
		// --------------------------------------------- 픽셀검사 후 속도 조정

		int pixel[2] = { 60, 60 };

		for (size_t j = 0; j < 2; j++)
		{
			for (size_t i = 0; i < 100; i++)
			{
				if (mImage->GetPixel(pos.x + 42.5 + (j * 42.5), pos.y + 60 + i) != air
					|| i == 99)
				{
					pixel[j] = 60 + i;
					break;
				}

			}
		}

		if (pixel[0] != pixel[1])
		{
			playerRb->AddVelocity(Vector2((pixel[1] - pixel[0]) / 5, 0));
		}

		// ----------------------------------------




		if (myfootdowncolor == air)
		{
			playerRb->SetGround(false);
		}



		// --------------------------------------------- 워터점프
		if (mPlayer->GetSonicState() == Sonic::eSonicState::waterjump
			&& mPlayer->mWater)
		{
			if (playerRb->GetGround() == true && mPlayer->GetWaterJump() == true)
			{
				velocity.y = -750.0f;
				playerRb->SetVelocity(velocity);
				playerRb->SetGround(false);
			}
			if (playerRb->GetGround() == true)
			{
				mPlayer->SetWaterJump(false);
			}
		}

		// ---------------------------------------------
		if (myrightcolor == yellowloop || myrightupcolor == yellowloop)
		{
			if (Input::GetKeyDown(eKeyCode::Space))
			{
				playerRb->SetGround(false);
				playerRb->SetGravity(Vector2(0, 800));
			}
			for (size_t i = 0; i < 114; i++)
			{
				if (mImage->GetPixel(pos.x + 10 + i, pos.y + 50) == yellowloop)
				{
					mFrontpos = (Vector2(pos.x + 10 + i, pos.y + 50) - Vector2(pos.x + 92.5, pos.y + 123)).Nomalize();
					playerRb->SetGravity(Vector2(mFrontpos.x, -1.0f * fabs(velocity.y * mFrontpos.y)));
					playerRb->SetVelocity(Vector2(velocity.x, -1.0f * fabs(velocity.Length() * mFrontpos.y)));
				}
			}
		}


		//if (myfootcolor == greenloop && mGreen == true)
		//{
		//	value = Vector2(pos.x + 62.5, pos.y + 123);
		//	while (mImage->GetPixel(value.x, value.y) != air && mGreen == true)
		//	{
		//		pos.y -= 1;
		//		value.y -= 1;
		//		playerTr->SetPos(pos);
		//	}

		//}
		//

		//if (myrightcolor == yellowloop && mYellow == true && myfootdowncolor != redloop)
		//{
		//	mGreen = false;
		//	if (Input::GetKeyDown(eKeyCode::Space))
		//	{
		//		playerRb->SetGround(false);
		//		playerRb->SetGravity(Vector2(0, 800));
		//	}
		//	for (size_t i = 0; i < 114; i++)
		//	{
		//		if (mImage->GetPixel(pos.x + 10 + i, pos.y + 50) == yellowloop)
		//		{
		//			mFrontpos = (Vector2(pos.x + 10 + i, pos.y + 50) - Vector2(pos.x + 92.5, pos.y + 123)).Nomalize();
		//			//playerRb->SetGravity(Vector2(mFrontpos.x, -1.0f * fabs(velocity.y * mFrontpos.y)));
		//			playerRb->SetVelocity(Vector2(velocity.x, -1.0f * fabs(velocity.Length() * mFrontpos.y)));
		//		}
		//	}
		//}

		//if (myfootcolor == blueloop)
		//{
		//	mYellow = true;
		//	mGreen = true;
		//	if (Input::GetKeyDown(eKeyCode::Space)
		//		&& mPlayer->GetSonicState() != Sonic::eSonicState::hang_left
		//		&& mPlayer->GetSonicState() != Sonic::eSonicState::hang_right)
		//	{
		//		playerRb->SetGround(false);
		//		playerRb->SetGravity(Vector2(0, 800));
		//	}
		//}
		//
		//if (myfootdowncolor == redloop)
		//{
		//	playerRb->AddVelocity(Vector2(-50.0f, -10.0f));
		//	mFrontpos = Vector2(0, 800).Nomalize();
		//	playerRb->SetGravity(Vector2(0, 800));
		//	if (Input::GetKeyDown(eKeyCode::Space)
		//		&& mPlayer->GetSonicState() != Sonic::eSonicState::hang_left
		//		&& mPlayer->GetSonicState() != Sonic::eSonicState::hang_right)
		//	{
		//		playerRb->SetGround(false);
		//		playerRb->SetGravity(Vector2(0, 800));
		//	}
		//}

		//if (myrightrightcolor == greyloop || myleftcolor == greyloop || myrightcolor == greyloop || myupcolor == greyloop || myfootcolor == blueloop)
		//{
		//	playerRb->AddVelocity(Vector2(50.0f, 0.0f));
		//	mFrontpos = Vector2(0, 800).Nomalize();
		//	playerRb->SetGravity(Vector2(0, 800));
		//	if (Input::GetKeyDown(eKeyCode::Space)
		//		&& mPlayer->GetSonicState() != Sonic::eSonicState::hang_left
		//		&& mPlayer->GetSonicState() != Sonic::eSonicState::hang_right)
		//	{
		//		playerRb->SetGround(false);
		//		playerRb->SetGravity(Vector2(0, 800));
		//	}

		//}

		//if (myrightcolor == yellowloop
		//	|| myleftcolor == yellowloop
		//	|| myrightupcolor == yellowloop
		//	|| myleftupcolor == yellowloop
		//	|| myleftcolor == blueloop
		//	|| myfootdowncolor == redloop
		//	|| myupcolor == greyloop)
		//	{
		//		mPlayer->SetSonicState(Sonic::eSonicState::rolling_right);
		//}

		if (Input::GetKeyDown(eKeyCode::Space)
			&& mPlayer->GetSonicState() != Sonic::eSonicState::hang_left
			&& mPlayer->GetSonicState() != Sonic::eSonicState::hang_right)
		{
			playerRb->SetGround(false);
			playerRb->SetGravity(Vector2(0, 800));
		}
		if (myupcolor == air && myrightcolor == air && myleftcolor == air && myfootcolor == air)
		{
			playerRb->SetGround(false);
			playerRb->SetGravity(Vector2(0, 800));
		}







		// --------------------------------------------- 오브젝트 위에 설 수 있음
		for (GameObject* obj : mObject)
		{
			if (obj == nullptr)
				continue;

			if (obj->mUse == true)
			{
				playerRb->SetGround(true);

				if (dynamic_cast<Rope*>(obj))
				{
					playerTr->SetPos(obj->GetComponent<Collider>()->GetPos());
				}
				else
				{
					value = Vector2(pos.x + 62.5, pos.y + 123);
					while (obj->GetComponent<Collider>()->GetPos().y < value.y)
					{
						pos.y -= 1;
						value.y -= 1;
						playerTr->SetPos(pos);
					}
				}
			}
			else if (obj->mUse == false)
			{
				if (obj->mUse == false && obj == dynamic_cast<MapRock_l*>(obj))
				{
					if (dynamic_cast<MapRock_l*>(obj)->mOn)
					{

						value = Vector2(pos.x + 62.5, pos.y + 123);
						while (obj->GetComponent<Collider>()->GetPos().y < value.y)
						{
							pos.y -= 1;
							value.y -= 1;
							playerTr->SetPos(pos);
						}
					}
				}
				else
				{

				}
			}
			

		}
		// --------------------------------------------- 스프링
		for (Spring* spring : mSpring)
		{
			if (spring == nullptr)
				continue;

			if (spring->mUse)
			{
				playerRb->SetGround(false);
			}
		}
		// --------------------------------------------- 점프 혹은 다치거나 죽었을 때
		if (Input::GetKeyDown(eKeyCode::Space)
			|| Input::GetKey(eKeyCode::Space)
			|| mPlayer->GetSonicState() == Sonic::eSonicState::hurt_left
			|| mPlayer->GetSonicState() == Sonic::eSonicState::hurt_right
			|| mPlayer->GetSonicState() == Sonic::eSonicState::death)
		{
			playerRb->SetGravity(Vector2(0, 800));
			playerRb->SetGround(false);
		}

}

	void Ground::Render(HDC hdc)
	{
		GameObject::Render(hdc);

		Transform* playerTr = mPlayer->GetComponent<Transform>();
		Vector2 ppos = playerTr->GetPos();
		//pos.x + 82.5, pos.y + 20
		ppos.x += 42.5;
		ppos.y += 123;
		Vector2 cpos = Camera::CalculatePos(Vector2::Zero);
		Vector2 pos = cpos;
		if (mOnOff == true) 
		{
			TransparentBlt(hdc, static_cast<int>(pos.x), static_cast<int>(pos.y),
				mImage->GetWidth(), mImage->GetHeight(),
				mImage->GetHdc(), 0, 0,
				mImage->GetWidth(), mImage->GetHeight(), RGB(255, 0, 255));

			//HPEN pen = CreatePen(BS_SOLID, 2, RGB(255, 255, 255));
			//HBRUSH brush = CreateSolidBrush(RGB(255, 255, 0));
			//brush = (HBRUSH)SelectObject(hdc, brush);
			//pen = (HPEN)SelectObject(hdc, pen);
			//Ellipse(hdc, Camera::CalculatePos(ppos).x - 2, Camera::CalculatePos(ppos).y - 2, Camera::CalculatePos(ppos).x + 2, Camera::CalculatePos(ppos).y + 2);
		}

	}

	void Ground::Release()
	{
	}

	void Ground::OnCollisionEnter(Collider* other)
	{
	}

	void Ground::OnCollisionStay(Collider* other)
	{

	}

	void Ground::OnCollisionExit(Collider* other)
	{

	}

}
