#include "Chip8.h"
#include <iostream>
#include <fstream>
#include "RandomNrGen.hpp"
#include "InputHandler.hpp"

#include <cassert>

unsigned char Chip8::myGfx[64 * 32];

unsigned char globalChip8FontSet[80] =
{
  0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
  0x20, 0x60, 0x20, 0x20, 0x70, // 1
  0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
  0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
  0x90, 0x90, 0xF0, 0x10, 0x10, // 4
  0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
  0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
  0xF0, 0x10, 0x20, 0x40, 0x40, // 7
  0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
  0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
  0xF0, 0x90, 0xF0, 0x90, 0x90, // A
  0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
  0xF0, 0x80, 0x80, 0x80, 0xF0, // C
  0xE0, 0x90, 0x90, 0x90, 0xE0, // D
  0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
  0xF0, 0x80, 0xF0, 0x80, 0x80  // F
};

void Chip8::Initialize()
{
	myProgramCounter = 0x200;
	myOpCode = 0;
	myIndexRegister = 0;
	myStackPointer = 0;

	// Clear display
	for (auto& pixel : myGfx)
		pixel = 0;
	// Clear Stack
	for (auto& state : myStack)
		state = 0;
	for (auto& mem : myMemory)
		mem = 0;
	// Clear registers V0 - VF
	for (auto& key : myKey)
		key = 0;
	// Clear Memory
	for (auto& mem : V)
	{
		mem = 0;
	}

	for (int i = 0; i < 80; ++i)
	{
		myMemory[i] = globalChip8FontSet[i];
	}
	myDrawFlag = true;
	myDelayTimer = 0;
	mySoundTimer = 0;
	myHertzTimer = 0;
}

void Chip8::EmulateCycle(float aDelta)
{
	static float t = 0;
	if (t <= 0)
	{
		// Fetch OpCode
		Fetch();
		// Decode OpCode https://en.wikipedia.org/wiki/CHIP-8#Opcode_table
		Decode();

		t = 1.f / 700.f;
	}
	t -= aDelta;

	if (myHertzTimer < 0)
	{
		myHertzTimer = 1.f / 60.f;
		//  Update Timers
		UpdateTimers();
	}

	KeyboardDown();
	KeyboardUp();
	myHertzTimer -= aDelta;
}

void Chip8::LoadGame(const std::string& aFilePath)
{
	std::ifstream file;
	file.open(aFilePath, std::fstream::in | std::fstream::binary);
	if (!file.is_open())
	{
		std::cout << "Failed to find file" << std::endl;
		return;
	}

	std::filebuf* buf = file.rdbuf();

	std::size_t size = static_cast<size_t>(buf->pubseekoff(0, file.end, file.in));
	buf->pubseekpos(0, file.in);

	char* buffer = new char[size];
	buf->sgetn(buffer, size);
	file.close();

	for (size_t i = 0; i < size; ++i)
	{
		myMemory[i + 512] = buffer[i];
	}
	delete[] buffer;
}

void Chip8::KeyboardDown()
{
	using namespace CommonUtilities;
	using Key = InputHandler::Key;
	auto& handler = InputHandler::GetInstance();
	if (handler.KeyWasPressed(Key::One))
	{
		assert(false);
		myKey[0x1] = 1;
	}
	if (handler.KeyWasPressed(Key::Two)) myKey[0x2] = 1;
	if (handler.KeyWasPressed(Key::Three)) myKey[0x3] = 1;
	if (handler.KeyWasPressed(Key::Four)) myKey[0xC] = 1;

	if (handler.KeyWasPressed(Key::Q)) myKey[0x4] = 1;
	if (handler.KeyWasPressed(Key::W))
	{
		myKey[0x5] = 1;
	}
	if (handler.KeyWasPressed(Key::E)) myKey[0x6] = 1;
	if (handler.KeyWasPressed(Key::R)) myKey[0xD] = 1;

	if (handler.KeyWasPressed(Key::A)) myKey[0x7] = 1;
	if (handler.KeyWasPressed(Key::S)) myKey[0x8] = 1;
	if (handler.KeyWasPressed(Key::D)) myKey[0x9] = 1;
	if (handler.KeyWasPressed(Key::F)) myKey[0xE] = 1;

	if (handler.KeyWasPressed(Key::Z)) myKey[0xA] = 1;
	if (handler.KeyWasPressed(Key::X)) myKey[0x0] = 1;
	if (handler.KeyWasPressed(Key::C)) myKey[0xB] = 1;
	if (handler.KeyWasPressed(Key::V)) myKey[0xF] = 1;
}

