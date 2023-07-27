#include "Stdafx.h"
#include "Fragment.h"

void Fragment::Update(float deltaTime , HDC hdc, int offsetX, int offsetY)
{
    if (_goUpdate)
    {
        float currentGravity = RigidBody::getGravity();
        SetAcceleration(0, currentGravity);

        Vec2 nextPosition;
        nextPosition.x = GetPosition().x + GetVelocity().x * deltaTime;
        nextPosition.y = GetPosition().y + GetVelocity().y * deltaTime;

        int colOBJ = GetRValue(GetPixel(hdc, static_cast<int>(nextPosition.x) + offsetX, static_cast<int>(nextPosition.y) + offsetY));

        const float friction = 0.87f; // 마찰력
        const float bounciness = 0.7f; // 반발력
        const float speedLimit = 0.1f; // 속도 제한

        if (colOBJ == 131)
        {

            SetVelocity(GetVelocity().x * friction, -GetVelocity().y * bounciness);
            SetAcceleration(0, 0);
            SetRotationSpeed(GetRotationSpeed() * friction);
            m_shouldRotate = true;

        }
        else
        {
            m_shouldRotate = false;
            RigidBody::Update(deltaTime);

        }

        SetPosition(nextPosition.x, nextPosition.y);

        if (colOBJ == 131)
        {
            // fragment.rotateImage(m_rotationSpeed * deltaTime, true);
            SetVelocity(GetVelocity().x * friction, GetVelocity().y);

            if (abs(GetVelocity().x) < speedLimit && abs(GetVelocity().y) < speedLimit)
            {
                SetVelocity(0, 0);
                SetRotationSpeed(0);
                m_shouldRotate = true;
                if (!_initCnt)
                {
                    _cnt++;
                }
                if (_cnt < 80)
                {
                    if (_cnt % 20 == 0)
                    {
                        m_render = !m_render;
                    }

                }
                else if (_cnt >= 80 && _cnt < 140)
                {
                    if (_cnt % 5 == 0)
                    {
                        m_render = !m_render;
                    }
                }
                if (_cnt > 140)
                {
                    m_render = false;
                    _goUpdate = false;
                    _initCnt = true;
                    //  m_rotationRender.release();
                     // _cnt = 0;
                }
            }
            else
            {
                m_shouldRotate = false;
                SetAcceleration(0, currentGravity);
            }
        }
      
        m_rotation += (m_rotationSpeed * deltaTime);
    }
   
    
}
