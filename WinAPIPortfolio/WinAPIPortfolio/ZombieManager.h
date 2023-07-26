#pragma once
#include "Zombiebot.h"
#include "Fragment.h"
#include "RotationRender.h"
#include "RigidBody.h"
#include "BoxBreakEffect.h"

class ZombieManager : public GameNode
{
public:

	HRESULT init();
    void createZombie(int x, int y);
    void update(int offsetX,int offsetY);
    void render();
    std::vector<Zombiebot*>& getZombies();
	void setShakeOffset(float& shakeOffsetX, float& shakeOffsetY)
	{
		_shakeOffsetX = &shakeOffsetX;
		_shakeOffsetY = &shakeOffsetY;
	}
	void applyShake(float shakeDuration);

private:
	BoxBreakEffect _slashEffect;
	bool createBoxEF;

	Zombiebot* _zm;
	vector<Zombiebot*> _Fzm;

	
	int _zombieDiePosX;
	int _zombieDiePosY;
	RECT _collider;
	std::vector<Fragment> _Zfragments;
	bool _zomIdle;
	int _zomIdleCnt;
	//�˹�
	bool _hitDelay;
	int _hitCnt;
	float _knockBackMagnitude;
	//ȭ����鸲
	float _shakeDuration;
	float *_shakeOffsetX = nullptr;
    float *_shakeOffsetY = nullptr;
	const float _initialShakeDuration = 0.5f;  // ���� ���ӽð�
	const float _initialShakeMagnitude = 15.0f; // ���� ����

	void updateShakeEffect();
	
	void createFragments(std::vector<Fragment>& fragments, const POINT& position, wchar_t* imagePath, int numFragments);

};
