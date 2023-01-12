#include "GraphicsPCH.h"
#include "Sphere.h"

CSphere::CSphere(XMFLOAT4 _col, int _slices, int _heightSegments, XMFLOAT3 _pos)
	: CEntity(_pos)
{
	if (_slices < 2 || _heightSegments < 3)
	{
		m_invalid = true;
		return;
	}

	m_vertexCount = (1 + _slices) * 2;
	m_indexCount = (_slices * 3) * 2;

	m_vertices = new SVertexPosColor[m_vertexCount];
	m_indices = new WORD[m_indexCount];

	int i = 0;
	// polkappe oben
	m_vertices[i++] = { XMFLOAT3(0.0f, 0.5f, 0.0f),XMFLOAT3(0, 0.5f, 0), _col };
	XMFLOAT3 pos;
	for (float x = 0; x < _slices; x++)
	{
		pos = XMFLOAT3(sin(x/_slices * XM_2PI) * 0.5f, cos((_heightSegments - 3) * XM_2PI) * 0.5f, cos(x / _slices * XM_2PI) * 0.5f);
		m_vertices[i++] = { pos, pos, _col };
	}

	m_vertices[i++] = { XMFLOAT3(0.0f, -0.5f, 0.0f),XMFLOAT3(0, -0.5f, 0), _col };
	for (float x = 0; x < _slices; x++)
	{
		pos = XMFLOAT3(sin(x / _slices * XM_2PI) * 0.5f, -cos((_heightSegments - 3) * XM_2PI) * 0.5f, cos(x / _slices * XM_2PI) * 0.5f);
		m_vertices[i++] = { pos, pos, _col };
	}


	i = 0;
	// polkappe oben
	for (int x = 0; x < _slices; x++)
	{
		m_indices[i++] = _slices +1;
		m_indices[i++] = _slices + 1 + x + 1;

		if (x != _slices - 1)
		{
			m_indices[i++] = _slices + 1 + x + 2;
		}
		else
		{
			m_indices[i++] = _slices + 2;
		}
	}

	// polkappe unten
	for (int x = 0; x < _slices; x++)
	{
		m_indices[i++] = 0;
		if (x != _slices - 1)
		{
			m_indices[i++] = x + 2;
		}
		else
		{
			m_indices[i++] = 1;
		}

		m_indices[i++] = x + 1;

	}
}

CSphere::~CSphere()
{
}

void CSphere::Update(float _deltaTime)
{
	m_rotation.x += -35 * _deltaTime;
	m_rotation.y += 14 * _deltaTime;
}
