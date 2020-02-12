#pragma once

// Studied and Copied from:
// 

#include "../Helpers/KeyCodes.hpp"

// Base class for all event args
class EventArgs
{
public:
    EventArgs()
    {}

};

class KeyEventArgs : public EventArgs
{
public:
    enum KeyState
    {
        Released = 0,
        Pressed = 1
    };
    
    KeyEventArgs(KeyCode::Key key, unsigned int c, KeyState state, bool control, bool shift, bool alt)
        : Key(key)
        , Char(c)
        , State(state)
        , Control(control)
        , Shift(shift)
        , Alt(alt)
    {}

    KeyCode::Key    Key;    // The Key Code that was pressed or released.
    unsigned int    Char;   // The 32-bit character code that was pressed. This value will be 0 if it is a non-printable character.
    KeyState        State;  // Was the key pressed or released?
    bool            Control;// Is the Control modifier pressed
    bool            Shift;  // Is the Shift modifier pressed
    bool            Alt;    // Is the Alt modifier pressed
};

class MouseMotionEventArgs : public EventArgs
{
public:
    MouseMotionEventArgs(bool leftButton, bool middleButton, bool rightButton, bool control, bool shift, int x, int y)
        : LeftButton(leftButton)
        , MiddleButton(middleButton)
        , RightButton(rightButton)
        , Control(control)
        , Shift(shift)
        , X(x)
        , Y(y)
    {}

    bool LeftButton;    // Is the left mouse button down?
    bool MiddleButton;  // Is the middle mouse button down?
    bool RightButton;   // Is the right mouse button down?
    bool Control;       // Is the CTRL key down?
    bool Shift;         // Is the Shift key down?

    int X;              // The X-position of the cursor relative to the upper-left corner of the client area.
    int Y;              // The Y-position of the cursor relative to the upper-left corner of the client area.
    int RelX;           // How far the mouse moved since the last event.
    int RelY;           // How far the mouse moved since the last event.

};

class MouseButtonEventArgs : public EventArgs
{
public:
    enum MouseButton
    {
        None = 0,
        Left = 1,
        Right = 2,
        Middel = 3
    };
    enum ButtonState
    {
        Released = 0,
        Pressed = 1
    };

    MouseButtonEventArgs(MouseButton buttonID, ButtonState state, bool leftButton, bool middleButton, bool rightButton, bool control, bool shift, int x, int y)
        : Button(buttonID)
        , State(state)
        , LeftButton(leftButton)
        , MiddleButton(middleButton)
        , RightButton(rightButton)
        , Control(control)
        , Shift(shift)
        , X(x)
        , Y(y)
    {}

    MouseButton Button; // The mouse button that was pressed or released.
    ButtonState State;  // Was the button pressed or released?
    bool LeftButton;    // Is the left mouse button down?
    bool MiddleButton;  // Is the middle mouse button down?
    bool RightButton;   // Is the right mouse button down?
    bool Control;       // Is the CTRL key down?
    bool Shift;         // Is the Shift key down?

    int X;              // The X-position of the cursor relative to the upper-left corner of the client area.
    int Y;              // The Y-position of the cursor relative to the upper-left corner of the client area.
};

class MouseWheelEventArgs : public EventArgs
{
public:
    MouseWheelEventArgs(float wheelDelta, bool leftButton, bool middleButton, bool rightButton, bool control, bool shift, int x, int y)
        : WheelDelta(wheelDelta)
        , LeftButton(leftButton)
        , MiddleButton(middleButton)
        , RightButton(rightButton)
        , Control(control)
        , Shift(shift)
        , X(x)
        , Y(y)
    {}

    float WheelDelta;   // How much the mouse wheel has moved. A positive value indicates that the wheel was moved to the right. A negative value indicates the wheel was moved to the left.
    bool LeftButton;    // Is the left mouse button down?
    bool MiddleButton;  // Is the middle mouse button down?
    bool RightButton;   // Is the right mouse button down?
    bool Control;       // Is the CTRL key down?
    bool Shift;         // Is the Shift key down?

    int X;              // The X-position of the cursor relative to the upper-left corner of the client area.
    int Y;              // The Y-position of the cursor relative to the upper-left corner of the client area.

};

class ResizeEventArgs : public EventArgs
{
public:
    ResizeEventArgs(int width, int height)
        : Width(width)
        , Height(height)
    {}

    // The new width of the window
    int Width;
    // The new height of the window.
    int Height;

};

class UpdateEventArgs : public EventArgs
{
public:
    UpdateEventArgs(double fDeltaTime, double fTotalTime)
        : ElapsedTime(fDeltaTime)
        , TotalTime(fTotalTime)
    {}

    double ElapsedTime;
    double TotalTime;
};

class RenderEventArgs : public EventArgs
{
public:
    RenderEventArgs(double fDeltaTime, double fTotalTime)
        : ElapsedTime(fDeltaTime)
        , TotalTime(fTotalTime)
    {}

    double ElapsedTime;
    double TotalTime;
};

class UserEventArgs : public EventArgs
{
public:
    UserEventArgs(int code, void* data1, void* data2)
        : Code(code)
        , Data1(data1)
        , Data2(data2)
    {}

    int Code;
    void* Data1;
    void* Data2;
};
