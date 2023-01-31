#pragma once
#include "OSNMEntity.h"
class COSNMCube :
    public COSNMEntity
{
public:
	COSNMCube(LPCWSTR _fileName, LPCWSTR _normalMapFileName, XMFLOAT3 _pos = XMFLOAT3(0, 0, 0));
	virtual ~COSNMCube();

	virtual void Update(float _deltaTime) override;
};

