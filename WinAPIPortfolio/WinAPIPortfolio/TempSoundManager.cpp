#include "Stdafx.h"
#include "TempSoundManager.h"


HRESULT TempSoundManager::init(void)
{
	// !do nothing

	return S_OK;
}

void TempSoundManager::addMp3FileWithKey(string key, string fileName)
{
	string first = "open \"";
	string end = "\" type mpegvideo alias ";
	string finalQuery = first + fileName + end + key;

	const char* str = finalQuery.c_str();

	//mciSendString() : 장치에 특정 명령어를 전송하여 구동시키는 함수
	// ㄴ 인자 : 문자열 명령어, 반환값을 알려줄 명령어 , 반환될 길이, 핸들콜백 
	mciSendString(str, NULL, 0, NULL);

}

void TempSoundManager::addWaveFileWithKey(string key, string fileName)
{
	string first = "open \"";
	string end = "\" type waveaudio alias ";
	string finalQuery = first + fileName + end + key;

	const char* str = finalQuery.c_str();

	//mciSendString() : 장치에 특정 명령어를 전송하여 구동시키는 함수
	// ㄴ 인자 : 문자열 명령어, 반환값을 알려줄 명령어 , 반환될 길이, 핸들콜백 
	mciSendString(str, NULL, 0, NULL);								//ㄴ쓰레드 쓰지마라

}

void TempSoundManager::playEffectSoundWave(char* fileName)
{
	//PlaySound() : TEXT(*파일이름.wav"), 파일명을 사용하면 NULL, 그렇지않다면 해당인스턴스핸들
	// fdwSound(옵션|옵션|옵션)
	/*
	원래 노래를 틀면 노래가끝날떄까지 컴파일러가 이 함수를 벗어날수없다
	 SND_ASYNC 를 사용해서

	 ===플래그옵션===
	- SND_ASYNC: 재생하면서 다음코드를 실행
	  ㄴ 비동기플래그

	- SND_LOOP : 반복재생

	- SND_NODEFAULT : 지정한 경로에 파일이 없어도 경고음을 재생하지 않는다.


	*/
	PlaySound(fileName, NULL, SND_ASYNC);
}

void TempSoundManager::playSoundWithKey(string key)
{
	string first = "play ";
	string finalQuery = first + key;

	const char* str = finalQuery.c_str();
	mciSendString(str, NULL, 0, NULL);


}

void TempSoundManager::stopMp3WithKey(string key)
{
	string first = "stop ";
	string finalQuery = "";
	finalQuery = first + key;

	const char* str = finalQuery.c_str();
	mciSendString(str, NULL, 0, NULL);
}

TempSoundManager::TempSoundManager()
{
}


TempSoundManager::~TempSoundManager()
{
}
