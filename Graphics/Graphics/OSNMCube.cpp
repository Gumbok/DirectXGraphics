#include "GraphicsPCH.h"
#include "OSNMCube.h"
#include "Game.h"

COSNMCube::COSNMCube(LPCWSTR _fileName, LPCWSTR _normalMapFileName, XMFLOAT3 _pos)
	: COSNMEntity(_fileName, _normalMapFileName, _pos)
{
	m_vertexCount = 4 * 6;
	m_indexCount = 6 * 6;

	m_vertices = new SVertexPosColor[m_vertexCount];
	m_indices = new WORD[m_indexCount];

	ID3D11Texture2D* tex2D = (ID3D11Texture2D*)m_textureData->m_texture;
	D3D11_TEXTURE2D_DESC tDesc;
	tex2D->GetDesc(&tDesc);

	// half pixel
	float hp = 1 / (tDesc.Width * 2.0f);

	XMFLOAT4 col = XMFLOAT4(1, 1, 1, 1);

	// Reguläre Ausdrücke
	// Suchen von Text mit einer "einfachen" Skriptsprache
	// XMFLOAT4\((\d\.\df,){3}1\)
	// findet XMLFLOAT4(1.0f,1.0f,1.0f,1)
	// https://rubular.com/ testen
	// https://regexper.com/#XMFLOAT4%5C%28%28%5Cd%5C.%5Cdf%2C%29%7B3%7D1%5C%29 verstehen

	int i = 0;
	// oben
	m_vertices[i++] = { XMFLOAT3(-0.5f, 0.5f, -0.5f), XMFLOAT3(0.0f, 1.0f, 0.0f),col, XMFLOAT2(0.5f + hp, 0 + hp) };
	m_vertices[i++] = { XMFLOAT3(0.5f, 0.5f, -0.5f), XMFLOAT3(0.0f, 1.0f, 0.0f), col, XMFLOAT2(1 - hp, 0 + hp) };
	m_vertices[i++] = { XMFLOAT3(0.5f, 0.5f, 0.5f), XMFLOAT3(0.0f, 1.0f, 0.0f), col, XMFLOAT2(1 - hp, 0.5f - hp) };
	m_vertices[i++] = { XMFLOAT3(-0.5f, 0.5f, 0.5f), XMFLOAT3(0.0f, 1.0f, 0.0f), col, XMFLOAT2(0.5f + hp, 0.5f - hp) };

	// unten
	m_vertices[i++] = { XMFLOAT3(0.5f, -0.5f, -0.5f), XMFLOAT3(0.0f, -1.0f, 0.0f), col,  XMFLOAT2(1 - hp, 0.5f + hp) };
	m_vertices[i++] = { XMFLOAT3(-0.5f, -0.5f, -0.5f), XMFLOAT3(0.0f, -1.0f, 0.0f), col, XMFLOAT2(0.5f + hp, 0.5f + hp) };
	m_vertices[i++] = { XMFLOAT3(-0.5f, -0.5f, 0.5f),XMFLOAT3(0.0f, -1.0f, 0.0f), col, XMFLOAT2(0.5f + hp, 1 - hp) };
	m_vertices[i++] = { XMFLOAT3(0.5f, -0.5f, 0.5f), XMFLOAT3(0.0f, -1.0f, 0.0f), col, XMFLOAT2(1 - hp, 1 - hp) };

	// vorne
	m_vertices[i++] = { XMFLOAT3(-0.5f, -0.5f, -0.5f), XMFLOAT3(0.0f, 0.0f, -1.0f), col, XMFLOAT2(0 + hp, 0.25f + hp) };
	m_vertices[i++] = { XMFLOAT3(0.5f, -0.5f, -0.5f), XMFLOAT3(0.0f, 0.0f, -1.0f), col, XMFLOAT2(0.25f - hp, 0.25f + hp) };
	m_vertices[i++] = { XMFLOAT3(0.5f, 0.5f, -0.5f), XMFLOAT3(0.0f, 0.0f, -1.0f), col,  XMFLOAT2(0.25f - hp, 0.5f - hp) };
	m_vertices[i++] = { XMFLOAT3(-0.5f, 0.5f, -0.5f), XMFLOAT3(0.0f, 0.0f, -1.0f),col, XMFLOAT2(0 + hp, 0.5f - hp) };

	// rechts
	m_vertices[i++] = { XMFLOAT3(0.5f, -0.5f, -0.5f), XMFLOAT3(1.0f, 0.0f, 0.0f), col, XMFLOAT2(0.25f + hp, 0 + hp) };
	m_vertices[i++] = { XMFLOAT3(0.5f, -0.5f, 0.5f), XMFLOAT3(1.0f, 0.0f, 0.0f), col, XMFLOAT2(0.25f + hp, 0.5f - hp) };
	m_vertices[i++] = { XMFLOAT3(0.5f, 0.5f, 0.5f), XMFLOAT3(1.0f, 0.0f, 0.0f), col, XMFLOAT2(0.5f - hp, 0.5f - hp) };
	m_vertices[i++] = { XMFLOAT3(0.5f, 0.5f, -0.5f), XMFLOAT3(1.0f, 0.0f, 0.0f), col, XMFLOAT2(0.5f - hp, 0 + hp) };

	// hinten
	m_vertices[i++] = { XMFLOAT3(0.5f, -0.5f, 0.5f), XMFLOAT3(0.0f, 0.0f, 1.0f), col, XMFLOAT2(0.25f - hp, 0 + hp) };
	m_vertices[i++] = { XMFLOAT3(-0.5f, -0.5f, 0.5f),XMFLOAT3(0.0f, 0.0f, 1.0f), col, XMFLOAT2(0 + hp,0 + hp) };
	m_vertices[i++] = { XMFLOAT3(-0.5f, 0.5f, 0.5f), XMFLOAT3(0.0f, 0.0f, 1.0f), col,  XMFLOAT2(0 + hp, 0.25f - hp) };
	m_vertices[i++] = { XMFLOAT3(0.5f, 0.5f, 0.5f), XMFLOAT3(0.0f, 0.0f, 1.0f), col, XMFLOAT2(0.25f - hp, 0.25f - hp) };

	// links
	m_vertices[i++] = { XMFLOAT3(-0.5f, -0.5f, 0.5f),XMFLOAT3(-1.0f, 0.0f, 0.0f), col, XMFLOAT2(0 + hp, 1 - hp) };
	m_vertices[i++] = { XMFLOAT3(-0.5f, -0.5f, -0.5f), XMFLOAT3(-1.0f, 0.0f, 0.0f), col,  XMFLOAT2(0 + hp, 0.5f + hp) };
	m_vertices[i++] = { XMFLOAT3(-0.5f, 0.5f, -0.5f), XMFLOAT3(-1.0f, 0.0f, 0.0f),col, XMFLOAT2(0.5f - hp, 0.5f + hp) };
	m_vertices[i++] = { XMFLOAT3(-0.5f, 0.5f, 0.5f), XMFLOAT3(-1.0f, 0.0f, 0.0f), col, XMFLOAT2(0.5f - hp, 1 - hp) };

	i = 0;
	for (int j = 0; j < 6 * 4; j += 4)
	{
		m_indices[i++] = j;
		m_indices[i++] = j + 2;
		m_indices[i++] = j + 1;

		m_indices[i++] = j;
		m_indices[i++] = j + 3;
		m_indices[i++] = j + 2;
	}
}

COSNMCube::~COSNMCube()
{
}

void COSNMCube::Update(float _deltaTime)
{
	if (IPM.GetKey(DIK_SPACE))
	{
		m_rotation.x += 30 * _deltaTime;
		m_rotation.y += 20 * _deltaTime;
	}
}
