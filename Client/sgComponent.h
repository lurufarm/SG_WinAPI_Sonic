#pragma once
#include "sgEntity.h"

namespace sg
{
	class GameObject;
	class Component : public Entity
	{
	public:

		enum class eComponentState
		{
			Normal,
			Disapper,
		};

		Component(eComponentType type);
		~Component();

		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);
		virtual void Release();

		eComponentType GetType() { return mType; }
		void SetOwner(GameObject* owner) { mOwner = owner; }
		GameObject* GetOwner() { return mOwner; }
		eComponentState GetState() { return mState; }
		void SetState(eComponentState state) { mState = state; }

	private:

		const eComponentType mType;
		GameObject* mOwner;
		eComponentState mState;

	};
}

