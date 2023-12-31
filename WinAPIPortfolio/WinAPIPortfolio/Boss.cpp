#include "Stdafx.h"
#include "Boss.h"

HRESULT Boss::init(void)
{
    _hp = 9;
    _dmg = 20;
    _die = false;
    _realDie = false;
    _rc = RectMake(620, 300, 108, 82);
    _obj1 = 0;
    _obj2 = 120;
    _obj3 = 240;
    _obj4 = 40;
    _obj5 = 80;
    _obj6 = 160;
    _obj7 = 200;
    _obj8 = 280;
    _obj9 = 320;

    _currentState = IDLE;
    _delayTime = 0;
    _isLeft = true;
    _maxMovementTime = 80;
    _currentPattern = 0;
    _dieAlpha = 255;
    _rockRc = RectMake(530, 318, 220, 164);
    _kunaiCol = new Kunai;
    return S_OK;
}

void Boss::release(void)
{
}

void Boss::update(void)
{
    if (!_realDie)
    {
        if (_hp <= 0 && !_once)
        {
            _breakStartX = (_rc.left + _rc.right) / 2;
            _breakStartY = (_rc.top + _rc.bottom) / 2;
            _die = true;
            _currentState = DIE;
            _FXDie = true;
            _once = true;
        }
        if (_hit)
        {
            if (!_hitSound)
            {
                SOUNDMANAGER->play("보스피격");
                SOUNDMANAGER->setVolume("보스피격", 0.2f);
                SOUNDMANAGER->play("칼피격");
                SOUNDMANAGER->setVolume("칼피격", 0.2f);
                SOUNDMANAGER->play("공통사망");
                SOUNDMANAGER->setVolume("공통사망", 0.2f);
                _hitSound = true;
            }
        }
        else
        {
            _hitSound = false;
        }


        if (!_die)
        {
            if (_currentState == IDLE)
            {
                _patternSound1 = false;
                _patternSound2 = false;
                _patternSound3 = false;
                if (!_shieldSound)
                {
                    SOUNDMANAGER->play("보스쉴드");
                    SOUNDMANAGER->setVolume("보스쉴드", 0.2f);
                    _shieldSound = true;
                   
                }

                if (_currentPattern % 3 == 0)
                {
                    _alpha = 0;
                    if (!_isLeft)
                    {
                        if (_rc.left > 200 && _rc.top > 100)
                        {
                            if (_rc.left > 200)
                            {
                                _rc.left -= 4;
                                _rc.right -= 4;
                            }
                            else
                            {
                                _rc.left = _rc.left;
                                _rc.right = _rc.right;
                            }
                            if (_rc.top > 110)
                            {
                                _rc.top -= 2;
                                _rc.bottom -= 2;
                            }
                            else
                            {
                                _rc.top = _rc.top;
                                _rc.bottom = _rc.bottom;
                            }



                        }
                        else
                        {
                            _delayTime++;
                            if (_delayTime > 120)
                            {
                                _currentState = ATTACK1;
                                _movementTime = 0;
                                _delayTime = 0;
                            }
                        }

                    }
                    else
                    {
                        if (_rc.left < 1000 && _rc.top > 100)
                        {
                            if (_rc.left < 1000)
                            {
                                _rc.left += 4;
                                _rc.right += 4;
                            }
                            else
                            {
                                _rc.left = _rc.left;
                                _rc.right = _rc.right;
                            }
                            if (_rc.top > 110)
                            {
                                _rc.top -= 2;
                                _rc.bottom -= 2;
                            }
                            else
                            {
                                _rc.top = _rc.top;
                                _rc.bottom = _rc.bottom;
                            }



                        }

                        else
                        {
                            _delayTime++;
                            if (_delayTime > 120)
                            {
                                _currentState = ATTACK1;
                                _movementTime = 0;
                                _delayTime = 0;
                            }
                        }
                    }
                }

                if (_currentPattern % 3 == 1)
                {
                    int screenWidth = 1280;
                    int screenHeight = 800;
                    int targetX = (screenWidth - 102) / 2;
                    int targetY = (screenHeight - 120) / 2;


                    int speedX = 1;
                    int speedY = 1;


                    if (_rc.left < targetX)
                    {
                        _rc.left += speedX;
                        _rc.right += speedX;
                    }
                    else if (_rc.left > targetX)
                    {
                        _rc.left -= speedX;
                        _rc.right -= speedX;
                    }


                    if (_rc.top < targetY)
                    {
                        _rc.top += speedY;
                        _rc.bottom += speedY;
                    }
                    else if (_rc.top > targetY)
                    {
                        _rc.top -= speedY;
                        _rc.bottom -= speedY;
                    }


                    if (_rc.left == targetX && _rc.top == targetY)
                    {
                      
                        _currentState = ATTACK2;
                    }
                }

                if (_currentPattern % 3 == 2)
                {
                    if (!_isLeft)
                    {
                        if (_rc.left > 200 && _rc.top > 100)
                        {
                            if (_rc.left > 200)
                            {
                                _rc.left -= 4;
                                _rc.right -= 4;
                            }
                            else
                            {
                                _rc.left = _rc.left;
                                _rc.right = _rc.right;
                            }
                            if (_rc.top > 110)
                            {
                                _rc.top -= 2;
                                _rc.bottom -= 2;
                            }
                            else
                            {
                                _rc.top = _rc.top;
                                _rc.bottom = _rc.bottom;
                            }



                        }
                        else
                        {
                            _delayTime2++;
                            if (_delayTime2 > 120)
                            {
                                _currentState = ATTACK3;
                                _delayTime2 = 0;
                            }
                        }

                    }
                    else
                    {
                        if (_rc.left < 1000 && _rc.top > 100)
                        {
                            if (_rc.left < 1000)
                            {
                                _rc.left += 4;
                                _rc.right += 4;
                            }
                            else
                            {
                                _rc.left = _rc.left;
                                _rc.right = _rc.right;
                            }
                            if (_rc.top > 110)
                            {
                                _rc.top -= 2;
                                _rc.bottom -= 2;
                            }
                            else
                            {
                                _rc.top = _rc.top;
                                _rc.bottom = _rc.bottom;
                            }



                        }

                        else
                        {
                            _delayTime2++;
                            if (_delayTime2 > 120)
                            {
                                _currentState = ATTACK3;
                                _delayTime2 = 0;
                            }
                        }
                    }
                }

                _breath = (_breath + 1) % 360;
                _obj1++;
                _obj2++;
                _obj3++;
                _obj4++;
                _obj5++;
                _obj6++;
                _obj7++;
                _obj8++;
                _obj9++;

                _idleHandCnt++;
                _idleWeaponCnt++;
            }

            if (_currentState == ATTACK1)
            {
                if (_movementTime < _maxMovementTime)
                {
                    if (!_patternSound1)
                    {
                        SOUNDMANAGER->play("보스패턴1");
                        SOUNDMANAGER->setVolume("보스패턴1", 0.2f);
                        _patternSound1 = true;
                    }
                    pattern1();
                    _movementTime++;
                }
                else
                {
                   
                    _isLeft = !_isLeft;
                    _currentState = IDLE;
                }

            }

            if (_currentState == ATTACK2)
            {
                _idleHandCnt++;
                _idleWeaponCnt++;
                if (!_hit)
                {
                    if (!_patternSound2)
                    {
                        SOUNDMANAGER->play("보스패턴2");
                        SOUNDMANAGER->setVolume("보스패턴2", 0.2f);
                        _patternSound2 = true;
                    }
                }
             
              
                if (_hit)
                {
                  
                    _currentState = IDLE;
                }
            }

            if (_currentState == ATTACK3)
            {
                if (!_patternSound3)
                {
                    SOUNDMANAGER->play("보스패턴3");
                    SOUNDMANAGER->setVolume("보스패턴3", 0.2f);
                    _patternSound3 = true;
                }
                _idleHandCnt++;
                _idleWeaponCnt++;
                pattern3();
                if (_hit)
                {
                   
                    _currentState == IDLE;
                }
            }
        }
        else if (_die)
        {
            _breath = (_breath + 1) % 360;
            _obj1++;
            _obj2++;
            _obj3++;
            _obj4++;
            _obj5++;
            _obj6++;
            _obj7++;
            _obj8++;
            _obj9++;
            _idleHandCnt++;
            _idleWeaponCnt++;
            dieAnim();

        }
    }
 
   
    
    
}

