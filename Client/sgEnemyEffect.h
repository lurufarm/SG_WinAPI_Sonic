#pragma once
#include "sgGameObject.h"

namespace sg
{

	class EnemyEffect : public GameObject
	{
	public:
		EnemyEffect();
		~EnemyEffect();

		enum class eEEState
		{
			None,
			MBA_left,
			MBA_right,
			MBA_explosion,
			explosion,
		};

		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);
		virtual void Release();

		virtual void OnCollisionEnter(class Collider* other);
		virtual void OnCollisionStay(class Collider* other);
		virtual void OnCollisionExit(class Collider* other);

		void SetTarget(class Miniboss* target) { mMB = target; }
		void SetTarget(class Lastboss* target) { mLB = target; }
		void SetEEState(eEEState state) { mEEState = state; }

	private:

		void None();
		void MBA_left();
		void MBA_right();
		void MBA_explosion();
		void explosion();

		eEEState mEEState;

		class Miniboss* mMB;
		class Lastboss* mLB;

		class Transform* mTr;
		class Animator* mAni;
		class Collider* mCol;
		
		float mTime;

	};
}

