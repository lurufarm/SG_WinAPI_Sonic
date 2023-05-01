#pragma once
#include "sgGameObject.h"

namespace sg
{
	class Ground2 : public GameObject
	{
	public:
		Ground2();
		virtual ~Ground2();

		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);
		virtual void Release();

		virtual void OnCollisionEnter(class Collider* other);
		virtual void OnCollisionStay(class Collider* other);
		virtual void OnCollisionExit(class Collider* other);

		void SetPlayer(class Sonic* player) { mPlayer = player; }

		void AddGameObject(GameObject* obj) {
			if (obj == nullptr)
				return;
			mObject.push_back(obj);
		}
		void AddSpring(Spring* obj)
		{
			if (obj == nullptr)
				return;
			mSpring.push_back(obj);
		}

		Vector2 GetFrontPos() { return mFrontpos; }
		bool mDarkRed;
		bool mDarkGreen;

		bool mYellow;
		bool mGreen;
		bool mBlue;
		bool mRed;

	private:
		//class Collider* mCollider;
		class Image* mImage;
		class Sonic* mPlayer;
		//class MovingTerrain* mMovTrr;

		Vector2 mFrontpos;

		bool mbAble;
		bool mOnOff;

		//std::vector<GameObject*> mMonster;
		std::vector<GameObject*> mObject;
		std::vector<Spring*> mSpring;

	};
}