void Boss::render(void)
{
    if (!_realDie)
    {
        if (_currentState == IDLE)
        {
            IdleBossRender();
        }

        if (_currentState == ATTACK1)
        {
            if (!_isLeft)
            {
                IMAGEMANAGER->frameRender("보스Attack1", getMemDC(), _rc.left, _rc.top, 0, 0);
                IMAGEMANAGER->frameRender("보스공격무기1", getMemDC(), _rc.left - 40, _rc.top + 20, 0, 0);
                IMAGEMANAGER->frameRender("보스공격얼굴1", getMemDC(), _rc.left + 40, _rc.top - 12, 0, 0);




            }
            else
            {
                IMAGEMANAGER->frameRender("보스Attack1", getMemDC(), _rc.left, _rc.top, 0, 1);
                IMAGEMANAGER->frameRender("보스공격무기1", getMemDC(), _rc.left + 40, _rc.top + 30, 0, 1);
                IMAGEMANAGER->frameRender("보스공격얼굴1", getMemDC(), _rc.left - 40, _rc.top - 12, 0, 1);


            }
        }

        if (_currentState == ATTACK2)
        {
            float _idleHandCntX = cos(_idleHandCnt * 0.1f) * 5;
            float _idleHandCntY = sin(_idleWeaponCnt * 0.1f) * 5;
            float _idleWeaponCntX = cos(_idleWeaponCnt * 0.08f) * 5;
            float _idleWeaponCntY = sin(_idleWeaponCnt * 0.08f) * 5;
            IMAGEMANAGER->render("보스Idle", getMemDC(), _rc.left, _rc.top);
            IMAGEMANAGER->render("보스공격무기2", getMemDC(), _rc.left + 70 + _idleWeaponCntX, _rc.top - 80 + _idleWeaponCntY);
            IMAGEMANAGER->render("보스공격얼굴2", getMemDC(), _rc.left + 16, _rc.top - 56 + _idleHandCntY);
        }

        if (_currentState == ATTACK3)
        {
            float _idleHandCntX = cos(_idleHandCnt * 0.1f) * 5;
            float _idleHandCntY = sin(_idleWeaponCnt * 0.1f) * 5;
            float _idleWeaponCntX = cos(_idleWeaponCnt * 0.08f) * 5;
            float _idleWeaponCntY = sin(_idleWeaponCnt * 0.08f) * 5;
            if (!_isLeft)
            {
                IMAGEMANAGER->render("보스Idle", getMemDC(), _rc.left, _rc.top);
                IMAGEMANAGER->frameRender("보스공격무기3", getMemDC(), _rc.left - 55 + _idleWeaponCntX, _rc.top + 25 + _idleWeaponCntY, 0, 0);
                IMAGEMANAGER->frameRender("보스공격얼굴3", getMemDC(), _rc.left, _rc.top - 46, 0, 0);
                IMAGEMANAGER->frameRender("보스공격손", getMemDC(), _rc.left + 70 + _idleHandCntX, _rc.top + 30 + _idleHandCntY, 0, 1);



            }
            else
            {
                IMAGEMANAGER->render("보스Idle", getMemDC(), _rc.left, _rc.top);
                IMAGEMANAGER->frameRender("보스공격무기3", getMemDC(), _rc.left + 70 + _idleWeaponCntX, _rc.top + 30 + _idleWeaponCntY, 0, 1);
                IMAGEMANAGER->frameRender("보스공격얼굴3", getMemDC(), _rc.left + 16, _rc.top - 46, 0, 1);
                IMAGEMANAGER->frameRender("보스공격손", getMemDC(), _rc.left - 35 + _idleHandCntX, _rc.top + 25 + _idleHandCntY, 0, 0);

            }
            IMAGEMANAGER->alphaRender("보스돌", getMemDC(), _rockRc.left, _rockRc.top, _alpha);

        }

        if (_currentState == DIE)
        {
            float _obj1X = cos(_obj1 * 0.07f) * 130;
            float _obj1Y = sin(_obj1 * 0.07f) * 130;
            float _obj2X = cos(_obj2 * 0.07f) * 130;
            float _obj2Y = sin(_obj2 * 0.07f) * 130;
            float _obj3X = cos(_obj3 * 0.07f) * 130;
            float _obj3Y = sin(_obj3 * 0.07f) * 130;
            float _obj4X = cos(_obj4 * 0.07f) * 130;
            float _obj5X = cos(_obj5 * 0.07f) * 130;
            float _obj6X = cos(_obj6 * 0.07f) * 130;
            float _obj7X = cos(_obj7 * 0.07f) * 130;
            float _obj8X = cos(_obj8 * 0.07f) * 130;
            float _obj9X = cos(_obj9 * 0.07f) * 130;
            float _obj4Y = sin(_obj4 * 0.07f) * 130;
            float _obj5Y = sin(_obj5 * 0.07f) * 130;
            float _obj6Y = sin(_obj6 * 0.07f) * 130;
            float _obj7Y = sin(_obj7 * 0.07f) * 130;
            float _obj8Y = sin(_obj8 * 0.07f) * 130;
            float _obj9Y = sin(_obj9 * 0.07f) * 130;

            float _idleHandCntX = cos(_idleHandCnt * 0.1f) * 5;
            float _idleHandCntY = sin(_idleWeaponCnt * 0.1f) * 5;
            float _idleWeaponCntX = cos(_idleWeaponCnt * 0.08f) * 3;
            float _idleWeaponCntY = sin(_idleWeaponCnt * 0.08f) * 3;

            IMAGEMANAGER->render("보스Idle", getMemDC(), _rc.left, _rc.top);
            IMAGEMANAGER->render("보스오브젝트1", getMemDC(), _rc.left + 18 + _obj1X, _rc.top - 5 + _obj1Y);
            IMAGEMANAGER->render("보스오브젝트2", getMemDC(), _rc.left + 18 + _obj2X, _rc.top - 5 + _obj2Y);
            IMAGEMANAGER->render("보스오브젝트3", getMemDC(), _rc.left + 18 + _obj3X, _rc.top - 5 + _obj3Y);
            IMAGEMANAGER->render("보스오브젝트2", getMemDC(), _rc.left + 18 + _obj4X, _rc.top - 5 + _obj4Y);
            IMAGEMANAGER->render("보스오브젝트1", getMemDC(), _rc.left + 18 + _obj5X, _rc.top - 5 + _obj5Y);
            IMAGEMANAGER->render("보스오브젝트3", getMemDC(), _rc.left + 18 + _obj6X, _rc.top - 5 + _obj6Y);
            IMAGEMANAGER->render("보스오브젝트3", getMemDC(), _rc.left + 18 + _obj7X, _rc.top - 5 + _obj7Y);
            IMAGEMANAGER->render("보스오브젝트2", getMemDC(), _rc.left + 18 + _obj8X, _rc.top - 5 + _obj8Y);
            IMAGEMANAGER->render("보스오브젝트1", getMemDC(), _rc.left + 18 + _obj9X, _rc.top - 5 + _obj9Y);
            IMAGEMANAGER->render("보스기본손", getMemDC(), _rc.left - 15 + _idleHandCntX, _rc.top + 25 + _idleHandCntY);
            IMAGEMANAGER->render("보스기본무기", getMemDC(), _rc.left + 40 + _idleWeaponCntX, _rc.top + 25 + _idleWeaponCntY);
            IMAGEMANAGER->render("보스피격얼굴", getMemDC(), _rc.left + 16, _rc.top - 56);
            if (_FXDie)
            {
                IMAGEMANAGER->render("깨지는파티클", getMemDC(), _breakStartX, _breakStartY, _breakSizeX, _breakSizeY);
                IMAGEMANAGER->alphaRender("보스사망이펙트", getMemDC(),0,0, _dieAlpha);
            }
        }
    }
  


    

}

