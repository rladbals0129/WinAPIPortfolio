#pragma once
#include "SingletonBase.h"
#include <mmsystem.h>
#include <mciapi.h>

#pragma comment(lib, "Winmm.lib")

class TempSoundManager : public SingletonBase <TempSoundManager>
{
public:

	HRESULT init(void);

	//MP3
	void addMp3FileWithKey(string key, string fileName);
	//WAV
	void addWaveFileWithKey(string key, string fileName);
	//효과음
	void playEffectSoundWave(char* fileName);
	//MP3재생
	void playSoundWithKey(string key);
	//정지
	void stopMp3WithKey(string key);


	TempSoundManager();
	~TempSoundManager();
};

