#pragma once
#include "TexturedEntity.h"
class CTexturedSphere :
    public CTexturedEntity
{
public:
	CTexturedSphere(LPCWSTR _filename, int _slices, int _heightSegments, XMFLOAT3 _pos = XMFLOAT3(0, 0, 0));
	virtual ~CTexturedSphere();

	virtual void Update(float _deltaTime) override;

private:
	float m_time = 0;
};

