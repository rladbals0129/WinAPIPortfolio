#pragma once



class Kunai 
{
private:
    RECT _rc1; 
    RECT _rc2; 
    int speed; 
    float angle; 

    bool isFlying;

    bool isLeftFlying;
    bool isRightFlying; 
   
    bool isLeftThrown;
    bool isRightThrown;
    float radian;
    float DistanceX;
    float DistanceY;

    bool isLeftStuck;
    bool isRightStuck;
    POINT leftWallCollision;
    POINT rightWallCollision;

    bool createL_Rope;
    bool createR_Rope;
    vector<pair<int, int>> L_pathPoints;
    vector<pair<int, int>> R_pathPoints;
    
    bool EfLeft;
    int lCnt;
    int lIdx;
    bool EfRight;
    int rCnt;
    int rIdx;
   
    bool leftAnimFinished;
    bool rightAnimFinished;

    bool inputQ, inputE;

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
    


    void eraseLeftPathPoints(size_t count);
    void eraseRightPathPoints(size_t count);
   // void setPosition(int x, int y) { this->x = x; this->y = y; }


    void kunaiLeftHitWallEF();
    void kunaiRightHitWallEF();
    
};




