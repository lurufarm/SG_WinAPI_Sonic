#include "sgInput.h"
#include "sgApplication.h"

extern sg::Application application;

namespace sg
{
	 int Keyboard[(UINT)eKeyCode::END] = {

		 0x25,
		 0x27,
		 0x26,
		 0x28,
		 0x11,
		 0x0D,
		 0x1B,
		 'W',
		 'A',
		 'S',
		 'D',
		 VK_SPACE,
		 VK_LBUTTON,
		 VK_RBUTTON,
		 
		 
		//VK_LEFT,
		//VK_RIGHT,
		//VK_UP,
		//VK_DOWN,
		//VK_CONTROL,
		//ENTER
		//ESC
	};

	 std::vector<Input::Key> Input::mKeys;
	 Vector2 Input::mMousePos = Vector2::Zero;

	void Input::Initialize()
	{
	
		for (UINT i = 0; i < (UINT)eKeyCode::END; i++)
		{
			Key keyInfo;
			keyInfo.Key = (eKeyCode)i;
			keyInfo.state = eKeyState::None;
			keyInfo.bPressed = false;

			mKeys.push_back(keyInfo);
		}
	}

	void Input::Update()
	{
		if (GetFocus())
		{
			for (UINT i = 0; i < (UINT)eKeyCode::END; i++)
			{
				if (GetAsyncKeyState(Keyboard[i]) & 0x8000)
				{
					if (mKeys[i].bPressed)
						mKeys[i].state = eKeyState::Pressed;
					else
						mKeys[i].state = eKeyState::Down;

					mKeys[i].bPressed = true;
				}
				else
				{
					if (mKeys[i].bPressed)
						mKeys[i].state = eKeyState::Up;
					else
						mKeys[i].state = eKeyState::None;

					mKeys[i].bPressed = false;
				}
			}

			POINT mousePos = {};
			GetCursorPos(&mousePos);
			ScreenToClient(application.GetHwnd(), &mousePos);
			mMousePos.x = mousePos.x;
			mMousePos.y = mousePos.y;
		}
		else
		{
			for (UINT i = 0; i < (UINT)eKeyCode::END; i++)
			{
				if (eKeyState::Down == mKeys[i].state
					|| eKeyState::Pressed == mKeys[i].state)
				{
					mKeys[i].state = eKeyState::Up;
				}
				else if (eKeyState::Up == mKeys[i].state)
				{
					mKeys[i].state = eKeyState::None;
				}

				mKeys[i].bPressed = false;
			}
		}
	}

	void Input::Render(HDC hdc)
	{
	}
}