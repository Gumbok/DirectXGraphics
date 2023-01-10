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
};

float4 SimplePixelShader(PixelShaderInput _in) : SV_TARGET
{
	float3 ambient = _in.color.xyz * AmbientColor.xyz * AmbientColor.a;

	// saturate - clampt werte im Bereich 0-1
	// normalize - verändert die Länge eines Vektors auf 1
	// cross - Kreuzprodukt float4 cross(float4 _a, float4 _b) gibt einen Vektor zurück im rechten Winkel auf beiden Inputs, 
	//				die Länge ist die Fläche des aufgespannten Parallelograms
	// dot - Punktprodukt float dot(float4 _a, float4 _b) gibt bei normalisierten Vektoren werte von -1 bis 1 aus, 
	//				beinhaltet den Innenwinkel

	float3 diffuse = saturate(_in.color.xyz 
								* DiffuseColor.xyz
								* dot(normalize(LightDir), normalize(_in.normal)) 
								* DiffuseColor.a);

	float3 specular = float3(0,0,0);


	return float4(saturate(ambient + diffuse + specular), _in.color.a);
}