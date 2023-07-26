#pragma once
#include "RotationRender.h"
#include "RigidBody.h"

class Fragment : public RigidBody
{
private:
    RotationRender m_rotationRender;
    float m_rotation;
    float m_rotationSpeed;

    bool m_shouldRotate;
    bool m_render;

    int _cnt;
    bool _initCnt;
    bool _goUpdate;

public:
    Fragment() : m_rotation(0.0f),m_shouldRotate(true), m_render(true),_cnt(0),_goUpdate(true){}

    void SetRotation(float rotation) { m_rotation = rotation; }
    float GetRotation() const { return m_rotation; }

    void LoadImage(wchar_t* filePath) { m_rotationRender.LoadImage(filePath); }

    void SetRotationSpeed(float rotationSpeed) { m_rotationSpeed = rotationSpeed; }
    float GetRotationSpeed() const { return m_rotationSpeed; }

    void RotateRender(int x, int y, int width, int height)
    {
        m_rotationRender.rotateImage(m_rotation, m_shouldRotate);    // 파편의 회전
        m_rotationRender.RotateRender(x, y, width, height, m_render); // 파편 렌더링
    }

    void Update(float deltaTime,HDC hdc,int offsetX,int offsetY);
 

};


/*
     SetVelocity(GetVelocity().x, GetVelocity().y + GetAcceleration().y * deltaTime);

        Vec2 nextPosition;
        nextPosition.x = GetPosition().x + GetVelocity().x * deltaTime;
        nextPosition.y = GetPosition().y + GetVelocity().y * deltaTime;

        int colOBJ = GetRValue(GetPixel(IMAGEMANAGER->findImage("스테이지1픽셀")->getMemDC(), static_cast<int>(nextPosition.x), static_cast<int>(nextPosition.y)));

        if (colOBJ == 131)
        {
            SetVelocity(GetVelocity().x, -GetVelocity().y * 0.7f);
        }
        else
        {
            RigidBody::Update(deltaTime);
        }

        m_rotation += deltaTime * 100.0f;
*/


/*
    SetVelocity(GetVelocity().x, GetVelocity().y + GetAcceleration().y * deltaTime); // 중력 가속도 적용
        RigidBody::Update(deltaTime);
        m_rotation += deltaTime * 100.0f;
*/