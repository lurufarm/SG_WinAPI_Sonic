#pragma once
#include "sgGameObject.h"
#include "sgImage.h"

namespace sg
{
	class MapObjects : public GameObject
	{
	public:

		MapObjects();
		~MapObjects();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

		virtual void OnCollisionEnter(class Collider* other) override;
		virtual void OnCollisionStay(class Collider* other) override;
		virtual void OnCollisionExit(class Collider* other) override;

	private:

		Image* mapObjectImage[4];
		class Collider* mCollider;
		
	};
}

