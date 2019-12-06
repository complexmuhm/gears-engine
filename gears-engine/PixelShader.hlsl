struct VertexShaderOut
{
	float4 color : Color;
	float4 position : SV_POSITION;
};

float4 main(VertexShaderOut input) : SV_TARGET
{
	return input.color;
}