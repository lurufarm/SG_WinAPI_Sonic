#include "Resource.h"

#include "sgApplication.h"
#include "sgSceneManager.h"
#include "sgTime.h"
#include "sgInput.h"
#include "sgCollisionManager.h"
#include "sgCamera.h"
#include "sgSoundManager.h"

namespace sg
{
	Application::Application()
		: mHwnd(NULL)
		, mHdc(NULL)
	{
	}

	Application::~Application()
	{
		SceneManager::Release();

		//ReleaseDC(mHwnd, mHdc);
		// DC는 조금 특별하게 해제함.
		//DeleteDC(mBackHDC);
		//DeleteObject(mBackBuffer);
	}

	void Application::Initialize(HWND hWnd)
	{
		mHwnd = hWnd;
		mHdc = GetDC(hWnd);
		mWidth = 1100;
		mHeight = 800;
		//mWidth = 1600;
		//mHeight = 900;


		//비트맵 해상도를 설정하기 위한 실제 윈도우 크기 계산
		RECT rect = { 0, 0, mWidth, mHeight };
		AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);

		//윈도우 크기 변경 및 출력 설정
		SetWindowPos(mHwnd
			, nullptr, 150, 50
			, rect.right - rect.left
			, rect.bottom - rect.top
			, 0);
		ShowWindow(hWnd, true);


		mBackBuffer = CreateCompatibleBitmap(mHdc, mWidth, mHeight);
		mBackHDC = CreateCompatibleDC(mHdc);
		mMenubar = LoadMenu(nullptr, MAKEINTRESOURCE(IDI_CLIENT));

		HBITMAP defaultBitmap
			= (HBITMAP)SelectObject(mBackHDC, mBackBuffer);
		DeleteObject(defaultBitmap);

		Time::Initialize();
		Input::Initialize();
		SoundManager::Initialize();
		SceneManager::Initialize();
		Camera::Initialize();

		SetMenuBar(false);
	}

	void Application::Run()
	{
		Update();
		Render();
		SceneManager::Destroy();
	}

	void Application::Update()
	{

		Time::Update();
		Input::Update();
		Camera::Update();

		SceneManager::Update();
		CollisionManager::Update();
	}
	void Application::Render()
	{
		//clear
		clear();

		Time::Render(mBackHDC);
		Input::Render(mBackHDC);
		SceneManager::Render(mBackHDC);
		Camera::Render(mBackHDC);

		// 백버퍼에 있는 그림을 원본 버퍼에 그려줘야 한다.
		BitBlt(mHdc, 0, 0, mWidth, mHeight, mBackHDC, 0, 0, SRCCOPY);

	}
	void Application::SetMenuBar(bool power)
	{
		SetMenu(mHwnd, mMenubar);

		RECT rect = { 0, 0, mWidth, mHeight };
		AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, power);

		SetWindowPos(mHwnd
			, nullptr, 0, 0
			, rect.right - rect.left
			, rect.bottom - rect.top
			, 0);
		ShowWindow(mHwnd, true);
	}
	void Application::clear()
	{
		HBRUSH greyBrush = CreateSolidBrush(RGB(255, 255, 255));
		HBRUSH oldBrush = (HBRUSH)SelectObject(mBackHDC, greyBrush);
		Rectangle(mBackHDC, -1, -1, 1602, 902);
		SelectObject(mBackHDC, oldBrush);
		DeleteObject(greyBrush);

	}
}
