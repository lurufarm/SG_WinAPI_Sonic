#pragma once
#include "sgGameObject.h"

namespace sg
{
	class MapDeco2 : public GameObject
	{
	public:

		MapDeco2();
		~MapDeco2();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

	private:

	};

}

