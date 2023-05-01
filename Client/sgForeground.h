#pragma once
#include "sgGameObject.h"

namespace sg
{
	class Foreground : public GameObject
	{
	public:

		Foreground();
		~Foreground();

		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);
		virtual void Release();

	private:

		class Transform* mTr;
		class Image* fg;
	};
}

