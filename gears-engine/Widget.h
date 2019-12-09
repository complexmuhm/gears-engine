#pragma once

#include "Transform.h"
#include <functional>

using GUICallback = std::function<void()>;

class D3DGFX;

class Widget : public Transform2D
{
public:
    Widget(
        const DirectX::XMFLOAT4X4* view,
        const DirectX::XMFLOAT4X4* ortho);

    void process_events();
    void update(float dt);
    void render(D3DGFX& gfx);

    void bind_enter(GUICallback callback_func);
    void bind_leave(GUICallback callback_func);

    void bind_left(GUICallback callback_func);
    void bind_right(GUICallback callback_func);
    void bind_middle(GUICallback callback_func);

private:
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

private:
    bool hasEntered;
    bool isHovering;
    bool hasPressed;
    bool hasReleased;
    bool hasLeft;

    bool isLeftPressed;
    bool isLeftReleased;
    bool isRightPressed;
    bool isRightReleased;
    bool isMiddlePressed;
    bool isMiddleReleased;

    GUICallback enter_callback;
    GUICallback leave_callback;

    GUICallback left_callback;
    GUICallback right_callback;
    GUICallback middle_callback;

};