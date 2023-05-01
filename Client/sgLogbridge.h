#pragma once
#include "sgGameObject.h"

namespace sg
{

	class Logbridge : public GameObject
	{
	public:
		Logbridge();
		~Logbridge();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

		virtual void OnCollisionEnter(class Collider* other);
		virtual void OnCollisionStay(class Collider* other);
		virtual void OnCollisionExit(class Collider* other);

	private:

		class Animator* mAni;
		class Collider* mCol;
		
		class Sound* sBreaking;

	};

}
