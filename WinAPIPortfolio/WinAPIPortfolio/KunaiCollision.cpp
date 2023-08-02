#include "Stdafx.h"
#include "KunaiCollision.h"
HRESULT KunaiCollision::init()
{
	_lerpSpeed = 0.1f;
	return S_OK;
}

void KunaiCollision::kunaiCollision(HDC hdc, int offsetX, int offsetY)
{
	int LKT[60];
	for (int i = 0; i < 60; i++)
	{
		LKT[i] = GetGValue(GetPixel(hdc,
			PLAYER->getKunai()->getLeftKuniaPos().left + offsetX + i,
			PLAYER->getKunai()->getLeftKuniaPos().top + offsetY));
		//cout << LKT[i] << endl;
	}
	int RKT[60];
	for (int i = 0; i < 60; i++)
	{
		RKT[i] = GetGValue(GetPixel(hdc,
			PLAYER->getKunai()->getRightKuniaPos().left + offsetX + i,
			PLAYER->getKunai()->getRightKuniaPos().top + offsetY));
	
	}

	for (int i = 0; i < 60; i++)
	{
		if (LKT[i] == 134)
		{
			
			PLAYER->getKunai()->setLeftStuck(true);
			POINT leftCollision;
			leftCollision.x = PLAYER->getKunai()->getLeftKuniaPos().left + i + 90;
			leftCollision.y = PLAYER->getKunai()->getLeftKuniaPos().top + 20;
			PLAYER->getKunai()->setLeftWallCollision(leftCollision);
			break;
		}
	}
	for (int i = 0; i < 60; i++)
	{
		if (RKT[i] == 134)
		{
			PLAYER->getKunai()->setRightStuck(true);
			POINT rightCollision;
			rightCollision.x = PLAYER->getKunai()->getRightKuniaPos().left + i - 90;
			rightCollision.y = PLAYER->getKunai()->getRightKuniaPos().top + 20;
			PLAYER->getKunai()->setRightWallCollision(rightCollision);
			break;
			
		}
	}

	if (!PLAYER->getKunai()->getLeftFlying())
	{
		if (PLAYER->getKunai()->getLeftStuck())
		{
			float targetPosX = PLAYER->getKunai()->getLeftWallCollision().x;
			float targetPosY = PLAYER->getKunai()->getLeftWallCollision().y;
			PLAYER->setPosX(PLAYER->getPosX() + (targetPosX - PLAYER->getPosX()) * _lerpSpeed);
			PLAYER->setPosY(PLAYER->getPosY() + (targetPosY - PLAYER->getPosY()) * _lerpSpeed);
			PLAYER->getKunai()->eraseLeftPathPoints(3);
			if (abs(PLAYER->getPosX() - targetPosX) < 1.f && abs(PLAYER->getPosY() - targetPosY) < 1.f)
			{

				PLAYER->setPosX(targetPosX);
				PLAYER->setPosY(targetPosY);
				PLAYER->getKunai()->setLeftStuck(false);

			}
		}
	}

	if (!PLAYER->getKunai()->getLeftFlying() && PLAYER->getKunai()->getLeftStuck())
	{

		PLAYER->setIsCanLeftWallJump(true);
		PLAYER->setGravity(0);
		PLAYER->setIsJumping(false);
	}
	else
	{
		PLAYER->setIsCanLeftWallJump(false);
		PLAYER->setGravity(8);
		PLAYER->setIsJumping(true);
	}


	if (!PLAYER->getKunai()->getRightFlying())
	{
		if (PLAYER->getKunai()->getRightStuck())
		{
			float targetPosX = PLAYER->getKunai()->getRightWallCollision().x;
			float targetPosY = PLAYER->getKunai()->getRightWallCollision().y;
			PLAYER->setPosX(PLAYER->getPosX() + (targetPosX - PLAYER->getPosX()) * _lerpSpeed);
			PLAYER->setPosY(PLAYER->getPosY() + (targetPosY - PLAYER->getPosY()) * _lerpSpeed);
			PLAYER->setIsJumping(false);
			PLAYER->getKunai()->eraseRightPathPoints(3);
			if (abs(PLAYER->getPosX() - targetPosX) < 1.f && abs(PLAYER->getPosY() - targetPosY) < 1.f)
			{
				PLAYER->setPosX(targetPosX);
				PLAYER->setPosY(targetPosY);
				PLAYER->getKunai()->setRightStuck(false);
			}
		}

	}
	if (!PLAYER->getKunai()->getRightFlying() && PLAYER->getKunai()->getRightStuck())
	{

		PLAYER->setIsCanRightWallJump(true);
		PLAYER->setGravity(0);
		PLAYER->setIsJumping(false);
	}
	else {
		PLAYER->setIsCanRightWallJump(false);
		PLAYER->setGravity(8);
		PLAYER->setIsJumping(true);
	}
}
