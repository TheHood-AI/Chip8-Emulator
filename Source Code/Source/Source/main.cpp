#include <Windows.h>
#include <iostream>
#include "Game.h"

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




int WINAPI wWinMain(_In_ HINSTANCE /*hInstance*/, _In_opt_ HINSTANCE /*hPrevInstance*/, _In_ LPWSTR /*lpCmdLine*/, _In_ int /*nShowCmd*/)
{
	InitConsole();
	Game game;
	game.Init(nullptr);
	
	CloseConsole();
	return 0;
}