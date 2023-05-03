#pragma once
#include "sgGameObject.h"
#include "sgImage.h"
#include "sgEffect.h"
#include "sgEffect2.h"

namespace sg
{
	class Rigidbody;
	class Animator;
	class Sonic : public GameObject
	{
	public:
		static int mAbility;

		enum class eSonicState
		{
			idle_left,
			idle_right,
			crouch_left,
			crouch_right,
			lookup_left,
			lookup_right,
			walk_left,
			walk_right,
			run_left,
			run_right,
			jump_left,
			jump_right,
			jump2_left,
			jump2_right,
			spindash_left,
			spindash_right,
			rolling_left,
			rolling_right,
			push_left,
			push_right,
			skid_left,
			skid_right,
			hurt_left,
			hurt_right,
			death,
			hang_left,
			hang_right,
			spring_up,
			waterjump,
			falldown,

		};

		Sonic();
		~Sonic();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;
		virtual void GetRing() { mRings++; }
		virtual int GetRingNumber() { return mRings; }
		virtual int GetLifeNumber() { return mLife; }
		virtual Sonic* GetSonic() { return this; }

		void SonicSceneChange(eSceneType type) {
			Scene* nowscene = SceneManager::GetActiveScene();
			Scene* scene = SceneManager::SetScene(type);
			scene->AddGameObject(nowscene->GetGameObjects(eLayerType::Player), eLayerType::Player);
		}

		eSonicState GetSonicState() { return mSonicState; }
		void SetSonicState(eSonicState state) { mSonicState = state; }
		bool GetHurt() { return mbHurt; }
		void SetHurt(bool value) { mbHurt = value; }
		bool GetWaterJump() { return mWaterJump; }
		void SetWaterJump(bool value) 
		{ 
			if (mWaterJump != value)
			{
				mWaterJump = value;
			}
		}

		virtual void OnCollisionEnter(class Collider* other) override;
		virtual void OnCollisionStay(class Collider* other) override;
		virtual void OnCollisionExit(class Collider* other) override;

		static bool mFlame;
		static bool mThunder;
		static bool mWater;
		float mLimitVel;
		
		void SonicReset();


	private:
		void idle_left();
		void idle_right();
		void crouch_left();
		void crouch_right();
		void lookup_left();
		void lookup_right();
		void walk_left();
		void walk_right();
		void run_left();
		void run_right();
		void jump_left();
		void jump_right();
		void jump2_left();
		void jump2_right();
		void spindash_left();
		void spindash_right();
		void rolling_left();
		void rolling_right();
		void skid_left();
		void skid_right();
		void hurt_left();
		void hurt_right();
		void death();
		void hang_left();
		void hang_right();
		void spring_up();
		void waterjump();
		void falldown();

		eSonicState mSonicState;
		Animator* mAnimator;
		Collider* mCollider;
		Rigidbody* mRigidbody;
		
		Vector2 mSonicVelocity;
		Vector2 mResetPos;
		float mTime;
		float mHurtTime;

		static int mRings;
		static int mLife;

		bool mbHurt;
		bool mR;

		bool mWaterJump;

		Effect* mEffect;
		Effect2* mEffect2;

		class Sound* sJump;
		class Sound* sJump2;
		class Sound* sJump_thunder;
		class Sound* sJump_flame;
		class Sound* sJump_water;
		class Sound* sSpin;
		class Sound* sDeath;
		class Sound* sHurt;
		class Sound* sGrap;
		class Sound* sSkid;
		class Sound* sGetring;
		class Sound* sLosering;
		
	};

}

