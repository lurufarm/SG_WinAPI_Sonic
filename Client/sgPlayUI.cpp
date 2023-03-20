#include "sgPlayUI.h"
#include "sgSonic.h"
#include "sgPlayScene.h"

#include "sgTime.h"
#include "sgInput.h"
#include "sgSceneManager.h"
#include "sgResources.h"
#include "sgTransform.h"
#include "sgAnimator.h"
#include "sgCamera.h"
#include "sgCollider.h"

namespace sg
{
	Sonic* PlayUI::mPlayer = nullptr;
	PlayUI::PlayUI()
		: value(0)
	{
	}

	PlayUI::~PlayUI()
	{
	}

	void PlayUI::Initialize()
	{
		GameObject::Initialize();
	}
	void PlayUI::Update()
	{
		GameObject::Update();
	}
	void PlayUI::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void PlayUI::Release()
	{
		GameObject::Release();
	}
}