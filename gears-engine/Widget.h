#pragma once

#include "Transform.h"
#include "Keyboard.h"
#include "Mouse.h"
#include <functional>

using GUICallback = std::function<void()>;

class D3DGFX;

class Widget : public Transform2D
{
public:
    Widget(
        const DirectX::XMFLOAT4X4* view,
        const DirectX::XMFLOAT4X4* ortho);

    virtual void process_events(Keyboard::Event key_event, Mouse::Event mouse_event);
    virtual void update(float dt) = 0;
    virtual void draw(D3DGFX& gfx) = 0;

    void bind_enter(GUICallback callback_func);
    void bind_leave(GUICallback callback_func);

    void bind_left(GUICallback callback_func);
    void bind_right(GUICallback callback_func);
    void bind_middle(GUICallback callback_func);

    bool entered();
    bool hovering();
    bool pressed();
    bool released();
    bool left();

protected:
    void on_enter();
    void on_hover();
    void on_pressed();
    void on_released();
    void on_leave();

    void on_left_pressed();
    void on_left_released();
    void on_left_clicked();

    void on_right_pressed();
    void on_right_released();
    void on_right_clicked();

    void on_middle_pressed();
    void on_middle_released();
    void on_middle_clicked();

    void reset_state();
    void reset_buttons();

protected:
    bool has_entered;
    bool is_hovering;
    bool has_pressed;
    bool has_released;
    bool has_left;

    bool is_left_pressed;
    bool is_left_released;
    bool is_right_pressed;
    bool is_right_released;
    bool is_middle_pressed;
    bool is_middle_released;

    GUICallback enter_callback;
    GUICallback leave_callback;

    GUICallback left_callback;
    GUICallback right_callback;
    GUICallback middle_callback;

};