#include "Stdafx.h"
#include "ResourceClass.h"


HRESULT ResourceClass::init()
{
	IMAGEMANAGER->addImage("타이틀","Resources/Images/Title/Title.bmp", 1280, 800);
	IMAGEMANAGER->addFrameImage("선택", "Resources/Images/Title/select.bmp",
		600, 80,
		6, 2,
		true,
		RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Idle", "Resources/Images/Player/PlayerIdle.bmp",
		1400, 200,
		14, 2,
		true,
		RGB(255, 0, 255));


	IMAGEMANAGER->addFrameImage("머리", "Resources/Images/Player/TabletFaces.bmp", 
		46,104,
		1,2
		);

	IMAGEMANAGER->addFrameImage("기본표정", "Resources/Images/Player/idleFaceA.bmp",
		1288, 104,
		 28, 2,
		true,
		RGB(255, 0, 255));
	
	IMAGEMANAGER->addFrameImage("런표정", "Resources/Images/Player/runFace.bmp",
		46, 104,
		1, 2,
		true,
		RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("숙인표정", "Resources/Images/Player/crouchFace.bmp",
		40, 60,
		1,2,
		true,
		RGB(255, 0, 255));
	IMAGEMANAGER->addImage("공격표정", "Resources/Images/Player/Attack/attackFace.bmp",
		40, 30,
		true,
		RGB(255, 0, 255));

	IMAGEMANAGER->addFrameImage("Move", "Resources/Images/Player/PlayerRun.bmp",
		2500, 200,
		25, 2,
		true,
		RGB(255, 0, 255));

	IMAGEMANAGER->addFrameImage("Jump", "Resources/Images/Player/PlayerJump.bmp",
		2300, 200,
		23, 2,
		true,
		RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Crouch", "Resources/Images/Player/crouch.bmp",
		70, 100,
		1, 2,
		true,
		RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Attack", "Resources/Images/Player/Attack/Attack.bmp",
		1440, 320,
		9, 2,
		true,
		RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("AttackFX", "Resources/Images/Player/Attack/attackFX.bmp",
		720, 280,
		4, 2,
		true,
		RGB(255, 0, 255));
	
	IMAGEMANAGER->addImage("스테이지1", "Resources/Images/Stage1/_tStage1-1.bmp", 8960,1600); //7680 1440
	IMAGEMANAGER->addImage("스테이지1픽셀", "Resources/Images/Stage1/tStage1-1.bmp", 8960, 1600 );
	
	IMAGEMANAGER->addImage("문", "Resources/Images/Stage1/Object/Door.bmp", 55, 225);// 37 166
	IMAGEMANAGER->addImage("일본도", "Resources/Images/Player/Weapon/Knife.bmp", 140, 50,true,RGB(255,0,255));// 37 166

	IMAGEMANAGER->addFrameImage("일본도이펙트", "Resources/Images/Stage1/Object/Knife_particle.bmp",
		980, 50,
		7, 1,
		true,
		RGB(255, 0, 255));

	IMAGEMANAGER->addFrameImage("방향키위", "Resources/Images/UI/UI-Keyboard-up.bmp",
		60, 30,
		2, 1,
		true,
		RGB(255, 0, 255));

	IMAGEMANAGER->addImage("일본도텍스트", "Resources/Images/UI/knifeTXT.bmp",
		468, 223,
		true,
		RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("엔터키", "Resources/Images/UI/UI_Keyboard_return.bmp",
		80, 40,
		2, 1,
		true,
		RGB(255, 0, 255));
	IMAGEMANAGER->addImage("일본도획득", "Resources/Images/UI/getKnifeUI.bmp", 1280, 800,true,RGB(255,0,255)); 
	
	
	
	
	
	
	
	
	
	
	
	return S_OK;
}

