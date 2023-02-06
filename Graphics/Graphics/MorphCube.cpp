#include "GraphicsPCH.h"
#include "MorphCube.h"
#include "Helper.h"
#include "Game.h"

CMorphCube::CMorphCube(int _subDivisions, XMFLOAT3 _pos)
	: CEntity(_pos)
{
	if (_subDivisions < 1)
	{
		m_invalid = true;
		return;
	}

	int sideVerts = (_subDivisions + 1) * (_subDivisions + 1);
	m_vertexCount = sideVerts * 6;
	m_indexCount = _subDivisions * _subDivisions * 6 * 6;

	m_vertices = new SVertexPosColor[m_vertexCount];
	m_indices = new WORD[m_indexCount];

	int i = 0;
	// vorne
	for (float y = 0; y < _subDivisions + 1; y++)
	{
		for (float x = 0; x < _subDivisions + 1; x++)
		{
			m_vertices[i++] = { XMFLOAT3(-0.5f + x / _subDivisions, 0.5f - y / _subDivisions ,-0.5f), XMFLOAT3(0,0, -1), XMFLOAT4(1,0,0,1) };
		}
	}

	// rechts
	for (float y = 0; y < _subDivisions + 1; y++)
	{
		for (float x = 0; x < _subDivisions + 1; x++)
		{
			m_vertices[i++] = { XMFLOAT3(0.5f, 0.5f - y / _subDivisions ,-0.5f + x / _subDivisions), XMFLOAT3(1,0, 0), XMFLOAT4(1,0,0,1) };
		}
	}

	// hinten
	for (float y = 0; y < _subDivisions + 1; y++)
	{
		for (float x = 0; x < _subDivisions + 1; x++)
		{
			m_vertices[i++] = { XMFLOAT3(0.5f - x / _subDivisions, 0.5f - y / _subDivisions ,0.5f), XMFLOAT3(0,0, 1), XMFLOAT4(1,0,0,1) };
		}
	}

	// links
	for (float y = 0; y < _subDivisions + 1; y++)
	{
		for (float x = 0; x < _subDivisions + 1; x++)
		{
			m_vertices[i++] = { XMFLOAT3(-0.5f, 0.5f - y / _subDivisions ,0.5f - x / _subDivisions), XMFLOAT3(-1,0, 0), XMFLOAT4(1,0,0,1) };
		}
	}

	// oben
	for (float y = 0; y < _subDivisions + 1; y++)
	{
		for (float x = 0; x < _subDivisions + 1; x++)
		{
			m_vertices[i++] = { XMFLOAT3(-0.5f + x / _subDivisions, 0.5f ,0.5f - y / _subDivisions), XMFLOAT3(0, 1, 0), XMFLOAT4(1,0,0,1) };
		}
	}

	// unten
	for (float y = 0; y < _subDivisions + 1; y++)
	{
		for (float x = 0; x < _subDivisions + 1; x++)
		{
			m_vertices[i++] = { XMFLOAT3(0.5f - x / _subDivisions, -0.5f ,0.5f - y / _subDivisions), XMFLOAT3(0, 1, 0), XMFLOAT4(1,0,0,1) };
		}
	}
	i = 0;
	for (int z = 0; z < 6; z++)
	{
		for (int y = 0; y < _subDivisions; y++)
		{
			for (int x = 0; x < _subDivisions; x++)
			{
				m_indices[i++] = z * sideVerts + y * (_subDivisions + 1) + x;
				m_indices[i++] = z * sideVerts + y * (_subDivisions + 1) + x + 1;
				m_indices[i++] = z * sideVerts + y * (_subDivisions + 1) + x + _subDivisions + 1;

				m_indices[i++] = z * sideVerts + y * (_subDivisions + 1) + x + 1;
				m_indices[i++] = z * sideVerts + y * (_subDivisions + 1) + x + _subDivisions + 1 + 1;
				m_indices[i++] = z * sideVerts + y * (_subDivisions + 1) + x + _subDivisions + 1;
			}
		}
	}

	m_cubeVertices = new SVertexPosColor[m_vertexCount];
	m_sphereVertices = new SVertexPosColor[m_vertexCount];

	memcpy(m_cubeVertices, m_vertices, m_vertexCount * sizeof(SVertexPosColor));

	for (int i = 0; i < m_vertexCount; i++)
	{
		m_sphereVertices[i].Position = m_sphereVertices[i].Normal = Normalize(m_cubeVertices[i].Position);
		m_sphereVertices[i].Color = XMFLOAT4(0, 0.5f, 1, 1);
	}
}

CMorphCube::~CMorphCube()
{
}

void CMorphCube::Update(float _deltaTime)
{
	m_timer += _deltaTime;


	float time = (sin(m_timer) + 1) / 2;


	for (int i = 0; i < m_vertexCount; i++)
	{
		m_vertices[i] = 
		{
						Lerp(m_cubeVertices[i].Position, m_sphereVertices[i].Position, time),
						Lerp(m_cubeVertices[i].Normal, m_sphereVertices[i].Normal, time),
						Lerp(m_cubeVertices[i].Color, m_sphereVertices[i].Color, time)
		};
	}

	DXS.m_deviceContext->UpdateSubresource(m_vertexBuffer, 0, nullptr, m_vertices, 0, 0);
}
