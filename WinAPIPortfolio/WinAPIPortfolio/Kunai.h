#pragma once



class Kunai 
{
private:
    RECT _rc1; //쿠나이 위치 왼쪽
    RECT _rc2; //쿠나이 위치 오른쪽
    int speed; // 쿠나이의 속도
    float angle; // 쿠나이의 회전 각도
    bool isFlying;
    bool isLeftFlying; // 쿠나이가 날아가는지 아닌지를 검사하는 변수
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




