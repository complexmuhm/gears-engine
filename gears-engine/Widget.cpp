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
            if(!hasEntered)
                on_enter();
        }
        else
        {
            if (hasEntered)
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

    if (hasEntered)
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
			if (isLeftPressed)
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
			if (isRightPressed)
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
			if (isMiddlePressed)
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

void Widget::on_enter()
{
    reset_state();
    reset_buttons();
    hasEntered = true;
    if (enter_callback)
    {
        enter_callback();
    }
    on_hover();
}
void Widget::on_hover()
{
    isHovering = true;
}
void Widget::on_pressed()
{
    hasPressed = true;
    hasReleased = false;
}
void Widget::on_released()
{
    hasReleased = true;
    hasPressed = false;
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
    isLeftPressed = true;

}
void Widget::on_left_released()
{
    reset_buttons();
    on_released();
    isLeftReleased = true;
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
    isRightPressed = true;
}
void Widget::on_right_released()
{
    reset_buttons();
    on_released();
    isRightReleased = true;
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
    isMiddlePressed = true;
}
void Widget::on_middle_released()
{
    reset_buttons();
    on_released();
    isMiddleReleased = true;
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
    hasEntered = false;
    isHovering = false;
    hasPressed = false;
    hasReleased = false;
}
void Widget::reset_buttons()
{
    isLeftPressed = false;
    isLeftReleased = false;
    isRightPressed = false;
    isRightReleased = false;
    isMiddlePressed = false;
    isMiddleReleased = false;
}
