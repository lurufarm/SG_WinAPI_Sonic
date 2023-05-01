#pragma once
#include "sgGameObject.h"
namespace sg
{

	class EndST : public GameObject
	{
	public:
		EndST();
		~EndST();

		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);
		virtual void Release();

	private:

		class Transform* mTr;
		class Animator* mAni;
		
		bool mBool;

	};
}

