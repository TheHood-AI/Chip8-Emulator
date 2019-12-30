#include "Game.h"
#include "GraphicsEngine.h"
#include "InputHandler.hpp"
#include "Chip8.h"
#include "Timer.hpp"
#include <thread>
#include <cassert>

Game::Keys Game::myKeys;

void Game::Init(HWND aHWND)
{
	//myChip8.Initialize();
	//myChip8.LoadGame("../Workbed/Rom/invaders.c8");

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
			assert(false);
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

void Game::GetInput(const char aKey, const bool aIsPressed)
{
	if (aKey == '1')
	{
		myKeys.one = aIsPressed;
	}
	if (aKey == '2')
	{
		myKeys.two = aIsPressed;
	}
	if (aKey == '3')
	{
		myKeys.three = aIsPressed;
	}
	if (aKey == '4')
	{
		myKeys.four = aIsPressed;
	}
	if (aKey == 'Q')
	{
		myKeys.Q = aIsPressed;
	}
	if (aKey == 'W')
	{
		myKeys.W = aIsPressed;
	}
	if (aKey == 'E')
	{
		myKeys.E = aIsPressed;
	}
	if (aKey == 'R')
	{
		myKeys.R = aIsPressed;
	}
	if (aKey == 'A')
	{
		myKeys.A = aIsPressed;
	}
	if (aKey == 'S')
	{
		myKeys.S = aIsPressed;
	}
	if (aKey == 'D')
	{
		myKeys.D = aIsPressed;
	}
	if (aKey == 'F')
	{
		myKeys.F = aIsPressed;
	}
	if (aKey == 'Z')
	{
		myKeys.Z = aIsPressed;
	}
	if (aKey == 'X')
	{
		myKeys.X = aIsPressed;
	}
	if (aKey == 'C')
	{
		myKeys.C = aIsPressed;
	}
	if (aKey == 'V')
	{
		myKeys.V = aIsPressed;
	}
}

void Game::LoadRom(const std::string& aFilePath)
{
	myChip8.Initialize();
	myChip8.LoadGame(aFilePath);
}

void Game::ShutDown()
{
	myShouldRun = false;
}
