#include "Stdafx.h"
#include "BoxBreakEffect.h"

void BoxBreakEffect::update()
{
	for (auto& breaker : _breakEFList)
	{
		if (breaker.key == "상자깨지기이펙트검은색")
		{
			if (breaker.alive)
			{
				breaker.frameCountStart++;
				breaker.x += breaker.vx;
				breaker.y += breaker.vy;
				if (breaker.frameCountStart > 50)
				{
					breaker.goAnim = true;
				}
				if (breaker.goAnim)
				{
					breaker.frameCount++;

					if (breaker.frameCount % 2 == 0)
					{
						breaker.frameX++;
					}

				}


				if (breaker.frameX > 9)
				{
					breaker.alive = false;
					breaker.frameCountStart = 0;
					breaker.frameCount = 0;
					breaker.goAnim = false;
				}

			}
		}

		if (breaker.key == "상자깨지기이펙트")
		{
			if (breaker.alive)
			{
				breaker.y += breaker.vy;
				breaker.frameCount++;
				if (breaker.frameCount % 3 == 0)
				{
					breaker.frameX++;
				}


				if (breaker.frameX > 9)
				{
					breaker.alive = false;
					breaker.frameCountStart = 0;
					breaker.frameCount = 0;
					breaker.goAnim = false;
				}

			}

		}

		if (breaker.key == "베기")
		{
			if (breaker.alive)
			{
				//breaker.y += breaker.vy;
				breaker.frameCount++;
				if (breaker.frameCount % 2 == 0)
				{
					breaker.frameX++;
				}


				if (breaker.frameX > 9)
				{
					breaker.alive = false;
				
					breaker.frameCount = 0;
		
				}

			}
		}
	

		if (breaker.key == "베기먼지")
		{
			if (breaker.alive)
			{
				breaker.y += breaker.vy;
				breaker.frameCount++;
				if (breaker.frameCount % 5 == 0)
				{
					breaker.frameX++;
				}


				if (breaker.frameX > 4)
				{
					breaker.alive = false;

					breaker.frameCount = 0;

				}

			}
		}
	}
}

void BoxBreakEffect::render(HDC hdc)
{
	for (const auto& breaker : _breakEFList) {
		if (breaker.alive) {
			IMAGEMANAGER->findImage(breaker.key)->frameRender(hdc, breaker.x, breaker.y, breaker.frameX, breaker.frameY);
		}
	}
}

void BoxBreakEffect::addEffect(float x, float y, int count, string key)
{
	for (int i = 0; i < count; i++) {
		BreakBox newBreakBox;
		newBreakBox.x = x + (i * 10);
		newBreakBox.y = y;
		newBreakBox.vx = RND->getFromFloatTo(-2.f,2.f);
		newBreakBox.vy = -1.5f;
		newBreakBox.key = key;
		newBreakBox.frameX = 0;
		newBreakBox.frameY = 0;
		newBreakBox.frameCountStart = 0;
		newBreakBox.frameCount = 0;
		newBreakBox.alive = true;
		newBreakBox.goAnim = false;

		_breakEFList.push_back(newBreakBox);
	}
}

void BoxBreakEffect::addSlashEffect(float x, float y, int count, string key)
{
	for (int i = 0; i < count; i++) {
		BreakBox newBreakBox;
		newBreakBox.x = x;
		newBreakBox.y = y;
		newBreakBox.vx = 0;
		newBreakBox.vy = 0;
		newBreakBox.key = key;
		newBreakBox.frameX = 0;
		newBreakBox.frameY = 0;
		newBreakBox.frameCountStart = 0;
		newBreakBox.frameCount = 0;
		newBreakBox.alive = true;
		newBreakBox.goAnim = false;

		_breakEFList.push_back(newBreakBox);
	}
}

