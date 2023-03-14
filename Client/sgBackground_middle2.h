#pragma once
#include "sgGameObject.h"
#include "sgImage.h"
#include "sgSonic.h"

namespace sg
{
	class Background_middle2 : public GameObject
	{
	public:

		Background_middle2();
		~Background_middle2();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;
		void SetSonic(GameObject* sonic) { mSonic = sonic; }

	private:

		Image* background_middle2;
		GameObject* mSonic;
	};

}

