#include "sgCamera.h"

#include "sgApplication.h"
#include "sgGameObject.h"
#include "sgTransform.h"
#include "sgInput.h"
#include "sgTime.h"

extern sg::Application application;
namespace sg
{
	Vector2 Camera::mResolution = Vector2::Zero;
	Vector2 Camera::mLookPos = Vector2::Zero;
	Vector2 Camera::mDistance = Vector2::Zero;
	GameObject* Camera::mTarget = nullptr;

	void Camera::Initialize()
	{
		mResolution.x = application.GetWidth();
		mResolution.y = application.GetHeight();

		//mLookPos = (mResolution / 2.0f);

		if (mTarget != nullptr)
		{
			mLookPos.x = mTarget->GetComponent<Transform>()->GetPos().x + 300.0f;
			mLookPos.y = mTarget->GetComponent<Transform>()->GetPos().y - 100.0f;

		}


	}
	void Camera::Update()
	{
		if (Input::GetKey(eKeyCode::A))
			mLookPos.x -= 1000.0f * Time::DeltaTime();

		if (Input::GetKey(eKeyCode::D))
			mLookPos.x += 1000.0f * Time::DeltaTime();

		if (Input::GetKey(eKeyCode::W))
			mLookPos.y -= 1000.0f * Time::DeltaTime();

		if (Input::GetKey(eKeyCode::S))
			mLookPos.y += 1000.0f * Time::DeltaTime();


		if (mTarget != nullptr)
		{
			mLookPos.x = mTarget->GetComponent<Transform>()->GetPos().x + 400.0f;
			mLookPos.y = mTarget->GetComponent<Transform>()->GetPos().y - 100.0f;
		}

		mDistance = mLookPos - (mResolution / 2.0f);
	}
	void Camera::Clear()
	{
		mLookPos.x = mTarget->GetComponent<Transform>()->GetPos().x + 300.0f;
		mLookPos.y = mTarget->GetComponent<Transform>()->GetPos().y - 100.0f;
		mDistance = Vector2::Zero;
	}
}