#include "Stdafx.h"
#include "Intro.h"

HRESULT Intro::init(void)
{
	m_videoPlayer = new VideoPlayer(); // VideoPlayer 객체 생성
	HRESULT hrInit = m_videoPlayer->init();
	if (FAILED(hrInit))
	{
		// 초기화가 실패한 경우 처리
	}

	m_videoPlayer->LoadVideo("Resources/Video/Intro.avi");
	_videoEnd = false;
	return S_OK;
}

void Intro::release(void)
{
	if (m_videoPlayer)
	{
		m_videoPlayer->Stop();
		m_videoPlayer->release();
		delete m_videoPlayer;
		m_videoPlayer = nullptr;
	}
}

void Intro::update(void)
{
	//if (KEYMANAGER->isOnceKeyDown(VK_ESCAPE))
	//{
	//	_videoEnd = true;
	//	cout << "오긴했냐?" << endl;
	//}
	//if (m_videoPlayer)
	//{
	//	m_videoPlayer->CheckVideoStatus();
	//	// 여기에 ESC 버튼 체크 코드를 추가하여 비디오 스킵 및 씬 전환 구현 가능
	//}
}

void Intro::render(void)
{
	
}

void Intro::playVideo()
{
	m_videoPlayer->Play();
}