void Chip8::KeyboardUp()
{
	using namespace CommonUtilities;
	using Key = InputHandler::Key;
	auto& handler = InputHandler::GetInstance();
	if (handler.KeyWasReleased(Key::One))
	{
		myKey[0x1] = 0;
	}
	if (handler.KeyWasReleased(Key::Two)) myKey[0x2] = 0;
	if (handler.KeyWasReleased(Key::Three)) myKey[0x3] = 0;
	if (handler.KeyWasReleased(Key::Four)) myKey[0xC] = 0;

	if (handler.KeyWasReleased(Key::Q)) myKey[0x4] = 0;
	if (handler.KeyWasReleased(Key::W)) myKey[0x5] = 0;
	if (handler.KeyWasReleased(Key::E)) myKey[0x6] = 0;
	if (handler.KeyWasReleased(Key::R)) myKey[0xD] = 0;

	if (handler.KeyWasReleased(Key::A)) myKey[0x7] = 0;
	if (handler.KeyWasReleased(Key::S)) myKey[0x8] = 0;
	if (handler.KeyWasReleased(Key::D)) myKey[0x9] = 0;
	if (handler.KeyWasReleased(Key::F)) myKey[0xE] = 0;

	if (handler.KeyWasReleased(Key::Z)) myKey[0xA] = 0;
	if (handler.KeyWasReleased(Key::X)) myKey[0x0] = 0;
	if (handler.KeyWasReleased(Key::C)) myKey[0xB] = 0;
	if (handler.KeyWasReleased(Key::V)) myKey[0xF] = 0;
}

void Chip8::UpdateTimers()
{
	if (myDelayTimer > 0)
	{
		--myDelayTimer;
	}
	if (mySoundTimer > 0)
	{
		if (mySoundTimer == 1)
		{
			std::cout << "BEEP!" << std::endl;
		}
		--mySoundTimer;
	}
}

inline void Chip8::ClearScreen()
{
	for (auto& pixel : myGfx)
	{
		pixel = 0;
	}
	myDrawFlag = true;
	myProgramCounter += 2;
}

inline void Chip8::ReturnFromSubRoutine()
{
	myStackPointer -= 1;
	myProgramCounter = myStack[myStackPointer];
	myProgramCounter += 2;
}

inline void Chip8::JumpToAddres()
{
	myProgramCounter = (myOpCode & 0x0FFF);
}

inline void Chip8::JumpToAddresPlusVO()
{
	myProgramCounter = (myOpCode & 0x0FFF) + V[0];
}

inline void Chip8::CallSubRoutine()
{
	myStack[myStackPointer] = myProgramCounter;
	++myStackPointer;
	myProgramCounter = myOpCode & 0x0FFF;
}

inline void Chip8::IfVXEqualNN()
{
	if (V[(myOpCode & 0x0F00) >> 8] == (myOpCode & 0x00FF))
		myProgramCounter += 4;
	else
		myProgramCounter += 2;
}

inline void Chip8::IfVXNotEqualNN()
{
	if (V[(myOpCode & 0x0F00) >> 8] != (myOpCode & 0x00FF))
		myProgramCounter += 4;
	else
		myProgramCounter += 2;
}

inline void Chip8::IfVXEqualVY()
{
	if (V[(myOpCode & 0x0F00) >> 8] == V[(myOpCode & 0x00F0) >> 4])
		myProgramCounter += 4;
	else
		myProgramCounter += 2;
}

inline void Chip8::SetVXToNN()
{
	V[(myOpCode & 0x0F00) >> 8] = myOpCode & 0x00FF;
	myProgramCounter += 2;
}

inline void Chip8::SetVXtoVY()
{
	V[(myOpCode & 0x0F00) >> 8] = V[(myOpCode & 0x00F0) >> 4];
	myProgramCounter += 2;
}

inline void Chip8::VXorVY()
{
	V[(myOpCode & 0x0F00) >> 8] |= V[(myOpCode & 0x00F0) >> 4];
	myProgramCounter += 2;
}

inline void Chip8::VXandVY()
{
	V[(myOpCode & 0x0F00) >> 8] &= V[(myOpCode & 0x00F0) >> 4];
	myProgramCounter += 2;
}

inline void Chip8::VXxorVY()
{
	V[(myOpCode & 0x0F00) >> 8] ^= V[(myOpCode & 0x00F0) >> 4];
	myProgramCounter += 2;
}

