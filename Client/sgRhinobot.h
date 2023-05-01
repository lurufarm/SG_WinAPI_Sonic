#pragma once
#include "sgGameObject.h"

namespace sg
{
	class Animator;
	class Collider;
	class Rigidbody;
	class Rhinobot : public GameObject
	{
	public:
		Rhinobot();
		~Rhinobot();

		enum class eRhinoState
		{
			idle_left,
			idle_right,
			move_left,
			move_right,
			death,
		};

		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);
		virtual void Release();
		void SetSonic(GameObject* sonic) { mSonic = sonic; }

		virtual void OnCollisionEnter(class Collider* other);
		virtual void OnCollisionStay(class Collider* other);
		virtual void OnCollisionExit(class Collider* other);

	private:

		void idle_left();
		void idle_right();
		void move_left();
		void move_right();
		void death();


		eRhinoState mRhinoState;
		Animator* mAnimator;
		Collider* mCollider;
		Rigidbody* mRigidbody;

		Vector2 mOriginPos;
		float mTime;
		float mAbility;
		GameObject* mSonic;

		class Sound* sMove;
		class Sound* sDeath;
		class Sound* sBoom;

	};
}

