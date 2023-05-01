#pragma once
#include "sgGameObject.h"
namespace sg
{

	class Miniboss : public GameObject
	{

	public:
		Miniboss();
		~Miniboss();

		enum class eMBState {
			idle,
			move_up,
			move,
			attack,
			attacked,
			death,
		};

		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);
		virtual void Release();

		virtual void OnCollisionEnter(class Collider* other);
		virtual void OnCollisionStay(class Collider* other);
		virtual void OnCollisionExit(class Collider* other);
		eMBState GetMBState() { return mMBState; }
		void SetPlayer(GameObject* player) { mPlayer = player; }

	private:

		void idle();
		void move_up();
		void move();
		void attack();
		void attacked();
		void death();

		int hp;
		bool mDir;
		bool mUp;
		bool mDeath;
		float mTime;
		eMBState mMBState;

		class Animator* mAni;
		class Transform* mTr;
		class Collider* mCol;

		GameObject* mPlayer;
		class EnemyEffect* mMeffect;

		class Sound* sAttacked;
		class Sound* sExp;

	};

};
