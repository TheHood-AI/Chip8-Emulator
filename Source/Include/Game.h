#pragma once
#include "Chip8.h"
#include <Windows.h>
class Game
{
public:
	void Init(HWND aHWND);
	void Update();
	void GetInput(const char aKey, const bool aIsPressed);
	void LoadRom(const std::string& aFilePath);
	void ShutDown();

	static struct Keys
	{
		bool one = false;
		bool two = false;
		bool three = false;
		bool four = false;
		bool Q= false;
		bool W= false;
		bool E= false;
		bool R= false;
		bool A= false;
		bool S= false;
		bool D= false;
		bool F= false;
		bool Z= false;
		bool X= false;
		bool C= false;
		bool V= false;

	}myKeys;
private:
	bool myShouldRun;

	Chip8 myChip8;
};

