#include "Mouse.h"

void Mouse::on_move(Vector2i position)
{
	this->position = position;
	event_buffer.emplace(Mouse::Event::Move, position, false, false, 0);
	trim_buffer();
}

void Mouse::on_left_pressed(Vector2i position)
{
	this->position = position;
	l_pressed = true;
	event_buffer.emplace(Mouse::Event::LMouseButtonPressed, position, true, false, 0);
	trim_buffer();
}

void Mouse::on_left_released(Vector2i position)
{
	this->position = position;
	l_pressed = false;
	event_buffer.emplace(Mouse::Event::LMouseButtonReleased, position, false, false, 0);
	trim_buffer();
}

void Mouse::on_right_pressed(Vector2i position)
{
	this->position = position;
	r_pressed = true;
	event_buffer.emplace(Mouse::Event::RMouseButtonReleased, position, false, true, 0);
	trim_buffer();
}

void Mouse::on_right_released(Vector2i position)
{
	this->position = position;
	r_pressed = false;
	event_buffer.emplace(Mouse::Event::RMouseButtonReleased, position, false, false, 0);
	trim_buffer();
}

void Mouse::on_scroll(Vector2i position, int delta)
{
	this->position = position;
	this->delta = delta;
	Mouse::Event::Type t = delta < 0 ? Mouse::Event::WheelDown : Mouse::Event::WheelUp;
	event_buffer.emplace(t, position, false, false, delta);
	trim_buffer();
}

void Mouse::on_enter(Vector2i position)
{
	this->position = position;
	focused = true;
	event_buffer.emplace(Mouse::Event::Enter, position, false, false, 0);
}

void Mouse::on_leave(Vector2i position)
{
	this->position = position;
	focused = false;
	event_buffer.emplace(Mouse::Event::Leave, position, false, false, 0);
}

void Mouse::trim_buffer()
{
	while (event_buffer.size() > max_buffer_size)
	{
		event_buffer.pop();
	}
}

Mouse::Mouse()
	: position({ 0, 0 })
	, l_pressed(false), r_pressed(false)
	, delta(0)
	, focused(false)
{
}

Vector2i Mouse::get_position() const
{
	return position;
}

//TODO: Does it make sense to reset delta after getting it? Maybe?
int Mouse::get_delta() 
{
	int temp = delta;
	delta = 0;
	return temp;
}

bool Mouse::is_focused() const
{
	return focused;
}

bool Mouse::is_left_pressed() const
{
	return l_pressed;
}

bool Mouse::is_right_pressed() const
{
	return r_pressed;
}

Mouse::Event Mouse::pop()
{
	Mouse::Event e = event_buffer.front();
	event_buffer.pop();
	return e;
}

bool Mouse::is_empty() const
{
	return event_buffer.empty();
}

void Mouse::clear_state()
{
	position = { 0, 0 };
	l_pressed = false;
	r_pressed = false;
	delta = 0;
}
