Texture2D mainTex : register(t0);
SamplerState mainSampler : register(s0);


struct PixelShaderInput
{
	float4 pos : SV_POSITION;
	float4 color : COLOR;
	float2 uv : TEXCOORD;
};

float4 SkyboxPixelShader(PixelShaderInput _in) : SV_TARGET
{
	return _in.color * mainTex.Sample(mainSampler, _in.uv);
}