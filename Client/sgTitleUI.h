#pragma once
#include "sgGameObject.h"
#include "sgImage.h"

namespace sg
{
	class TitleUI : public GameObject
	{
	public:

		enum class eUIState {
			gamestart,
			exit,
		};

		TitleUI();
		~TitleUI();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

	private:

		void gamestart();
		void exit();


		Image* mGamestart;
		Image* mExit;
		eUIState mState;

	};
}

