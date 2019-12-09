#include "Cuboid.h"

Cuboid::Cuboid(D3DGFX& gfx, 
	float length, float height, float width, 
	const DirectX::XMFLOAT4X4* view,
	const DirectX::XMFLOAT4X4* persp)
	: Transform3D(view, persp)
{
	this->length = length;
	this->height = height;
	this->width = width;

	std::vector<UINT> indices =
	{
		0, 1, 2,
		0, 2, 3,
		1, 5, 6,
		1, 6, 2,
		5, 4, 7,
		5, 7, 6,
		4, 0, 3,
		4, 3, 7,
		4, 5, 1,
		4, 1, 0,
		3, 2, 6,
		3, 6, 7
	};

	float hlength = length / 2.f;
	float hheight = height / 2.f;
	float hwidth = width / 2.f;

	std::vector<Vertex> vertices =
	{
		{ -hlength,  hheight,  -hwidth, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f},
		{  hlength,  hheight,  -hwidth, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f},
		{  hlength, -hheight,  -hwidth, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f},
		{ -hlength, -hheight,  -hwidth, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f},
		{ -hlength,  hheight,   hwidth, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f},
		{  hlength,  hheight,   hwidth, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f},
		{  hlength, -hheight,   hwidth, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f},
		{ -hlength, -hheight,   hwidth, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f},
	};

	const wchar_t* vertex_shader_binary = L"VertexShader.cso";
	const wchar_t* pixel_shader_binary = L"PixelShader.cso";
	D3D11_PRIMITIVE_TOPOLOGY top = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;

	std::unique_ptr<IndexBuffer> index_buffer = 
		std::make_unique<IndexBuffer>(gfx, indices);
	std::unique_ptr<VertexBuffer> vertex_buffer =
		std::make_unique<VertexBuffer>(gfx, vertices);
	std::unique_ptr<VertexShader> vertex_shader =
		std::make_unique<VertexShader>(gfx, vertex_shader_binary);
	std::unique_ptr<InputLayout> input_layout = 
		std::make_unique<InputLayout>(gfx, vertex_shader->get_compiled_shader());
	std::unique_ptr<PixelShader> pixel_shader = 
		std::make_unique<PixelShader>(gfx, pixel_shader_binary);
	std::unique_ptr<Topology> topology = 
		std::make_unique<Topology>(gfx, top);

	add_index_buffer(std::move(index_buffer));
	add_bindable(std::move(vertex_buffer));
	add_bindable(std::move(vertex_shader));
	add_bindable(std::move(input_layout));
	add_bindable(std::move(pixel_shader));
	add_bindable(std::move(topology));

	vertex_cbuffer = std::make_unique<VertexConstantBuffer<DirectX::XMMATRIX>>(gfx);
	
}

void Cuboid::update(float dt)
{
	// Update the constant buffer
	vertex_cbuffer->update(
		DirectX::XMMatrixTranspose(
			get_transformation_matrix() *
			DirectX::XMLoadFloat4x4(perspective_matrix)));
	// and manually bind it
	vertex_cbuffer->bind();
}
