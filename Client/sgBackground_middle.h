#pragma once
#include "sgGameObject.h"
#include "sgImage.h"
#include "sgSonic.h"

namespace sg
{
	class Background_middle : public GameObject
	{
	public:

		Background_middle();
		~Background_middle();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;
		void SetSonic(GameObject* sonic) { mSonic = sonic; }

	private:

		DWORD m_LastUpdateTime;
		Image* background_middle;
		GameObject* mSonic;
	};

}

