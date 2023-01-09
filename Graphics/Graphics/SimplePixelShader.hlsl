struct PixelShaderInput
{
	float4 pos : SV_POSITION;
	float4 color : COLOR;
};

float4 SimplePixelShader(PixelShaderInput _in) : SV_TARGET
{
	return _in.color;
}