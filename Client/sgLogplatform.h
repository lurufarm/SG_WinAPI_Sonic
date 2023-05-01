#pragma once
#include "sgGameObject.h"

namespace sg
{

	class Logplatform : public GameObject
	{
	public:
		Logplatform();
		~Logplatform();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

		void SetPlayer(class Sonic* player) { mPlayer = player; }

		virtual void OnCollisionEnter(class Collider* other);
		virtual void OnCollisionStay(class Collider* other);
		virtual void OnCollisionExit(class Collider* other);

	private:

		class Sonic* mPlayer;
		class Collider* mCol;

	};

}
