#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <Shlwapi.h>

#include "GameBase/Application.hpp"
#include "GameCode/EndlessTanksGame.hpp"

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
	int returnCode = 0;

	// Set the working directory to the path of the executable.
	//WCHAR path[MAX_PATH];
	//HMODULE hModule = GetModuleHandleW(NULL);
	//if (GetModuleFileNameW(hModule, path, MAX_PATH) > 0)
	//{
	//	PathRemoveFileSpecW(path);
	//	SetCurrentDirectoryW(path);
	//}

	Application::Create(hInstance);
	{
		std::shared_ptr<EndlessTanksGame> game = std::make_shared<EndlessTanksGame>(L"Endless Tanks - v0.1", 1280, 720);
		
		// Run the game
		returnCode = Application::Get().Run(game);
	}
	Application::Destroy();
	
	/*
	MSG uMsg = { };
	while (WM_QUIT != uMsg.message)
	{
		while (PeekMessage(&uMsg, NULL, 0, 0, PM_REMOVE))
		{
			// Process the message
			if (uMsg.message == WM_QUIT)
				break;

			TranslateMessage(&uMsg);
			DispatchMessage(&uMsg);
		}

		// Here is were all the "animation that isn't used when the user does something" code will go.
		if (WM_QUIT != uMsg.message)
		{
			// One GameLoop
		}
	}
	*/

	return returnCode;
}
