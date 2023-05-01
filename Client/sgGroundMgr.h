#pragma once
#include "sgGameObject.h"
#include "sgRigidBody.h"
#include "sgScene.h"
#include "sgSceneManager.h"
#include "sgTransform.h"
#include "sgCollider.h"


namespace sg
{
    template <typename T>
    void ColPosControl(Collider* other, T* col)
    {
        GameObject* gameobj = dynamic_cast<GameObject*>(other->GetOwner());
        if (gameobj == nullptr)
            return;

        Rigidbody* rb = gameobj->GetComponent<Rigidbody>();
        rb->SetGround(true);  // ������ �� �Ը� ��� ���ľ���.�� �Լ��� ��� ��ü�� enter�Ҷ� ����ϵ��� ���� �Լ��̴�.

        //Collider* gameobjCol = gameobj->GetComponent<Collider>();
        //Vector2 gameobjPos = gameobjCol->GetPos();

        //Collider* thisCol = col->GetComponent<Collider>();
        //Vector2 thisPos = thisCol->GetPos();


        //float fLen = fabs(gameobjPos.y - thisPos.y);
        //float fSize = (gameobjCol->GetSize().y / 2.0f) + (thisCol->GetSize().y / 2.0f);

        //if (fLen < fSize)
        //{
        //    Transform* gameobjTr = gameobj->GetComponent<Transform>();
        //    Transform* colTr = col->GetComponent<Transform>();

        //    Vector2 gameobjPos = gameobjTr->GetPos();
        //    Vector2 colPos = colTr->GetPos();

        //    gameobjPos -= (fSize - fLen) - 1.0f;
        //    gameobjTr->SetPos(gameobjPos);
        //}

        Sonic* sonic = dynamic_cast<Sonic*>(other->GetOwner());

        if (gameobj == sonic
            && sonic->GetSonicState() == Sonic::eSonicState::death)
        {
            rb->SetGround(false);
        }
    }
}