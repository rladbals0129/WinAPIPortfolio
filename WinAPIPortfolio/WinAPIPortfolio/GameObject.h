#pragma once
class GameObject {
public:
    virtual void Update(float deltaTime) = 0;
    virtual void Render() = 0;
    RECT rc;
    bool isBreak;
};

