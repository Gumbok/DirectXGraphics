#pragma once
#include "Entity.h"
#include "TextureData.h"

class CSplatMapEntity :
    public CEntity
{
public:
	CSplatMapEntity(LPCWSTR _controllFileName, LPCWSTR _fileNameR, LPCWSTR _fileNameG, LPCWSTR _fileNameB, LPCWSTR _fileNameA, LPCWSTR _fileNameHeight,XMFLOAT3 _pos);
	virtual ~CSplatMapEntity();

	virtual void Render() override;

protected:
	STextureData* m_controllTexture;
	STextureData* m_TextureR;
	STextureData* m_TextureG;
	STextureData* m_TextureB;
	STextureData* m_TextureA;
	STextureData* m_TextureHeight;

};

