#pragma once
#include "Entity.h"
#include "TextureData.h"

class CTexturedEntity : public CEntity
{
public:
	CTexturedEntity(LPCWSTR _fileName, XMFLOAT3 _pos);
	virtual ~CTexturedEntity();

	virtual void Render() override;

protected:
	STextureData m_textureData;
};

