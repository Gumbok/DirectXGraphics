#pragma once
#include "TexturedEntity.h"
class CTexturedPlane :
    public CTexturedEntity
{
public:
	CTexturedPlane(LPCWSTR _filename, XMFLOAT3 _pos = XMFLOAT3(0, 0, 0));
	virtual ~CTexturedPlane();
};

