#include "sgTitletails.h"

#include "sgTime.h"
#include "sgSceneManager.h"
#include "sgInput.h"
#include "sgResources.h"
#include "sgTransform.h"
#include "sgAnimator.h"
#include "sgScene.h"
#include "sgObject.h"

namespace sg
{
	Titletails::Titletails()
	{
	}
	Titletails::~Titletails()
	{
	}
	void Titletails::Initialize()
	{
		Image* intro_tails = Resources::Load<Image>(L"intro_tails", L"..\\Resources\\intro\\intro_tails.bmp");
		Transform* intro_tails_tr = GetComponent<Transform>();
		mAnimator = AddComponent<Animator>();
		//intro_tails_tr->SetPos(Vector2(2500, 3500));
		//intro_tails_tr->SetScale(Vector2(3.0f, 3.0f));

		mAnimator->CreateAnimation(L"intro_tails_right_ani", intro_tails, Vector2::Zero, 2, 2, 2, Vector2::Zero, 0.03);
		mAnimator->CreateAnimation(L"intro_tails_left_ani", intro_tails, Vector2(0, 24), 2, 2, 2, Vector2::Zero, 0.03);
		
		mtailsState = eTailsState::right;

		GameObject::Initialize();

	}
		void Titletails::Update()
	{
		GameObject::Update();

		switch (mtailsState)
		{
		case sg::Titletails::eTailsState::right:
			right();
			break;
		case sg::Titletails::eTailsState::left:
			left();
			break;
		}
	}

	void Titletails::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void Titletails::Release()
	{
		GameObject::Release();
	}
	void Titletails::right()
	{
		Transform* intro_tails_tr = GetComponent<Transform>();
		Vector2 intro_tails_pos = intro_tails_tr->GetPos();
		mAnimator->Play(L"intro_tails_right_ani", true);
		intro_tails_tr->SetScale(Vector2(3.5f, 3.5f));
		intro_tails_pos.y = 3000;
		intro_tails_pos.x += 300.0f * Time::DeltaTime();
		intro_tails_tr->SetPos(intro_tails_pos);
		
		if (intro_tails_pos.x > 2500)
		{
			intro_tails_pos.y = 3200;
			mtailsState = eTailsState::left;
		}
	}
	void Titletails::left()
	{
		Transform* intro_tails_tr = GetComponent<Transform>();
		Vector2 intro_tails_pos = intro_tails_tr->GetPos();
		mAnimator->Play(L"intro_tails_left_ani", true);
		intro_tails_tr->SetScale(Vector2(2.0f, 2.0f));
		intro_tails_pos.y = 3200;
		intro_tails_pos.x -= 200.0f * Time::DeltaTime();
		intro_tails_tr->SetPos(intro_tails_pos);

		if (intro_tails_pos.x < 1050)
		{
			intro_tails_pos.y = 3000;
			mtailsState = eTailsState::right;
		}

	}
}