#pragma once
#include "sgGameObject.h"

namespace sg
{
	class Rope : public GameObject
	{
	public:
		Rope();
		~Rope();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;


		virtual void OnCollisionEnter(class Collider* other);
		virtual void OnCollisionStay(class Collider* other);
		virtual void OnCollisionExit(class Collider* other);

		int index;

	private:
		class Animator* mAnimator;
		class Collider* mCollider;
		float mTime;
		Vector2 colpos;
	};
}

