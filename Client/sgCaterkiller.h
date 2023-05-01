#pragma once
#include "sgGameObject.h"

namespace sg
{
	class Caterkiller : public GameObject
	{
	public:
		Caterkiller();
		~Caterkiller();

		enum class eCKState
		{
			move_left,
			move_right,
			turn_left,
			turn_right,
			death,
		};

		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);
		virtual void Release();

		virtual void OnCollisionEnter(class Collider* other);
		virtual void OnCollisionStay(class Collider* other);
		virtual void OnCollisionExit(class Collider* other);

	private:

		void move_left();
		void move_right();
		void turn_left();
		void turn_right();
		void death();

		eCKState mCKState;
		int mAbillity;
		Vector2 mOriginPos;

		class Animator* mAni;
		class Collider* mCol;

		class Sound* sDeath;
		class Sound* sBoom;


	};
}

