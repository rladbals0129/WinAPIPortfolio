#pragma once



class Kunai 
{
private:
    RECT _rc1; //���� ��ġ ����
    RECT _rc2; //���� ��ġ ������
    int speed; // ������ �ӵ�
    float angle; // ������ ȸ�� ����
    bool isFlying;
    bool isLeftFlying; // ���̰� ���ư����� �ƴ����� �˻��ϴ� ����
    bool isRightFlying; 
    bool _render;

    bool isLeftThrown;
    bool isRightThrown;

    float DistanceX;
    float DistanceY;

    bool isLeftStuck;
    bool isRightStuck;
    POINT leftWallCollision;
    POINT rightWallCollision;

   

public :
    HRESULT init();
    void release(void);
    void update(void);
    void render(HDC hdc);

    RECT getLeftKuniaPos() { return _rc1; }
    RECT getRightKuniaPos() { return _rc2; }

    bool getLeftFlying() { return isLeftFlying; }
    bool getRightFlying() { return isRightFlying; }



    void setLeftStuck(bool stuck) { isLeftStuck = stuck; }
    void setRightStuck(bool stuck) { isRightStuck = stuck; }
    bool getLeftStuck() { return isLeftStuck; }
    bool getRightStuck() { return isRightStuck; }

    void setLeftWallCollision(POINT p) { leftWallCollision = p; }
    void setRightWallCollision(POINT p) { rightWallCollision = p; }
    const POINT& getLeftWallCollision() const { return leftWallCollision; }
    const POINT& getRightWallCollision() const { return rightWallCollision; }
    
   // void setPosition(int x, int y) { this->x = x; this->y = y; }

    
    
};




