#pragma once

struct SStandardConstantBuffer
{
	XMMATRIX m_matrix;
};

struct SLightConstantBuffer
{
	XMFLOAT4 AmbientColor;

	XMFLOAT4 DiffuseColor;
	XMFLOAT3 LightDir;

	XMFLOAT4 SpecularColor;
	XMFLOAT3 CameraPos;
};