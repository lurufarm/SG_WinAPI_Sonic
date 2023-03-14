#include "sgBackground_middle2.h"
#include "sgTime.h"
#include "sgInput.h"
#include "sgSceneManager.h"
#include "sgResources.h"
#include "sgTransform.h"
#include "sgCamera.h"

sg::Background_middle2::Background_middle2()
{
}

sg::Background_middle2::~Background_middle2()
{
}

void sg::Background_middle2::Initialize()
{
    background_middle2 = Resources::Load<Image>(L"background_middle2", L"..\\Resources\\map\\Background_middle2.bmp");
    GameObject::Initialize();
}

void sg::Background_middle2::Update()
{
    GameObject::Update();
}

void sg::Background_middle2::Render(HDC hdc)
{
    //GameObject::Render(hdc);

    //Vector2 pos;
    //pos.x = background_middle->GetWidth();
    //pos.y = background_middle->GetHeight();

    //Vector2 cPos = Camera::CalculatePos(pos); // 카메라 위치 계산

    //int x = static_cast<int>(cPos.x - background_middle->GetWidth() / 2.0f); // 카메라 위치에서 이미지 너비의 반을 빼서 X 좌표 계산
    //int y = static_cast<int>(cPos.y - background_middle->GetHeight() / 2.0f); // 카메라 위치에서 이미지 높이의 반을 빼서 Y 좌표 계산

    //for (size_t i = 0; i < 12800; i += 1280)
    //{
    //	TransparentBlt(hdc, x + i, y + 2826, background_middle->GetWidth(), background_middle->GetHeight(),
    //	background_middle->GetHdc(), 0, 0, background_middle->GetWidth(), background_middle->GetHeight(), RGB(255, 0, 255));
    //}
    GameObject::Render(hdc);
    Transform* tr = mSonic->GetComponent<Transform>();
    Vector2 sonicPos = tr->GetPos();

    // 카메라 위치 계산
    Vector2 pos;
    pos.x = background_middle2->GetWidth();
    pos.y = background_middle2->GetHeight();
    Vector2 cPos = Camera::CalculatePos(pos);

    // 이미지 출력
    for (size_t i = 0; i < 41050; i += 4105)
    {
        int x = static_cast<int>(cPos.x - background_middle2->GetWidth() / 2.0f + i + sonicPos.x / 4 );
        int y = static_cast<int>(cPos.y - background_middle2->GetHeight() / 2.0f + 3196.5);
        TransparentBlt(hdc, x-4105, y, background_middle2->GetWidth(), background_middle2->GetHeight()*1.02,
            background_middle2->GetHdc(), 0, 0, background_middle2->GetWidth(), background_middle2->GetHeight(), RGB(255, 0, 255));
    }
}



void sg::Background_middle2::Release()
{
    GameObject::Release();
}
