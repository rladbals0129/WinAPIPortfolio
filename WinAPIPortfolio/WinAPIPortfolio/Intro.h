#pragma once
#include "GameNode.h"
#include "VideoPlayer.h"
class Intro : public GameNode
{
private:
	VideoPlayer* m_videoPlayer;

	bool _videoEnd;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void playVideo();
	bool getEnd() { return _videoEnd; }
	void setEnd(bool videoEnd) { _videoEnd = videoEnd; }

};

