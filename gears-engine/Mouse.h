#pragma once
#include <queue>
#include "Vector.h"

class Mouse
{
	friend class Window;
public:
	struct Event
	{
		enum class Type
		{
			LMouseButtonPressed,
			LMouseButtonReleased,
			RMouseButtonPressed,
			RMouseButtonReleased,
			WheelUp,
			WheelDown,
			Move,
			Enter,
			Leave,
			Invalid
		};

		Event(Type type, Vector2i position, bool l_pressed, bool r_pressed, int delta)
			: type(type), position(position)
			, l_pressed(l_pressed), r_pressed(r_pressed)
			, delta(delta)
		{}
		Type type;
		Vector2i position;
		bool l_pressed, r_pressed;
		int delta;
	};

public:
	Mouse();
	Mouse(const Mouse&) = delete;
	Mouse& operator=(const Mouse&) = delete;


	Vector2i get_position() const;
	bool is_left_pressed() const;
	bool is_right_pressed() const;
	int get_delta();
	bool is_focused() const;
	Mouse::Event pop();
	bool is_empty() const;

	void clear_state();

private:
	void on_move(Vector2i position);
	void on_left_pressed(Vector2i position);
	void on_left_released(Vector2i position);
	void on_right_pressed(Vector2i position);
	void on_right_released(Vector2i position);
	void on_scroll(Vector2i position, int delta);
	void on_enter(Vector2i position);
	void on_leave(Vector2i position);
	void trim_buffer();

private:
	static const unsigned int max_buffer_size = 32;
	Vector2i position;
	bool l_pressed, r_pressed;
	int delta;
	bool focused;

	std::queue<Event> event_buffer;
	
};

