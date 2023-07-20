#include "Stdafx.h"
#include "RigidBody.h"

void RigidBody::Update(float deltaTime)
{
    // �߷� ����
    m_acceleration.y = m_gravity;

    // �ӵ� ������Ʈ
    m_velocity.x += m_acceleration.x * deltaTime;
    m_velocity.y += m_acceleration.y * deltaTime;

    // ��ġ ������Ʈ
    m_position.x += m_velocity.x * deltaTime;
    m_position.y += m_velocity.y * deltaTime;
}
