#include "Stdafx.h"
#include "SoundClass.h"

HRESULT SoundClass::init()
{
	SOUNDMANAGER->addSound("���", "Resources/Sound/SoundEffects/zombie_death.wav", false);
	SOUNDMANAGER->addSound("��׷�", "Resources/Sound/SoundEffects/zombie_aggro.wav", false);
	SOUNDMANAGER->addSound("Į����", "Resources/Sound/SoundEffects/kunai-swordslash.wav", false);
	SOUNDMANAGER->addSound("�Ѱ���", "Resources/Sound/SoundEffects/blob_machine_gun.wav", true);
	SOUNDMANAGER->addSound("�޸���", "Resources/Sound/SoundEffects/kunai-footstep.wav", false);
	SOUNDMANAGER->addSound("����", "Resources/Sound/SoundEffects/jump2.wav", false);
	SOUNDMANAGER->addSound("�ǰ�", "Resources/Sound/SoundEffects/hurt3.wav", false);
	SOUNDMANAGER->addSound("������", "Resources/Sound/SoundEffects/door_open.wav", false);
	SOUNDMANAGER->addSound("������", "Resources/Sound/SoundEffects/door_close.wav", false);
	SOUNDMANAGER->addSound("����Ÿ��","Resources/Sound/SoundEffects/galsspup.wav", false);
	SOUNDMANAGER->addSound("�����ı�","Resources/Sound/SoundEffects/breakGlass.wav", false);
	SOUNDMANAGER->addSound("�����ı�", "Resources/Sound/SoundEffects/kunai-cratebreak.wav", false);
	SOUNDMANAGER->addSound("���̺��浹", "Resources/Sound/SoundEffects/kunai-kunaihitwall.wav", false);
	SOUNDMANAGER->addSound("�����ν�", "Resources/Sound/SoundEffects/lipo_damage.wav", false);
	SOUNDMANAGER->addSound("�����غ�", "Resources/Sound/SoundEffects/lipo_special_long.wav", false);
	SOUNDMANAGER->addSound("����", "Resources/Sound/SoundEffects/lipo_destroy.wav", false);

	SOUNDMANAGER->addSound("Į�ǰ�", "Resources/Sound/SoundEffects/kunai-swordhit.wav", false);

	SOUNDMANAGER->addSound("������", "Resources/Sound/SoundEffects/kunai-explosion.wav", false);

	SOUNDMANAGER->addSound("��������1", "Resources/Sound/SoundEffects/GhostBoss-Dive.wav", false);
	SOUNDMANAGER->addSound("��������2", "Resources/Sound/SoundEffects/GhostBoss-readyzombies.wav", false);
	SOUNDMANAGER->addSound("��������3", "Resources/Sound/SoundEffects/GhostBoss-junkplatform.wav", false);

	SOUNDMANAGER->addSound("��������", "Resources/Sound/SoundEffects/ghostboss_shield.wav", false);
	SOUNDMANAGER->addSound("�����ǰ�", "Resources/Sound/SoundEffects/ghostboss_death_3.wav", false);
	SOUNDMANAGER->addSound("��������", "Resources/Sound/SoundEffects/ghostboss_wakeup.wav", false);


	
	
	
	
	SOUNDMANAGER->addSound("��������1�����", "Resources/Sound/background/lab.wav", true);
	SOUNDMANAGER->addSound("��������23�����", "Resources/Sound/background/fallencity.wav", true);
	SOUNDMANAGER->addSound("���������", "Resources/Sound/background/boss.wav", true);
	SOUNDMANAGER->addSound("Ÿ��Ʋ�����", "Resources/Sound/background/theme.wav", true);

	return S_OK;
}
