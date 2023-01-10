#pragma once
#include "CEntity.h"

class COktaeder : public CEntity
{
public:
	COktaeder(XMFLOAT4 _col, XMFLOAT3 _pos = XMFLOAT3(0, 0, 0));
	virtual ~COktaeder();

	virtual void Update(float _deltaTime) override;
};

