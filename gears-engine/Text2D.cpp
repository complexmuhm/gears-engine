#include "Text2D.h"
#include <fstream>
#include "Exceptions.h"
#include <cmath>

const std::vector<ASCIICharUVCoord>& get_font_array()
{
	static bool initialized = false;
	static std::vector<ASCIICharUVCoord> result;

	if (!initialized)
	{
		const unsigned int ascii_range = 0x7F - 0x20; // ASCII range
		result.reserve(ascii_range); 
		const std::string fontdata_file = "fontdata7x9";
		std::ifstream fontdata(fontdata_file);

		if (!fontdata.is_open())
		{
			throw EXCEPTION("Couldn't open fontdata file \"" 
				+ fontdata_file + "\".");
		}

		unsigned int ascii_value = 0;
		float u_start = 0.f, u_end = 0.f;
		float v_start = 0.f, v_end = 0.f;

		for (int i = 0; i < ascii_range; ++i)
		{
			fontdata >> ascii_value >> u_start >> v_start
									>> u_end >> v_end;
			result.emplace_back(u_start, u_end, v_start, v_end);
		}
		initialized = true;
	}

	return result;
}

Text2D::Text2D(D3DGFX& gfx,
	float x, float y, const std::string& text,
	const DirectX::XMFLOAT4X4* ortho)
	: gfx(gfx), ortho(ortho)
{
	px = x; py = y;
	set_text(text);

	//indices.clear();
	//vertices.clear();

	//ASCIICharUVCoord character = get_font_array()['H' - 32];

	//float du = character.u_end - character.u_start;
	//float dv = character.v_end - character.v_start;


	//float startX = px, startY = py, temp_z = 0.0f;
	//vertices.emplace_back(
	//	startX, startY, temp_z, 1.0f, 1.0f, 1.0f, 1.0f,
	//	character.u_start, character.v_start);
	//vertices.emplace_back(
	//	startX + du, startY, temp_z, 1.0f, 1.0f, 1.0f, 1.0f,
	//	character.u_end, character.v_start);
	//vertices.emplace_back(
	//	startX + du, startY + dv, temp_z, 1.0f, 1.0f, 1.0f, 1.0f,
	//	character.u_end, character.v_end);
	//vertices.emplace_back(
	//	startX, startY + dv, temp_z, 1.0f, 1.0f, 1.0f, 1.0f,
	//	character.u_start, character.v_end);

	//// setup the belongin indices
	//int i = 0;
	//indices.emplace_back(i + 3);
	//indices.emplace_back(i + 2);
	//indices.emplace_back(i);
	//indices.emplace_back(i + 2);
	//indices.emplace_back(i + 1);
	//indices.emplace_back(i);
	
	//float hlength = 0.5f, hheight = 0.5f, hwidth = 0.0f;
	//indices =
	//{
	//	0, 1, 2,
	//	0, 2, 3,
	//	1, 5, 6,
	//	1, 6, 2,
	//	5, 4, 7,
	//	5, 7, 6,
	//	4, 0, 3,
	//	4, 3, 7,
	//	4, 5, 1,
	//	4, 1, 0,
	//	3, 2, 6,
	//	3, 6, 7
	//};
	//vertices =
	//{
	//	{ -hlength,  hheight,  -hwidth, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f},
	//	{  hlength,  hheight,  -hwidth, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f},
	//	{  hlength, -hheight,  -hwidth, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f},
	//	{ -hlength, -hheight,  -hwidth, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f},
	//	{ -hlength,  hheight,   hwidth, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f},
	//	{  hlength,  hheight,   hwidth, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f},
	//	{  hlength, -hheight,   hwidth, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f},
	//	{ -hlength, -hheight,   hwidth, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f},
	//};
	//

	init_bindables();

	vertex_cbuffer = std::make_unique<VertexConstantBuffer<DirectX::XMMATRIX>>(gfx);
}

