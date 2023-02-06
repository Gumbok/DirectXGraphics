#pragma once
#include "TriplanarEntity.h"
class CTriplanarOktaeder :
    public CTriplanarEntity
{
public:
	CTriplanarOktaeder(LPCWSTR _fileName, XMFLOAT3 _pos = XMFLOAT3(0, 0, 0));
	virtual ~CTriplanarOktaeder();

	virtual void Update(float _deltaTime) override;
};

