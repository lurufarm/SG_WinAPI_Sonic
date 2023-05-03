#pragma once
#include "sgGameObject.h"

namespace sg
{
	class Clouds : public GameObject
	{
	public:

		Clouds(int a);
		~Clouds();
		
		enum class eCNumber
		{
			Cloud1,
			Cloud2,
			Cloud3,
			Cloud4,
		};

		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);
		virtual void Release();

	private:

		eCNumber mCNumber;
		
		class Transform* mTr;
		class Animator* mAni;

	};
}

