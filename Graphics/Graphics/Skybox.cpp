#include "GraphicsPCH.h"
#include "Skybox.h"
#include "Game.h"
#include "Helper.h"

CSkybox::CSkybox(LPCWSTR _fileName1, LPCWSTR _fileName2)
	: CEntity(XMFLOAT3(0,0,0))
{
	D3D11_RASTERIZER_DESC rasterDesc;
	ZeroMemory(&rasterDesc, sizeof(D3D11_RASTERIZER_DESC));
	rasterDesc.CullMode = D3D11_CULL_NONE;
	rasterDesc.AntialiasedLineEnable = false;
	rasterDesc.FillMode = D3D11_FILL_SOLID;		// Komplette Dreiecke zeigen, rumspielen!
	rasterDesc.DepthBias = 0;
	rasterDesc.DepthBiasClamp = 0.0f;
	rasterDesc.DepthClipEnable = true;
	rasterDesc.FrontCounterClockwise = false;		// Dreiecke im Uhrzeigersinn zeigen nach vorne
	rasterDesc.MultisampleEnable = false;
	rasterDesc.ScissorEnable = false;
	rasterDesc.SlopeScaledDepthBias = 0.0f;


	HRESULT hr = DXS.m_device->CreateRasterizerState(&rasterDesc, &m_rasterizerState);
	if (FAILED(hr))
	{
		m_invalid = true;
		return;
	}

	D3D11_DEPTH_STENCIL_DESC depthDesc;
	ZeroMemory(&depthDesc, sizeof(D3D11_DEPTH_STENCIL_DESC));
	depthDesc.DepthEnable = true;
	depthDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	depthDesc.DepthFunc = D3D11_COMPARISON_LESS_EQUAL;
	depthDesc.StencilEnable = false;
	hr = DXS.m_device->CreateDepthStencilState(&depthDesc, &m_depthStencilState);
	if (FAILED(hr))
	{
		m_invalid = true;
		return;
	}

	m_textureData1 = ASM.LoadTexture(_fileName1);
	m_textureData2 = ASM.LoadTexture(_fileName2);

	int subDivisions = 10;

	int sideVerts = (subDivisions + 1) * (subDivisions + 1);
	m_vertexCount = sideVerts * 6;
	m_indexCount = subDivisions * subDivisions * 6 * 6;

	m_vertices = new SVertexPosColor[m_vertexCount];
	m_indices = new WORD[m_indexCount];

	int i = 0;
	// vorne
	for (float y = 0; y < subDivisions + 1; y++)
	{
		for (float x = 0; x < subDivisions + 1; x++)
		{
			m_vertices[i++] = { XMFLOAT3(-0.5f + x / subDivisions, 0.5f - y / subDivisions ,-0.5f), XMFLOAT3(0,0, -1), XMFLOAT4(1,1,1,1), XMFLOAT2(x/subDivisions, y/subDivisions)};
		}
	}

	// rechts
	for (float y = 0; y < subDivisions + 1; y++)
	{
		for (float x = 0; x < subDivisions + 1; x++)
		{
			m_vertices[i++] = { XMFLOAT3(0.5f, 0.5f - y / subDivisions ,-0.5f + x / subDivisions), XMFLOAT3(1,0, 0), XMFLOAT4(1,1,1,1), XMFLOAT2(x / subDivisions, y / subDivisions) };
		}
	}

	// hinten
	for (float y = 0; y < subDivisions + 1; y++)
	{
		for (float x = 0; x < subDivisions + 1; x++)
		{
			m_vertices[i++] = { XMFLOAT3(0.5f - x / subDivisions, 0.5f - y / subDivisions ,0.5f), XMFLOAT3(0,0, 1), XMFLOAT4(1,1,1,1), XMFLOAT2(x / subDivisions, y / subDivisions )};
		}
	}

	// links
	for (float y = 0; y < subDivisions + 1; y++)
	{
		for (float x = 0; x < subDivisions + 1; x++)
		{
			m_vertices[i++] = { XMFLOAT3(-0.5f, 0.5f - y / subDivisions ,0.5f - x / subDivisions), XMFLOAT3(-1,0, 0), XMFLOAT4(1,1,1,1), XMFLOAT2(x / subDivisions, y / subDivisions )};
		}
	}

	// oben
	for (float y = 0; y < subDivisions + 1; y++)
	{
		for (float x = 0; x < subDivisions + 1; x++)
		{
			m_vertices[i++] = { XMFLOAT3(-0.5f + x / subDivisions, 0.5f ,0.5f - y / subDivisions), XMFLOAT3(0, 1, 0), XMFLOAT4(1,1,1,1), XMFLOAT2(x / subDivisions, y / subDivisions )};
		}
	}

	// unten
	for (float y = 0; y < subDivisions + 1; y++)
	{
		for (float x = 0; x < subDivisions + 1; x++)
		{
			m_vertices[i++] = { XMFLOAT3(0.5f - x / subDivisions, -0.5f ,0.5f - y / subDivisions), XMFLOAT3(0, 1, 0), XMFLOAT4(1,1,1,1), XMFLOAT2(x / subDivisions , y / subDivisions )};
		}
	}
	i = 0;
	for (int z = 0; z < 6; z++)
	{
		for (int y = 0; y < subDivisions; y++)
		{
			for (int x = 0; x < subDivisions; x++)
			{
				m_indices[i++] = z * sideVerts + y * (subDivisions + 1) + x;
				m_indices[i++] = z * sideVerts + y * (subDivisions + 1) + x + subDivisions + 1;
				m_indices[i++] = z * sideVerts + y * (subDivisions + 1) + x + 1;

				m_indices[i++] = z * sideVerts + y * (subDivisions + 1) + x + 1;
				m_indices[i++] = z * sideVerts + y * (subDivisions + 1) + x + subDivisions + 1;
				m_indices[i++] = z * sideVerts + y * (subDivisions + 1) + x + subDivisions + 1 + 1;
			}
		}
	}

	for (int i = 0; i < m_vertexCount; i++)
	{
		m_vertices[i].Position  = Normalize(m_vertices[i].Position);
		m_vertices[i].Normal = m_vertices[i].Position * -1;

		//m_vertices[i].Position = m_vertices[i].Position * 100;
	}
}

