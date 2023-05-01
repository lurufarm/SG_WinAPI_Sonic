#pragma once
#include "sgGameObject.h"

namespace sg
{
	class LastbossR: public GameObject
	{
	public:

		LastbossR();
		~LastbossR();

		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);
		virtual void Release();

		void SetLB(Lastboss* LB) { mLB = LB; }

	private:

		bool mDir;
		class Transform* mTr;
		class Animator* mAni;
		
		class Lastboss* mLB;

		float mTime;

	};
}

