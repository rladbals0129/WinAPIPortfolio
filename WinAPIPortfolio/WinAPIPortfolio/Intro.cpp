#include "Stdafx.h"
#include "Intro.h"

HRESULT Intro::init(void)
{
	m_videoPlayer = new VideoPlayer(); // VideoPlayer ��ü ����
	HRESULT hrInit = m_videoPlayer->init();
	if (FAILED(hrInit))
	{
		// �ʱ�ȭ�� ������ ��� ó��
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
	//	cout << "�����߳�?" << endl;
	//}
	//if (m_videoPlayer)
	//{
	//	m_videoPlayer->CheckVideoStatus();
	//	// ���⿡ ESC ��ư üũ �ڵ带 �߰��Ͽ� ���� ��ŵ �� �� ��ȯ ���� ����
	//}
}

void Intro::render(void)
{
	
}

void Intro::playVideo()
{
	m_videoPlayer->Play();
}


