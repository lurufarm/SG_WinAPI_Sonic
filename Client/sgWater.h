#pragma once
#include "sgGameObject.h"

namespace sg
{
	class Water : public GameObject
	{
	public:
		Water();
		Water(Vector2 scale, Vector2 pos);
		~Water();

		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);
		virtual void Release();

		virtual void OnCollisionEnter(class Collider* other);
		virtual void OnCollisionStay(class Collider* other);
		virtual void OnCollisionExit(class Collider* other);

		void SetWaterScale(Vector2 scale) { mScale = scale; }

	private:

		class Transform* mTr;
		class Collider* mCol;
		class Animator* mAni;

		class Image* mWater;
		Vector2 mScale;
		Vector2 mWaterPos;
	};
}
