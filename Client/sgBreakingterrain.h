#pragma once
#include "sgGameObject.h"

namespace sg
{

	class Breakingterrain : public GameObject
	{
	public:
		Breakingterrain();
		~Breakingterrain();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

		virtual void OnCollisionEnter(class Collider* other);
		virtual void OnCollisionStay(class Collider* other);
		virtual void OnCollisionExit(class Collider* other);

		void SetDir(bool value) { mDir = value; }

	private:

		class Collider* mCol;
		class Animator* mAni;

		bool mPlay;
		bool mDir;
		float mTime;

		bool mOn;


		class Sound* sBreaking;

	};

}
