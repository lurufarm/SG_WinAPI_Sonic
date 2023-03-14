#pragma once
#include "sgGameObject.h"

namespace sg
{
	class PlayUI : public GameObject
	{
	public:

		PlayUI();
		~PlayUI();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

	private:

	};

}