void Chip8::Decode()
{
	switch (myOpCode & 0xF000)
	{
	case 0x0000:
		switch (myOpCode & 0x000F)
		{
		case 0x0000: // 0x00E0 Clears screen
			ClearScreen();
			break;
		case 0x000E: // 0x00EE Returns from subroutine
			ReturnFromSubRoutine();
			break;
		default:
			std::cout << "Unkown opcode: 0x" << myOpCode << std::endl;
			break;
		}
		break;
	case 0x1000:
		JumpToAddres();
		break;
	case 0x2000:
		CallSubRoutine();
		break;
	case 0x3000:
		IfVXEqualNN();
		break;
	case 0x4000:
		IfVXNotEqualNN();
		break;
	case 0x5000:
		IfVXEqualVY();
		break;
	case 0x6000: // 0x6XNN: Sets VX to NN
		SetVXToNN();
		break;
	case 0x7000: // 0x7XNN
		AddNNToVX();
		break;
	case 0x8000:
	{
		switch (myOpCode & 0x000F)
		{
		case 0x0000: // 0x8XY0: Sets VX to the value of VY
			SetVXtoVY();
			break;
		case 0x0001:
			VXorVY();
			break;
		case 0x0002: // 8XY2
			VXandVY();
			break;
		case 0x0003: //8XY3
			VXxorVY();
			break;
		case 0x0004: // 0x8XY4
			AddVYtoVX();
			break;
		case  0x0005: // 8XY5
			VXMinusVY();
			break;
		case 0x0006:
			ShiftVXtoRight();
			break;
		case 0x0007:
			VYMinusVX();
			break;
		case 0x000E:
			ShiftVXtoLeft();
			break;
		default:
			printf("Unkown opcode: 0x%X\n", myOpCode);
			break;
		}
		break;
	}
	case 0x9000:
	{
		VXNotEqualVY();
		break;
	}
	case 0xA000: // ANNN: Sets I to the address NNN
	{
		SetIndexRegister();
		break;
	}
	case 0xB000:
		JumpToAddresPlusVO();
		break;
	case 0xC000: // 0xCXNN
	{
		RandomNr();
		break;
	}
	case 0xD000: // DXYN
	{
		DrawSprite();
		break;
	}
	case 0xE000:
		switch (myOpCode & 0x00FF)
		{
		case 0x009E:
			IfKeyIsPressed();
			break;
		case 0x00A1:
			IfKeyIsNotPressed();
			break;
		default:
			printf("Unkown opcode: 0x%X\n", myOpCode);
			break;
		}
		break;
	case 0xF000:
	{
		switch (myOpCode & 0x00FF)
		{
		case 0x0007: // FX07
			VXEqualDelayTimer();
			break;
		case 0x0015: // FX15
			DelayTimerEqualVX();
			break;
		case 0x0018: // FX18
			SoundTimerEqualVX();
			break;
		case 0x01E: // FX1E
			AddVXToIndexRegister();
			break;
		case 0x0029: // 0xFX29
			SetIndexRegisterToSpritePos();
			break;
		case 0x0033: // 0xFX33
			StoreBinaryCodedDecimal();
			break;
		case 0x055: // FX55
			StoreV0toVX();
			break;
		case 0x0065: // 0xFX65
			FillV0toVX();
			break;
		default:
			printf("Unkown opcode: 0x%X\n", myOpCode);
			break;
		}
		break;
	}
	default:
		printf("Unkown opcode: 0x%X\n", myOpCode);
		break;
	}

}

void Chip8::Fetch()
{
	myOpCode = myMemory[myProgramCounter] << 8 | myMemory[myProgramCounter + 1];
}

inline void Chip8::AddNNToVX()
{
	V[(myOpCode & 0x0F00) >> 8] += (myOpCode & 0x00FF);
	myProgramCounter += 2;
}

inline void Chip8::AddVYtoVX()
{
	if (V[(myOpCode & 0x00F0) >> 4] > (0xFF - V[(myOpCode & 0x0F00) >> 8]))
		V[0xF] = 1;
	else
		V[0xF] = 0;
	V[(myOpCode & 0x0F00) >> 8] += V[(myOpCode & 0x00F0) >> 4];
	myProgramCounter += 2;
}

inline void Chip8::VXMinusVY()
{
	if (V[(myOpCode & 0x00F0) >> 4] > (0xFF - V[(myOpCode & 0x0F00) >> 8]))
		V[0xF] = 0;
	else
		V[0xF] = 1;
	V[(myOpCode & 0x0F00) >> 8] -= V[(myOpCode & 0x00F0) >> 4];
	myProgramCounter += 2;
}

inline void Chip8::VXNotEqualVY()
{

	if (V[(myOpCode & 0x0F00) >> 8] != V[(myOpCode & 0x00F0) >> 4])
		myProgramCounter += 4;
	else
		myProgramCounter += 2;
}

