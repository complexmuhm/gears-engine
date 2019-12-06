#pragma once
#include "Window.h"
#include "D3DGFX.h"

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
};

