#include "Stdafx.h"
#include "Kunai.h"

HRESULT Kunai::init()
{
  
    speed = 30;
    angle = 0.0;
    isLeftFlying = false;
    isRightFlying = false;
    lIdx = 5;
    isLeftStuck = false;
    isRightStuck = false;
    createL_Rope = false;
    createR_Rope = false;
   
	return S_OK;
}

void Kunai::release(void)
{

}

void Kunai::update(void)
{
    radian = angle * (3.14159265f / 180.0f);
    if (KEYMANAGER->isStayKeyDown('Q'))
    {
        isLeftFlying = false;
        createL_Rope = true;
        inputQ = true;
        angle = -135.0f;
    }
    else
    {
        inputQ = false;
        isLeftFlying = true;
        isLeftStuck = false;
        leftAnimFinished = false;

        createL_Rope = false;
        EfLeft = false;
        L_pathPoints.clear();
    }
    if (KEYMANAGER->isStayKeyDown('E'))
    {
        inputE = true;
        isRightFlying = false;
        createR_Rope = true;
        angle = -55.0f;
    }
    else
    {
        inputQ = false;
        rightAnimFinished = false;
        isRightFlying = true;
        isRightStuck = false;

        createR_Rope = false;
        EfRight = false;
        R_pathPoints.clear();
    }

    if (!isLeftFlying && !isLeftStuck)
    {
  
      
        _rc1.left += speed * cos(radian);
        _rc1.right+= speed * cos(radian);
        _rc1.top += speed * sin(radian);
        _rc1.bottom += speed * sin(radian);
        L_pathPoints.push_back(make_pair(_rc1.left+70, _rc1.top+110));
    }
    else
    {
        _rc1 = RectMake(PLAYER->getPlayerPos().left - 60, PLAYER->getPlayerPos().top - 20, 60, 160);
    }
    if (!isRightFlying && !isRightStuck)
    {
        //float radian = angle * (3.14159265f / 180.0f);
        _rc2.left += speed * cos(radian);
        _rc2.right += speed * cos(radian);
        _rc2.top += speed * sin(radian);
        _rc2.bottom += speed * sin(radian);
        R_pathPoints.push_back(make_pair(_rc2.left+20, _rc2.top+60));
    }
    else
    {
        _rc2 = RectMake(PLAYER->getPlayerPos().left + 70, PLAYER->getPlayerPos().top - 20, 60, 160);
    }

    if (isLeftStuck)
    {
        
        EfLeft = true;
        
        kunaiLeftHitWallEF();

    }

    if (isRightStuck)
    {
     //   rIdx = 0;
        EfRight = true;
        kunaiRightHitWallEF();
    }
}

void Kunai::render(HDC hdc)
{
    HPEN newPen, oldPen;
    newPen = CreatePen(PS_SOLID, 3, RGB(0, 0, 0));

    oldPen = (HPEN)SelectObject(hdc, newPen);
    IMAGEMANAGER->frameRender("Äí³ªÀÌ1", hdc, _rc1.left, _rc1.top,0,1);
    if (isLeftStuck && !leftAnimFinished && inputQ)
    {
        IMAGEMANAGER->frameRender("Äí³ªÀÌº®1", hdc, _rc1.left, _rc1.top, lIdx, 1);
    }
    if (createL_Rope)
    {
        for (size_t i = 0; i + 1 < L_pathPoints.size(); ++i)
        {
            MoveToEx(hdc, L_pathPoints[i].first, L_pathPoints[i].second, NULL);
            LineTo(hdc, L_pathPoints[i + 1].first, L_pathPoints[i + 1].second);
        }
       
       
        
    }

    IMAGEMANAGER->frameRender("Äí³ªÀÌ2", hdc, _rc2.left, _rc2.top,0,0);
    if (isRightStuck && !rightAnimFinished && inputE)
    {
        IMAGEMANAGER->frameRender("Äí³ªÀÌº®2", hdc, _rc2.left, _rc2.top, rIdx, 0);
    }
    if (createR_Rope)
    {
        for (size_t i = 0; i + 1< R_pathPoints.size(); ++i)
        {
            MoveToEx(hdc, R_pathPoints[i].first, R_pathPoints[i].second, NULL);
            LineTo(hdc, R_pathPoints[i + 1].first, R_pathPoints[i + 1].second);
        }
    }
    SelectObject(hdc, oldPen);
    DeleteObject(newPen);
}

void Kunai::eraseLeftPathPoints(size_t count)
{
    
    if (count > L_pathPoints.size())
    {
        L_pathPoints.clear();
    }
    else
    {
        L_pathPoints.erase(L_pathPoints.begin(), L_pathPoints.begin() + count);
    }
}

void Kunai::eraseRightPathPoints(size_t count)
{
    if (count > R_pathPoints.size())
    {
        R_pathPoints.clear();
    }
    else
    {
        R_pathPoints.erase(R_pathPoints.begin(), R_pathPoints.begin() + count);
    }
}

void Kunai::kunaiLeftHitWallEF()
{
    if (EfLeft && !leftAnimFinished)
    {
        lCnt++;
      
        if (lCnt % 5 == 0)
        {
            lIdx--;
            cout << lIdx << endl;
            if (lIdx < 0)
            {
               
                leftAnimFinished = true;
                lIdx = 5;
            }
        }
    }
}

void Kunai::kunaiRightHitWallEF()
{
    if (EfRight && !rightAnimFinished)
    {
        rCnt++;
        if (rCnt % 5 == 0)
        {
            rIdx++;
            if (rIdx > 5)
            {
                rightAnimFinished = true;
                rIdx = 0;
                
            }
        }
    }
}