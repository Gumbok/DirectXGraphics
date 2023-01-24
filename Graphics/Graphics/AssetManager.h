#pragma once
#include "TextureData.h"
#include <map>

class CAssetManager
{
public:
	CAssetManager();
	~CAssetManager();

	STextureData* LoadTexture(LPCWSTR _fileName, D3D11_FILTER _filterMode = D3D11_FILTER_MIN_MAG_MIP_LINEAR);

private:
	std::map<LPCWSTR, STextureData*> m_textures;
};

