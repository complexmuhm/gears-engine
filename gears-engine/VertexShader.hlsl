cbuffer cBuf
{
	matrix transformation;
};

struct VertexShaderOut
{
	float4 color : Color;
	float4 position : SV_POSITION;
};

VertexShaderOut main(float3 position : Position, float4 color : Color)
{
	VertexShaderOut output;
	float4 newpos = mul(float4(position.xyz, 1.0f), transformation);
	output.position = newpos;
	output.color = color;
	return output;
}