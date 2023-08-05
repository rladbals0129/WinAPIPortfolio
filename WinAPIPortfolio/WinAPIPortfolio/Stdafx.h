#pragma once
#pragma warning(disable : 4005)
#include <SDKDDKVER.h>
#include "targetver.h"

#define WIN32_LEAN_AND_MEAN
#pragma comment(linker,"/entry:WinMainCRTStartup /subsystem:console") 



#pragma comment (lib,"msimg32.lib")

#include <Windows.h>

//! C��Ÿ�� �������
#include <stdlib.h> 
#include <malloc.h>
#include <memory.h> 
#include <tchar.h> 
#include <time.h>

#include <stdio.h>

#include <iostream>
#include <string>
#include <chrono>
#include <random>
#include <vector>
#include <map>
#include <unordered_map> 

#include <cassert> 
#include <bitset>

using namespace std;

#include "CommonMacroFunction.h"
#include "RandomFunction.h"
#include "KeyManager.h"
#include "ImageManager.h"
#include "FontManager.h"
#include "TempSoundManager.h"
#include "UIManager.h"
#include "Player.h"
#include "SoundManager.h"
//#include "VideoPlayer.h"

#include <Vfw.h>
#pragma comment(lib, "vfw32.lib")
#define PI 3.141592f
#define RADIAN(dig)  (PI * dig) / 180.f
#define GRAVITY  0.5f;
#define RND RandomFunction::getSingleton()
#define KEYMANAGER KeyManager::getSingleton()
#define IMAGEMANAGER ImageManager::getSingleton()
#define FONTMANAGER FontManager::getSingleton()
#define TEMPSOUNDMANAGER TempSoundManager::getSingleton()
#define UI UIManager::getSingleton()
#define PLAYER Player::getSingleton()
#define SOUNDMANAGER SoundManager::getSingleton()




#define WINNAME		(LPTSTR)(TEXT("WindowsAPI"))

//��üȭ��
//#define FULLSCREEN

#ifdef FULLSCREEN

#define WINSTART_X	0
#define WINSTART_Y	0
#define WINSIZE_X	GetSystemMetrics(SM_CXSCREEN) //GetSystemMetrics()���ڷ� ���޵Ǵ� �ý��� ���� ������ ��ȯ
#define WINSIZE_Y	GetSystemMetrics(SM_CYSCREEN) //SM_CXSCREEN ,SM_CYSCREEN ���� ȭ�� �ػ� ��ȯ(x,y��) 
#define WINSTYLE	WS_POPUPWINDOW | WS_MAXIMIZE


#else
#define WINSTART_X	240
#define WINSTART_Y	0
#define WINSIZE_X	1280
#define WINSIZE_Y	800
#define WINSTYLE	WS_CAPTION | WS_SYSMENU

#endif

#define SAFE_DELETE(p) {if(p) { delete (p); (p) = nullptr; }}
#define SAFE_DELETE_ARRAY(p) {if(p) { delete[] (p); (p) = nullptr; }}
#define SAFE_RELEASE(p)	{if(p) {(p)->release(); (p) = nullptr; }}




extern HINSTANCE _hInstance;
extern HWND      _hWnd;

extern POINT	 _ptMouse;




