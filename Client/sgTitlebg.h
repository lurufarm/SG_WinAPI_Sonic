#pragma once
#include "sgGameObject.h"
#include "sgAnimator.h"

namespace sg
{
	class Animator;
	class Titlebg : public GameObject
	{
	public:

		Titlebg();
		~Titlebg();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

	private:
		Animator* mAnimator;
	};
}

