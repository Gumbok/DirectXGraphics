#pragma once
#include "Entity.h"
#include "TextureData.h"

class CSkybox :
    public CEntity
{
public:
	CSkybox(LPCWSTR _fileName1, LPCWSTR _fileName2);
	virtual ~CSkybox();

	virtual void Render() override;
	virtual void Update(float _deltaTime) override;


protected:
	STextureData* m_textureData1;
	STextureData* m_textureData2;
	ID3D11DepthStencilState* m_depthStencilState = nullptr;
	ID3D11RasterizerState* m_rasterizerState = nullptr;
};

