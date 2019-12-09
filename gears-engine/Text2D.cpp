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
		// Use fontdata7x9 for all text
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

	vertex_cbuffer = std::make_unique<VertexConstantBuffer<DirectX::XMMATRIX>>(gfx);
}

void Text2D::set_text(const std::string& text)
{
	// first call drawables reset to get rid of 
	// the old vertices and indices
	// TODO: add maybe another bindable type that allows editing of vertices and indices
	reset();
	this->text = text;
	length = 0.f; height = 0.f;
	const auto& fontdata = get_font_array();

	// clear the vertex buffer and reserver the amount of
	// vertices needed for the new text
	vertices.clear();
	vertices.reserve(4 * text.size());
	// the same for indices
	indices.clear();
	indices.reserve(4 * text.size());

	float startX = 0.f, startY = 0.f;
	float temp_z = 0.1f;

	float du = 7; //char width
	float dv = 9; //char height

	for (int i = 0; i < text.size(); ++i)
	{
		// ascii range is [0x20, 0x7F), clamp it if it goes beyond
		int char_pos = min(int(text[i] - 32), 0x7F - 0x20);
		ASCIICharUVCoord character = fontdata[char_pos];

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
		length += du;
	}
	height += dv;
	init_bindables();
}

std::string Text2D::get_text() const
{
	return text;
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

	DirectX::XMMATRIX transformation_matrix = get_transformation_matrix();
	DirectX::XMMATRIX orthogr_matrix = DirectX::XMLoadFloat4x4(ortho);
	DirectX::XMMATRIX result = 
		transformation_matrix * 
		orthogr_matrix;

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
