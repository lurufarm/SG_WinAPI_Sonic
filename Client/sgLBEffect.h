#pragma once
#include "sgGameObject.h"

namespace sg
{
	class LBEffect : public GameObject
	{
	public:

		enum class eLBE
		{
			splash,
			fire,
			fire2,
			explosion,
		};

		LBEffect(eLBE a);
		~LBEffect();

		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);
		virtual void Release();

		virtual void OnCollisionEnter(class Collider* other);
		virtual void OnCollisionStay(class Collider* other);
		virtual void OnCollisionExit(class Collider* other);
		void SetTarget(class Lastboss* target) { mTarget = target; }

	private:

		void splash();
		void fire();
		void fire2();
		void explosion();

		eLBE mLBEState;

		class Transform* mTr;
		class Animator* mAni;
		class Collider* mCol;

		class Lastboss* mTarget;
		bool mDir;

	};
}

