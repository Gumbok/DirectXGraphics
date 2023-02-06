#pragma once
#include "TriplanarEntity.h"
class CTriplanarSphere :
    public CTriplanarEntity
{
public:
	CTriplanarSphere(LPCWSTR _filename, int _slices, int _heightSegments, XMFLOAT3 _pos = XMFLOAT3(0, 0, 0));
	virtual ~CTriplanarSphere();

	virtual void Update(float _deltaTime) override;

private:
};

