#include "pch.h"

#include "Chip8Bridge.h"
#include <msclr\marshal_cppstd.h>
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
	myGame->ShutDown();
}

void Chip8Bridge::CBridge::GetInput(char aKey, bool aIsPressed)
{
	myGame->GetInput(aKey, aIsPressed);
}

void Chip8Bridge::CBridge::LoadRom(System::String^ aFilePath)
{
	std::string unmanaged = msclr::interop::marshal_as<std::string>(aFilePath);
	myGame->LoadRom(unmanaged);
}
