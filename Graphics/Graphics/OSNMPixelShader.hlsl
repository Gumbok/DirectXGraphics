Texture2D mainTex : register(t0);
SamplerState mainSampler : register(s0);
Texture2D normalTex : register(t1);
SamplerState normalSampler : register(s1);

cbuffer Light : register(b0)
{
	float4 AmbientColor;
	float4 DiffuseColor;
	float4 SpecularColor;
	float3 LightDir;
	float filler;
	float3 CameraPos;
}

cbuffer PerApplication : register(b1)
{
	matrix worldMatrix;			// Umrechnung von Object zu World
}

struct PixelShaderInput
{
	float4 pos : SV_POSITION;
	//float3 normal : NORMAL;
	float4 color : COLOR;
	float4 posWorld : POSITION1;
	float2 uv : TEXCOORD;
};

float4 OSNMPixelShader(PixelShaderInput _in) : SV_TARGET
{
	float4 col = _in.color * mainTex.Sample(mainSampler, _in.uv);

	float3 ambient = col.xyz * AmbientColor.xyz * AmbientColor.a;

	// saturate - clampt werte im Bereich 0-1
	// normalize - verändert die Länge eines Vektors auf 1
	// cross - Kreuzprodukt float4 cross(float4 _a, float4 _b) gibt einen Vektor zurück im rechten Winkel auf beiden Inputs, 
	//				die Länge ist die Fläche des aufgespannten Parallelograms
	// dot - Punktprodukt float dot(float4 _a, float4 _b) gibt bei normalisierten Vektoren werte von -1 bis 1 aus, 
	//				beinhaltet den Innenwinkel

	float3 normal = normalTex.Sample(normalSampler, _in.uv);
	normal = normalize(normal * 2 - float3(1, 1, 1));
	normal = mul(worldMatrix, float4(normal, 0));

	float3 diffuse = saturate(col.xyz
								* DiffuseColor.xyz
								* dot(normalize(-LightDir), normal)
								* DiffuseColor.a);

	// Hilfsvektor ist der durchschnitt aus Lichtrichtung und Punkt zu Kamera
	// dieser wird mit der normalen verglichen um bei übereinstimmung viel zu glänzen
	float3 halfVector = normalize(normalize(CameraPos - _in.posWorld.xyz) + normalize(-LightDir));

	float dotP = dot(halfVector, normal);
	dotP = pow(dotP, 100);

	float3 specular = saturate(SpecularColor.xyz * dotP * SpecularColor.w);


	return float4(saturate(ambient + diffuse + specular), _in.color.a);
}