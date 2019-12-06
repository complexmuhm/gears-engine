#include "Keyboard.h"
#include <cstring>


Keyboard::Keyboard()
	: autorepeat(false)
{
}


Keyboard::~Keyboard()
{
}

bool Keyboard::is_key_pressed(unsigned char key) const
{
	return keys[key];
}

bool Keyboard::is_autorepeat_set() const
{
	return autorepeat;
}

bool Keyboard::is_key_empty()
{
	return event_buffer.empty();
}

bool Keyboard::is_char_empty()
{
	return char_buffer.empty();
}

Keyboard::Event Keyboard::pop_key()
{
	Event e;
	if (event_buffer.empty())
	{
		return e;
	}

	e = event_buffer.front();
	event_buffer.pop();
	return e;
}

char Keyboard::pop_char()
{
	char c = 0;
	if (char_buffer.empty())
	{
		return c;
	}

	c = char_buffer.front();
	char_buffer.pop();
	return c;
}

void Keyboard::clear_events()
{
	event_buffer = {};
	char_buffer = {};
}

void Keyboard::set_autorepeat(bool state)
{
	autorepeat = state;
}

// TODO: Possible template here for both pressed and released?
void Keyboard::on_key_pressed(unsigned char key)
{
	keys[key] = true;
	event_buffer.push(Event(Event::Type::Pressed, key));
	trim_buffer(event_buffer);
}

void Keyboard::on_key_released(unsigned char key)
{
	keys[key] = false;
	event_buffer.push(Event(Event::Type::Released, key));
	trim_buffer(event_buffer);
}

void Keyboard::on_char(char character)
{
	char_buffer.push(character);
	trim_buffer(char_buffer);
}

void Keyboard::clear_state()
{
	keys.reset();
}
