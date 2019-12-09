#include "Widget.h"

Widget::Widget(
    const DirectX::XMFLOAT4X4* view,
    const DirectX::XMFLOAT4X4* ortho)
    : Transform2D(view, ortho)
{
    reset_state();
    reset_buttons();
}

void Widget::process_events(Keyboard::Event key_event, Mouse::Event mouse_event)
{
    if (mouse_event.type == Mouse::Event::Type::Move)
    {
        float posx = (float)mouse_event.position.x;
        float posy = (float)mouse_event.position.y;
        if (contains(posx, posy))
        {
            if(!has_entered)
                on_enter();
        }
        else
        {
            if (has_entered)
                on_leave();
            return;
        }
    }

    switch (key_event.type)
    {
    case Keyboard::Event::Type::Pressed:
    {

        break;
    }
    case Keyboard::Event::Type::Released:
    {
        break;
    }
    }

    if (has_entered)
    {
		switch (mouse_event.type)
		{
		case Mouse::Event::Type::LMouseButtonPressed:
		{
			on_left_pressed();
			break;
		}
		case Mouse::Event::Type::LMouseButtonReleased:
		{
			if (is_left_pressed)
			{
				on_left_clicked();
			}
			on_left_released();
			break;
		}
		case Mouse::Event::Type::RMouseButtonPressed:
		{
			on_right_pressed();
			break;
		}
		case Mouse::Event::Type::RMouseButtonReleased:
		{
			if (is_right_pressed)
			{
				on_right_clicked();
			}
			on_right_released();
			break;
		}
		case Mouse::Event::Type::MMouseButtonPressed:
		{
			on_middle_pressed();
			break;
		}
		case Mouse::Event::Type::MMouseButtonReleased:
		{
			if (is_middle_pressed)
			{
				on_middle_clicked();
			}
			on_middle_released();
			break;
		}
		}
    }
}

void Widget::bind_enter(GUICallback callback_func)
{
    enter_callback = callback_func;
}
void Widget::bind_leave(GUICallback callback_func)
{
    leave_callback = callback_func;
}
void Widget::bind_left(GUICallback callback_func)
{
    left_callback = callback_func;
}
void Widget::bind_right(GUICallback callback_func)
{
    right_callback = callback_func;
}
void Widget::bind_middle(GUICallback callback_func)
{
    middle_callback = callback_func;
}

bool Widget::entered()
{
    return has_entered;
}

bool Widget::hovering()
{
    return is_hovering;
}

bool Widget::pressed()
{
    return has_pressed;
}

bool Widget::released()
{
    return has_released;
}

bool Widget::left()
{
    return has_left;
}

void Widget::on_enter()
{
    reset_state();
    reset_buttons();
    has_entered = true;
    if (enter_callback)
    {
        enter_callback();
    }
    on_hover();
}
void Widget::on_hover()
{
    is_hovering = true;
}
void Widget::on_pressed()
{
    has_pressed = true;
    has_released = false;
}
void Widget::on_released()
{
    has_released = true;
    has_pressed = false;
}
void Widget::on_leave()
{
    reset_state();
    reset_buttons();
    if (leave_callback)
    {
        leave_callback();
    }
}
void Widget::on_left_pressed()
{
    reset_buttons();
    on_pressed();
    is_left_pressed = true;

}
void Widget::on_left_released()
{
    reset_buttons();
    on_released();
    is_left_released = true;
}
void Widget::on_left_clicked()
{
    if (left_callback)
    {
        left_callback();
    }
}
void Widget::on_right_pressed()
{
    reset_buttons();
    on_pressed();
    is_right_pressed = true;
}
void Widget::on_right_released()
{
    reset_buttons();
    on_released();
    is_right_released = true;
}
void Widget::on_right_clicked()
{
    if (right_callback)
    {
        right_callback();
    }
}
void Widget::on_middle_pressed()
{
    reset_buttons();
    on_pressed();
    is_middle_pressed = true;
}
void Widget::on_middle_released()
{
    reset_buttons();
    on_released();
    is_middle_released = true;
}
void Widget::on_middle_clicked()
{
    if (middle_callback)
    {
        middle_callback();
    }
}
void Widget::reset_state()
{
    has_entered = false;
    is_hovering = false;
    has_pressed = false;
    has_released = false;
}
void Widget::reset_buttons()
{
    is_left_pressed = false;
    is_left_released = false;
    is_right_pressed = false;
    is_right_released = false;
    is_middle_pressed = false;
    is_middle_released = false;
}
