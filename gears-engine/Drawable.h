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
	virtual void draw(D3DGFX& gfx) const;
	// TODO: implement a not so expensive way of changing the pipeline
	void reset();

protected:
	const IndexBuffer* cindex_buffer;
	std::vector<std::unique_ptr<Bindable>> bindables;

};

