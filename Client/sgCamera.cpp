#include "sgCamera.h"

#include "sgApplication.h"
#include "sgGameObject.h"
#include "sgTransform.h"
#include "sgInput.h"
#include "sgTime.h"
#include "sgImage.h"

#include "sgPlayScene.h"
#include "sgPlayScene2.h"
#include "sgSonic.h"
#include "sgLastboss.h"

extern sg::Application application;
extern sg::Sonic* mSonic;
extern sg::Sonic* mSonic2;

namespace sg
{
	Vector2 Camera::mResolution = Vector2::Zero;
	Vector2 Camera::mLookPos = Vector2::Zero;
	Vector2 Camera::mDistance = Vector2::Zero;
	//Sonic* Camera::mTarget = nullptr;
	GameObject* Camera::mTarget = nullptr;

	Camera::eCameraEffectType Camera::mType = Camera::eCameraEffectType::None;
	class Image* Camera::mCurtain = nullptr;
	float Camera::mCurtainAlpha = 1.0f;
	float Camera::mAlphaTime = 0.0f;
	float Camera::mEndTime = 3.0f;

	void Camera::Initialize()
	{
		mResolution.x = application.GetWidth();
		mResolution.y = application.GetHeight();
		//mLookPos = (mResolution / 2.0f);

		mType = eCameraEffectType::FadeIn;
		mCurtain = Image::Create(L"Curtain", mResolution.x, mResolution.y, RGB(0, 0, 0));

		if (mTarget != nullptr)
		{
			mLookPos.x = mTarget->GetComponent<Transform>()->GetPos().x + 300.0f;
			mLookPos.y = mTarget->GetComponent<Transform>()->GetPos().y - 100.0f;
		}
		//else if (mTarget == nullptr)
		//{
		//	mLookPos.x = mResolution.x / 2;
		//	mLookPos.x = mResolution.y / 2;
		//}


	}
	void Camera::Update()
	{

		if (Input::GetKey(eKeyCode::A))
			mLookPos.x -= 3000.0f * Time::DeltaTime();

		if (Input::GetKey(eKeyCode::D))
			mLookPos.x += 3000.0f * Time::DeltaTime();

		if (Input::GetKey(eKeyCode::W))
			mLookPos.y -= 3000.0f * Time::DeltaTime();

		if (Input::GetKey(eKeyCode::S))
			mLookPos.y += 3000.0f * Time::DeltaTime();

		if (mTarget != nullptr)
		{
			mLookPos.x = mTarget->GetComponent<Transform>()->GetPos().x + 300.0f;
			mLookPos.y = mTarget->GetComponent<Transform>()->GetPos().y - 100.0f;
		}

		if (mAlphaTime < mEndTime)
		{
			//255 = 1
			mAlphaTime += Time::DeltaTime();
			float ratio = (mAlphaTime / mEndTime);

			if (mType == eCameraEffectType::FadeIn)
			{
				mCurtainAlpha = 1.0f - ratio;
			}
			else if (mType == eCameraEffectType::FadeOut)
			{
				mCurtainAlpha = ratio;
			}
			else
			{

			}
		}

		mDistance = mLookPos - (mResolution / 2.0f);
	}
	void Camera::Render(HDC hdc)
	{
		if (mAlphaTime < mEndTime
			&& mType == eCameraEffectType::FadeIn)
		{
			BLENDFUNCTION func = {};
			func.BlendOp = AC_SRC_OVER;
			func.BlendFlags = 0;
			func.AlphaFormat = 0;
			func.SourceConstantAlpha = (BYTE)(255.0f * mCurtainAlpha);

			AlphaBlend(hdc, 0, 0
				, mResolution.x, mResolution.y
				, mCurtain->GetHdc()
				, 0, 0
				, mCurtain->GetWidth(), mCurtain->GetHeight()
				, func);
		}
		else if (mType == eCameraEffectType::FadeOut)
		{
			BLENDFUNCTION func = {};
			func.BlendOp = AC_SRC_OVER;
			func.BlendFlags = 0;
			func.AlphaFormat = 0;
			func.SourceConstantAlpha = (BYTE)(255.0f * mCurtainAlpha);

			AlphaBlend(hdc, 0, 0
				, mResolution.x, mResolution.y
				, mCurtain->GetHdc()
				, 0, 0
				, mCurtain->GetWidth(), mCurtain->GetHeight()
				, func);
		}
	}
	void Camera::Clear()
	{
		if (mTarget == nullptr)
		{
			mLookPos.x = 0;
			mLookPos.y = 0;
		}
		else {
			mLookPos.x = mTarget->GetComponent<Transform>()->GetPos().x + 300.0f;
			mLookPos.y = mTarget->GetComponent<Transform>()->GetPos().y - 100.0f;
			mDistance = Vector2::Zero;
		}
	}
}