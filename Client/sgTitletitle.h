#pragma once
#include "sgGameObject.h"
#include "sgImage.h"

namespace sg
{
	class Titletitle : public GameObject
	{
	public:

		Titletitle();
		~Titletitle();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

	private:
		Image* mtitletitle;
	};
}

