#pragma once
#include "sgGameObject.h"

namespace sg
{

	class MapRock_l : public GameObject
	{
	public:
		MapRock_l();
		~MapRock_l();


		enum eRocklState
		{
			norm,
			broken,
		};

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

		virtual void OnCollisionEnter(class Collider* other) override;
		virtual void OnCollisionStay(class Collider* other) override;
		virtual void OnCollisionExit(class Collider* other) override;

		bool mOn;

	private:
		void Norm();
		void Broken();

	private:

		class Animator* mAnimator;
		class Collider* mCollider;
		class Transform* mTr;
		eRocklState mRocklState;

		class Sound* sBreaking;


	};

}
