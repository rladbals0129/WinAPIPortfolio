#pragma once
#include "SingletonBase.h"
#include <fmod.h>
#include <fmod_common.h>
#include <fmod.hpp>
#include <fmod_errors.h>
#pragma comment(lib, "fmod_vc.lib")
class SoundManager : public SingletonBase <SoundManager>
{
private:
    FMOD_SYSTEM* _system;
    map<string, FMOD_SOUND*> _sounds;
    map<string, FMOD_CHANNEL*> _channels;

    void _checkError(FMOD_RESULT result);
public:
	HRESULT init(void);
    void release(void);
	void update(void);
	
    void addSound(string soundKey, string filePath, bool loop);
    void play(string soundKey);
    void stop(string soundKey);
    void pause(string soundKey);
    void resume(string soundKey);
    void setVolume(string soundKey, float volume);
   
};


