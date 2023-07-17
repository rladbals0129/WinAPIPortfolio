#include "Stdafx.h"
#include "ResourceClass.h"


HRESULT ResourceClass::init()
{
	IMAGEMANAGER->addImage("Ÿ��Ʋ","Resources/Images/Title/Title.bmp", 1280, 800);
	IMAGEMANAGER->addFrameImage("����", "Resources/Images/Title/select.bmp",
		600, 80,
		6, 2,
		true,
		RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Idle", "Resources/Images/Player/PlayerIdle.bmp",
		1400, 200,
		14, 2,
		true,
		RGB(255, 0, 255));


	IMAGEMANAGER->addFrameImage("�Ӹ�", "Resources/Images/Player/TabletFaces.bmp", 
		46,104,
		1,2
		);

	IMAGEMANAGER->addFrameImage("�⺻ǥ��", "Resources/Images/Player/idleFaceA.bmp",
		1288, 104,
		 28, 2,
		true,
		RGB(255, 0, 255));
	
	IMAGEMANAGER->addFrameImage("��ǥ��", "Resources/Images/Player/runFace.bmp",
		46, 104,
		1, 2,
		true,
		RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("����ǥ��", "Resources/Images/Player/crouchFace.bmp",
		40, 60,
		1,2,
		true,
		RGB(255, 0, 255));
	IMAGEMANAGER->addImage("����ǥ��", "Resources/Images/Player/Attack/attackFace.bmp",
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
	
	IMAGEMANAGER->addImage("��������1", "Resources/Images/Stage1/_tStage1-1.bmp", 8960,1600); //7680 1440
	IMAGEMANAGER->addImage("��������1�ȼ�", "Resources/Images/Stage1/tStage1-1.bmp", 8960, 1600 );
	
	IMAGEMANAGER->addImage("��", "Resources/Images/Stage1/Object/Door.bmp", 55, 225);// 37 166
	IMAGEMANAGER->addImage("�Ϻ���", "Resources/Images/Player/Weapon/Knife.bmp", 140, 50,true,RGB(255,0,255));// 37 166

	IMAGEMANAGER->addFrameImage("�Ϻ�������Ʈ", "Resources/Images/Stage1/Object/Knife_particle.bmp",
		980, 50,
		7, 1,
		true,
		RGB(255, 0, 255));

	IMAGEMANAGER->addFrameImage("����Ű��", "Resources/Images/UI/UI-Keyboard-up.bmp",
		60, 30,
		2, 1,
		true,
		RGB(255, 0, 255));

	IMAGEMANAGER->addImage("�Ϻ����ؽ�Ʈ", "Resources/Images/UI/knifeTXT.bmp",
		468, 223,
		true,
		RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("����Ű", "Resources/Images/UI/UI_Keyboard_return.bmp",
		80, 40,
		2, 1,
		true,
		RGB(255, 0, 255));
	IMAGEMANAGER->addImage("�Ϻ���ȹ��", "Resources/Images/UI/getKnifeUI.bmp", 1280, 800,true,RGB(255,0,255)); 
	
	
	
	
	
	
	
	
	
	
	
	return S_OK;
}

