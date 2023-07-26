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

        const float friction = 0.87f; // ������
        const float bounciness = 0.7f; // �ݹ߷�
        const float speedLimit = 0.1f; // �ӵ� ����

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
        // cout << m_rotationSpeed << endl;
        m_rotation += (m_rotationSpeed * deltaTime);
    }
   
    
}


/*
   int currentGravity = RigidBody::getGravity();
    SetAcceleration(0, currentGravity);

    Vec2 nextPosition;
    nextPosition.x = GetPosition().x + GetVelocity().x * deltaTime;
    nextPosition.y = GetPosition().y + GetVelocity().y * deltaTime;

    int colOBJ = GetRValue(GetPixel(hdc, static_cast<int>(nextPosition.x), static_cast<int>(nextPosition.y)));

    const float friction = 0.92f; // ������
    const float bounciness = 0.7f; // �ݹ߷�

    if (colOBJ == 131)
    {
        SetVelocity(GetVelocity().x * friction, -GetVelocity().y * bounciness);
        SetAcceleration(0, 0); // ���ӵ��� 0���� ����
        SetRotationSpeed(GetRotationSpeed() * friction);
        cout << "����?" << endl;
    }
    else
    {
        RigidBody::Update(deltaTime);
    }

    SetPosition(nextPosition.x, nextPosition.y);

    // ���� �ӵ��� ȸ�� �ӵ� ���� ��Ű��
    float speedLimit = 0.1f; // �ӵ� ����
    if (colOBJ == 131)
    {
        SetVelocity(GetVelocity().x * friction, GetVelocity().y);
    }
    if (abs(GetVelocity().x) < speedLimit)
    {
        SetVelocity(0, GetVelocity().y);
    }

    m_rotation += m_rotationSpeed * deltaTime;

*/


/*
    // ���� �ڵ� �������� �ٷ� ���ӵ��� ����
    float currentGravity = RigidBody::getGravity();
    SetAcceleration(0, currentGravity);

    Vec2 nextPosition;
    nextPosition.x = GetPosition().x + GetVelocity().x * deltaTime;
    nextPosition.y = GetPosition().y + GetVelocity().y * deltaTime;

    int colOBJ = GetRValue(GetPixel(hdc, static_cast<int>(nextPosition.x), static_cast<int>(nextPosition.y)));

    
    const float friction = 0.98f; // ������
    const float bounciness = 0.7f; // �ݹ߷�
    const float speedLimit = 0.1f; // �ӵ� ����

    if (colOBJ == 131)
    {
        float velX = GetVelocity().x * friction;
        float velY = -GetVelocity().y * bounciness;

        SetVelocity(velX, velY);

        SetRotationSpeed(GetRotationSpeed() * friction);

        if (abs(GetVelocity().x) < speedLimit && abs(GetVelocity().y) < speedLimit)
        {
            SetVelocity(0, 0);
            SetRotationSpeed(0);
            SetAcceleration(0, 0);
        }
        else
        {
            SetAcceleration(0, currentGravity);
        }
    }
    else
    {
        RigidBody::Update(deltaTime);
    }

    SetPosition(nextPosition.x, nextPosition.y);

    m_rotation += m_rotationSpeed * deltaTime;

*/


/*
   SetVelocity(GetVelocity().x, GetVelocity().y + GetAcceleration().y * deltaTime);

    Vec2 nextPosition;
    nextPosition.x = GetPosition().x + GetVelocity().x * deltaTime;
    nextPosition.y = GetPosition().y + GetVelocity().y * deltaTime;

    int colOBJ = GetRValue(GetPixel(hdc, static_cast<int>(nextPosition.x), static_cast<int>(nextPosition.y)));
   // cout << "colOBJ ��: " << colOBJ << endl;
  //  cout << "X ��ǥ: " << nextPosition.x << " Y ��ǥ: " << nextPosition.y << endl;
    const float friction = 0.98f; //������
    if (colOBJ == 131)
    {
        SetVelocity(GetVelocity().x, -GetVelocity().y * 0.7f);
        SetRotationSpeed(GetRotationSpeed() * 0.7f);


    }
    else
    {
        RigidBody::Update(deltaTime);
    }
    SetPosition(nextPosition.x, nextPosition.y);

    float speedLimit = 0.1f; // �ӵ� ����
    if (colOBJ == 131)
    {
        SetVelocity(GetVelocity().x * friction, GetVelocity().y);
        if (abs(GetVelocity().x) < speedLimit)
        {
            SetVelocity(0, GetVelocity().y);
        }

        SetRotationSpeed(GetRotationSpeed() * friction);
        if (abs(GetRotationSpeed()) < speedLimit)
        {
            SetRotationSpeed(0);
        }
    }


    m_rotation += m_rotationSpeed * deltaTime;

*/