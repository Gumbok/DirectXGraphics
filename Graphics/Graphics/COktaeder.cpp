#include "GraphicsPCH.h"
#include "COktaeder.h"

COktaeder::COktaeder(XMFLOAT4 _col, XMFLOAT3 _pos)
	: CEntity(_pos)
{
	m_vertexCount = 6;
	m_indexCount = 8 * 3;

	m_vertices = new SVertexPosColor[m_vertexCount];
	m_indices = new WORD[m_indexCount];

	int i = 0;
	m_vertices[i++] = { XMFLOAT3(0.0f, 0.5f, 0.0f),XMFLOAT3(0.0f, 0.5f, 0.0f), _col };
	
	m_vertices[i++] = { XMFLOAT3(0.0f, 0.0f, 0.5f),XMFLOAT3(0.0f, 0.0f, 0.5f), _col };
	m_vertices[i++] = { XMFLOAT3(0.5f, 0.0f, 0.0f),XMFLOAT3(0.5f, 0.0f, 0.0f),		_col };
	m_vertices[i++] = { XMFLOAT3(0.0f, 0.0f, -0.5f),XMFLOAT3(0.0f, 0.0f, -0.5f),	_col };
	m_vertices[i++] = { XMFLOAT3(-0.5f, 0.0f, 0.0f),XMFLOAT3(-0.5f, 0.0f, 0.0f),	_col };

	m_vertices[i++] = { XMFLOAT3(0.0f, -0.5f, 0.0f),XMFLOAT3(0.0f, -0.5f, 0.0f), _col };

	i = 0;
	// oben
	m_indices[i++] = 0;
	m_indices[i++] = 1;
	m_indices[i++] = 2;
	
	m_indices[i++] = 0;
	m_indices[i++] = 2;
	m_indices[i++] = 3;

	m_indices[i++] = 0;
	m_indices[i++] = 3;
	m_indices[i++] = 4;

	m_indices[i++] = 0;
	m_indices[i++] = 4;
	m_indices[i++] = 1;

	// unten
	m_indices[i++] = 5;
	m_indices[i++] = 2;
	m_indices[i++] = 1;

	m_indices[i++] = 5;
	m_indices[i++] = 3;
	m_indices[i++] = 2;

	m_indices[i++] = 5;
	m_indices[i++] = 4;
	m_indices[i++] = 3;

	m_indices[i++] = 5;
	m_indices[i++] = 1;
	m_indices[i++] = 4;
}

COktaeder::~COktaeder()
{

}

void COktaeder::Update(float _deltaTime)
{
	m_rotation.x += -35 * _deltaTime;
	m_rotation.y += 14 * _deltaTime;
}
