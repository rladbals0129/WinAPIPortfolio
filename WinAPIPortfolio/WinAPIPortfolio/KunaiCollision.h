#pragma once
class KunaiCollision
{
private:
	float _lerpSpeed;
public:
	HRESULT init();
	void kunaiCollision(HDC hdc,int offsetX, int offsetY);
};

