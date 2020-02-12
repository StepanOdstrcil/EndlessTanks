#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <Shlwapi.h>

#include "BaseAppEngine/Application.hpp"
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
		std::shared_ptr<EndlessTanksGame> game = std::make_shared<EndlessTanksGame>(L"Endless Tanks - v0.2", 1280, 720);
		
		// Run the game
		returnCode = Application::Get().Run(game);
	}
	Application::Destroy();

	return returnCode;
}
