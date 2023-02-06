#include "GraphicsPCH.h"
#include "TriplanarOktaeder.h"
#include "Game.h"

CTriplanarOktaeder::CTriplanarOktaeder(LPCWSTR _fileName, XMFLOAT3 _pos)
	: CTriplanarEntity(_fileName, _pos)
{
	m_vertexCount = 8 * 3;
	m_indexCount = 8 * 3;

	m_vertices = new SVertexPosColor[m_vertexCount];
	m_indices = new WORD[m_indexCount];

	int i = 0;
	m_vertices[i++] = { XMFLOAT3(0.0f, 0.5f, 0.0f),XMFLOAT3(1, 1, -1) };
	m_vertices[i++] = { XMFLOAT3(0.5f, 0.0f, 0.0f),XMFLOAT3(1, 1, -1) };
	m_vertices[i++] = { XMFLOAT3(0.0f, 0.0f, -0.5f),XMFLOAT3(1, 1, -1) };

	m_vertices[i++] = { XMFLOAT3(0.0f, 0.5f, 0.0f),XMFLOAT3(1, 1, 1) };
	m_vertices[i++] = { XMFLOAT3(0.0f, 0.0f, 0.5f),XMFLOAT3(1, 1, 1) };
	m_vertices[i++] = { XMFLOAT3(0.5f, 0.0f, 0.0f),XMFLOAT3(1, 1, 1) };

	m_vertices[i++] = { XMFLOAT3(0.0f, 0.5f, 0.0f),XMFLOAT3(-1, 1, 1) };
	m_vertices[i++] = { XMFLOAT3(-0.5f, 0.0f, 0.0f),XMFLOAT3(-1, 1, 1) };
	m_vertices[i++] = { XMFLOAT3(0.0f, 0.0f, 0.5f),XMFLOAT3(-1, 1, 1) };

	m_vertices[i++] = { XMFLOAT3(0.0f, 0.5f, 0.0f),XMFLOAT3(-1, 1, -1) };
	m_vertices[i++] = { XMFLOAT3(0.0f, 0.0f, -0.5f),XMFLOAT3(-1, 1, -1) };
	m_vertices[i++] = { XMFLOAT3(-0.5f, 0.0f, 0.0f),XMFLOAT3(-1, 1, -1) };

	//----

	m_vertices[i++] = { XMFLOAT3(0.0f, -0.5f, 0.0f),XMFLOAT3(1, -1, -1) };
	m_vertices[i++] = { XMFLOAT3(0.0f, 0.0f, -0.5f),XMFLOAT3(1, -1, -1) };
	m_vertices[i++] = { XMFLOAT3(0.5f, 0.0f, 0.0f),XMFLOAT3(1, -1, -1) };

	m_vertices[i++] = { XMFLOAT3(0.0f, -0.5f, 0.0f),XMFLOAT3(1, -1, 1) };
	m_vertices[i++] = { XMFLOAT3(0.5f, 0.0f, 0.0f),XMFLOAT3(1, -1, 1) };
	m_vertices[i++] = { XMFLOAT3(0.0f, 0.0f, 0.5f),XMFLOAT3(1, -1, 1) };

	m_vertices[i++] = { XMFLOAT3(0.0f, -0.5f, 0.0f),XMFLOAT3(-1, -1, 1) };
	m_vertices[i++] = { XMFLOAT3(0.0f, 0.0f, 0.5f),XMFLOAT3(-1, -1, 1) };
	m_vertices[i++] = { XMFLOAT3(-0.5f, 0.0f, 0.0f),XMFLOAT3(-1, -1, 1) };

	m_vertices[i++] = { XMFLOAT3(0.0f, -0.5f, 0.0f),XMFLOAT3(-1, -1, -1) };
	m_vertices[i++] = { XMFLOAT3(-0.5f, 0.0f, 0.0f),XMFLOAT3(-1, -1, -1) };
	m_vertices[i++] = { XMFLOAT3(0.0f, 0.0f, -0.5f),XMFLOAT3(-1, -1, -1) };

	for (i = 0; i < 3 * 8; i++)
	{
		m_indices[i] = i;
	}
}

CTriplanarOktaeder::~CTriplanarOktaeder()
{
}

void CTriplanarOktaeder::Update(float _deltaTime)
{
	if (IPM.GetKey(DIK_SPACE))
	{
		m_rotation.x += -35 * _deltaTime;
		m_rotation.y += 14 * _deltaTime;

	}
	if (IPM.GetKey(DIK_LEFTARROW))
	{
		m_position.x -= _deltaTime;
	}
	if (IPM.GetKey(DIK_RIGHTARROW))
	{
		m_position.x += _deltaTime;
	}
	if (IPM.GetKey(DIK_DOWNARROW))
	{
		m_position.y -= _deltaTime;
	}
	if (IPM.GetKey(DIK_UPARROW))
	{
		m_position.y += _deltaTime;
	}
}
