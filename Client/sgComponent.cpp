#include "sgComponent.h"

namespace sg
{
    Component::Component(eComponentType type)
        : mType(type)
        , mState(eComponentState::Normal)
    {
    }
    Component::~Component()
    {
    }
    void Component::Initialize()
    {
    }
    void Component::Update()
    {
    }
    void Component::Render(HDC hdc)
    {
    }

    void Component::Release()
    {
    }
}