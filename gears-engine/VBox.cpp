#include "VBox.h"

void VBox::add_widget(std::unique_ptr<Widget> widget)
{
	widgets.emplace_back(std::move(widget));
	adjust_widgets();
}

void VBox::set_position(float x, float y, Transform2D::RELPOS relative_pos)
{
	Transform2D::set_position(x, y, relative_pos);
	for (auto& w : widgets)
	{
		w->set_position(x, y, relative_pos);
	}
	adjust_widgets();
}

void VBox::set_scale(float x, float y)
{
	Transform2D::set_scale(x, y);
	for (auto& w : widgets)
	{
		w->set_scale(x, y);
	}
	adjust_widgets();
}

void VBox::set_rotation(float angle)
{
	Transform2D::set_rotation(angle);
	for (auto& w : widgets)
	{
		w->set_rotation(angle);
	}
	adjust_widgets();
}

void VBox::set_dimension(float length, float height)
{
	Transform2D::set_dimension(length, height);
	for (auto& w : widgets)
	{
		w->set_dimension(length, height);
	}
	adjust_widgets();
}

// TODO: maybe set the label always as the first element and provide text input for the label name
VBox::VBox(const DirectX::XMFLOAT4X4* view, const DirectX::XMFLOAT4X4* ortho)
	: Widget(view, ortho)
{
}

void VBox::process_events(Keyboard::Event key_event, Mouse::Event mouse_event)
{
	if (mouse_event.type == Mouse::Event::Type::Move)
	{
		old_mpos = new_mpos;
		new_mpos = mouse_event.position;
		if (widgets.front()->pressed())
		{
			Vector2f diff = Vector2f(new_mpos - old_mpos);
			move(diff);
		}
	}
	Widget::process_events(key_event, mouse_event);
	for (auto& w : widgets)
	{
		w->process_events(key_event, mouse_event);
	}
}

void VBox::update(float dt)
{
	for (auto& w : widgets)
	{
		w->update(dt);
	}
}

void VBox::draw(D3DGFX& gfx)
{
	for (auto& w : widgets)
	{
		w->draw(gfx);
	}
}

void VBox::adjust_widgets()
{
	// the first widgets top left coords determine
	// the VBoxes coordinate
	Vector2f first_top_left = widgets.front()->get_position();
	px = first_top_left.x;
	py = first_top_left.y;

	// find the widget with the greatest length in the vector
	// and use it to position the rest of the widgets
	float max_length = 0.f;
	for (auto& w : widgets)
	{
		Vector2f dim = w->get_real_dimension();
		if (dim.x >= max_length)
			max_length = dim.x;
	}

	Vector2f first_bottom_center = widgets.front()->get_position(Transform2D::BOTTOM_CENTER);
	Vector2f first_size = widgets.front()->get_real_dimension();
	// calculate the center x pos based on the maximum widget length in the vector
	// divide the difference in length by two since it is affected only half as much on a change
	float real_max_length_pos = first_bottom_center.x + (max_length - first_size.x) / 2.f;
	// set the length of the VBox based on the max widget length
	length = max_length / sx;
	// set the first new pos
	Vector2f new_pos = { real_max_length_pos, py };
	
	// Adjust each following widget relative to its precursor
	// and accumulate the VBox's height
	height = 0.f;
	for (auto& w : widgets)
	{
		// add the curr widgets height to the VBox's height
		Vector2f w_dimension = w->get_dimension();
		height += w_dimension.y;

		// position the curr widget
		w->set_position(new_pos, Transform2D::TOP_CENTER);
		new_pos.y = w->get_position(Transform2D::BOTTOM_CENTER).y;
	}
}
