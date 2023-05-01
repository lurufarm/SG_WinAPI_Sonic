#pragma once
#include "sgEntity.h"
#include "sgComponent.h"
#include "sgPlayScene.h"

extern sg::Sonic* mSonic;

namespace sg
{
	class GameObject : public Entity
	{
	public:
		enum class eState
		{
			Active,
			Pause,
			Death,
		};

		GameObject();
		virtual ~GameObject();

		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);
		virtual void Release();

		virtual void OnCollisionEnter(class Collider* other);
		virtual void OnCollisionStay(class Collider* other);
		virtual void OnCollisionExit(class Collider* other);

		Sonic* GetSonic() { return mSonic; }


		template <typename T>
		T* AddComponent()
		{
			T* comp = new T();
			UINT compType = (UINT)comp->GetType();
			mComponents[compType] = comp;
			comp->SetOwner(this);

			return comp;
		}

		template <typename T>
		T* GetComponent()
		{
			for (Component* comp : mComponents)
			{
				if (dynamic_cast<T*>(comp))
					return dynamic_cast<T*>(comp);
			}

			return nullptr;
		}
		

		eState GetState() { return mState; }
		void SetState(eState state) { mState = state; }
		bool mUse;

	private:
		std::vector<Component*> mComponents;
		eState mState;
	};

}