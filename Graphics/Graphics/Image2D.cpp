#include "GraphicsPCH.h"
#include "Image2D.h"
#include "Game.h"

CImage2D::CImage2D(XMFLOAT2 _pos, LPCWSTR _fileName)
	: CEntity2D(_pos)
{
	m_textureData = ASM.LoadTexture(_fileName, D3D11_FILTER_MIN_MAG_MIP_POINT);
	ID3D11Texture2D* tex2D = (ID3D11Texture2D*) m_textureData->m_texture;

	D3D11_TEXTURE2D_DESC tDesc;
	tex2D->GetDesc(&tDesc);

	m_size.x = tDesc.Width;
	m_size.y = tDesc.Height;

	m_sourceRect.left = 0;
	m_sourceRect.top = 0;
	m_sourceRect.right = m_size.x;
	m_sourceRect.bottom = m_size.y;
}

CImage2D::~CImage2D()
{
}

void CImage2D::Render()
{
	CTM.m_spriteBatch->Draw(m_textureData->m_shaderRessourceView,
					m_position,
					&m_sourceRect,
					Colors::White,
					XMConvertToRadians(m_rotation));
}
