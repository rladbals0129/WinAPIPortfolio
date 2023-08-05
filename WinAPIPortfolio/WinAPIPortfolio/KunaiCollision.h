#pragma once
class KunaiCollision
{
private:
	float _lerpSpeed;

	bool _soundL;
	bool _soundR;
public:
	HRESULT init();
	void kunaiCollision(HDC hdc,int offsetX, int offsetY);
};

