#ifndef UNICODE
#define UNICODE
#endif

#ifndef _UNICODE
#define _UNICODE
#endif

#include <Windows.h>

#include "Game/GameEngine.h"

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
	// Init window/GameEngine

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

	return 0;
}
