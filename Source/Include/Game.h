#pragma once
#include "Chip8.h"
#include <Windows.h>
class Game
{
public:
	void Init(HWND aHWND);
	void Update();
private:
	bool myShouldRun;
	Chip8 myChip8;
};

