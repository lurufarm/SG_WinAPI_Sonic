#include "sgPlayUI.h"
#include "sgSonic.h"
#include "sgPlayScene.h"

#include "sgImage.h"
#include "sgResources.h"
#include "sgTime.h"

#include "sgTransform.h"
#include "sgAnimator.h"


namespace sg
{
	PlayUI::PlayUI()
		: mPlayer(nullptr)
		, mTime(0.0f)
		, mTimeint(0)
		, mRings(0)
		, mLife(0)
	{
		SetName(L"UI");
	}

	PlayUI::~PlayUI()
	{
	}

	void PlayUI::Initialize()
	{
		mImage = Resources::Load<Image>(L"UI", L"..\\Resources\\object\\ui.bmp");


		mFont = {};
		mFont.lfHeight = 40;
		mFont.lfWeight = FW_NORMAL;
		mFont.lfItalic = FALSE;
		mFont.lfCharSet = DEFAULT_CHARSET;
		wcscpy_s(mFont.lfFaceName, L"Impact");
		
		mFont2 = {};
		mFont2.lfHeight = 18;
		mFont2.lfWeight = FW_NORMAL;
		mFont2.lfItalic = FALSE;
		mFont2.lfCharSet = DEFAULT_CHARSET;
		wcscpy_s(mFont.lfFaceName, L"Impact");

		GameObject::Initialize();
	}
	void PlayUI::Update()
	{
		GameObject::Update();

		mTime += Time::DeltaTime();
		if (mTime >= 1.0f)
		{
			mTimeint++;
			mTime = 0.0f;
		}
		mRings = mPlayer->GetRingNumber();
		mLife = mPlayer->GetLifeNumber();
	}
	void PlayUI::Render(HDC hdc)
	{
		GameObject::Render(hdc);

		TransparentBlt(hdc, 0, 0, mImage->GetWidth(), mImage->GetHeight(), mImage->GetHdc(), 0, 0, mImage->GetWidth(), mImage->GetHeight(), RGB(255, 0, 255));
		HFONT font = CreateFontIndirect(&mFont);
		HFONT oldfont = static_cast<HFONT>(SelectObject(hdc, font));
		HFONT font2 = CreateFontIndirect(&mFont2);
		HFONT oldfont2 = static_cast<HFONT>(SelectObject(hdc, font2));

		SelectObject(hdc, font);
		SetBkMode(hdc, TRANSPARENT);
		SetTextColor(hdc, RGB(255, 255, 255));
		std::wstring timeString = std::to_wstring(mTimeint);
		TextOut(hdc, 150, 25, timeString.c_str(), static_cast<int>(timeString.length()));

		std::wostringstream ringsStream;
		ringsStream << std::setw(2) << std::setfill(L'0') << mRings;
		std::wstring ringsString = ringsStream.str();
		TextOut(hdc, 150, 65, ringsString.c_str(), static_cast<int>(ringsString.length()));


		SelectObject(hdc, font2);
		std::wostringstream lifeStream;
		lifeStream << std::setw(1) << std::setfill(L'0') << mLife;
		std::wstring lifeString = lifeStream.str();
		TextOut(hdc, 102, 772, lifeString.c_str(), static_cast<int>(lifeString.length()));
		
		SelectObject(hdc, oldfont);
		DeleteObject(font);
		SelectObject(hdc, oldfont2);
		DeleteObject(font2);

	}
	void PlayUI::Release()
	{
		GameObject::Release();
	}
}