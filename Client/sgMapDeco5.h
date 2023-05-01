#pragma once
#include "sgGameObject.h"

namespace sg
{
	class MapDeco5 : public GameObject
	{
	public:

		MapDeco5();
		~MapDeco5();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;
		bool mNumber;

	private:

		class Animator* mAni;
	};

}