void Boss::pattern1(void)
{
    const float pi = 3.14159265;

  
    float t = static_cast<float>(_movementTime) / static_cast<float>(_maxMovementTime);

    float startX = _isLeft ? 1000 : 200;
    float endX = _isLeft ? 200 : 1000;

    float startY = 110;
    float endY = 110;

    int amplitude = 400;  

   
    float newX = startX + t * (endX - startX);

   
    float newY = startY + t * (endY - startY);

   
    int newTop = static_cast<int>(newY + amplitude * sin(pi * t));


    int width = _rc.right - _rc.left;
    int height = _rc.bottom - _rc.top;

    _rc.left = static_cast<int>(newX);
    _rc.right = static_cast<int>(newX + width);
    _rc.top = newTop;
    _rc.bottom = newTop + height;
}

void Boss::pattern2(void)
{
}

void Boss::pattern3(void)
{
    _aCnt++;
    if (_aCnt % 2 == 0)
    {
        
        if (_alpha < 255)
        {
            _alpha++;
        }
        else if (_alpha >= 255)
        {
            _alpha = 255;
        }
    }
  

    if (IntersectRect(&_collider, &_rockRc, &PLAYER->getPlayerPos()))
    {
        PLAYER->setOnRock(true);
        PLAYER->setPlayerPosBottom(8);
    }
    else
    {
        PLAYER->setOnRock(false);
    }
   
   
}

