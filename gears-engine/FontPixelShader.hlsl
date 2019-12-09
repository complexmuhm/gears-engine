Texture2D tex;
SamplerState smplr;

cbuffer cbuf
{
	float4 text_color;
};

struct VertexOut
{
	float4 position : SV_POSITION;
	float4 color : Color;
	float2 texcoord : Texcoord;
};

float4 main(VertexOut input) : SV_TARGET
{
	float4 color = tex.Sample(smplr, input.texcoord);
	if (color.r == 0.0f)
	{
		color = float4(0.0f, 0.0f, 0.0f, 0.0f);
	}
	else
	{
		color = text_color;
	}
	return color;
}