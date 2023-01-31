#pragma once
#include "SplatMapEntity.h"
class CTerrain :
    public CSplatMapEntity
{
public:
	CTerrain(LPCWSTR _controllFileName, LPCWSTR _fileNameR, LPCWSTR _fileNameG, LPCWSTR _fileNameB, LPCWSTR _fileNameA, LPCWSTR _fileNameHeight, int _xSize, int _zSize, XMFLOAT3 _pos = XMFLOAT3(0,0,0));
	virtual ~CTerrain();

	virtual void Update(float _deltatime) override;
};

