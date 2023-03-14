#pragma once
#include "sgGameObject.h"

namespace sg
{
	class MapDeco3 : public GameObject
	{
	public:

		MapDeco3();
		~MapDeco3();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

	private:

	};

}

