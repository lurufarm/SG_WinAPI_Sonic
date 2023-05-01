#pragma once
#include "sgGameObject.h"

namespace sg
{

	class MovingTerrain : public GameObject
	{
	public:
		MovingTerrain();
		~MovingTerrain();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

		virtual void OnCollisionEnter(class Collider* other);
		virtual void OnCollisionStay(class Collider* other);
		virtual void OnCollisionExit(class Collider* other);

		bool mUpDown;

	private:

		Vector2 mFirstPos;
		class Collider* mCol;

	};

}
