#pragma once

#include "Bindable.h"
#include <vector>

struct Vertex
{
	float x, y, z;
	float r, g, b, a;
};

class VertexBuffer : public Bindable
{
public:
	VertexBuffer(D3DGFX& gfx, std::vector<Vertex> vertices);
	
	void bind() override;

private:
	wrl::ComPtr<ID3D11Buffer> vertex_buffer;

};

