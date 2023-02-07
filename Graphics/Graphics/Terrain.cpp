#include "GraphicsPCH.h"
#include "Terrain.h"

CTerrain::CTerrain(LPCWSTR _controllFileName, LPCWSTR _fileNameR, LPCWSTR _fileNameG, LPCWSTR _fileNameB, LPCWSTR _fileNameA, LPCWSTR _fileNameHeight, LPCWSTR _controllNormal, int _xSize, int _zSize, XMFLOAT3 _pos)
	: CSplatMapEntity(_controllFileName, _fileNameR, _fileNameG, _fileNameB, _fileNameA, _fileNameHeight, _controllNormal, _pos)
{
	m_vertexCount = (_xSize + 1) * (_zSize + 1);
	m_indexCount = _xSize * _zSize * 2 * 3;

	m_vertices = new SVertexPosColor[m_vertexCount];
	m_indices = new WORD[m_indexCount];

	int i = 0;
	for (float z = 0; z < _zSize + 1; z++)
	{
		for (float x = 0; x < _xSize + 1; x++)
		{
			m_vertices[i++] = { XMFLOAT3(x * 0.1f, 0, z * 0.1f), XMFLOAT3(0,1,0), XMFLOAT4(1,1,1,1), XMFLOAT2(x / _xSize, 1 - (z / _zSize)) };
		}
	}

	i = 0;
	for (int z = 0; z < _zSize; z++)
	{
		for (int x = 0; x < _xSize; x++)
		{
			m_indices[i++] = x + (z * (_xSize + 1));			// 7
			m_indices[i++] = x + ((z + 1) * (_xSize + 1));		// 13
			m_indices[i++] = x + (z * (_xSize + 1)) + 1;		// 8

			m_indices[i++] = x + (z * (_xSize + 1)) + 1;		// 8
			m_indices[i++] = x + ((z + 1) * (_xSize + 1));		// 13
			m_indices[i++] = x + ((z + 1) * (_xSize + 1)) + 1;	// 14
		}
	}
}

CTerrain::~CTerrain()
{
}

void CTerrain::Update(float _deltatime)
{
	//m_position.x += 0.1f * _deltatime;
}