CSkybox::~CSkybox()
{
}

void CSkybox::Render()
{
	// Prepare Object to World Matrix
	XMMATRIX scale = XMMatrixScaling(m_scale.x, m_scale.y, m_scale.z);
	XMMATRIX rotation = XMMatrixRotationRollPitchYaw(
		XMConvertToRadians(m_rotation.x),
		XMConvertToRadians(m_rotation.y),
		XMConvertToRadians(m_rotation.z));
	XMMATRIX translation = XMMatrixTranslation(m_position.x,
		m_position.y, m_position.z);

	// Saufen, Rauchen, Taxifahren
	m_objectConstantBuffer.m_matrix = scale * rotation * translation;

	DXS.m_deviceContext->UpdateSubresource(DXS.m_constantBuffers[CB_OBJECT],
		0, nullptr, &m_objectConstantBuffer, 0, 0);

	unsigned int offset = 0;
	unsigned int stride = sizeof(SVertexPosColor);

	// Input Assembler
	DXS.m_deviceContext->IASetInputLayout(DXS.m_skyboxInputLayout);
	DXS.m_deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	DXS.m_deviceContext->IASetVertexBuffers(0, 1, &m_vertexBuffer, &stride, &offset);
	DXS.m_deviceContext->IASetIndexBuffer(m_indexBuffer, DXGI_FORMAT_R16_UINT, offset);

	// Vertex Shader
	DXS.m_deviceContext->VSSetConstantBuffers(0, 4, DXS.m_constantBuffers);
	DXS.m_deviceContext->VSSetShader(DXS.m_skyboxVertexShader, nullptr, 0);

	// Rasterizer
	DXS.m_deviceContext->RSSetState(m_rasterizerState);
	//DXS.m_deviceContext->RSSetState(DXS.m_currentRasterrizerState);
	DXS.m_viewPort.MinDepth = 1;
	DXS.m_deviceContext->RSSetViewports(1, &DXS.m_viewPort);
	DXS.m_viewPort.MinDepth = 0;

	// Pixel Shader
	DXS.m_deviceContext->PSSetShader(DXS.m_skyboxPixelShader, nullptr, 0);
	DXS.m_deviceContext->PSSetSamplers(0, 1, &m_textureData1->m_textureSampler);
	DXS.m_deviceContext->PSSetSamplers(1, 1, &m_textureData2->m_textureSampler);
	DXS.m_deviceContext->PSSetShaderResources(0, 1, &m_textureData1->m_shaderRessourceView);
	DXS.m_deviceContext->PSSetShaderResources(1, 1, &m_textureData2->m_shaderRessourceView);

	// Output Merger
	DXS.m_deviceContext->OMSetRenderTargets(1, &DXS.m_renderTargetView, DXS.m_depthStencilView);
	DXS.m_deviceContext->OMSetDepthStencilState(m_depthStencilState, 1);
	//DXS.m_deviceContext->OMSetDepthStencilState(DXS.m_depthStencilState, 1);

	// Objekt zeichnen
	DXS.m_deviceContext->DrawIndexed(m_indexCount, 0, 0);

}

void CSkybox::Update(float _deltaTime)
{
}
