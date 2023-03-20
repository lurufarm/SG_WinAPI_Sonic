#pragma once
#include "YamYamEngine.h"

namespace sg
{
	class GameObject;
	class Camera
	{
	public:
		enum class eCameraEffectType
		{
			None,
			FadeIn,
			FadeOut,
			//Shake,
			End,
		};

		static void Initialize();
		static void Update();
		static void Render(HDC hdc);
		static void Clear();

		static void SetTarget(GameObject* target) { mTarget = target; }
		static Vector2 GetCameraPos() { return mLookPos; }
		static Vector2 CalculatePos(Vector2 pos) { return pos - mDistance; }

	private:
		static Vector2 mResolution;
		static Vector2 mLookPos;
		static Vector2 mDistance;
		static GameObject* mTarget;

		static eCameraEffectType mType;
		static class Image* mCurtain;
		static float mCurtainAlpha;
		static float mAlphaTime;
		static float mEndTime;
	};
}

