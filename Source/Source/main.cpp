#include <Windows.h>
#include <iostream>
#include "GraphicsEngine.h"
#include "InputHandler.hpp"
#include "Chip8.h"
#include "Timer.hpp"
#include <thread>

void InitConsole()
{
#pragma warning( push )
#pragma warning( disable : 4996 )
#pragma warning(disable : 6031)
	AllocConsole();
	freopen("CONIN$", "r", stdin);
	freopen("CONOUT$", "w", stdout);
	freopen("CONOUT$", "w", stderr);

	setbuf(stdin, NULL);
	setbuf(stdout, NULL);
	setbuf(stderr, NULL);
#pragma warning( pop )
}

void CloseConsole()
{
#pragma warning( push )
#pragma warning( disable : 4996 )
	fclose(stdin);
	fclose(stdout);
	fclose(stderr);
#pragma warning( pop )
}

bool globalShouldRun = false;

Chip8 myChip8;

void Update()
{

	CommonUtilities::Timer myTimer;
	float delta = 0;
	MSG windowMessage = { 0 };
	while (globalShouldRun)
	{
		while (PeekMessage(&windowMessage, 0, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&windowMessage);
			DispatchMessage(&windowMessage);

			CommonUtilities::InputHandler::GetInstance().UpdateEvents(windowMessage.message, windowMessage.wParam, windowMessage.lParam);
			if (windowMessage.message == WM_QUIT)
			{
				globalShouldRun = false;
			}
		}

		delta = myTimer.GetDeltaTime();

		myTimer.Update();
		CommonUtilities::InputHandler::GetInstance().Update();


		myChip8.EmulateCycle(delta);

	}
}

int WINAPI wWinMain(_In_ HINSTANCE /*hInstance*/, _In_opt_ HINSTANCE /*hPrevInstance*/, _In_ LPWSTR /*lpCmdLine*/, _In_ int /*nShowCmd*/)
{
	InitConsole();

	myChip8.Initialize();
	myChip8.LoadGame("../Workbed/Rom/invaders.c8");

	CWindowHandler::SWindowData windowData{};
	windowData.myX = 0;
	windowData.myY = 0;
	windowData.myHeight = 480;
	windowData.myWidth = 600;

	CGraphicsEngine* grapihcsEngine = new CGraphicsEngine();

	globalShouldRun = grapihcsEngine->Init(windowData);
	std::thread graphicsThread([grapihcsEngine]()
		{
			while (globalShouldRun)
			{
				grapihcsEngine->BegineFrame();

				grapihcsEngine->Render();
				grapihcsEngine->EndFrame();
			}
		});
	graphicsThread.detach();

	Update();
	
	delete grapihcsEngine;
	grapihcsEngine = nullptr;
	CloseConsole();
	return 0;
}