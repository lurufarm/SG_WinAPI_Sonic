#pragma once
#include "sgGameObject.h"

namespace sg
{

	class Spike : public GameObject
	{
	public:
		Spike();
		~Spike();

		enum class eSpikeState
		{
			up,
			right,
			left,
			down,
		};

		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);
		virtual void Release();

		virtual void OnCollisionEnter(class Collider* other);
		virtual void OnCollisionStay(class Collider* other);
		virtual void OnCollisionExit(class Collider* other);

		void SetSpike(eSpikeState state) { mSpikeState = state; }

	private:

		class Transform* mTr;
		class Animator* mAni;
		class Collider* mCol;

		eSpikeState mSpikeState;

		class Sound* sSpike;

	};
}

