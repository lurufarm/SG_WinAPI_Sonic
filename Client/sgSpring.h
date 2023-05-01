#pragma once
#include "sgGameObject.h"

namespace sg
{
	class Spring : public GameObject
	{
	public:
		Spring(int a);
		Spring();
		~Spring();

		enum class eSpringState
		{
			up_norm,
			up_use,
			right_norm,
			right_use,
			left_norm,
			left_use,
		};

		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);
		virtual void Release();

		virtual void OnCollisionEnter(class Collider* other);
		virtual void OnCollisionStay(class Collider* other);
		virtual void OnCollisionExit(class Collider* other);

		virtual eSpringState GetState() { return mSpringState; }
		void SetDirection(int num) 
		{
			if (num == 0)
			{
				mSpringState = eSpringState::up_norm;
			}
			else if (num == 1)
			{
				mSpringState = eSpringState::right_norm;
			}
			else if (num == 2)
			{
				mSpringState = eSpringState::left_norm;
			}
		}

	private:

		void up_norm();
		void up_use();
		void right_norm();
		void right_use();
		void left_norm();
		void left_use();

		class Transform* mTr;
		class Animator* mAnimator;
		class Collider* mCollider;
		eSpringState mSpringState;

		class Sound* sSpring;
		int direction;
	};
};

