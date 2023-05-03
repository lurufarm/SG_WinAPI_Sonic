#pragma once
#include "sgGameObject.h"

namespace sg
{

	class Giantring : public GameObject
	{

	public:

		Giantring();
		~Giantring();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

		virtual void OnCollisionEnter(class Collider* other) override;
		virtual void OnCollisionStay(class Collider* other) override;
		virtual void OnCollisionExit(class Collider* other) override;


	private:

		class Animator* mAni;
		class Collider* mCol;

		class Sound* sRing;

	};
}