void Boss::dieAnim(void)
{
    _FXDieCnt++;
    if (_FXDieCnt % 2 == 0)
    {
        
        _FXDie = true;
        if (_FXDie && _goFX < 5)
        {
            _dieAlpha -= 5;
            _breakSizeX += 30;
            _breakSizeY += 30;
            _breakStartX -= 15;
            _breakStartY -= 15;
            if (_breakSizeX > 1000 && _breakSizeY > 800)
            {
                _goFX++;
                SOUNDMANAGER->play("공통사망");
                SOUNDMANAGER->setVolume("공통사망", 0.2f);
                _dieAlpha = 255;
                _FXDie = false;
                _breakSizeX = 0;
                _breakSizeY = 0;
                _breakStartX = (_rc.left + _rc.right) / 2;
                _breakStartY = (_rc.top + _rc.bottom) / 2;

            }
        }
        else
        {
            _realDie = true;
            
            cout << _realDie << endl;
        }
    }
   
}

void Boss::IdleBossRender(void)
{
    float _breathY = sin(_breath * 0.1f) * 5;

    float _obj1X = cos(_obj1 * 0.07f) * 130;
    float _obj1Y = sin(_obj1 * 0.07f) * 130;
    float _obj2X = cos(_obj2 * 0.07f) * 130;
    float _obj2Y = sin(_obj2 * 0.07f) * 130;
    float _obj3X = cos(_obj3 * 0.07f) * 130;
    float _obj3Y = sin(_obj3 * 0.07f) * 130;
    float _obj4X = cos(_obj4 * 0.07f) * 130;
    float _obj5X = cos(_obj5 * 0.07f) * 130;
    float _obj6X = cos(_obj6 * 0.07f) * 130;
    float _obj7X = cos(_obj7 * 0.07f) * 130;
    float _obj8X = cos(_obj8 * 0.07f) * 130;
    float _obj9X = cos(_obj9 * 0.07f) * 130;
    float _obj4Y = sin(_obj4 * 0.07f) * 130;
    float _obj5Y = sin(_obj5 * 0.07f) * 130;
    float _obj6Y = sin(_obj6 * 0.07f) * 130;
    float _obj7Y = sin(_obj7 * 0.07f) * 130;
    float _obj8Y = sin(_obj8 * 0.07f) * 130;
    float _obj9Y = sin(_obj9 * 0.07f) * 130;

    float _idleHandCntX = cos(_idleHandCnt * 0.1f) * 5;
    float _idleHandCntY = sin(_idleWeaponCnt * 0.1f) * 5;
    float _idleWeaponCntX = cos(_idleWeaponCnt * 0.08f) * 3;
    float _idleWeaponCntY = sin(_idleWeaponCnt * 0.08f) * 3;

    IMAGEMANAGER->render("보스Idle", getMemDC(), _rc.left, _rc.top);
    IMAGEMANAGER->render("보스오브젝트1", getMemDC(), _rc.left + 18 + _obj1X, _rc.top - 5 + _obj1Y);
    IMAGEMANAGER->render("보스오브젝트2", getMemDC(), _rc.left + 18 + _obj2X, _rc.top - 5 + _obj2Y);
    IMAGEMANAGER->render("보스오브젝트3", getMemDC(), _rc.left + 18 + _obj3X, _rc.top - 5 + _obj3Y);
    IMAGEMANAGER->render("보스오브젝트2", getMemDC(), _rc.left + 18 + _obj4X, _rc.top - 5 + _obj4Y);
    IMAGEMANAGER->render("보스오브젝트1", getMemDC(), _rc.left + 18 + _obj5X, _rc.top - 5 + _obj5Y);
    IMAGEMANAGER->render("보스오브젝트3", getMemDC(), _rc.left + 18 + _obj6X, _rc.top - 5 + _obj6Y);
    IMAGEMANAGER->render("보스오브젝트3", getMemDC(), _rc.left + 18 + _obj7X, _rc.top - 5 + _obj7Y);
    IMAGEMANAGER->render("보스오브젝트2", getMemDC(), _rc.left + 18 + _obj8X, _rc.top - 5 + _obj8Y);
    IMAGEMANAGER->render("보스오브젝트1", getMemDC(), _rc.left + 18 + _obj9X, _rc.top - 5 + _obj9Y);

    IMAGEMANAGER->render("보스기본손", getMemDC(), _rc.left - 15 + _idleHandCntX, _rc.top + 25 + _idleHandCntY);
    IMAGEMANAGER->render("보스기본무기", getMemDC(), _rc.left + 40 + _idleWeaponCntX, _rc.top + 25 + _idleWeaponCntY);
    if (!_hit)
    {
        IMAGEMANAGER->render("보스기본얼굴", getMemDC(), _rc.left + 16, _rc.top - 56 + _breathY);
    }
    else
    {
        IMAGEMANAGER->render("보스피격얼굴", getMemDC(), _rc.left + 16, _rc.top - 56);
    }
   
}

