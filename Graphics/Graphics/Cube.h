#pragma once
#include "Entity.h"
class CCube : public CEntity
{
public:
	CCube(XMFLOAT3 _pos = XMFLOAT3(0, 0, 0));
	virtual ~CCube();

	virtual void Update(float _deltaTime) override;
};

