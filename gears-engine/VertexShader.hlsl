struct VertexShaderOut
{
	float4 color : Color;
	float4 position : SV_POSITION;
};

VertexShaderOut main(float3 position : Position, float4 color : Color)
{
	VertexShaderOut output;
	output.position = float4(position.xyz, 1.0f);
	output.color = color;
	return output;
}