#pragma once
#include "sgGameObject.h"

namespace sg
{
	class Effect2 : public GameObject
	{
	public:

		Effect2();
		~Effect2();

		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);
		virtual void Release();

		void SetTarget(GameObject* target) { mTarget = target; }
		void SetEffect(Effect* effect) { mEffect = effect; }

		virtual void OnCollisionEnter(class Collider* other);
		virtual void OnCollisionStay(class Collider* other);
		virtual void OnCollisionExit(class Collider* other);

		static bool mFlame;

	private:


		class Animator* mAni;
		class Transform* mTr;

		Effect* mEffect;
		GameObject* mTarget;

	};

}

