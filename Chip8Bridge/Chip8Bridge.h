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
	private:
		Game* myGame;
	};
}
