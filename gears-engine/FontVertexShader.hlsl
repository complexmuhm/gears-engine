
cbuffer cbuf
{
	matrix trans;
};

struct VertexOut
{
	float4 position : SV_POSITION;
	float4 color : Color;
	float2 texcoord : Texcoord;
};

VertexOut main(float3 pos : Position, float4 color : Color, float2 texc : Texcoord)
{
	VertexOut output;

	output.position = mul(float4(pos.xyz, 1.0f), trans);
	output.color = color;
	output.texcoord = texc;

	return output;
}