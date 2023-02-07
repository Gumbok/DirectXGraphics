#include "GraphicsPCH.h"
#include "Cube.h"

CCube::CCube(XMFLOAT3 _pos)
	: CEntity(_pos)
{
	m_vertexCount = 4 * 6;
	m_indexCount = 6 * 6;

	m_vertices = new SVertexPosColor[m_vertexCount];
	m_indices = new WORD[m_indexCount];

	int i = 0;
	// oben
	m_vertices[i++] = { XMFLOAT3(-0.5f, 0.5f, -0.5f), XMFLOAT3(0.0f, 1.0f, 0.0f),XMFLOAT4(0.4f,0.3f,0.5f,1) };
	m_vertices[i++] = { XMFLOAT3(0.5f, 0.5f, -0.5f), XMFLOAT3(0.0f, 1.0f, 0.0f), XMFLOAT4(1.0f,0.0f,0.0f,1) };
	m_vertices[i++] = { XMFLOAT3(0.5f, 0.5f, 0.5f), XMFLOAT3(0.0f, 1.0f, 0.0f), XMFLOAT4(0.0f,1.0f,0.0f,1) };
	m_vertices[i++] = { XMFLOAT3(-0.5f, 0.5f, 0.5f), XMFLOAT3(0.0f, 1.0f, 0.0f), XMFLOAT4(0.0f,0.0f,1.0f,1) };

	// unten
	m_vertices[i++] = { XMFLOAT3(0.5f, -0.5f, -0.5f), XMFLOAT3(0.0f, -1.0f, 0.0f), XMFLOAT4(0.0f,1.0f,1.0f,1) };
	m_vertices[i++] = { XMFLOAT3(-0.5f, -0.5f, -0.5f), XMFLOAT3(0.0f, -1.0f, 0.0f), XMFLOAT4(1.0f,0.0f,1.0f,1) };
	m_vertices[i++] = { XMFLOAT3(-0.5f, -0.5f, 0.5f),XMFLOAT3(0.0f, -1.0f, 0.0f), XMFLOAT4(1.0f,1.0f,1.0f,1) };
	m_vertices[i++] = { XMFLOAT3(0.5f, -0.5f, 0.5f), XMFLOAT3(0.0f, -1.0f, 0.0f), XMFLOAT4(1.0f,1.0f,0.0f,1) };

	// vorne
	m_vertices[i++] = { XMFLOAT3(-0.5f, -0.5f, -0.5f), XMFLOAT3(0.0f, 0.0f, -1.0f), XMFLOAT4(1.0f,0.0f,1.0f,1) };
	m_vertices[i++] = { XMFLOAT3(0.5f, -0.5f, -0.5f), XMFLOAT3(0.0f, 0.0f, -1.0f), XMFLOAT4(0.0f,1.0f,1.0f,1) };
	m_vertices[i++] = { XMFLOAT3(0.5f, 0.5f, -0.5f), XMFLOAT3(0.0f, 0.0f, -1.0f), XMFLOAT4(1.0f,0.0f,0.0f,1) };
	m_vertices[i++] = { XMFLOAT3(-0.5f, 0.5f, -0.5f), XMFLOAT3(0.0f, 0.0f, -1.0f),XMFLOAT4(0.4f,0.3f,0.5f,1) };

	// rechts
	m_vertices[i++] = { XMFLOAT3(0.5f, -0.5f, -0.5f), XMFLOAT3(1.0f, 0.0f, 0.0f), XMFLOAT4(0.0f,1.0f,1.0f,1) };
	m_vertices[i++] = { XMFLOAT3(0.5f, -0.5f, 0.5f), XMFLOAT3(1.0f, 0.0f, 0.0f), XMFLOAT4(1.0f,1.0f,0.0f,1) };
	m_vertices[i++] = { XMFLOAT3(0.5f, 0.5f, 0.5f), XMFLOAT3(1.0f, 0.0f, 0.0f), XMFLOAT4(0.0f,1.0f,0.0f,1) };
	m_vertices[i++] = { XMFLOAT3(0.5f, 0.5f, -0.5f), XMFLOAT3(1.0f, 0.0f, 0.0f), XMFLOAT4(1.0f,0.0f,0.0f,1) };

	// hinten
	m_vertices[i++] = { XMFLOAT3(0.5f, -0.5f, 0.5f), XMFLOAT3(0.0f, 0.0f, 1.0f), XMFLOAT4(1.0f,1.0f,0.0f,1) };
	m_vertices[i++] = { XMFLOAT3(-0.5f, -0.5f, 0.5f),XMFLOAT3(0.0f, 0.0f, 1.0f), XMFLOAT4(1.0f,1.0f,1.0f,1) };
	m_vertices[i++] = { XMFLOAT3(-0.5f, 0.5f, 0.5f), XMFLOAT3(0.0f, 0.0f, 1.0f), XMFLOAT4(0.0f,0.0f,1.0f,1) };
	m_vertices[i++] = { XMFLOAT3(0.5f, 0.5f, 0.5f), XMFLOAT3(0.0f, 0.0f, 1.0f), XMFLOAT4(0.0f,1.0f,0.0f,1) };

	// links
	m_vertices[i++] = { XMFLOAT3(-0.5f, -0.5f, 0.5f),XMFLOAT3(-1.0f, 0.0f, 0.0f), XMFLOAT4(1.0f,1.0f,1.0f,1) };
	m_vertices[i++] = { XMFLOAT3(-0.5f, -0.5f, -0.5f), XMFLOAT3(-1.0f, 0.0f, 0.0f), XMFLOAT4(1.0f,0.0f,1.0f,1) };
	m_vertices[i++] = { XMFLOAT3(-0.5f, 0.5f, -0.5f), XMFLOAT3(-1.0f, 0.0f, 0.0f),XMFLOAT4(0.4f,0.3f,0.5f,1) };
	m_vertices[i++] = { XMFLOAT3(-0.5f, 0.5f, 0.5f), XMFLOAT3(-1.0f, 0.0f, 0.0f), XMFLOAT4(0.0f,0.0f,1.0f,1) };


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

CCube::~CCube()
{
	
}

void CCube::Update(float _deltaTime)
{
	m_rotation.x += 30 * _deltaTime;
	m_rotation.y += 20 * _deltaTime;
}
