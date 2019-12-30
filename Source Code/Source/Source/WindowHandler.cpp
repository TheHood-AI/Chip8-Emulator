#include "WindowHandler.h"
#include "InputHandler.hpp"
#include <cassert>

bool CWindowHandler::Init(const SWindowData& someWindowData)
{
	myWindowData = someWindowData;
	WNDCLASS windowClass = {};
	windowClass.style = CS_VREDRAW | CS_HREDRAW | CS_OWNDC;
	windowClass.lpfnWndProc = CWindowHandler::WindowProc;
	windowClass.hCursor = LoadCursor(nullptr, IDC_ARROW);
	windowClass.lpszClassName = L"Engine";
	RegisterClass(&windowClass);

	if (someWindowData.myHandle == nullptr)
	{
		myWindowHandle = CreateWindow(L"Engine", L"Game", WS_OVERLAPPEDWINDOW | WS_POPUP | WS_VISIBLE,
			myWindowData.myX, myWindowData.myY, myWindowData.myWidth, myWindowData.myHeight,
			nullptr, nullptr, nullptr, this);
	}
	else
	{
		myWindowHandle = someWindowData.myHandle;

	}

	CommonUtilities::InputHandler::GetInstance().AttachWindow(myWindowHandle);


	return true;
}

LRESULT CALLBACK CWindowHandler::WindowProc(_In_ HWND aHwnd, _In_ UINT aUMsg, _In_ WPARAM aWParam, _In_ LPARAM aLParam)
{
	static CWindowHandler* windowHandler = nullptr;

	if (aUMsg == WM_DESTROY || aUMsg == WM_CLOSE)
	{
		PostQuitMessage(0);
		return 0;
	}
	else if (aUMsg == WM_CREATE)
	{
		auto* createStruct = reinterpret_cast<CREATESTRUCT*>(aLParam);
		windowHandler = reinterpret_cast<CWindowHandler*>(createStruct->lpCreateParams);
	}/*
	CommonUtilities::InputHandler::GetInstance().UpdateEvents(aUMsg, aWParam, aLParam);*/

	return DefWindowProc(aHwnd, aUMsg, aWParam, aLParam);
}

HWND CWindowHandler::GetWindowHandle() const
{
	return myWindowHandle;
}

const unsigned int CWindowHandler::GetWidth() const
{
	return myWindowData.myWidth;
}

const unsigned int CWindowHandler::GetHeight() const
{
	return myWindowData.myHeight;
}
