#include "GraphicsPCH.h"
#include "TexturedSphere.h"
#include "Game.h"
#include "Helper.h"

CTexturedSphere::CTexturedSphere(LPCWSTR _filename, int _slices, int _heightSegments, XMFLOAT3 _pos)
	: CTexturedEntity(_filename, _pos)
{
	if (_slices < 2 || _heightSegments < 1)
	{
		m_invalid = true;
		return;
	}

	m_vertexCount = _slices * _heightSegments + 2 + _heightSegments;
	m_indexCount = _heightSegments * _slices * 6;

	m_vertices = new SVertexPosColor[m_vertexCount];
	m_indices = new WORD[m_indexCount];
	ZeroMemory(m_vertices, m_vertexCount * sizeof(SVertexPosColor));
	ZeroMemory(m_indices, m_indexCount * sizeof(WORD));

	XMFLOAT4 col = XMFLOAT4(2,2,2,1);

	int i = 0;
	m_vertices[i++] = { XMFLOAT3(0.0f, 0.5f, 0.0f),XMFLOAT3(0, 0.5f, 0), col, XMFLOAT2(0.5f, 0)};
	XMFLOAT3 pos;
	float yPos;
	float radius;
	for (float y = 0; y < _heightSegments; y++)
	{
		yPos = cos(((y + 1) / (_heightSegments + 1) * XM_PI));
		radius = sin(((y + 1) / (_heightSegments + 1) * XM_PI));
		for (float x = 0; x <= _slices; x++)
		{
			pos = XMFLOAT3(sin(x / _slices * XM_2PI) * 0.5f * radius,
				yPos * 0.5f,
				cos(x / _slices * XM_2PI) * 0.5f * radius);
			m_vertices[i++] = { pos, pos, col, XMFLOAT2(1-(x / _slices), y / _heightSegments)};
		}
	}
	m_vertices[i++] = { XMFLOAT3(0.0f, -0.5f, 0.0f),XMFLOAT3(0, -0.5f, 0), col, XMFLOAT2(0.5f, 1)};

	i = 0;
	// polkappe oben
	for (int x = 0; x < _slices; x++)
	{
		m_indices[i++] = 0;
		m_indices[i++] = x + 1;

		//if (x != _slices - 1)
		{
			m_indices[i++] = x + 2;
		}/*
		else
		{
			m_indices[i++] = 1;
		}*/
	}

	// mitte
	for (int y = 0; y < _heightSegments - 1; y++)
	{
		for (int x = 0; x < _slices; x++)
		{
			//if (x < _slices - 1)
			{
				m_indices[i++] = x + 1 + y * (_slices + 1);
				m_indices[i++] = x + 1 + (_slices + 1) + y * (_slices + 1);
				m_indices[i++] = x + 2 + y * (_slices + 1);

				m_indices[i++] = x + 2 + y * (_slices + 1);
				m_indices[i++] = x + 1 + (_slices + 1) + y * (_slices + 1);
				m_indices[i++] = x + 2 + (_slices + 1) + y * (_slices + 1);
			}
			/*else
			{
				m_indices[i++] = x + 1 + y * _slices;
				m_indices[i++] = x + 1 + _slices + y * _slices;
				m_indices[i++] = x + 2 + (y - 1) * _slices;

				m_indices[i++] = x + 2 + (y - 1) * _slices;
				m_indices[i++] = x + 1 + _slices + y * _slices;
				m_indices[i++] = x + 2 + _slices + (y - 1) * _slices;
			}*/
		}
	}

	// polkappe unten - FIX
	for (int x = 0; x < _slices; x++)
	{
		//if (x < _slices - 1)
		{
			m_indices[i++] = m_vertexCount - 1;
			m_indices[i++] = m_vertexCount - 1 - (_slices + 1) + 1 + x;
			m_indices[i++] = m_vertexCount - 1 - (_slices + 1) + x;
		}
		/*else
		{
			m_indices[i++] = m_vertexCount - 1;
			m_indices[i++] = m_vertexCount - 1 - _slices;
			m_indices[i++] = m_vertexCount - 1 - _slices + x;
		}*/
	}
}

CTexturedSphere::~CTexturedSphere()
{
}

void CTexturedSphere::Update(float _deltaTime)
{
	float rot = 0;
	if (IPM.GetKey(DIK_LEFTARROW))
	{
		rot = 1;
	}
	else if (IPM.GetKey(DIK_RIGHTARROW))
	{
		rot = -1;
	}

	m_rotation.y += rot * 23.5f * _deltaTime;

	rot = 0;
	if (IPM.GetKey(DIK_UPARROW))
	{
		rot = 1;
	}
	else if (IPM.GetKey(DIK_DOWNARROW))
	{
		rot = -1;
	}
	m_rotation.x += rot * 23.5f * _deltaTime;

	if (IPM.GetKey(DIK_SPACE))
	{
		m_time += _deltaTime;

		//m_scale = XMFLOAT3(1, 1, 1) + XMFLOAT3(0.5f, 0.5f, 0.5f) * sin(time);
		m_scale.x = 1 + 0.5f * sin(m_time);
		m_scale.y = 1 + 0.5f * sin(m_time * 0.456f);
		m_scale.z = 1 + 0.5f * sin(m_time * 1.235f);
	}
}
