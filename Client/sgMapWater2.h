#pragma once
#include "sgGameObject.h"
#include "sgAnimator.h"

namespace sg
{
	class Animator;
	class MapWater2 : public GameObject
	{

	public:

		MapWater2();
		~MapWater2();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

	private:

		Animator* mAnimator;

	};

}