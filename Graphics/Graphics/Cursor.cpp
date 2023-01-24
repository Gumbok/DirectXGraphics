#include "GraphicsPCH.h"
#include "Cursor.h"
#include "Game.h"

CCursor::CCursor(LPCWSTR _fileName)
	: CImage2D(XMFLOAT2(), _fileName)
{
	m_size.x = m_size.x / 2;

	m_sourceRect.left = 0;
	m_sourceRect.right = m_size.x;
}

CCursor::~CCursor()
{
}

void CCursor::Update(float _deltaTime)
{
	m_position = IPM.GetMousePos();

	if (IPM.GetMouseKey(0))
	{
		m_sourceRect.left = m_size.x;
		m_sourceRect.right = m_size.x * 2;
	}
	else
	{
		m_sourceRect.left = 0;
		m_sourceRect.right = m_size.x;
	}
}