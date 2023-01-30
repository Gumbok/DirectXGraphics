Texture2D controllTex : register(t0);
Texture2D RTex : register(t1);
Texture2D GTex : register(t2);
Texture2D BTex : register(t3);
Texture2D ATex : register(t4);

SamplerState controllSampler : register(s0);
SamplerState RSampler : register(s1);
SamplerState GSampler : register(s2);
SamplerState BSampler : register(s3);
SamplerState ASampler : register(s4);

cbuffer Light : register(b0)
{
	float4 AmbientColor;
	float4 DiffuseColor;
	float4 SpecularColor;
	float3 LightDir;
	float filler;
	float3 CameraPos;
}

struct PixelShaderInput
{
	float4 pos : SV_POSITION;
	float3 normal : NORMAL;
	float4 color : COLOR;
	float4 posWorld : POSITION1;
	float2 uv : TEXCOORD;
};

float4 SplatMapPixelShader(PixelShaderInput _in) : SV_TARGET
{
	float4 controllCol = controllTex.Sample(controllSampler, _in.uv);
	float3 colR = RTex.Sample(RSampler, _in.posWorld.xz * 8).rgb;
	float3 colG = GTex.Sample(GSampler, _in.posWorld.xz * 11).rgb;
	float3 colB = BTex.Sample(BSampler, _in.posWorld.xz * 17).rgb;
	float3 colA = ATex.Sample(ASampler, _in.posWorld.xz * 13).rgb;


	float3 col = _in.color * (colR * controllCol.r * controllCol.r +
								colG * controllCol.g * controllCol.g +
								colB * controllCol.b * controllCol.b/* +*/)
					/ (controllCol.r * controllCol.r + controllCol.g * controllCol.g+ controllCol.b * controllCol.b);
				//				colA * controllCol.a * controllCol.a) 
				//	/ (controllCol.r * controllCol.r+ controllCol.g * controllCol.g + controllCol.b * controllCol.b+ controllCol.a * controllCol.a);

	return float4(col, 1);

	float3 ambient = col.xyz * AmbientColor.xyz * AmbientColor.a;

	// saturate - clampt werte im Bereich 0-1
	// normalize - verändert die Länge eines Vektors auf 1
	// cross - Kreuzprodukt float4 cross(float4 _a, float4 _b) gibt einen Vektor zurück im rechten Winkel auf beiden Inputs, 
	//				die Länge ist die Fläche des aufgespannten Parallelograms
	// dot - Punktprodukt float dot(float4 _a, float4 _b) gibt bei normalisierten Vektoren werte von -1 bis 1 aus, 
	//				beinhaltet den Innenwinkel

	float3 diffuse = saturate(col.xyz
								* DiffuseColor.xyz
								* dot(normalize(-LightDir), normalize(_in.normal))
								* DiffuseColor.a);

	// Hilfsvektor ist der durchschnitt aus Lichtrichtung und Punkt zu Kamera
	// dieser wird mit der normalen verglichen um bei übereinstimmung viel zu glänzen
	float3 halfVector = normalize(normalize(CameraPos - _in.posWorld.xyz) + normalize(-LightDir));

	float dotP = dot(halfVector, normalize(_in.normal));
	dotP = pow(dotP, 100);

	float3 specular = saturate(SpecularColor.xyz * dotP * SpecularColor.w);


	return float4(saturate(ambient + diffuse + specular), _in.color.a);
}