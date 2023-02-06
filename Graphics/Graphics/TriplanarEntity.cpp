#include "GraphicsPCH.h"
#include "TriplanarEntity.h"
#include "Game.h"

CTriplanarEntity::CTriplanarEntity(LPCWSTR _fileName, XMFLOAT3 _pos)
 : CEntity(_pos)
{
    m_textureData = ASM.LoadTexture(_fileName);

}

CTriplanarEntity::~CTriplanarEntity()
{
}

void CTriplanarEntity::Render()
{
    // Prepare Object to World Matrix
    XMMATRIX scale = XMMatrixScaling(m_scale.x, m_scale.y, m_scale.z);
    XMMATRIX rotation = XMMatrixRotationRollPitchYaw(
        XMConvertToRadians(m_rotation.x),
        XMConvertToRadians(m_rotation.y),
        XMConvertToRadians(m_rotation.z));
    XMMATRIX translation = XMMatrixTranslation(m_position.x,
        m_position.y, m_position.z);

    // Saufen, Rauchen, Taxifahren
    m_objectConstantBuffer.m_matrix = scale * rotation * translation;

    DXS.m_deviceContext->UpdateSubresource(DXS.m_constantBuffers[CB_OBJECT],
        0, nullptr, &m_objectConstantBuffer, 0, 0);

    unsigned int offset = 0;
    unsigned int stride = sizeof(SVertexPosColor);

    // Input Assembler
    DXS.m_deviceContext->IASetInputLayout(DXS.m_triplanarInputLayout);
    DXS.m_deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    DXS.m_deviceContext->IASetVertexBuffers(0, 1, &m_vertexBuffer, &stride, &offset);
    DXS.m_deviceContext->IASetIndexBuffer(m_indexBuffer, DXGI_FORMAT_R16_UINT, offset);

    // Vertex Shader
    DXS.m_deviceContext->VSSetConstantBuffers(0, 3, DXS.m_constantBuffers);
    DXS.m_deviceContext->VSSetShader(DXS.m_triplanarVertexShader, nullptr, 0);

    // Rasterizer
    DXS.m_deviceContext->RSSetState(DXS.m_currentRasterrizerState);
    DXS.m_deviceContext->RSSetViewports(1, &DXS.m_viewPort);

    // Pixel Shader
    DXS.m_deviceContext->PSSetConstantBuffers(0, 1, &DXS.m_constantBuffers[CB_LIGHT]);
    DXS.m_deviceContext->PSSetShader(DXS.m_triplanarPixelShader, nullptr, 0);
    DXS.m_deviceContext->PSSetSamplers(0, 1, &m_textureData->m_textureSampler);
    DXS.m_deviceContext->PSSetShaderResources(0, 1, &m_textureData->m_shaderRessourceView);

    // Output Merger
    DXS.m_deviceContext->OMSetRenderTargets(1, &DXS.m_renderTargetView, DXS.m_depthStencilView);
    DXS.m_deviceContext->OMSetDepthStencilState(DXS.m_depthStencilState, 1);

    // Objekt zeichnen
    DXS.m_deviceContext->DrawIndexed(m_indexCount, 0, 0);
}
