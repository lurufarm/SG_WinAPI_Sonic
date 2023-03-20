#pragma once
#include "YamYamEngine.h"

namespace sg
{

	enum class eKeyState
	{
		Down,
		Pressed,
		Up,
		None,
	};

	enum class eKeyCode
	{
		Left,
		Right,
		Up,
		Down,
		Ctrl,
		Enter,
		ESC,
		W,
		A,
		S,
		D,
		Space,
		END,
	};

	class Input
	{
	public:

		struct Key
		{
			eKeyCode Key;
			eKeyState state;
			bool bPressed;
		};


		static void Initialize();
		static void Update();
		static void Render(HDC hdc);
		inline static eKeyState GetKeyStateNone() { return eKeyState::None; }
		inline static eKeyState GetKeyState(eKeyCode keyCode)
		{
			return mKeys[(UINT)keyCode].state;
		};

		//GetKey()		Ű�� ������ �ð���ŭ true�� ��ȯ
		//GetKeyDown()	Ű�� ������ ��, �� �ѹ� true�� ��ȯ
		//GetKeyUp()	Ű�� ������ ���� ��, �� �ѹ� true�� ��ȯ

		static __forceinline bool GetKey(eKeyCode keyCode)
		{
			return mKeys[static_cast<UINT>(keyCode)].state == eKeyState::Pressed;
		}

		static __forceinline bool GetKeyDown(eKeyCode keyCode)
		{
			return mKeys[static_cast<UINT>(keyCode)].state == eKeyState::Down;
		}

		static __forceinline bool GetKeyUp(eKeyCode keyCode)
		{
			return mKeys[static_cast<UINT>(keyCode)].state == eKeyState::Up;
		}


	private:
		static std::vector<Key>mKeys;
	};

}

