#pragma once

#include <wrl.h> // Windows Runtime Library. Needed for Microsoft::WRL::ComPtr<> template class.

#include <memory>
#include <string>

#include <d2d1.h>
#pragma comment(lib, "d2d1")

#include "../Helpers/Events.hpp"

class Window;
class Game;

class Application
{
private:
    Application(const Application& copy) = delete;
    Application& operator=(const Application& other) = delete;

    // The application instance handle that this application was created with.
    HINSTANCE mhInstance;

    Microsoft::WRL::ComPtr<ID2D1Factory> mDxFactory;
    Microsoft::WRL::ComPtr<ID2D1HwndRenderTarget> mDxRenderTarget;

protected:
    // Create an application instance.
    Application(HINSTANCE hInst);

    // Destroy the application instance and all windows associated with this application.
    virtual ~Application();

    KeyEventArgs GetKeyPressed();

    Microsoft::WRL::ComPtr<ID2D1Factory> GetFactory();
    Microsoft::WRL::ComPtr<ID2D1HwndRenderTarget> CreateRenderTarget(Microsoft::WRL::ComPtr<ID2D1Factory> factory);

public:
    /**
    * Create the application singleton with the application instance handle.
    */
    static void Create(HINSTANCE hInst);

    /**
    * Destroy the application instance and all windows created by this application instance.
    */
    static void Destroy();

    /**
    * Get the application singleton.
    */
    static Application& Get();

    /**
    * Create a new DirectX2D render window instance.
    * @param windowName The name of the window. This name will appear in the title bar of the window. This name should be unique.
    * @param clientWidth The width (in pixels) of the window's client area.
    * @param clientHeight The height (in pixels) of the window's client area.
    * @returns The created window instance. If an error occurred while creating the window an invalid
    * window instance is returned. If a window with the given name already exists, that window will be
    * returned.
    */
    std::shared_ptr<Window> CreateRenderWindow(const std::wstring& windowName, int clientWidth, int clientHeight);

    /**
    * Destroy a window given the window reference.
    */
    void DestroyWindow(std::shared_ptr<Window> window);

    /**
    * Run the application loop and message pump.
    * @return The error code if an error occurred.
    */
    int Run(std::shared_ptr<Game> pGame);

    /**
    * Request to quit the application and close all windows.
    * @param exitCode The error code to return to the invoking process.
    */
    void Quit(int exitCode = 0);

    /**
     * Get the Direct3D 12 device
     */
    Microsoft::WRL::ComPtr<ID2D1HwndRenderTarget> GetRenderTarget() const;
};

