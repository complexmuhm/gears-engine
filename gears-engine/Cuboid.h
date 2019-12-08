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
#include <memory>

class Cuboid : public Drawable, public Transform3D
{
public:
	Cuboid(D3DGFX& gfx, 
		float length, float height, float width, 
		float inv_aspr, float z_near, float z_far);

	void update(float dt) override;

private:
	float length, width, height;
	std::unique_ptr<VertexConstantBuffer<DirectX::XMMATRIX>> vertex_cbuffer;
	DirectX::XMFLOAT4X4 perspective_matrix;

};

