#pragma once

#include <vector>
#include <memory>

class Bindable;
class IndexBuffer;
class D3DGFX;

class Drawable
{
public:
	Drawable() = default;
	Drawable(const Drawable&) = delete;
	virtual ~Drawable() = default;
	
	void add_bindable(std::unique_ptr<Bindable> bindable);
	void add_index_buffer(std::unique_ptr<IndexBuffer> index_buffer);

	virtual void update(float dt) = 0;
	// TODO: maybe save a reference to gfx object in ctor?
	void draw(D3DGFX& gfx) const;

private:
	const IndexBuffer* index_buffer;
	std::vector<std::unique_ptr<Bindable>> bindables;

};

