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
};

struct VertexShaderOutput
{
	float4 pos : SV_POSITION;
	float3 normal : NORMAL;
	float4 color : COLOR;
};


VertexShaderOutput SimpleVertexShader(VertexShaderInput _in)
{
	VertexShaderOutput o;
	matrix mvp = mul(projectionMatrix, mul(viewMatrix, worldMatrix));

	o.pos = mul(mvp, float4(_in.pos, 1.0f));	// 1 für positionen, 0 für Richtungen
	o.normal = mul(worldMatrix, float4(_in.pos, 0.0f));	// Lichtberechnung in Worldspace
	o.color = _in.color;

	return o;
}