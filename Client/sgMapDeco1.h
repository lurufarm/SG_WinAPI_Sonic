#pragma once
#include "sgGameObject.h"

namespace sg
{
	class MapDeco1 : public GameObject
	{
	public:

		MapDeco1();
		~MapDeco1();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

	private:

	};

}

