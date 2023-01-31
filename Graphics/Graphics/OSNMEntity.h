#pragma once
#include "Entity.h"
#include "TextureData.h"

// Object sprace normal map
class COSNMEntity :
    public CEntity
{
public:
	COSNMEntity(LPCWSTR _fileName, LPCWSTR _normalMapFileName, XMFLOAT3 _pos);
	virtual ~COSNMEntity();

	virtual void Render() override;

protected:
	STextureData* m_textureData;
	STextureData* m_normalMapTextureData;
};

