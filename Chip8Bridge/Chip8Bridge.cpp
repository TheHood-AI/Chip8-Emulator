#include "pch.h"

#include "Chip8Bridge.h"

Chip8Bridge::CBridge::CBridge()
{
	myGame = new Game();
}

Chip8Bridge::CBridge::~CBridge()
{
	delete myGame;
	myGame = nullptr;
}

void Chip8Bridge::CBridge::Init(System::IntPtr aHWND)
{
	myGame->Init((HWND)aHWND.ToPointer());
}

void Chip8Bridge::CBridge::Shutdown()
{
	throw gcnew System::NotImplementedException();
}
