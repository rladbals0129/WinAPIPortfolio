#pragma once
#include "Zombiebot.h"
#include "Fragment.h"
#include "RotationRender.h"
#include "RigidBody.h"
#include "BoxBreakEffect.h"

class ZombieManager : public GameNode
{
public:
    ZombieManager();
    ~ZombieManager();

    void createZombie(int x, int y);
    void update();
    void render();
    std::vector<Zombiebot*>& getZombies();

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
	float _shakeOffsetX;
	float _shakeOffsetY;
	const float _initialShakeDuration = 0.5f;  // ���� ���ӽð�
	const float _initialShakeMagnitude = 15.0f; // ���� ����

	void updateShakeEffect(float& shakeDuration, float& shakeOffsetX, float& shakeOffsetY);
	void applyShake(float shakeDuration);
	void createFragments(std::vector<Fragment>& fragments, const POINT& position, wchar_t* imagePath, int numFragments);

};
