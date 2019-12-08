#include "Drawable.h"
#include "Bindable.h"
#include "IndexBuffer.h"
#include <cassert>

void Drawable::add_bindable(std::unique_ptr<Bindable> bindable)
{
	// Make sure to bind the index buffer with its own function
	assert(typeid(*bindable) != typeid(IndexBuffer));
	bindables.push_back(std::move(bindable));
}

void Drawable::add_index_buffer(std::unique_ptr<IndexBuffer> index_buffer)
{
	// Make sure not to bind two index buffers
	assert(this->cindex_buffer == nullptr);
	this->cindex_buffer = index_buffer.get();
	bindables.push_back(std::move(index_buffer));
}

void Drawable::draw(D3DGFX& gfx) const
{
	for (auto& b : bindables)
	{
		b->bind();
	}
	
	gfx.draw_indexed(cindex_buffer->count());
}

void Drawable::reset()
{
	cindex_buffer = nullptr;
	bindables.clear();
}
