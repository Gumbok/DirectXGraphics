#include "GraphicsPCH.h"
#include "AssetManager.h"
#include "Game.h"

CAssetManager::CAssetManager()
{
}

CAssetManager::~CAssetManager()
{
}

STextureData* CAssetManager::LoadTexture(LPCWSTR _fileName, D3D11_FILTER _filterMode)
{
	if (_fileName == nullptr)
	{
		return nullptr;
	}

	// Falls der Eintrag nicht gefunden ist, erzeigen wir die Textur
	if (m_textures.find(_fileName) == m_textures.end())
	{
		ID3D11Resource* t;
		ID3D11ShaderResourceView* srv;
		ID3D11SamplerState* ts;

		HRESULT hr = CreateWICTextureFromFile(DXS.m_device, _fileName, &t, &srv);
		if (FAILED(hr))
		{
			LPCWSTR text = L"Failed to load texture";
			MessageBox(nullptr, _fileName, text, MB_OK);
		}

		D3D11_SAMPLER_DESC desc;
		ZeroMemory(&desc, sizeof(D3D11_SAMPLER_DESC));
		desc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
		desc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
		desc.Filter = _filterMode; // Lineare interpolation
		desc.ComparisonFunc = D3D11_COMPARISON_NEVER;
		desc.MinLOD = 0;
		desc.MaxLOD = D3D11_FLOAT32_MAX;

		DXS.m_device->CreateSamplerState(&desc, &ts);
		m_textures[_fileName] = new STextureData(t, srv, ts);
	}

	return m_textures[_fileName];
}
