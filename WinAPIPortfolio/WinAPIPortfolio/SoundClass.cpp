#include "Stdafx.h"
#include "SoundClass.h"

HRESULT SoundClass::init()
{
	SOUNDMANAGER->addSound("사망", "Resources/Sound/SoundEffects/zombie_death.wav", false);
	SOUNDMANAGER->addSound("어그로", "Resources/Sound/SoundEffects/zombie_aggro.wav", false);
	SOUNDMANAGER->addSound("칼공격", "Resources/Sound/SoundEffects/kunai-swordslash.wav", false);
	SOUNDMANAGER->addSound("총공격", "Resources/Sound/SoundEffects/blob_machine_gun.wav", true);
	SOUNDMANAGER->addSound("달리기", "Resources/Sound/SoundEffects/kunai-footstep.wav", false);
	SOUNDMANAGER->addSound("점프", "Resources/Sound/SoundEffects/jump2.wav", false);
	SOUNDMANAGER->addSound("피격", "Resources/Sound/SoundEffects/hurt3.wav", false);
	SOUNDMANAGER->addSound("문열림", "Resources/Sound/SoundEffects/door_open.wav", false);
	SOUNDMANAGER->addSound("문닫힘", "Resources/Sound/SoundEffects/door_close.wav", false);
	SOUNDMANAGER->addSound("유리타격","Resources/Sound/SoundEffects/galsspup.wav", false);
	SOUNDMANAGER->addSound("유리파괴","Resources/Sound/SoundEffects/breakGlass.wav", false);
	SOUNDMANAGER->addSound("상자파괴", "Resources/Sound/SoundEffects/kunai-cratebreak.wav", false);
	SOUNDMANAGER->addSound("쿠나이벽충돌", "Resources/Sound/SoundEffects/kunai-kunaihitwall.wav", false);
	SOUNDMANAGER->addSound("자폭인식", "Resources/Sound/SoundEffects/lipo_damage.wav", false);
	SOUNDMANAGER->addSound("자폭준비", "Resources/Sound/SoundEffects/lipo_special_long.wav", false);
	SOUNDMANAGER->addSound("자폭", "Resources/Sound/SoundEffects/lipo_destroy.wav", false);

	SOUNDMANAGER->addSound("칼피격", "Resources/Sound/SoundEffects/kunai-swordhit.wav", false);

	SOUNDMANAGER->addSound("공통사망", "Resources/Sound/SoundEffects/kunai-explosion.wav", false);

	SOUNDMANAGER->addSound("보스패턴1", "Resources/Sound/SoundEffects/GhostBoss-Dive.wav", false);
	SOUNDMANAGER->addSound("보스패턴2", "Resources/Sound/SoundEffects/GhostBoss-readyzombies.wav", false);
	SOUNDMANAGER->addSound("보스패턴3", "Resources/Sound/SoundEffects/GhostBoss-junkplatform.wav", false);

	SOUNDMANAGER->addSound("보스쉴드", "Resources/Sound/SoundEffects/ghostboss_shield.wav", false);
	SOUNDMANAGER->addSound("보스피격", "Resources/Sound/SoundEffects/ghostboss_death_3.wav", false);
	SOUNDMANAGER->addSound("보스등장", "Resources/Sound/SoundEffects/ghostboss_wakeup.wav", false);


	
	
	
	
	SOUNDMANAGER->addSound("스테이지1배경음", "Resources/Sound/background/lab.wav", true);
	SOUNDMANAGER->addSound("스테이지23배경음", "Resources/Sound/background/fallencity.wav", true);
	SOUNDMANAGER->addSound("보스배경음", "Resources/Sound/background/boss.wav", true);
	SOUNDMANAGER->addSound("타이틀배경음", "Resources/Sound/background/theme.wav", true);

	return S_OK;
}
