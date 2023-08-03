#pragma once
#include "GameNode.h"
#include "RotationRender.h"
#include "RigidBody.h"
#include "Fragment.h"
#include "Zombiebot.h"
#include "BoxBreakEffect.h"
#include "Title.h"
#include "ZombieManager.h" 
#include "KunaiCollision.h"
#include "Boss.h"

struct Button
{
	RECT rect;
	string text;

	Button(int left, int top, int width, int height, const string& buttonText)
	{
		rect.left = left;
		rect.top = top;
		rect.right = left + width;
		rect.bottom = top + height;
		text = buttonText;
	}
};

class Tutorial : public GameNode
{
private:
	std::vector<Button> _buttons;
	const int _buttonWidth = 200;
	const int _buttonHeight = 100;
	ZombieManager _zombieManager;
	//ZombieManager* getZombieManager() { return &_zombieManager; }

private:
	
	bool _goTitle;
	
	RotationRender* _rot;

	KunaiCollision* _kunaiCol;

	Boss* _boss;


	
	//타격이펙트
	BoxBreakEffect _slashEffect;
	bool createBoxEF;
	//============//
	//좀비//
	Zombiebot* _zm;
	vector<Zombiebot*> _Fzm;
	Title _title;
	int _zombieDiePosX;
	int _zombieDiePosY;
	RECT _collider;
	std::vector<Fragment> _Zfragments;
	bool _zomIdle;
	int _zomIdleCnt;
	//==================//
	//다른적..//

	//====//


	//플레이어위치
	RECT _pPosRc;

	//넉백
	bool _hitDelay;
	int _hitCnt;
	float _knockBackMagnitude;
	//화면흔들림
	float _shakeDuration;
	float _shakeOffsetX;
	float _shakeOffsetY;
	 float _initialShakeDuration = 0.5f;  // 흔들기 지속시간
	 float _initialShakeMagnitude = 15.0f; // 흔들기 강도


	//버튼

	//RECT _button;


public:

	HRESULT init();
	void relese();
	void update();
	void render();

	bool getGoTitle() { return _goTitle; }

	void setGoTitle(bool x) { _goTitle = x; }
	
	void playerPixel();

	void onButtonClick(int buttonIndex);
	void createFragments(std::vector<Fragment>& fragments, const POINT& position, wchar_t* imagePath, int numFragments);
	void updateShakeEffect(float& shakeDuration, float& shakeOffsetX, float& shakeOffsetY);
	void applyShake(float shakeDuration);
};

