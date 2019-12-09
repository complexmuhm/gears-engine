#pragma once

#include "Drawable.h"
#include "Transform.h"

#include "IndexBuffer.h"
#include "VertexBuffer.h"
#include "VertexShader.h"
#include "PixelShader.h"
#include "Topology.h"
#include "InputLayout.h"
#include "ConstantBuffer.h"
#include "Texture.h"
#include "Sampler.h"
#include <memory>

struct ASCIICharUVCoord 
{
	ASCIICharUVCoord(float us, float ue, float vs, float ve)
		: u_start(us), u_end(ue)
		, v_start(vs), v_end(ve)
	{}
	float u_start, u_end;
	float v_start, v_end;
};

const std::vector<ASCIICharUVCoord>& get_font_array();

class Text2D : public Drawable, public Transform2D
{
public:
	Text2D(D3DGFX& gfx, 
		float x, float y, const std::string& text,
		const DirectX::XMFLOAT4X4* ortho);
	Text2D(const Text2D&) = delete;
	Text2D& operator=(const Text2D&) = delete;

	void set_text(const std::string& text);

	float get_length() const;
	float get_height() const;
	std::string get_text() const;

	virtual void update(float dt) override;
	virtual void draw(D3DGFX& gfx) const override;

	virtual DirectX::XMMATRIX get_transformation_matrix() const override;

private:
	void init_bindables();

private:
	std::string text;

	D3DGFX& gfx;
	const DirectX::XMFLOAT4X4* ortho;
	std::vector<UINT> indices;
	std::vector<Vertex> vertices;

	std::unique_ptr<VertexConstantBuffer<DirectX::XMMATRIX>> vertex_cbuffer;

};

