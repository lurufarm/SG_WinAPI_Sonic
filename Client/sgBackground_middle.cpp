#include "sgBackground_middle.h"
#include "sgTime.h"
#include "sgInput.h"
#include "sgSceneManager.h"
#include "sgResources.h"
#include "sgTransform.h"
#include "sgCamera.h"

sg::Background_middle::Background_middle()
{
}

sg::Background_middle::~Background_middle()
{
}

void sg::Background_middle::Initialize()
{
    background_middle = Resources::Load<Image>(L"background_middle", L"..\\Resources\\map\\Background_middle.bmp");
    GameObject::Initialize();
}

void sg::Background_middle::Update()
{
    GameObject::Update();
}

void sg::Background_middle::Render(HDC hdc)
{

    GameObject::Render(hdc);
    Transform* tr = mSonic->GetComponent<Transform>();
    Vector2 sonicPos = tr->GetPos();

    // 카메라 위치 계산
    Vector2 pos;
    pos.x = background_middle->GetWidth();
    pos.y = background_middle->GetHeight();
    Vector2 cPos = Camera::CalculatePos(pos);

    // 이미지 출력
    for (size_t i = 0; i < 25600; i += 1280)
    {
        int x = static_cast<int>(cPos.x - background_middle->GetWidth() / 2.0f + i + sonicPos.x / 3.0 );
        int y = static_cast<int>(cPos.y - background_middle->GetHeight() / 2.0f + 2828);
        TransparentBlt(hdc, x-2560, y, background_middle->GetWidth(), background_middle->GetHeight()*1.02,
            background_middle->GetHdc(), 0, 0, background_middle->GetWidth(), background_middle->GetHeight(), RGB(255, 0, 255));
    }
}



void sg::Background_middle::Release()
{
    GameObject::Release();
}
