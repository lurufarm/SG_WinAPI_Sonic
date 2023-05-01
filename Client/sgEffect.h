#pragma once
#include "sgGameObject.h"

namespace sg
{
	class Effect : public GameObject
	{
	public:
		enum class eEffectState
		{
			None,
			Flame,
			Fire_dash,
			Thunder,
			Water,
			WaterJump,
		};

		Effect();
		~Effect();

		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);
		virtual void Release();

		virtual eEffectState GetEffectState() { return mEffectState; }
		static void SetEffectState(eEffectState state) { mEffectState = state; }
		virtual void SetTarget(class Sonic* target) { mTarget = target; }

		virtual void OnCollisionEnter(class Collider* other);
		virtual void OnCollisionStay(class Collider* other);
		virtual void OnCollisionExit(class Collider* other);

	private:

		void None();
		void Flame();
		void Thunder();
		void Water();
		void Fire_dash();
		void WaterJump();

		static eEffectState mEffectState;
		class Animator* mAni;
		class Transform* mTr;
		class Collider* mCol;

		class Sonic* mTarget;

	};

}

