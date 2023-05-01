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
		// DC�� ���� Ư���ϰ� ������.
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


		//��Ʈ�� �ػ󵵸� �����ϱ� ���� ���� ������ ũ�� ���
		RECT rect = { 0, 0, mWidth, mHeight };
		AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);

		//������ ũ�� ���� �� ��� ����
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

		// ����ۿ� �ִ� �׸��� ���� ���ۿ� �׷���� �Ѵ�.
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
