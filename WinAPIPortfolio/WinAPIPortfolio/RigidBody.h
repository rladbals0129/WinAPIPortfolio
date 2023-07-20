#pragma once
#include "GameNode.h"
#include "RotationRender.h"
struct Vec2
{
    float x, y;

    Vec2() : x(0), y(0) {}
    Vec2(float x, float y) : x(x), y(y) {}
};

class RigidBody
{
private:
    float m_gravity;
    Vec2 m_position;
    Vec2 m_velocity;
    Vec2 m_acceleration;
   // POINTFLOAT m_position;
  //  POINTFLOAT m_velocity;
   // POINTFLOAT m_acceleration;

public:
    RigidBody() : m_gravity(9.81f) {}
    ~RigidBody() {}

    void SetPosition(float x, float y) { m_position.x = x; m_position.y = y; }
    void SetVelocity(float x, float y) { m_velocity.x = x; m_velocity.y = y; }
    void SetAcceleration(float x, float y) { m_acceleration.x = x; m_acceleration.y = y; }

    const Vec2& GetPosition() const { return m_position; }
    Vec2 GetVelocity() const { return m_velocity; }
    Vec2 GetAcceleration() const { return m_acceleration; }
   // float GetVelocity() { return m_position.x, m_position.y; }
    //float GetPosition() { return m_position.x, m_position.y; }


    void Update(float deltaTime);
};