void Text2D::set_text(const std::string& text)
{
	// first call drawables reset to get rid of 
	// the old vertices and indices
	// TODO: add maybe another bindable type that allows editing of vertices and indices
	reset();
	this->text = text;
	const auto& fontdata = get_font_array();

	// clear the vertex buffer and reserver the amount of
	// vertices needed for the new text
	vertices.clear();
	//vertices.reserve(4 * text.size());
	// the same for indices
	indices.clear();
	indices.reserve(4 * text.size());

	float startX = px, startY = py;
	float temp_z = 0.0f;
	for (int i = 0; i < text.size(); ++i)
	{
		// ascii range is [0x20, 0x7F), clamp it if it goes beyond
		int char_pos = min(int(text[i] - 32), 0x7F - 0x20);
		ASCIICharUVCoord character = fontdata[char_pos];

		float du = character.u_end - character.u_start;
		float dv = character.v_end - character.v_start;

		// Setup vertices and tex coords
		vertices.emplace_back(
			startX, startY, temp_z, 1.0f, 1.0f, 1.0f, 1.0f,
			character.u_start, character.v_start);
		vertices.emplace_back(
			startX + du, startY, temp_z, 1.0f, 1.0f, 1.0f, 1.0f,
			character.u_end, character.v_start);
		vertices.emplace_back(
			startX + du, startY - dv, temp_z, 1.0f, 1.0f, 1.0f, 1.0f,
			character.u_end, character.v_end);
		vertices.emplace_back(
			startX, startY - dv, temp_z, 1.0f, 1.0f, 1.0f, 1.0f,
			character.u_start, character.v_end);

		// setup the belongin indices
		UINT base = 4 * i;
		indices.emplace_back(base);
		indices.emplace_back(base + 1);
		indices.emplace_back(base + 2);
		indices.emplace_back(base);
		indices.emplace_back(base + 2);
		indices.emplace_back(base + 3);

		startX += du;
	}
}

void Text2D::update(float dt)
{
}

void Text2D::draw(D3DGFX& gfx) const
{
	for (auto& b : bindables)
	{
		b->bind();
	}

	DirectX::XMFLOAT4 pos = DirectX::XMFLOAT4(0.0f, 0.0f, -1.0f, 0.0f);
	DirectX::XMFLOAT4 focus = DirectX::XMFLOAT4(0.0f, 0.0f, 1.0f, 0.0f);
	DirectX::XMFLOAT4 up = DirectX::XMFLOAT4(0.0f, 1.0f, 0.0f, 0.0f);
	DirectX::XMMATRIX m =
		DirectX::XMMatrixLookAtLH(
			DirectX::XMLoadFloat4(&pos),
			DirectX::XMLoadFloat4(&focus),
			DirectX::XMLoadFloat4(&up));

	DirectX::XMMATRIX proj = DirectX::XMMatrixPerspectiveLH(1280, 720, 0.5f, 100.f);
	DirectX::XMMATRIX id = DirectX::XMMatrixIdentity();

	DirectX::XMMATRIX result = 
		get_transformation_matrix() *
		DirectX::XMMatrixTranslation(0.f, 0.f, 1.0f) *
		DirectX::XMLoadFloat4x4(ortho);

	vertex_cbuffer->update(
		DirectX::XMMatrixTranspose(result));
	vertex_cbuffer->bind();

	gfx.draw_indexed(cindex_buffer->count());

}

DirectX::XMMATRIX Text2D::get_transformation_matrix() const
{
	return 
		Transform2D::get_transformation_matrix();
}

void Text2D::init_bindables()
{
	const wchar_t* vertex_shader_binary = L"FontVertexShader.cso";
	const wchar_t* pixel_shader_binary = L"FontPixelShader.cso";
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
	std::unique_ptr<Texture> texture = 
		std::make_unique<Texture>(gfx, "ascii_bmp_7x9.png");
	std::unique_ptr<Sampler> sampler =
		std::make_unique<Sampler>(gfx);

	add_index_buffer(std::move(index_buffer));
	add_bindable(std::move(vertex_buffer));
	add_bindable(std::move(vertex_shader));
	add_bindable(std::move(input_layout));
	add_bindable(std::move(pixel_shader));
	add_bindable(std::move(topology));
	add_bindable(std::move(texture));
	add_bindable(std::move(sampler));
}
