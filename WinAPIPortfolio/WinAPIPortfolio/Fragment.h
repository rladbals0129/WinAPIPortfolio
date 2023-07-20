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
        m_rotationRender.rotateImage(m_rotation);    // ������ ȸ��
        m_rotationRender.RotateRender(x, y, width, height); // ���� ������
    }

    void Update(float deltaTime)
    {
        SetVelocity(GetVelocity().x, GetVelocity().y + GetAcceleration().y * deltaTime); // �߷� ���ӵ� ����
        RigidBody::Update(deltaTime);
        m_rotation += deltaTime * 100.0f; 
    }

};
