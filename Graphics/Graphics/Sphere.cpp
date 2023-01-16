#include "GraphicsPCH.h"
#include "Sphere.h"

CSphere::CSphere(XMFLOAT4 _col, int _slices, int _heightSegments, XMFLOAT3 _pos)
	: CEntity(_pos)
{
	if (_slices < 2 || _heightSegments < 1)
	{
		m_invalid = true;
		return;
	}

	m_vertexCount = _slices * _heightSegments + 2;
	m_indexCount = _heightSegments * _slices * 6;

	m_vertices = new SVertexPosColor[m_vertexCount];
	m_indices = new WORD[m_indexCount];
	ZeroMemory(m_vertices, m_vertexCount * sizeof(SVertexPosColor));
	ZeroMemory(m_indices, m_indexCount * sizeof(WORD));


	int i = 0;
	m_vertices[i++] = { XMFLOAT3(0.0f, 0.5f, 0.0f),XMFLOAT3(0, 0.5f, 0), _col };
	XMFLOAT3 pos;
	float yPos;
	float radius;
	for (float y = 0; y < _heightSegments; y++)
	{
		yPos = cos(((y + 1) / (_heightSegments + 1) * XM_PI));
		radius = sin(((y + 1) / (_heightSegments + 1) * XM_PI));
		for (float x = 0; x < _slices; x++)
		{
			pos = XMFLOAT3(sin(x / _slices * XM_2PI) * 0.5f * radius, 
							yPos * 0.5f, 
							cos(x / _slices * XM_2PI) * 0.5f * radius);
			m_vertices[i++] = { pos, pos, _col};
		}
	}
	m_vertices[i++] = { XMFLOAT3(0.0f, -0.5f, 0.0f),XMFLOAT3(0, -0.5f, 0), _col };

	i = 0;
	// polkappe oben
	for (int x = 0; x < _slices; x++)
	{
		m_indices[i++] = 0;
		m_indices[i++] = x + 1;

		if (x != _slices - 1)
		{
			m_indices[i++] = x + 2;
		}
		else
		{
			m_indices[i++] = 1;
		}
	}

	// mitte
	for (int y = 0; y < _heightSegments - 1; y++)
	{
		for (int x = 0; x < _slices; x++)
		{
			if (x < _slices - 1)
			{
				m_indices[i++] = x + 1 + y * _slices;
				m_indices[i++] = x + 1 + _slices + y * _slices;
				m_indices[i++] = x + 2 + y * _slices;

				m_indices[i++] = x + 2 + y * _slices;
				m_indices[i++] = x + 1 + _slices + y * _slices;
				m_indices[i++] = x + 2 + _slices + y * _slices;
			}
			else
			{
				m_indices[i++] = x + 1 + y * _slices;
				m_indices[i++] = x + 1 + _slices + y * _slices;
				m_indices[i++] = x + 2 + (y - 1) * _slices;

				m_indices[i++] = x + 2 + (y - 1) * _slices;
				m_indices[i++] = x + 1 + _slices + y * _slices;
				m_indices[i++] = x + 2 + _slices + (y - 1) * _slices;
			}
		}
	}

	// polkappe unten - FIX
	for (int x = 0; x < _slices; x++)
	{
		if (x < _slices - 1)
		{
			m_indices[i++] = m_vertexCount - 1;
			m_indices[i++] = m_vertexCount - 1 - _slices + 1 + x;
			m_indices[i++] = m_vertexCount - 1 - _slices + x;
		}
		else
		{
			m_indices[i++] = m_vertexCount - 1;
			m_indices[i++] = m_vertexCount - 1 - _slices;
			m_indices[i++] = m_vertexCount - 1 - _slices + x;
		}
	}
}

CSphere::~CSphere()
{
}

void CSphere::Update(float _deltaTime)
{
	m_rotation.x -= 20 * _deltaTime;
	m_rotation.y += 14 * _deltaTime;
}
