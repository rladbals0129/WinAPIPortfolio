#include "Stdafx.h"
#include "SoundManager.h"

void SoundManager::_checkError(FMOD_RESULT result)
{
    if (result != FMOD_OK)
    {
        MessageBox(NULL, FMOD_ErrorString(result), "FMOD Error", MB_OK);
    }
}

HRESULT SoundManager::init(void)
{
    FMOD_RESULT result;

    result = FMOD_System_Create(&_system, FMOD_VERSION);
    _checkError(result);

    result = FMOD_System_Init(_system, 200, FMOD_INIT_NORMAL, nullptr);
    _checkError(result);

    return S_OK;
}

void SoundManager::release(void)
{
    for (auto& sound : _sounds)
    {
        FMOD_Sound_Release(sound.second);
    }

    FMOD_System_Release(_system);
}

void SoundManager::update(void)
{
    FMOD_System_Update(_system);

 
}

void SoundManager::addSound(string soundKey, string filePath, bool loop)
{
    FMOD_SOUND* sound;
    FMOD_MODE mode = loop ? FMOD_LOOP_NORMAL : FMOD_LOOP_OFF;

    string copiedFilePath = filePath;
    FMOD_RESULT result = FMOD_System_CreateSound(_system, copiedFilePath.c_str(), mode, nullptr, &sound);
    _checkError(result);

    _sounds[soundKey] = sound;
}

void SoundManager::play(string soundKey)
{
    FMOD_CHANNEL* channel;
    FMOD_System_PlaySound(_system, _sounds[soundKey], nullptr, false, &channel);
    _channels[soundKey] = channel;
   
}

void SoundManager::stop(string soundKey)
{
    FMOD_Channel_Stop(_channels[soundKey]);
}

void SoundManager::pause(string soundKey)
{
    FMOD_Channel_SetPaused(_channels[soundKey], true);
}

void SoundManager::resume(string soundKey)
{
    FMOD_Channel_SetPaused(_channels[soundKey], false);
}

void SoundManager::setVolume(string soundKey, float volume)
{
    FMOD_Channel_SetVolume(_channels[soundKey], volume);
}



