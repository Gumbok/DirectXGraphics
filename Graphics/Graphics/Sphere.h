#pragma once
#include "Entity.h"

class CSphere : public CEntity
{
public:
	CSphere(XMFLOAT4 _col, int _slices, int _heightSegments, XMFLOAT3 _pos = XMFLOAT3(0, 0, 0));
	virtual ~CSphere();

	virtual void Update(float _deltaTime) override;

};

