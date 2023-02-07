cbuffer PerApplication : register(b0)
{
	matrix projectionMatrix;	// Umrechnung von Camera zu Screenspace
}

cbuffer PerFrame : register(b1)
{
	matrix viewMatrix;			// Umrechnung von World zu Camera
}

cbuffer PerObject : register(b2)
{
	matrix worldMatrix;			// Umrechnung von Object zu World
}

cbuffer Light : register(b3)
{
	float4 AmbientColor;
	float4 DiffuseColor;
	float4 SpecularColor;
	float3 LightDir;
	float filler;
	float3 CameraPos;
}

struct VertexShaderInput
{
	float3 pos : POSITION;
	float4 color : COLOR;
	float2 uv : TEXCOORD;
};

struct VertexShaderOutput
{
	float4 pos : SV_POSITION;
	float4 color : COLOR;
	float2 uv : TEXCOORD;
};


VertexShaderOutput SkyboxVertexShader(VertexShaderInput _in)
{
	VertexShaderOutput o;

	//float4 pos = mul(float4(_in.pos, 1), worldMatrix);
	//pos.xyz += CameraPos ;
	float4 pos = float4(_in.pos + CameraPos, 1);

	matrix mvp = mul(projectionMatrix, viewMatrix);

	o.pos = mul(mvp, pos);	// 1 für positionen, 0 für Richtungen
	//o.pos.z = 1;
	o.color = _in.color;
	o.uv = _in.uv;

	return o;
}