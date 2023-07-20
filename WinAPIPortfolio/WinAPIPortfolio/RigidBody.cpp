#include "Stdafx.h"
#include "RigidBody.h"

void RigidBody::Update(float deltaTime)
{
    // 중력 적용
    m_acceleration.y = m_gravity;

    // 속도 업데이트
    m_velocity.x += m_acceleration.x * deltaTime;
    m_velocity.y += m_acceleration.y * deltaTime;

    // 위치 업데이트
    m_position.x += m_velocity.x * deltaTime;
    m_position.y += m_velocity.y * deltaTime;
}
