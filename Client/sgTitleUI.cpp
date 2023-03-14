#include "sgTitleUI.h"
#include "sgTitleScene.h"

#include "sgInput.h"
#include "sgSceneManager.h"
#include "sgResources.h"
#include "sgTransform.h"
#include "sgScene.h"
#include "sgObject.h"


namespace sg
{
	TitleUI::TitleUI()
	{
	}
	TitleUI::~TitleUI()
	{
	}


	void TitleUI::Initialize()
	{
		mGamestart = Resources::Load<Image>(L"intro_gamestart", L"..\\Resources\\intro\\intro_gamestart.bmp");
		mExit = Resources::Load<Image>(L"intro_exit", L"..\\Resources\\intro\\intro_exit.bmp");
		
		mState = eUIState::gamestart;


		GameObject::Initialize();

	}
	void TitleUI::Update()
	{
		GameObject::Update();

	}
	void TitleUI::Render(HDC hdc)
	{
		switch (mState)
		{	
		case sg::TitleUI::eUIState::gamestart:
			TransparentBlt(hdc, 390, 690, mGamestart->GetWidth()*3.5, mGamestart->GetHeight()*3.5,
				mGamestart->GetHdc(), 0, 0, mGamestart->GetWidth(), mGamestart->GetHeight(), RGB(255, 0, 255));
			gamestart();
			break;
		case sg::TitleUI::eUIState::exit:
			TransparentBlt(hdc, 390, 690, mExit->GetWidth()*3.5, mExit->GetHeight()*3.5,
				mExit->GetHdc(), 0, 0, mExit->GetWidth(), mExit->GetHeight(), RGB(255, 0, 255));
			exit();
			break;
		}
		GameObject::Render(hdc);
	}
	void TitleUI::Release()
	{
		GameObject::Release();
	}
	void TitleUI::gamestart()
	{
		if (Input::GetKeyDown(eKeyCode::Up) ||
			Input::GetKeyDown(eKeyCode::Down))
		{
			mState = eUIState::exit;
		}
		if (Input::GetKeyDown(eKeyCode::Enter))
		{
			SceneManager::LoadScene(eSceneType::Play);
		}

	}
	void TitleUI::exit()
	{
		if (Input::GetKeyDown(eKeyCode::Up) ||
			Input::GetKeyDown(eKeyCode::Down))
		{
			mState = eUIState::gamestart;
		}

		if (Input::GetKeyDown(eKeyCode::Enter))
		{
		}
	}
}