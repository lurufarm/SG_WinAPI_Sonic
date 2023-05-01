#pragma once
#include "sgGameObject.h"

namespace sg
{
	class Lastboss : public GameObject
	{
	public:
		Lastboss();
		~Lastboss();

		enum class eLBState {

			idle,
			move_norm,
			changelayer,
			attack_log,
			attack_player,
			death,

		};


		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);
		virtual void Release();

		virtual void OnCollisionEnter(class Collider* other);
		virtual void OnCollisionStay(class Collider* other);
		virtual void OnCollisionExit(class Collider* other);

		void SetPlayer(GameObject* player) { mPlayer = player; }
		void SetLayer(eLayerType layer) { mLayer = layer; }

		bool mDir;
		bool mAttack_log;
		bool mStart;


	private:

		void idle();
		void move_norm();
		void changelayer();
		void attack_log();
		void attack_player();
		void death();

		eLBState mLBState;
		eLayerType mLayer;

		GameObject* mPlayer;
		class LastbossR* mLBr;

		class Transform* mTr;
		class Animator* mAni;
		class Collider* mCol;

		float mTime;
		int hp;
		int mAttack;
		bool mLayerChange;
		bool mdAttack;
		bool mLBrb;

		class Sound* sCL;
		class Sound* sAttack;
		class Sound* sAttacked;
		class Sound* sExp;
		
	};
}