inline void Chip8::VYMinusVX()
{
	if (V[(myOpCode & 0x0F00) >> 8] > V[(myOpCode & 0x00F0) >> 4])	// VY-VX
		V[0xF] = 0; // there is a borrow
	else
		V[0xF] = 1;
	V[(myOpCode & 0x0F00) >> 8] = V[(myOpCode & 0x00F0) >> 4] - V[(myOpCode & 0x0F00) >> 8];
	myProgramCounter += 2;
}

inline void Chip8::ShiftVXtoRight()
{
	V[0xF] = V[(myOpCode & 0x0F00) >> 8] & 0x1;
	V[(myOpCode & 0x0F00) >> 8] >>= 1;
	myProgramCounter += 2;
}

inline void Chip8::ShiftVXtoLeft()
{
	V[0xF] = V[(myOpCode & 0x0F00) >> 8] >> 7;
	V[(myOpCode & 0x0F00) >> 8] <<= 1;
	myProgramCounter += 2;
}

inline void Chip8::SetIndexRegister()
{
	myIndexRegister = myOpCode & 0x0FFF;
	myProgramCounter += 2;
}

inline void Chip8::RandomNr()
{
	const short rng = static_cast<short>(CommonUtilities::GenerateRandomNr(0, 255));
	V[(myOpCode & 0x0F00) >> 8] = rng & (myOpCode & 0x00FF);
	myProgramCounter += 2;
}

inline void Chip8::DrawSprite()
{
	unsigned short x = V[(myOpCode & 0x0F00) >> 8];
	unsigned short y = V[(myOpCode & 0x00F0) >> 4];
	unsigned short height = myOpCode & 0x000F;
	unsigned short pixel;

	V[0xF] = 0;
	for (int yLine = 0; yLine < height; ++yLine)
	{
		pixel = myMemory[myIndexRegister + yLine];
		for (int xLine = 0; xLine < 8; ++xLine)
		{
			if ((pixel & (0x80 >> xLine)) != 0)
			{
				if (myGfx[(x + xLine + ((y + yLine) * 64))] == 1)
				{
					V[0xF] = 1;
				}
				myGfx[x + xLine + ((y + yLine) * 64)] ^= 1;
			}
		}
	}
	myDrawFlag = true;
	myProgramCounter += 2;
}

inline void Chip8::IfKeyIsPressed()
{
	if (myKey[V[(myOpCode & 0x0F00) >> 8]] != 0)
		myProgramCounter += 4;
	else
		myProgramCounter += 2;
}

inline void Chip8::IfKeyIsNotPressed()
{
	if (myKey[V[(myOpCode & 0x0F00) >> 8]] == 0)
		myProgramCounter += 4;
	else
		myProgramCounter += 2;
}

inline void Chip8::VXEqualDelayTimer()
{
	V[(myOpCode & 0x0F00) >> 8] = myDelayTimer;
	myProgramCounter += 2;
}

inline void Chip8::DelayTimerEqualVX()
{
	myDelayTimer = V[(myOpCode & 0x0F00) >> 8];
	myProgramCounter += 2;
}

inline void Chip8::SoundTimerEqualVX()
{
	mySoundTimer = V[(myOpCode & 0x0F00) >> 8];
	myProgramCounter += 2;
}

inline void Chip8::AddVXToIndexRegister()
{
	if ((myIndexRegister + V[(myOpCode & 0x0F00) >> 8]) > 0xFFF)
		V[0xF] = 1;
	else
		V[0xF] = 0;
	myIndexRegister += V[(myOpCode & 0x0F00) >> 8];
	myProgramCounter += 2;
}

inline void Chip8::SetIndexRegisterToSpritePos()
{
	myIndexRegister = V[(myOpCode & 0x0F00) >> 8] * 0x5;
	myProgramCounter += 2;
}

inline void Chip8::StoreBinaryCodedDecimal()
{
	myMemory[myIndexRegister] = V[(myOpCode & 0x0F00) >> 8] / 100;
	myMemory[myIndexRegister + 1] = (V[(myOpCode & 0x0F00) >> 8] / 10) % 10;
	myMemory[myIndexRegister + 2] = (V[(myOpCode & 0x0F00) >> 8] % 100) % 10;
	myProgramCounter += 2;
}

inline void Chip8::StoreV0toVX()
{
	for (int i = 0; i <= ((myOpCode & 0x0F00) >> 8); ++i)
	{
		myMemory[myIndexRegister + i] = V[i];
	}
	myIndexRegister += ((myOpCode & 0x0F00) >> 8) + 1;
	myProgramCounter += 2;
}

inline void Chip8::FillV0toVX()
{
	for (int i = 0; i <= ((myOpCode & 0x0F00) >> 8); ++i)
	{
		V[i] = myMemory[myIndexRegister + i];
	}
	myIndexRegister += ((myOpCode & 0x0F00) >> 8) + 1;
	myProgramCounter += 2;
}
