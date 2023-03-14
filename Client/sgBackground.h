#pragma once
#include "sgGameObject.h"
#include "sgImage.h"

namespace sg
{
	class Background : public GameObject
	{
	public:

		Background();
		~Background();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

	private:

		Image* backgroundImage;

	};

}

