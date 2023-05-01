#include "sgBomber.h"
#include "sgBomberboom.h"

#include "sgImage.h"
#include "sgResources.h"
#include "sgTime.h"
#include "sgObject.h"
#include "sgSound.h"

#include "sgTransform.h"
#include "sgAnimator.h"
#include "sgRigidbody.h"


namespace sg
{
	Bomber::Bomber()
		: mTime(0.0f)
		, mthrowBomb(false)
		, mBombindex(0)
	{
		SetName(L"Bomber");
	}
	Bomber::~Bomber()
	{
	}
	void Bomber::Initialize()
	{

		mTr = GetComponent<Transform>();
		mAni = AddComponent<Animator>();
		sBomb = Resources::Load<Sound>(L"bomb", L"..\\Resources\\sound\\bomber_throwbomb.wav");

		Image* bomber = Resources::Load<Image>(L"bomber", L"..\\Resources\\enemies\\bomber.bmp");
		mAni->CreateAnimation(L"bomberani", bomber, Vector2::Zero, 4, 1, 4, Vector2::Zero, 0.05);
		mAni->Play(L"bomberani", true);
		Vector2 pos = mTr->GetPos();

		mBomb[0] = object::Instantiate<Bomberbomb>(Vector2(pos.x + 1123, pos.y + 64), eLayerType::Bomb, eSceneType::Play2);
		mBomb[1] = object::Instantiate<Bomberbomb>(Vector2(pos.x + 1003, pos.y + 64), eLayerType::Bomb, eSceneType::Play2);
		mBomb[2] = object::Instantiate<Bomberbomb>(Vector2(pos.x + 1123, pos.y + 64), eLayerType::Bomb, eSceneType::Play2);
		mBomb[3] = object::Instantiate<Bomberbomb>(Vector2(pos.x + 1003, pos.y + 64), eLayerType::Bomb, eSceneType::Play2);
		mBomb[4] = object::Instantiate<Bomberbomb>(Vector2(pos.x + 803, pos.y + 64), eLayerType::Bomb, eSceneType::Play2);
		mBomb[5] = object::Instantiate<Bomberbomb>(Vector2(pos.x + 683, pos.y + 64), eLayerType::Bomb, eSceneType::Play2);
		mBomb[6] = object::Instantiate<Bomberbomb>(Vector2(pos.x + 803, pos.y + 64), eLayerType::Bomb, eSceneType::Play2);
		mBomb[7] = object::Instantiate<Bomberbomb>(Vector2(pos.x + 683, pos.y + 64), eLayerType::Bomb, eSceneType::Play2);
		mBomb[8] = object::Instantiate<Bomberbomb>(Vector2(pos.x + 483, pos.y + 64), eLayerType::Bomb, eSceneType::Play2);
		mBomb[9] = object::Instantiate<Bomberbomb>(Vector2(pos.x + 363, pos.y + 64), eLayerType::Bomb, eSceneType::Play2);
		mBomb[10] = object::Instantiate<Bomberbomb>(Vector2(pos.x + 483, pos.y + 64), eLayerType::Bomb, eSceneType::Play2);
		mBomb[11] = object::Instantiate<Bomberbomb>(Vector2(pos.x + 363, pos.y + 64), eLayerType::Bomb, eSceneType::Play2);
		mBomb[12] = object::Instantiate<Bomberbomb>(Vector2(pos.x + 203, pos.y + 64), eLayerType::Bomb, eSceneType::Play2);
		mBomb[13] = object::Instantiate<Bomberbomb>(Vector2(pos.x + 203, pos.y + 64), eLayerType::Bomb, eSceneType::Play2);

		GameObject::Initialize();
	}
	void Bomber::Update()
	{
		GameObject::Update();

		Vector2 pos = mTr->GetPos();

		if (mthrowBomb == false)
		{
			mBomb[0]->GetComponent<Transform>()->SetPos(Vector2(pos.x + 1123, pos.y + 64));
			mBomb[1]->GetComponent<Transform>()->SetPos(Vector2(pos.x + 1003, pos.y + 64));
			mBomb[2]->GetComponent<Transform>()->SetPos(Vector2(pos.x + 1123, pos.y + 64));
			mBomb[3]->GetComponent<Transform>()->SetPos(Vector2(pos.x + 1003, pos.y + 64));
			mBomb[4]->GetComponent<Transform>()->SetPos(Vector2(pos.x + 803, pos.y + 64));
			mBomb[5]->GetComponent<Transform>()->SetPos(Vector2(pos.x + 683, pos.y + 64));
			mBomb[6]->GetComponent<Transform>()->SetPos(Vector2(pos.x + 803, pos.y + 64));
			mBomb[7]->GetComponent<Transform>()->SetPos(Vector2(pos.x + 683, pos.y + 64));
			mBomb[8]->GetComponent<Transform>()->SetPos(Vector2(pos.x + 483, pos.y + 64));
			mBomb[9]->GetComponent<Transform>()->SetPos(Vector2(pos.x + 363, pos.y + 64));
			mBomb[10]->GetComponent<Transform>()->SetPos(Vector2(pos.x + 483, pos.y + 64));
			mBomb[11]->GetComponent<Transform>()->SetPos(Vector2(pos.x + 363, pos.y + 64));
			mBomb[12]->GetComponent<Transform>()->SetPos(Vector2(pos.x + 203, pos.y + 64));
			mBomb[13]->GetComponent<Transform>()->SetPos(Vector2(pos.x + 203, pos.y + 64));
		}
		else if (mthrowBomb)
		{
			mTime += Time::DeltaTime();

			if (mTime >= 0.5f
				&& mBombindex < 14)
			{
				mBomb[mBombindex]->mDown = true;
				sBomb->Play(false);
				mBombindex++;
				mTime = 0.0f;
			}
		}
			

	}
	void Bomber::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void Bomber::Release()
	{
		GameObject::Release();
	}
}