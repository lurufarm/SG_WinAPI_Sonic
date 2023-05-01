#pragma once
#include "sgGameObject.h"

namespace sg
{
	class Bomberbomb : public GameObject
	{
	public:
		Bomberbomb();
		~Bomberbomb();

		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);
		virtual void Release();

		virtual void OnCollisionEnter(class Collider* other);
		virtual void OnCollisionStay(class Collider* other);
		virtual void OnCollisionExit(class Collider* other);

		bool mDown;

	private:

		class Transform* mTr;
		class Animator* mAni;
		class Collider* mCol;
		class Rigidbody* mRb;
		float mTime;

		
		class Sound* sExp;
	};
}

