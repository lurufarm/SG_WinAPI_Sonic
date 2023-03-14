#pragma once
#include "sgGameObject.h"
#include "sgImage.h"
#include "sgAnimator.h"

namespace sg
{
	class Redcard : public GameObject
	{
	public:
		Redcard();
		~Redcard();

		enum class efade {
			start,
			stay,
			exit,
		};

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

	private:

		void Start();
		void Stay();
		void Exit();

		
		Image* mredcard;
		Animator* mAnimator;
		float mTime;
		efade mfadestate;

	};
}

