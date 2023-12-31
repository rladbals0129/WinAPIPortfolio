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

	IMAGEMANAGER->addFrameImage("달리기먼지", "Resources/Images/Effect/dust.bmp",
		96,32,
		3,1,
		true,
		RGB(255,0,255));
	IMAGEMANAGER->addFrameImage("머리", "Resources/Images/Player/TabletFaces.bmp",
		46, 104,
		1, 2,
		true,
		RGB(255, 0, 255)
		);
	IMAGEMANAGER->addFrameImage("개피", "Resources/Images/Player/TabletFaces_battery.bmp",
		32, 72,
		1, 2
		);
	IMAGEMANAGER->addImage("개피화면", "Resources/Images/UI/UI-CriticalEnergyIndicator.bmp",
		1280, 800,
		true,
		RGB(255,0,255)
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

	IMAGEMANAGER->addImage("스테이지2", "Resources/Images/Stage2/Stage2.bmp", 5120, 2400); 
	IMAGEMANAGER->addImage("스테이지2픽셀", "Resources/Images/Stage2/_Stage2.bmp", 5120, 2400);

	IMAGEMANAGER->addImage("스테이지3", "Resources/Images/Stage3/Stage3.bmp", 6400, 800);
	IMAGEMANAGER->addImage("스테이지3픽셀", "Resources/Images/Stage3/_Stage3.bmp", 6400, 800);
	
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
	IMAGEMANAGER->addImage("쿠나이획득", "Resources/Images/UI/getKunaiPanal.bmp", 1280, 800, true, RGB(255, 0, 255));
	
	IMAGEMANAGER->addImage("쿠나이", "Resources/Images/Stage1/Object/kunai1.bmp",
		58, 26,
		true,
		RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("쿠나이이펙트", "Resources/Images/Stage1/Object/Knife_particle.bmp",
		980, 50,
		7, 1,
		true,
		RGB(255, 0, 255));
	IMAGEMANAGER->addImage("쿠나이텍스트", "Resources/Images/UI/kunaiTXT.bmp",
		312, 165,
		true,
		RGB(255, 0, 255));

	
		IMAGEMANAGER->addImage("총획득", "Resources/Images/UI/getGunPanal.bmp", 1280, 800, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("총", "Resources/Images/Stage2/Gun.bmp",
		80, 60,
		true,
		RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("총이펙트", "Resources/Images/Stage1/Object/Knife_particle.bmp",
		980, 50,
		7, 1,
		true,
		RGB(255, 0, 255));
	IMAGEMANAGER->addImage("총텍스트", "Resources/Images/UI/txtGun.bmp",
		312, 165,
		true,
		RGB(255, 0, 255));
		

	IMAGEMANAGER->addFrameImage("손", "Resources/Images/Player/Weapon/hand.bmp",
		40, 64,
		1, 2,
		true,
		RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("칼", "Resources/Images/Player/Weapon/useknife.bmp",
		140, 80,
		1, 2,
		true,
		RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("총1", "Resources/Images/Player/Weapon/p90Shoot.bmp",
		560, 144,
		7, 2,
		true,
		RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("총2", "Resources/Images/Player/Weapon/p90Shoot.bmp",
		560, 144,
		7, 2,
		true,
		RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("총기화염", "Resources/Images/Player/Weapon/FXMuzzleFlash32_4.bmp",
		650, 160,
		5, 2, true,
		RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("총알", "Resources/Images/Player/Weapon/FXBullet.bmp",
		34, 36,
		1, 2, true,
		RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("쿠나이1", "Resources/Images/Player/Weapon/kunai.bmp",
		60, 160,
		1, 2,
		true,
		RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("쿠나이2", "Resources/Images/Player/Weapon/kunai.bmp",
		60, 160,
		1, 2,
		true,
		RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("쿠나이벽1", "Resources/Images/Effect/FXKunaiHitWall.bmp", 350, 72,
		5,2,
		true,
		RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("쿠나이벽2", "Resources/Images/Effect/FXKunaiHitWall.bmp", 350, 72,
		5, 2,
		true,
		RGB(255, 0, 255));
	
	IMAGEMANAGER->addImage("배경시체", "Resources/Images/Stage1/Object/bgDumi.bmp", 600, 300, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("상자", "Resources/Images/Stage1/Object/Box.bmp", 120, 80, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("상자깨지기이펙트", "Resources/Images/Effect/breakBox.bmp",
		1134, 126,
		9, 1,
		true,
		RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("상자깨지기이펙트검은색", "Resources/Images/Effect/breakBoxblack.bmp",
		756, 84,
		9, 1,
		true,
		RGB(255, 0, 255));

	IMAGEMANAGER->addFrameImage("베기", "Resources/Images/Effect/slashEF.bmp",
		1424, 70,
		8, 1,
		true,
		RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("베기먼지", "Resources/Images/Effect/slashEF2.bmp",
		400, 100,
		4, 1,
		true,
		RGB(255, 0, 255));

	
	IMAGEMANAGER->addFrameImage("좀비정지", "Resources/Images/Enemy/Zombie/Zombiebot_sleep.bmp", 200, 52, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("좀비기상", "Resources/Images/Enemy/Zombie/Zombiebot_wake.bmp", 200, 70, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("좀비이동", "Resources/Images/Enemy/Zombie/Zombiebot_move.bmp", 396, 172, 4, 2, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("버튼", "Resources/Images/UI/button.bmp", 200, 100);
	IMAGEMANAGER->addImage("튜토리얼", "Resources/Images/Stage1/tutorial.bmp", 1280, 800);
	IMAGEMANAGER->addImage("튜토리얼픽셀", "Resources/Images/Stage1/_tutorial.bmp", 1280, 800);
	
	

	IMAGEMANAGER->addFrameImage("보스정지", "Resources/Images/Enemy/Boss/BossSleep.bmp",
		240, 80,
		2, 1,
		true,
		RGB(255, 0, 255));

	IMAGEMANAGER->addImage("보스텍스트1", "Resources/Images/Enemy/Boss/txtBoss.bmp",
		312, 165,
		true,
		RGB(255, 0, 255));
	IMAGEMANAGER->addImage("보스텍스트2", "Resources/Images/Enemy/Boss/txt1.bmp",
		273, 131,
		true,
		RGB(255, 0, 255));
	IMAGEMANAGER->addImage("보스텍스트3", "Resources/Images/Enemy/Boss/txt2.bmp",
		315, 102,
		true,
		RGB(255, 0, 255));
	IMAGEMANAGER->addImage("보스텍스트4", "Resources/Images/Enemy/Boss/txt3.bmp",
		320, 222,
		true,
		RGB(255, 0, 255));
	IMAGEMANAGER->addImage("보스패널", "Resources/Images/Enemy/Boss/PanalBoss.bmp",
		815, 154,
		true,
		RGB(255, 0, 255));


	IMAGEMANAGER->addImage("보스Idle", "Resources/Images/Enemy/Boss/GhostBoss_body.bmp",
		108, 82,
		true,
		RGB(255, 0, 255));
	IMAGEMANAGER->addImage("보스기본얼굴", "Resources/Images/Enemy/Boss/GhostBoss_head-front.bmp",
		76, 76,
		true,
		RGB(255, 0, 255));
	IMAGEMANAGER->addImage("보스피격얼굴", "Resources/Images/Enemy/Boss/BossHit.bmp",
		72, 82,
		true,
		RGB(255, 0, 255));

	IMAGEMANAGER->addImage("보스기본손", "Resources/Images/Enemy/Boss/BossHand.bmp",
		38, 40,
		true,
		RGB(255, 0, 255));

	IMAGEMANAGER->addImage("보스기본무기", "Resources/Images/Enemy/Boss/BossWeapon.bmp",
		100, 86,
		true,
		RGB(255, 0, 255));
	IMAGEMANAGER->addImage("보스오브젝트1", "Resources/Images/Enemy/Boss/bossCicle1.bmp",
		67, 69,
		true,
		RGB(255, 0, 255));
	IMAGEMANAGER->addImage("보스오브젝트2", "Resources/Images/Enemy/Boss/bossCicle2.bmp",
		66, 77,
		true,
		RGB(255, 0, 255));
	IMAGEMANAGER->addImage("보스오브젝트3", "Resources/Images/Enemy/Boss/bossCicle3.bmp",
		74, 88,
		true,
		RGB(255, 0, 255));


	IMAGEMANAGER->addFrameImage("보스공격얼굴1", "Resources/Images/Enemy/Boss/BossAttack1Face.bmp",
		104, 132,
		1,2,
		true,
		RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("보스Attack1", "Resources/Images/Enemy/Boss/BossAttack1.bmp",
		124, 148,
		1,2,
		true,
		RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("보스공격무기1", "Resources/Images/Enemy/Boss/BossAttackWeapon1.bmp",
		120,88,
		1,2,
		true,
		RGB(255, 0, 255));


	IMAGEMANAGER->addImage("보스공격얼굴2", "Resources/Images/Enemy/Boss/BossAttack2Face.bmp",
		78, 86,
		true,
		RGB(255, 0, 255));
	IMAGEMANAGER->addImage("보스공격무기2", "Resources/Images/Enemy/Boss/BossAttackWeapon2.bmp",
		70, 118,
		true,
		RGB(255, 0, 255));
	//BossAttackWeapon3
	IMAGEMANAGER->addFrameImage("보스공격얼굴3", "Resources/Images/Enemy/Boss/BossAttack1Face.bmp",
		104, 132,
		1, 2,
		true,
		RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("보스공격무기3", "Resources/Images/Enemy/Boss/BossAttackWeapon3.bmp",
		100, 172,
		1,2,
		true,
		RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("보스공격손", "Resources/Images/Enemy/Boss/BossHand3.bmp",
		38, 80,
		1,2,
		true,
		RGB(255, 0, 255));
	IMAGEMANAGER->addImage("보스돌", "Resources/Images/Enemy/Boss/BossRock.bmp",
		220, 164,
		true,
		RGB(255, 0, 255));
	IMAGEMANAGER->addImage("보스돌픽셀", "Resources/Images/Enemy/Boss/_BossRock.bmp",
		220, 164,
		true,
		RGB(255, 0, 255));
	IMAGEMANAGER->addImage("보스사망이펙트" ,"Resources/Images/Enemy/Boss/BossDieFX.bmp",
		1280, 800,
		true,
		RGB(255,0,255));


	IMAGEMANAGER->addFrameImage("자폭좀비기본", "Resources/Images/Enemy/Lipo/LipoZombieIdle.bmp",
		384, 164,
		4, 2,
		true,
		RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("자폭좀비폭파", "Resources/Images/Enemy/Lipo/LipoZombieBoom.bmp",
		160, 180,
		2, 2,
		true,
		RGB(255, 0, 255));


	return S_OK;
}

