#include "GraphicsPCH.h"
#include "Entity2D.h"

CEntity2D::CEntity2D(XMFLOAT2 _pos)
{
	m_position = _pos;
	m_rotation = 0;
	m_size = XMFLOAT2(1,1);
}

CEntity2D::~CEntity2D()
{
}

bool CEntity2D::Initialize()
{
	return true;
}

void CEntity2D::Update(float _deltaTime)
{
}

void CEntity2D::CleanUp()
{
}
