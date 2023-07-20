#pragma once
#include "RotationRender.h"
#include "RigidBody.h"

class Fragment : public RigidBody
{
private:
    RotationRender m_rotationRender;
    float m_rotation;

public:
    Fragment() : m_rotation(0.0f) {}

    void SetRotation(float rotation) { m_rotation = rotation; }
    float GetRotation() const { return m_rotation; }

    void LoadImage(wchar_t* filePath) { m_rotationRender.LoadImage(filePath); }
    void RotateRender(int x, int y, int width, int height)
    {
        m_rotationRender.rotateImage(m_rotation);    // 파편의 회전
        m_rotationRender.RotateRender(x, y, width, height); // 파편 렌더링
    }

    void Update(float deltaTime)
    {
        SetVelocity(GetVelocity().x, GetVelocity().y + GetAcceleration().y * deltaTime); // 중력 가속도 적용
        RigidBody::Update(deltaTime);
        m_rotation += deltaTime * 100.0f; 
    }

};
