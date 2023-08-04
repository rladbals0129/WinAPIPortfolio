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

	IMAGEMANAGER->addFrameImage("�޸������", "Resources/Images/Effect/dust.bmp",
		96,32,
		3,1,
		true,
		RGB(255,0,255));
	IMAGEMANAGER->addFrameImage("�Ӹ�", "Resources/Images/Player/TabletFaces.bmp",
		46, 104,
		1, 2,
		true,
		RGB(255, 0, 255)
		);
	IMAGEMANAGER->addFrameImage("����", "Resources/Images/Player/TabletFaces_battery.bmp",
		32, 72,
		1, 2
		);
	IMAGEMANAGER->addImage("����ȭ��", "Resources/Images/UI/UI-CriticalEnergyIndicator.bmp",
		1280, 800,
		true,
		RGB(255,0,255)
	);
	IMAGEMANAGER->addFrameImage("�ǰ�ǥ��", "Resources/Images/Player/TabletFacesHit.bmp",
		32, 72,
		1, 2,
		true,
		RGB(255, 0, 255)
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
	IMAGEMANAGER->addFrameImage("�÷��̾����", "Resources/Images/Player/MonoBoy-fall.bmp",
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

	
	IMAGEMANAGER->addImage("��������1", "Resources/Images/Stage1/_tStage1-1.bmp", 8960,1600); //7680 1440
	IMAGEMANAGER->addImage("��������1�ȼ�", "Resources/Images/Stage1/tStage1-1.bmp", 8960, 1600 );

	IMAGEMANAGER->addImage("��������2", "Resources/Images/Stage2/Stage2.bmp", 5120, 2400); 
	IMAGEMANAGER->addImage("��������2�ȼ�", "Resources/Images/Stage2/_Stage2.bmp", 5120, 2400);

	IMAGEMANAGER->addImage("��������3", "Resources/Images/Stage3/Stage3.bmp", 6400, 800);
	IMAGEMANAGER->addImage("��������3�ȼ�", "Resources/Images/Stage3/_Stage3.bmp", 6400, 800);
	
	IMAGEMANAGER->addImage("���������Ʒ�", "Resources/Images/Stage1/Object/breakGlassTubeDown.bmp", 146, 51,true,RGB(255,0,255));
	IMAGEMANAGER->addImage("����������", "Resources/Images/Stage1/Object/breakGlassTubeUP.bmp", 146, 51,true,RGB(255,0,255));
	IMAGEMANAGER->addFrameImage("������", "Resources/Images/Stage1/Object/glassTube.bmp",
		502, 200,
		4,1,
		true,
		RGB(255, 0, 255));
	IMAGEMANAGER->addImage("�������÷��̾�", "Resources/Images/Stage1/Object/Laboratory-PlayerSprite.bmp",
		50, 88,
		true,
		RGB(255,0,255));
																						//536,213
	IMAGEMANAGER->addFrameImage("EŰ", "Resources/Images/UI/PushE.bmp",
		40, 20,
		2, 1,
		true,
		RGB(255, 0, 255));
	IMAGEMANAGER->addImage("ü���г�", "Resources/Images/UI/hpUI.bmp", 202, 47, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("�����г�", "Resources/Images/UI/coinUI.bmp", 133, 46, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("ü�¹�", "Resources/Images/UI/hpbarUI.bmp", 155, 29, true, RGB(255, 0, 255));
	


	IMAGEMANAGER->addImage("��������ƼŬ", "Resources/Images/Effect/Shockwave.bmp", 484, 477, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�޸�������Ʈ", "Resources/Images/Effect/run.bmp", 120, 200, 3, 2, true, RGB(255, 0, 255));

	IMAGEMANAGER->addFrameImage("��������", "Resources/Images/Effect/GlassSheet.bmp",
		360, 380,
		5, 5,
		true,
		RGB(255, 0, 255));

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
		312,165,
		true,
		RGB(255, 0, 255));
	IMAGEMANAGER->addImage("��ǻ���ؽ�Ʈ", "Resources/Images/UI/txtCom.bmp",
		296, 82
	);
	IMAGEMANAGER->addFrameImage("����Ű", "Resources/Images/UI/UI_Keyboard_return.bmp",
		80, 40,
		2, 1,
		true,
		RGB(255, 0, 255));
	IMAGEMANAGER->addImage("�Ϻ���ȹ��", "Resources/Images/UI/getKnifeUI.bmp", 1280, 800,true,RGB(255,0,255)); 
	IMAGEMANAGER->addImage("����ȹ��", "Resources/Images/UI/getKunaiPanal.bmp", 1280, 800, true, RGB(255, 0, 255));
	
	IMAGEMANAGER->addImage("����", "Resources/Images/Stage1/Object/kunai1.bmp",
		58, 26,
		true,
		RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("��������Ʈ", "Resources/Images/Stage1/Object/Knife_particle.bmp",
		980, 50,
		7, 1,
		true,
		RGB(255, 0, 255));
	IMAGEMANAGER->addImage("�����ؽ�Ʈ", "Resources/Images/UI/kunaiTXT.bmp",
		312, 165,
		true,
		RGB(255, 0, 255));

	
		IMAGEMANAGER->addImage("��ȹ��", "Resources/Images/UI/getGunPanal.bmp", 1280, 800, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("��", "Resources/Images/Stage2/Gun.bmp",
		80, 60,
		true,
		RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("������Ʈ", "Resources/Images/Stage1/Object/Knife_particle.bmp",
		980, 50,
		7, 1,
		true,
		RGB(255, 0, 255));
	IMAGEMANAGER->addImage("���ؽ�Ʈ", "Resources/Images/UI/txtGun.bmp",
		312, 165,
		true,
		RGB(255, 0, 255));
		

	IMAGEMANAGER->addFrameImage("��", "Resources/Images/Player/Weapon/hand.bmp",
		40, 64,
		1, 2,
		true,
		RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Į", "Resources/Images/Player/Weapon/useknife.bmp",
		140, 80,
		1, 2,
		true,
		RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("��1", "Resources/Images/Player/Weapon/p90Shoot.bmp",
		560, 144,
		7, 2,
		true,
		RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("��2", "Resources/Images/Player/Weapon/p90Shoot.bmp",
		560, 144,
		7, 2,
		true,
		RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�ѱ�ȭ��", "Resources/Images/Player/Weapon/FXMuzzleFlash32_4.bmp",
		650, 160,
		5, 2, true,
		RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�Ѿ�", "Resources/Images/Player/Weapon/FXBullet.bmp",
		34, 36,
		1, 2, true,
		RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("����1", "Resources/Images/Player/Weapon/kunai.bmp",
		60, 160,
		1, 2,
		true,
		RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("����2", "Resources/Images/Player/Weapon/kunai.bmp",
		60, 160,
		1, 2,
		true,
		RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("���̺�1", "Resources/Images/Effect/FXKunaiHitWall.bmp", 350, 72,
		5,2,
		true,
		RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("���̺�2", "Resources/Images/Effect/FXKunaiHitWall.bmp", 350, 72,
		5, 2,
		true,
		RGB(255, 0, 255));
	
	IMAGEMANAGER->addImage("����ü", "Resources/Images/Stage1/Object/bgDumi.bmp", 600, 300, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("����", "Resources/Images/Stage1/Object/Box.bmp", 120, 80, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("���ڱ���������Ʈ", "Resources/Images/Effect/breakBox.bmp",
		1134, 126,
		9, 1,
		true,
		RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("���ڱ���������Ʈ������", "Resources/Images/Effect/breakBoxblack.bmp",
		756, 84,
		9, 1,
		true,
		RGB(255, 0, 255));

	IMAGEMANAGER->addFrameImage("����", "Resources/Images/Effect/slashEF.bmp",
		1424, 70,
		8, 1,
		true,
		RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�������", "Resources/Images/Effect/slashEF2.bmp",
		400, 100,
		4, 1,
		true,
		RGB(255, 0, 255));

	
	IMAGEMANAGER->addFrameImage("��������", "Resources/Images/Enemy/Zombie/Zombiebot_sleep.bmp", 200, 52, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("������", "Resources/Images/Enemy/Zombie/Zombiebot_wake.bmp", 200, 70, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�����̵�", "Resources/Images/Enemy/Zombie/Zombiebot_move.bmp", 396, 172, 4, 2, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("��ư", "Resources/Images/UI/button.bmp", 200, 100);
	IMAGEMANAGER->addImage("Ʃ�丮��", "Resources/Images/Stage1/tutorial.bmp", 1280, 800);
	IMAGEMANAGER->addImage("Ʃ�丮���ȼ�", "Resources/Images/Stage1/_tutorial.bmp", 1280, 800);
	
	

	IMAGEMANAGER->addFrameImage("��������", "Resources/Images/Enemy/Boss/BossSleep.bmp",
		240, 80,
		2, 1,
		true,
		RGB(255, 0, 255));

	IMAGEMANAGER->addImage("�����ؽ�Ʈ1", "Resources/Images/Enemy/Boss/txtBoss.bmp",
		312, 165,
		true,
		RGB(255, 0, 255));
	IMAGEMANAGER->addImage("�����ؽ�Ʈ2", "Resources/Images/Enemy/Boss/txt1.bmp",
		273, 131,
		true,
		RGB(255, 0, 255));
	IMAGEMANAGER->addImage("�����ؽ�Ʈ3", "Resources/Images/Enemy/Boss/txt2.bmp",
		315, 102,
		true,
		RGB(255, 0, 255));
	IMAGEMANAGER->addImage("�����ؽ�Ʈ4", "Resources/Images/Enemy/Boss/txt3.bmp",
		320, 222,
		true,
		RGB(255, 0, 255));
	IMAGEMANAGER->addImage("�����г�", "Resources/Images/Enemy/Boss/PanalBoss.bmp",
		815, 154,
		true,
		RGB(255, 0, 255));


	IMAGEMANAGER->addImage("����Idle", "Resources/Images/Enemy/Boss/GhostBoss_body.bmp",
		108, 82,
		true,
		RGB(255, 0, 255));
	IMAGEMANAGER->addImage("�����⺻��", "Resources/Images/Enemy/Boss/GhostBoss_head-front.bmp",
		76, 76,
		true,
		RGB(255, 0, 255));
	IMAGEMANAGER->addImage("�����ǰݾ�", "Resources/Images/Enemy/Boss/BossHit.bmp",
		72, 82,
		true,
		RGB(255, 0, 255));

	IMAGEMANAGER->addImage("�����⺻��", "Resources/Images/Enemy/Boss/BossHand.bmp",
		38, 40,
		true,
		RGB(255, 0, 255));

	IMAGEMANAGER->addImage("�����⺻����", "Resources/Images/Enemy/Boss/BossWeapon.bmp",
		100, 86,
		true,
		RGB(255, 0, 255));
	IMAGEMANAGER->addImage("����������Ʈ1", "Resources/Images/Enemy/Boss/bossCicle1.bmp",
		67, 69,
		true,
		RGB(255, 0, 255));
	IMAGEMANAGER->addImage("����������Ʈ2", "Resources/Images/Enemy/Boss/bossCicle2.bmp",
		66, 77,
		true,
		RGB(255, 0, 255));
	IMAGEMANAGER->addImage("����������Ʈ3", "Resources/Images/Enemy/Boss/bossCicle3.bmp",
		74, 88,
		true,
		RGB(255, 0, 255));


	IMAGEMANAGER->addFrameImage("�������ݾ�1", "Resources/Images/Enemy/Boss/BossAttack1Face.bmp",
		104, 132,
		1,2,
		true,
		RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("����Attack1", "Resources/Images/Enemy/Boss/BossAttack1.bmp",
		124, 148,
		1,2,
		true,
		RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�������ݹ���1", "Resources/Images/Enemy/Boss/BossAttackWeapon1.bmp",
		120,88,
		1,2,
		true,
		RGB(255, 0, 255));


	IMAGEMANAGER->addImage("�������ݾ�2", "Resources/Images/Enemy/Boss/BossAttack2Face.bmp",
		78, 86,
		true,
		RGB(255, 0, 255));
	IMAGEMANAGER->addImage("�������ݹ���2", "Resources/Images/Enemy/Boss/BossAttackWeapon2.bmp",
		70, 118,
		true,
		RGB(255, 0, 255));
	//BossAttackWeapon3
	IMAGEMANAGER->addFrameImage("�������ݾ�3", "Resources/Images/Enemy/Boss/BossAttack1Face.bmp",
		104, 132,
		1, 2,
		true,
		RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�������ݹ���3", "Resources/Images/Enemy/Boss/BossAttackWeapon3.bmp",
		100, 172,
		1,2,
		true,
		RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�������ݼ�", "Resources/Images/Enemy/Boss/BossHand3.bmp",
		38, 80,
		1,2,
		true,
		RGB(255, 0, 255));
	IMAGEMANAGER->addImage("������", "Resources/Images/Enemy/Boss/BossRock.bmp",
		220, 164,
		true,
		RGB(255, 0, 255));
	IMAGEMANAGER->addImage("�������ȼ�", "Resources/Images/Enemy/Boss/_BossRock.bmp",
		220, 164,
		true,
		RGB(255, 0, 255));
	IMAGEMANAGER->addImage("�����������Ʈ" ,"Resources/Images/Enemy/Boss/BossDieFX.bmp",
		1280, 800,
		true,
		RGB(255,0,255));


	IMAGEMANAGER->addFrameImage("��������⺻", "Resources/Images/Enemy/Lipo/LipoZombieIdle.bmp",
		384, 164,
		4, 2,
		true,
		RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("������������", "Resources/Images/Enemy/Lipo/LipoZombieBoom.bmp",
		160, 180,
		2, 2,
		true,
		RGB(255, 0, 255));


	return S_OK;
}

