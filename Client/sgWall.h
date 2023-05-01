#pragma once
#include "sgGameObject.h"

namespace sg
{

	class Wall : public GameObject
	{
	public:
		Wall();
		~Wall();
		
		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);
		virtual void Release();

		virtual void OnCollisionEnter(class Collider* other);
		virtual void OnCollisionStay(class Collider* other);
		virtual void OnCollisionExit(class Collider* other);

	private:
		class Transform* mTr;
		class Collider* mCollider;
	};
}

