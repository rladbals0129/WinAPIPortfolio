#pragma once
#pragma comment(lib, "strmiids")
#pragma comment(lib, "comsuppw.lib")
#include <dshow.h>
#include <comutil.h>
#include "GameNode.h"


class VideoPlayer : public GameNode
{
public:
	VideoPlayer();
	~VideoPlayer();

	HRESULT init(void);
	void release();

	bool LoadVideo(const std::string& videoFilePath);
	void Play();
	void Pause();
	void Stop();


	bool getIsVideoEnd() { return _videoEnd; }
	bool getIsVideoSkip() { return _videoSkip; }

	void setIsVideoSkip(bool videoSkip) { _videoSkip = videoSkip; }

private:
	
	IGraphBuilder* m_pGraphBuilder;
	IMediaControl* m_pMediaControl;
	IMediaEventEx* m_pMediaEvent;
	IMediaSeeking* m_pMediaSeeking;
	bool m_videoLoaded;

	bool _videoEnd;
	bool _videoSkip;
};


