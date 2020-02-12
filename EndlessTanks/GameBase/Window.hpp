/**
* @brief A window for application.
*/
#pragma once

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#include <wrl.h>
#include <string>
#include <memory>

#include "../Helpers/Events.hpp"
#include "../Helpers/HighResolutionClock.hpp"

// Forward-declare the DirectXTemplate class.
class Game;

class Window
{
private:
    // Windows should not be copied.
    Window(const Window& copy) = delete;
    Window& operator=(const Window& other) = delete;

    HWND mhWnd;

    std::wstring mWindowName;

    int mClientWidth;
    int mClientHeight;
    bool mIsFullscreen;

    HighResolutionClock mUpdateClock;
    HighResolutionClock mRenderClock;
    uint64_t mFrameCounter;

    std::weak_ptr<Game> mpGame;

    UINT mRTVDescriptorSize;
    UINT mCurrentBackBufferIndex;

    RECT mWindowRect;

protected:
    // The Window procedure needs to call protected methods of this class.
    friend LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

    // Only the application can create a window.
    friend class Application;
    // The DirectXTemplate class needs to register itself with a window.
    friend class Game;

    Window() = delete;

    // Register a Game with this window. This allows
    // the window to callback functions in the Game class.
    void RegisterCallbacks(std::shared_ptr<Game> pGame);

    // Update and Draw can only be called by the application.
    virtual void OnUpdate(UpdateEventArgs& e);
    virtual void OnRender(RenderEventArgs& e);

    // A keyboard key was pressed
    virtual void OnKeyPressed(KeyEventArgs& e);
    // A keyboard key was released
    virtual void OnKeyReleased(KeyEventArgs& e);

    // The mouse was moved
    virtual void OnMouseMoved(MouseMotionEventArgs& e);
    // A button on the mouse was pressed
    virtual void OnMouseButtonPressed(MouseButtonEventArgs& e);
    // A button on the mouse was released
    virtual void OnMouseButtonReleased(MouseButtonEventArgs& e);
    // The mouse wheel was moved.
    virtual void OnMouseWheel(MouseWheelEventArgs& e);

    // The window was resized.
    virtual void OnResize(ResizeEventArgs& e);

    // Update the render target views for the swapchain back buffers.
    void UpdateRenderTargetViews();

public:
    Window(HWND hWnd, const std::wstring& windowName, int clientWidth, int clientHeight); // Had to move it from "Protected"
    virtual ~Window(); // Had to move it from "Protected"

    /**
    * Get a handle to this window's instance.
    * @returns The handle to the window instance or nullptr if this is not a valid window.
    */
    HWND GetWindowHandle() const;

    /**
    * Destroy this window.
    */
    void Destroy();

    const std::wstring& GetWindowName() const;

    int GetClientWidth() const;
    int GetClientHeight() const;

    /**
    * Is this a windowed window or full-screen?
    */
    bool IsFullScreen() const;

    // Set the fullscreen state of the window.
    void SetFullscreen(bool fullscreen);
    void ToggleFullscreen();

    /**
     * Show this window.
     */
    void Show();

    /**
     * Hide the window.
     */
    void Hide();

    /**
     * Present the swapchain's back buffer to the screen.
     * Returns the current back buffer index after the present.
     */
    UINT Present();
};
