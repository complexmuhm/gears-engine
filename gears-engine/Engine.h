#pragma once
#include "Window.h"
#include "D3DGFX.h"
#include "EdgeCuboid.h"
#include "Text2D.h"

class Engine
{
public:
	Engine(Vector2i size, const std::wstring& title);
	void run();

private:
	void process_events();
	void update();
	void render();

private:
	Window window;
	D3DGFX gfx;

	const float FOV = 100.f;
	const float z_near = 0.5f;
	const float z_far = 1000.f;

	const float z_nearGUI = 0.0f;
	const float z_farGUI = 100.f;

	DirectX::XMFLOAT4X4 view;
	DirectX::XMFLOAT4X4 ortho;
	DirectX::XMFLOAT4X4 proj;

	std::unique_ptr<Text2D> label;
	std::unique_ptr<EdgeCuboid> edge_cuboid;
};

