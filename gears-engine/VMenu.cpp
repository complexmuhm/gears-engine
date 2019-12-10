#include "VMenu.h"

VMenu::VMenu(
	D3DGFX& gfx, 
	const std::string& title, 
	std::vector<std::unique_ptr<Button>> buttons, 
	const DirectX::XMFLOAT4X4* view, 
	const DirectX::XMFLOAT4X4* ortho)
	: Widget(view, ortho)
	, title(gfx, title, view, ortho)
	//, buttons(std::move(buttons))
	, organizer(view, ortho)
{
	this->buttons = std::move(buttons);

	// place the widgets into the organizer and the general
	// list of widgets (for processing)
	widgets.emplace_back(&this->title);
	organizer.add_widget(&this->title);
	for (auto& b : this->buttons)
	{
		widgets.emplace_back(b.get());
		organizer.add_widget(b.get());
	}

	this->title.bind_right(std::bind(&VMenu::toggle, this));
}

void VMenu::process_events(Keyboard::Event key_event, Mouse::Event mouse_event)
{
	if (mouse_event.type == Mouse::Event::Type::Move)
	{
		old_mpos = new_mpos;
		new_mpos = mouse_event.position;

		if (title.pressed())
		{
			move(Vector2f(new_mpos - old_mpos));
		}
	}

	Widget::process_events(key_event, mouse_event);
	for (auto& w : widgets)
	{
		w->process_events(key_event, mouse_event);
	}
}

void VMenu::update(float dt)
{
	for (auto& w : widgets)
	{
		if (w->visible())
		{
			w->update(dt);
		}
	}
}

void VMenu::draw(D3DGFX& gfx)
{
	for (auto& w : widgets)
	{
		if (w->visible())
		{
			w->draw(gfx);
		}
	}
}

void VMenu::set_position(float x, float y, Transform2D::RELPOS relative_pos)
{
	Transform2D::set_position(x, y, relative_pos);
	organizer.set_position(x, y, relative_pos);
}

void VMenu::set_scale(float x, float y)
{
	Transform2D::set_scale(x, y);
	organizer.set_scale(x, y);
}

void VMenu::set_rotation(float angle)
{
	Transform2D::set_rotation(angle);
	organizer.set_rotation(angle);
}

void VMenu::set_dimension(float length, float height)
{
	Transform2D::set_dimension(length, height);
	organizer.set_dimension(length, height);
}

void VMenu::toggle()
{
	if (is_minimized)
	{
		maximize();
		is_minimized = false;
	}
	else
	{
		minimize();
		is_minimized = true;
	}
}

void VMenu::minimize()
{
	for (auto& b : buttons)
	{
		b->set_visibility(false);
	}
}

void VMenu::maximize()
{
	for (auto& b : buttons)
	{
		b->set_visibility(true);
	}
}
