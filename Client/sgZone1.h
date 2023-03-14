#pragma once
#include "sgGameObject.h"
#include "sgImage.h"
#include "sgAnimator.h"

namespace sg
{
	class Zone1 : public GameObject
	{
	public:
		Zone1();
		~Zone1();

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


		Image* mzone;
		Animator* mAnimator;
		float mTime;
		efade mfadestate;

	};
}

