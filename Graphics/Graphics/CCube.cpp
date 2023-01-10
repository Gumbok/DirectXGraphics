#include "GraphicsPCH.h"
#include "CCube.h"

CCube::CCube(XMFLOAT3 _pos)
	: CEntity(_pos)
{
	m_vertexCount = 8;
	m_indexCount = 6 * 6;

	m_vertices = new SVertexPosColor[m_vertexCount];
	m_indices = new WORD[m_indexCount];

	int i = 0;
	m_vertices[i++] = { XMFLOAT3(-0.5f, 0.5f, -0.5f), XMFLOAT3(-0.5f, 0.5f, -0.5f),XMFLOAT4(0.4f,0.3f,0.5f,1) };
	m_vertices[i++] = { XMFLOAT3(0.5f, 0.5f, -0.5f), XMFLOAT3(0.5f, 0.5f, -0.5f), XMFLOAT4(1.0f,0.0f,0.0f,1) };
	m_vertices[i++] = { XMFLOAT3(0.5f, 0.5f, 0.5f), XMFLOAT3(0.5f, 0.5f, 0.5f), XMFLOAT4(0.0f,1.0f,0.0f,1) };
	m_vertices[i++] = { XMFLOAT3(-0.5f, 0.5f, 0.5f), XMFLOAT3(-0.5f, 0.5f, 0.5f), XMFLOAT4(0.0f,0.0f,1.0f,1) };

	m_vertices[i++] = { XMFLOAT3(-0.5f, -0.5f, -0.5f), XMFLOAT3(-0.5f, -0.5f, -0.5f), XMFLOAT4(1.0f,0.0f,1.0f,1) };
	m_vertices[i++] = { XMFLOAT3(0.5f, -0.5f, -0.5f), XMFLOAT3(0.5f, -0.5f, -0.5f), XMFLOAT4(0.0f,1.0f,1.0f,1) };
	m_vertices[i++] = { XMFLOAT3(0.5f, -0.5f, 0.5f), XMFLOAT3(0.5f, -0.5f, 0.5f), XMFLOAT4(1.0f,1.0f,0.0f,1) };
	m_vertices[i++] = { XMFLOAT3(-0.5f, -0.5f, 0.5f),XMFLOAT3(-0.5f, -0.5f, 0.5f), XMFLOAT4(1.0f,1.0f,1.0f,1) };

	i = 0;
	// oben
	m_indices[i++] = 1;
	m_indices[i++] = 0;
	m_indices[i++] = 3;

	m_indices[i++] = 1;
	m_indices[i++] = 3;
	m_indices[i++] = 2;
	
	// vorne
	m_indices[i++] = 4;
	m_indices[i++] = 0;
	m_indices[i++] = 1;

	m_indices[i++] = 4;
	m_indices[i++] = 1;
	m_indices[i++] = 5;

	// rechts
	m_indices[i++] = 5;
	m_indices[i++] = 1;
	m_indices[i++] = 2;

	m_indices[i++] = 5;
	m_indices[i++] = 2;
	m_indices[i++] = 6;

	// hinten
	m_indices[i++] = 6;
	m_indices[i++] = 2;
	m_indices[i++] = 3;

	m_indices[i++] = 6;
	m_indices[i++] = 3;
	m_indices[i++] = 7;

	// links
	m_indices[i++] = 7;
	m_indices[i++] = 3;
	m_indices[i++] = 4;

	m_indices[i++] = 4;
	m_indices[i++] = 3;
	m_indices[i++] = 0;

	// unten
	m_indices[i++] = 6;
	m_indices[i++] = 7;
	m_indices[i++] = 5;

	m_indices[i++] = 5;
	m_indices[i++] = 7;
	m_indices[i++] = 4;
}

CCube::~CCube()
{
}

void CCube::Update(float _deltaTime)
{
	m_rotation.x += 30 * _deltaTime;
	m_rotation.y += 20 * _deltaTime;
}
