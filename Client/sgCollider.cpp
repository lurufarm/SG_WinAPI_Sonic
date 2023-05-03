#include "sgCollider.h"
#include "sgTransform.h"
#include "sgGameObject.h"
#include "sgCamera.h"
#include "sgInput.h"


namespace sg
{
	UINT Collider::ColliderNumber = 0;
	Collider::Collider()
		: Component(eComponentType::Collider)
		, mCenter(Vector2::Zero)
		, mPos(Vector2::Zero)
		, mSize(100.0f, 100.0f)
		, mID(ColliderNumber++)
		, mCollisionCount(0)
		, mOnOff(true)
	{

	}
	Collider::~Collider()
	{
	}
	void Collider::Initialize()
	{
		Transform* tr = GetOwner()->GetComponent<Transform>();
		mPos = tr->GetPos() + mCenter;
		
	}
	void Collider::Update()
	{
		Transform* tr = GetOwner()->GetComponent<Transform>();
		mPos = tr->GetPos() + mCenter;

		if (Input::GetKeyDown(eKeyCode::A))
		{
			if (mOnOff == true)
			{
				mOnOff = false;
			}
			else
			{
				mOnOff = true;
			}
		}
	}
	void Collider::Render(HDC hdc)
	{
		if (mOnOff == true) {

			HPEN pen = NULL;
			if (mCollisionCount <= 0 && mOnOff == true)
				pen = CreatePen(BS_SOLID, 2, RGB(255, 0, 255));
			else
				pen = CreatePen(BS_SOLID, 2, RGB(0, 0, 255));

			HPEN oldpen = (HPEN)SelectObject(hdc, pen);
			HBRUSH brush = (HBRUSH)GetStockObject(NULL_BRUSH);
			HBRUSH oldbrush = (HBRUSH)SelectObject(hdc, brush);

			Vector2 pos = Camera::CalculatePos(mPos);
			Rectangle(hdc, pos.x, pos.y, pos.x + mSize.x, pos.y + mSize.y);

			(HPEN)SelectObject(hdc, oldpen);
			(HBRUSH)SelectObject(hdc, oldbrush);
			DeleteObject(pen);

			mCollisionCount = 0;
		}
	}
	void Collider::Release()
	{
	}
	void Collider::OnCollisionEnter(Collider* other)
	{
		Vector2 normal = GetNormal(other);
		GetOwner()->OnCollisionEnter(other);
	}
	void Collider::OnCollisionStay(Collider* other)
	{
		mCollisionCount = 1;
		GetOwner()->OnCollisionStay(other);
	}
	void Collider::OnCollisionExit(Collider* other)
	{
		GetOwner()->OnCollisionExit(other);
	}

	Vector2 Collider::GetNormal(Collider* other)
	{
		Vector2 diff = other->mPos - mPos;
		Vector2 half = (mSize + other->mSize) / 2.0f;
			
		float x_overlap = half.x - fabs(diff.x);
		float y_overlap = half.y - fabs(diff.y);

		if (x_overlap > 0 && y_overlap > 0)
		{
			if (x_overlap < y_overlap)
			{
				return Vector2(diff.x > 0 ? half.x : -half.x, 0.0f).Nomalize();
			}
			else
			{
				return Vector2(0.0f, diff.y > 0 ? half.y : -half.y).Nomalize();
			}
		}

		return Vector2::Zero;
	}

}