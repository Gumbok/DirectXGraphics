#include "Entity.h"
#include "TextureData.h"

#pragma once
class CTriplanarEntity : public CEntity
{
public:
	CTriplanarEntity(LPCWSTR _fileName, XMFLOAT3 _pos);
	virtual ~CTriplanarEntity();

	virtual void Render() override;

protected:
	STextureData* m_textureData;
};

