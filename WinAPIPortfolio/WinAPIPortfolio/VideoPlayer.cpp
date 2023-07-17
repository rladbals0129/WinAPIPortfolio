#include "Stdafx.h"
#include "VideoPlayer.h"

VideoPlayer::VideoPlayer() : m_pGraphBuilder(nullptr),
m_pMediaControl(nullptr),
m_pMediaEvent(nullptr),
m_pMediaSeeking(nullptr),
m_videoLoaded(false)
{
}

VideoPlayer::~VideoPlayer()
{
	release();
}

HRESULT VideoPlayer::init()
{
	HRESULT hrInit = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED);
	if (FAILED(hrInit)) { return hrInit; }

	HRESULT hrCreate = CoCreateInstance(CLSID_FilterGraph, NULL, CLSCTX_INPROC_SERVER, IID_IGraphBuilder, (void **)&m_pGraphBuilder);

	_videoEnd = false;
	_videoSkip = false;

	return hrCreate;
}

void VideoPlayer::release()
{

	if (m_pGraphBuilder)
		m_pGraphBuilder->Release();
	if (m_pMediaControl)
		m_pMediaControl->Release();
	if (m_pMediaEvent)
		m_pMediaEvent->Release();
	if (m_pMediaSeeking)
		m_pMediaSeeking->Release();
	CoUninitialize();
}

bool VideoPlayer::LoadVideo(const std::string& videoFilePath)
{
	if (!m_pGraphBuilder) return false;

	m_pGraphBuilder->QueryInterface(IID_IMediaControl, (void**)&m_pMediaControl);
	m_pGraphBuilder->QueryInterface(IID_IMediaEventEx, (void**)&m_pMediaEvent);
	m_pGraphBuilder->QueryInterface(IID_IMediaSeeking, (void**)&m_pMediaSeeking);

	HRESULT hr = m_pGraphBuilder->RenderFile(_bstr_t(videoFilePath.c_str()), NULL);
	if (FAILED(hr))
	{
		// 오류 처리
		return false;
	}

	m_videoLoaded = true;
	return true;
}

void VideoPlayer::Play()
{
	if (!m_videoLoaded) return;
	m_pMediaControl->Run();

}

void VideoPlayer::Pause()
{
	if (!m_videoLoaded) return;
	m_pMediaControl->Pause();
}

void VideoPlayer::Stop()
{
	if (!m_videoLoaded) return;
	m_pMediaControl->Stop();
	
}

