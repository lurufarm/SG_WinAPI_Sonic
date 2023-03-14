#pragma once
#include "sgGameObject.h"

namespace sg
{
	class Backgroundsea : public GameObject
	{
	public:

		Backgroundsea();
		~Backgroundsea();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

	private:

	};

}

