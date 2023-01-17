#include "GraphicsPCH.h"
#include "TexturedPlane.h"

CTexturedPlane::CTexturedPlane(LPCWSTR _filename, XMFLOAT3 _pos)
 : CTexturedEntity(_filename, _pos)
{
	m_vertexCount = 4;
	m_indexCount = 6;

	m_vertices = new SVertexPosColor[m_vertexCount];
	m_indices = new WORD[m_indexCount];

	int i = 0;
	m_vertices[i++] = { XMFLOAT3(-0.5f, 0.0f, -0.5f),XMFLOAT3(1, 1, -1), XMFLOAT4(1,1,1,1), XMFLOAT2(0,1)};
	m_vertices[i++] = { XMFLOAT3(0.5f, 0.0f, -0.5f),XMFLOAT3(1, 1, -1), XMFLOAT4(1,1,1,1), XMFLOAT2(1,1) };
	m_vertices[i++] = { XMFLOAT3(0.5f, 0.0f, 0.5f),XMFLOAT3(1, 1, -1), XMFLOAT4(1,1,1,1), XMFLOAT2(1,0) };
	m_vertices[i++] = { XMFLOAT3(-0.5f, 0.0f, 0.5f),XMFLOAT3(1, 1, -1), XMFLOAT4(1,1,1,1), XMFLOAT2(0,0) };

	i = 0;
	m_indices[i++] = 0;
	m_indices[i++] = 3;
	m_indices[i++] = 2;

	m_indices[i++] = 2;
	m_indices[i++] = 1;
	m_indices[i++] = 0;
}

CTexturedPlane::~CTexturedPlane()
{
}
