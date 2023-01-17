#include "GraphicsPCH.h"
#include "TextureData.h"

STextureData::STextureData()
{
}

STextureData::STextureData(ID3D11Resource* _texture, ID3D11ShaderResourceView* _ressourceView, ID3D11SamplerState* _sampler)
{
	m_texture = _texture;
	m_shaderRessourceView = _ressourceView;
	m_textureSampler = _sampler;
}
