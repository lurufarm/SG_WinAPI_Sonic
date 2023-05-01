#pragma once
#include "sgGameObject.h"

namespace sg
{
	class MapObjects2 : public GameObject
	{
	public:
		MapObjects2();
		MapObjects2(int a);
		~MapObjects2();


		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

	private:

		class Animator* mAni;
		class Transform* mTr;
		Image* map2[7];

		int mAninum;

	};
}

