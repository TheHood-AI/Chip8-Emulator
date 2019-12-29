#include "Game.h"
#include "GraphicsEngine.h"
#include "InputHandler.hpp"
#include "Chip8.h"
#include "Timer.hpp"
#include <thread>

void Game::Init(HWND aHWND)
{
	myChip8.Initialize();
	myChip8.LoadGame("../Workbed/Rom/invaders.c8");

	CWindowHandler::SWindowData windowData{};
	windowData.myX = 0;
	windowData.myY = 0;
	windowData.myHeight = 480;
	windowData.myWidth = 600;
	windowData.myHandle = aHWND;

	CGraphicsEngine* grapihcsEngine = new CGraphicsEngine();

	myShouldRun = grapihcsEngine->Init(windowData);
	std::thread graphicsThread([this, grapihcsEngine]()
	{
		while (myShouldRun)
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
}

void Game::Update()
{

	CommonUtilities::Timer myTimer;
	float delta = 0;
	MSG windowMessage = { 0 };
	while (myShouldRun)
	{
		while (PeekMessage(&windowMessage, 0, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&windowMessage);
			DispatchMessage(&windowMessage);

			CommonUtilities::InputHandler::GetInstance().UpdateEvents(windowMessage.message, windowMessage.wParam, windowMessage.lParam);
			if (windowMessage.message == WM_QUIT)
			{
				myShouldRun = false;
			}
		}

		delta = myTimer.GetDeltaTime();

		myTimer.Update();
		CommonUtilities::InputHandler::GetInstance().Update();


		myChip8.EmulateCycle(delta);

	}
}
