Texture2D HeightTex : register(t0);
SamplerState heightSampler : register(s0);

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

struct VertexShaderInput
{
	float3 pos : POSITION;
	float3 normal : NORMAL;
	float4 color : COLOR;
	float2 uv : TEXCOORD;
};

struct VertexShaderOutput
{
	float4 pos : SV_POSITION;
	float3 normal : NORMAL;
	float4 color : COLOR;
	float4 posWorld : POSITION1;
	float2 uv : TEXCOORD;
};


VertexShaderOutput SplatMapVertexShader(VertexShaderInput _in)
{
	VertexShaderOutput o;
	matrix mvp = mul(projectionMatrix, mul(viewMatrix, worldMatrix));

	o.pos = mul(mvp, float4(_in.pos + float3(0,1,0) * HeightTex.SampleLevel(heightSampler, _in.uv * 2, 0).r, 1.0f));	// 1 für positionen, 0 für Richtungen
	o.posWorld = mul(worldMatrix, float4(_in.pos, 1.0f));
	o.normal = mul(worldMatrix, float4(_in.normal, 0.0f));	// Lichtberechnung in Worldspace
	o.color = _in.color;
	o.uv = _in.uv;

	return o;
}