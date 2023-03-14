#include "sgInput.h"

namespace sg
{

	//int ASCII[(UINT)eKeyCode::END] = {
	//	'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P',
	//	'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L',
	//	'Z', 'X', 'C', 'V', 'B', 'N', 'M',
	//};

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
		 
		 
		//VK_LEFT,
		//VK_RIGHT,
		//VK_UP,
		//VK_DOWN,
		//VK_CONTROL,
		//ENTER
		//ESC
	};

	//std::vector<Input::Key> Input::mKeys;
	 std::vector<Input::Key> Input::mKeys;

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
	}
	void Input::Render(HDC hdc)
	{
	}
}