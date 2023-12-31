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
#include "Lipo.h"

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
	

private:
	
	bool _goTitle;
	
	RotationRender* _rot;

	KunaiCollision* _kunaiCol;

	Boss* _boss;


	
	//Ÿ������Ʈ
	BoxBreakEffect _slashEffect;
	bool createBoxEF;
	
	//����//

	vector<Zombiebot*> _Fzm;
	Title _title;
	int _zombieDiePosX;
	int _zombieDiePosY;
	RECT _collider;

	bool _zomIdle;
	int _zomIdleCnt;
	//==================//
	
	//����

	vector<Lipo*> _Flp;
	vector<Fragment> _Lfragments;
	
	//����
	bool _bossHitDelay;
	int _bossHitCnt;

	bool _zombieOnce;
	int _zombieOnceCnt;
	
	


	
	RECT _pPosRc;

	
	bool _hitDelay;
	int _hitCnt;
	float _knockBackMagnitude;
	
	float _shakeDuration;
	float _shakeOffsetX;
	float _shakeOffsetY;
	 float _initialShakeDuration = 0.5f;  
	 float _initialShakeMagnitude = 15.0f; 

	 
	


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

	void bossBattle();

	void createLipo(int x, int y);
	void updateLipo();
	void renderLipo();
};

