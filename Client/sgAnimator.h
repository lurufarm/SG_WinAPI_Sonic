#pragma once
#include "sgComponent.h"
#include "sgAnimation.h"
#include "sgImage.h"


namespace sg
{
	class Animator : public Component
	{
	public:
		struct Event
		{
			void operator=(std::function<void()> func)
			{
				mEvent = std::move(func);
			}
			void operator()()
			{
				if (mEvent)
					mEvent();
			}

			//void(*name)(int, int);
			std::function<void()> mEvent;
		};

		struct Events
		{
			Event mStartEvent;
			Event mCompleteEvent;
			Event mEndEvent;

			//mStartEvent();
			//mStartEvent = test;
		};

		Animator();
		~Animator();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Render(HDC hdc, int sourceconstantalpha);
		virtual	void Release() override;


		//완성된 스프라이트 시트를 지정해서 애니메이션 제작
		void CreateAnimation(const std::wstring& name
			, Image* sheet
			, Vector2 leftTop
			, UINT coulmn,UINT row, UINT spriteLength
			, Vector2 offset, float duration);
		//폴더에 들어있는 스프라이트들을 이용해서 애니메이션 제작
		void CreateAnimations(const std::wstring& path, Vector2 offset, float duration);

		Animation* FindAnimation(const std::wstring& name);
		void Play(const std::wstring& name, bool loop);

		Events* FindEvents(const std::wstring& name);
		std::function<void()>& GetStartEvent(const std::wstring& name);
		std::function<void()>& GetCompleteEvent(const std::wstring& name);
		std::function<void()>& GetEndEvent(const std::wstring& name);
		bool IsComplete() { return mActiveAnimation->IsComplete(); }
		void Reset() { mActiveAnimation->Reset(); }


	private:
		std::map<std::wstring, Animation*> mAnimations;
		std::map<std::wstring, Events*> mEvents;

		Animation* mActiveAnimation;
		Image* mSpriteSheet;
		bool mbLoop;
	};
}

