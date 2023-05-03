#include "sgEndingScene.h"
#include "sgEndST.h"
#include "sgTitlebg.h"
#include "sgSonic.h"
#include "sgPlayScene.h"
#include "sgPlayScene2.h"

#include "sgInput.h"
#include "sgResources.h"
#include "sgSound.h"
#include "sgTime.h"

#include "sgApplication.h"
#include "sgCamera.h"
#include "sgSceneManager.h"
#include "sgObject.h"

extern sg::Application application;
extern sg::Sonic* mSonic;
extern sg::Sonic* mSonic2;

namespace sg
{
	EndingScene::EndingScene()
	{
	}
	EndingScene::~EndingScene()
	{
	}
	void EndingScene::Initialize()
	{
		mTarget = object::Instantiate<Titlebg>(Vector2(0, 0), eLayerType::BG, eSceneType::Ending);
		object::Instantiate<Titlebg>(Vector2(-250, -500), eLayerType::BG, eSceneType::Ending);
		EndST* st = object::Instantiate<EndST>(Vector2(-250, 0), eLayerType::BG2, eSceneType::Ending);

		mFont = {};
		mFont.lfHeight = 100;
		mFont.lfWeight = FW_NORMAL;
		mFont.lfItalic = FALSE;
		mFont.lfCharSet = DEFAULT_CHARSET;
		wcscpy_s(mFont.lfFaceName, L"Impact");

	}
	void EndingScene::Update()
	{
		if (Input::GetKeyDown(eKeyCode::ESC))
		{
			SceneManager::LoadScene(eSceneType::Title);
		}

		Scene::Update();
	}
	void EndingScene::Render(HDC hdc)
	{
		Scene::Render(hdc);

		HFONT font = CreateFontIndirect(&mFont);
		SelectObject(hdc, font);
		SetBkMode(hdc, TRANSPARENT);
		SetTextColor(hdc, RGB(255, 255, 255));

		if (mSonic->GetLifeNumber() <= 0)
		{
			TextOut(hdc, 100, 100, L"Game Over", 9);
		}
		else
		{
			TextOut(hdc, 150, 300, L"Thank You for Watching!", 23);
		}

		mTime += Time::DeltaTime();

		if (mTime > 1.0f)
		{
			int Cnum = rand() % 2 + 3;
			mClouds.push_back(object::CloudsInstantiate(300, Cnum, eSceneType::Ending));
			mTime = 0.0;
		}
		if (mClouds.size() > 50)
		{
			mClouds.erase(mClouds.begin());
		}


	}
	void EndingScene::Release()
	{
		Scene::Release();
	}
	void EndingScene::OnEnter()
	{
		Camera::SetTarget(mTarget);
		mBG = Resources::Load<Sound>(L"EndingTheme", L"..\\Resources\\sound\\music\\ending.wav");
		mBG->Play(false);
	}
	void EndingScene::OnExit()
	{
		mBG->Stop(true);
	}
}