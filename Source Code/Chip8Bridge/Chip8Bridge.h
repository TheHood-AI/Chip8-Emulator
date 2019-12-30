#pragma once
#include "../Source/Include/Game.h"

using namespace System;

namespace Chip8Bridge 
{
	public ref class CBridge
	{
	public:
		CBridge();
		~CBridge();
		void Init(System::IntPtr aHWND);
		void Shutdown();
		void GetInput(char aKey, bool aIsPressed);
		void LoadRom(System::String^ aFilePath);
	private:
		Game* myGame;
	};
}
