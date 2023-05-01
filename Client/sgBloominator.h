#pragma once
#include "sgGameObject.h"

namespace sg
{
	class BloomBullet;
	class Animator;
	class Collider;
	class Rigidbody;
	class Bloominator : public GameObject
	{
	public:
		Bloominator();
		~Bloominator();

		enum class eBloomState
		{
			idle,
			shoot,
			//shoot_right,
			death,
		};

		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);
		virtual void Release();
		void SetSonic(Sonic* sonic) { mSonic = sonic; }

		virtual void OnCollisionEnter(class Collider* other);
		virtual void OnCollisionStay(class Collider* other);
		virtual void OnCollisionExit(class Collider* other);

	private:

		void idle();
		void shoot();
		//void shoot_right();
		void death();


		eBloomState mBloomState;
		Animator* mAnimator = AddComponent<Animator>();
		Collider* mCollider = AddComponent<Collider>();
		Rigidbody* mRigidbody = AddComponent<Rigidbody>();

		float mTime;
		float mAbility;
		Sonic* mSonic;
		bool mbShoot;
		BloomBullet* mLeftBullet;
		BloomBullet* mRightBullet;

		class Sound* sBullet;
		class Sound* sDeath;
		class Sound* sBoom;

	};
}

