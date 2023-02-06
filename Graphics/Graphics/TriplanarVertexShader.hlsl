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
};

struct VertexShaderOutput
{
	float4 pos : SV_POSITION;
	float3 normal : NORMAL;
	float3 posWorld : POSITION1;
	float3 posObject : POSITION2;
	float3 posCamera : POSITION3;
};


VertexShaderOutput TriplanarVertexShader(VertexShaderInput _in)
{
	VertexShaderOutput o;
	matrix mvp = mul(viewMatrix, worldMatrix);

	o.posCamera = mul(mvp, float4(_in.pos, 1.0f));	// 1 für positionen, 0 für Richtungen
	mvp = mul(projectionMatrix, mvp);
	o.posObject = _in.pos;
	o.pos = mul(mvp, float4(_in.pos, 1.0f));	// 1 für positionen, 0 für Richtungen
	o.posWorld = mul(worldMatrix, float4(_in.pos, 1.0f));
	o.normal = mul(worldMatrix, float4(_in.normal, 0.0f));	// Lichtberechnung in Worldspace

	return o;
}