#pragma once
#include "sgGameObject.h"

namespace sg
{
	class MapDeco4 : public GameObject
	{
	public:

		MapDeco4();
		~MapDeco4();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

	private:

	};

}

