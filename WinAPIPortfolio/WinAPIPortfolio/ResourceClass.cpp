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

	IMAGEMANAGER->addFrameImage("달리기먼지", "Resources/Images/Effect/run.bmp",
		120,200,
		3,2,
		true,
		RGB(255,0,255));
	IMAGEMANAGER->addFrameImage("머리", "Resources/Images/Player/TabletFaces.bmp",
		46, 104,
		1, 2,
		true,
		RGB(255, 0, 255)
		);
	IMAGEMANAGER->addFrameImage("개피", "Resources/Images/Player/TabletFaces_battery.bmp",
		28, 64,
		1, 2
		);
	IMAGEMANAGER->addFrameImage("피격표정", "Resources/Images/Player/TabletFacesHit.bmp",
		32, 72,
		1, 2,
		true,
		RGB(255, 0, 255)
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
	IMAGEMANAGER->addFrameImage("플레이어생성", "Resources/Images/Player/MonoBoy-fall.bmp",
		240, 120,
		2, 1,
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
	IMAGEMANAGER->addFrameImage("AttackFXUP", "Resources/Images/Player/Attack/attackFXUP.bmp",
		800, 400,
		4, 2,
		true,
		RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("AttackFXDown", "Resources/Images/Player/Attack/attackFXDown.bmp",
		800, 400,
		4, 2,
		true,
		RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("AttackUP", "Resources/Images/Player/Attack/playerUpAttack.bmp",
		800, 240,
		5, 2,
		true,
		RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("AttackDown", "Resources/Images/Player/Attack/playerDownAttack.bmp",
		800, 160,
		5, 2,
		true,
		RGB(255, 0, 255));

	
	IMAGEMANAGER->addImage("스테이지1", "Resources/Images/Stage1/_tStage1-1.bmp", 8960,1600); //7680 1440
	IMAGEMANAGER->addImage("스테이지1픽셀", "Resources/Images/Stage1/tStage1-1.bmp", 8960, 1600 );
	
	IMAGEMANAGER->addImage("깨진유리아래", "Resources/Images/Stage1/Object/breakGlassTubeDown.bmp", 146, 51,true,RGB(255,0,255));
	IMAGEMANAGER->addImage("깨진유리위", "Resources/Images/Stage1/Object/breakGlassTubeUP.bmp", 146, 51,true,RGB(255,0,255));
	IMAGEMANAGER->addFrameImage("유리관", "Resources/Images/Stage1/Object/glassTube.bmp",
		502, 200,
		4,1,
		true,
		RGB(255, 0, 255));
	IMAGEMANAGER->addImage("유리관플레이어", "Resources/Images/Stage1/Object/Laboratory-PlayerSprite.bmp",
		50, 88,
		true,
		RGB(255,0,255));
																						//536,213
	IMAGEMANAGER->addFrameImage("E키", "Resources/Images/UI/PushE.bmp",
		40, 20,
		2, 1,
		true,
		RGB(255, 0, 255));
	IMAGEMANAGER->addImage("체력패널", "Resources/Images/UI/hpUI.bmp", 202, 47, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("코인패널", "Resources/Images/UI/coinUI.bmp", 133, 46, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("체력바", "Resources/Images/UI/hpbarUI.bmp", 155, 29, true, RGB(255, 0, 255));


	IMAGEMANAGER->addImage("깨지는파티클", "Resources/Images/Effect/Shockwave.bmp", 484, 477, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("달리기이펙트", "Resources/Images/Effect/run.bmp", 120, 200, 3, 2, true, RGB(255, 0, 255));

	IMAGEMANAGER->addFrameImage("유리폭발", "Resources/Images/Effect/GlassSheet.bmp",
		360, 380,
		5, 5,
		true,
		RGB(255, 0, 255));

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
		312,165,
		true,
		RGB(255, 0, 255));
	IMAGEMANAGER->addImage("컴퓨터텍스트", "Resources/Images/UI/txtCom.bmp",
		296, 82
	);
	IMAGEMANAGER->addFrameImage("엔터키", "Resources/Images/UI/UI_Keyboard_return.bmp",
		80, 40,
		2, 1,
		true,
		RGB(255, 0, 255));
	IMAGEMANAGER->addImage("일본도획득", "Resources/Images/UI/getKnifeUI.bmp", 1280, 800,true,RGB(255,0,255)); 
	
	
	
	
	IMAGEMANAGER->addImage("배경시체", "Resources/Images/Stage1/Object/bgDumi.bmp", 600, 300, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("상자", "Resources/Images/Stage1/Object/Box.bmp", 120, 80, true, RGB(255, 0, 255));
	//IMAGEMANAGER->addImage("상자조각", "Resources/Images/Stage1/Object/BoxBreak.bmp", 72, 40, true, RGB(255, 0, 255));
	

	
	IMAGEMANAGER->addFrameImage("좀비정지", "Resources/Images/Enemy/Zombie/Zombiebot_sleep.bmp", 200, 52, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("좀비기상", "Resources/Images/Enemy/Zombie/Zombiebot_wake.bmp", 200, 70, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("좀비이동", "Resources/Images/Enemy/Zombie/Zombiebot_move.bmp", 396, 172, 4, 2, true, RGB(255, 0, 255));


	
	
	
	return S_OK;
}

