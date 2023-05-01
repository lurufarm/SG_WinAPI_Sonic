#pragma once
#include "sgGameObject.h"

namespace sg
{
	class Item : public GameObject
	{
	public:
		enum class eItemState
		{
			Life,
			Ring,
			Flame,
			Thunder,
			Water,
			Broken,
		};

		Item();
		Item(int a);
		~Item();

		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);
		virtual void Release();
		
		virtual eItemState GetState() { return mItemState; }
		void SetState(eItemState state) { mItemState = state; }

		virtual void OnCollisionEnter(class Collider* other);
		virtual void OnCollisionStay(class Collider* other);
		virtual void OnCollisionExit(class Collider* other);

	private:

		void Life();
		void Ring();
		void Flame();
		void Thunder();
		void Water();
		void Broken();

		eItemState mItemState;
		class Animator* mAni;
		class Transform* mTr;
		class Collider* mCol;

		bool mBroken;

		class Sound* sItem;

	};
}

