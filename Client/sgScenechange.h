#pragma once
#include "sgGameObject.h"

namespace sg
{
	class Scenechange : public GameObject
	{
	public:
		Scenechange();
		~Scenechange();


		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

	private:

		class Animator* mAni;
		class Transform* mTr;

		class Sound* sSC;

	};
}

