cbuffer cBuf
{
	float4 color[6];
};

struct VertexShaderOut
{
	float4 color : Color;
	float4 position : SV_POSITION;
};

float4 main(uint uid : SV_PRIMITIVEID) : SV_TARGET
{
	return color[uid / 2];
}