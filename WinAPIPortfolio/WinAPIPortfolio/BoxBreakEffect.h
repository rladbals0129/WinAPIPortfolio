#pragma once
#include "GameNode.h"
class BoxBreakEffect
{
private:
	struct BreakBox {
		float x;
		float y;
		float vx;
		float vy;
		string key;
		int frameX;
		int frameY;
		int frameCountStart;
		int frameCount;
		bool alive;
		bool goAnim;
	};
	std::vector<BreakBox> _breakEFList;

public:
	void update();
	void render(HDC hdc);
	void addEffect(float x, float y, int count, string key);
	void addSlashEffect(float x, float y, int count, string key);


	void setLeft(float x)
	{
		for (auto& Ef : _breakEFList)
		{
			Ef.x -= x;
		}
	}
	void setTop(float y)
	{
		for (auto& Ef : _breakEFList)
		{
			Ef.y -= y;
		}
	}
	void setRight(float x)
	{
		for (auto& Ef : _breakEFList)
		{
			Ef.x += x;
		}
	}
	void setBottom(float y)
	{
		for (auto& Ef : _breakEFList)
		{
			Ef.y += y;
		}
	}
	
};

