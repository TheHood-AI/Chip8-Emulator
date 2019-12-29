#pragma once
#include <Windows.h>
class CWindowHandler
{
public:
	struct SWindowData
	{
		unsigned int myX;
		unsigned int myY;
		unsigned int myWidth;
		unsigned int myHeight;
	};

	CWindowHandler() = default;
	~CWindowHandler() = default;
	bool Init(const SWindowData& someWindowData);
	static LRESULT CALLBACK WindowProc(_In_ HWND aHwnd, _In_ UINT aUMsg, _In_ WPARAM aWParam, _In_ LPARAM aLParam);
	HWND GetWindowHandle()const;
	const unsigned int GetWidth()const;
	const unsigned int GetHeight()const;
private:
	HWND myWindowHandle;
	SWindowData myWindowData;
};

