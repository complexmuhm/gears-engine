#pragma once

#include "Bindable.h"
#include <vector>

struct Vertex
{
	Vertex(
		float x, float y, float z,
		float r, float g, float b, float a,
		float u, float v)
		: x(x), y(y), z(z)
		, r(r), g(g), b(b), a(a)
		, u(u), v(v)
	{}
	float x, y, z;
	float r, g, b, a;
	float u, v;
};

class VertexBuffer : public Bindable
{
public:
	VertexBuffer(D3DGFX& gfx, const std::vector<Vertex>& vertices);
	
	void bind() override;

private:
	wrl::ComPtr<ID3D11Buffer> vertex_buffer;

};

