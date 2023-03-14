#pragma once
#include "sgGameObject.h"
#include "sgAnimator.h"

namespace sg
{
	class Animator;
	class Titletails : public GameObject
	{
	public:

		Titletails();
		~Titletails();

		enum class eTailsState{
			right,
			left,
		};

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

	private:
\
		void right();
		void left();

	private:
		Animator* mAnimator;
		eTailsState mtailsState;
	};
}

