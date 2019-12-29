#pragma once
#include <string>

class Chip8
{
public:
	void Initialize();
	void EmulateCycle(float aDelta);
	void LoadGame(const std::string& aFilePath);
	void KeyboardDown();
	void KeyboardUp();
	void UpdateTimers();
	bool myDrawFlag;
	static unsigned char myGfx[64 * 32];
private:
	void Decode();
	void Fetch();

	inline void AddNNToVX();
	inline void AddVYtoVX();
	inline void AddVXToIndexRegister();

	inline void CallSubRoutine();
	inline void ClearScreen();
	
	inline void DelayTimerEqualVX();
	inline void DrawSprite();
	
	inline void FillV0toVX();
	
	inline void JumpToAddres();
	inline void JumpToAddresPlusVO();
	
	inline void IfKeyIsPressed();
	inline void IfKeyIsNotPressed();
	inline void IfVXEqualNN();
	inline void IfVXNotEqualNN();
	inline void IfVXEqualVY();
	
	inline void RandomNr();
	inline void ReturnFromSubRoutine();
	
	inline void SetVXToNN();
	inline void SetVXtoVY();
	inline void SetIndexRegisterToSpritePos();
	inline void ShiftVXtoRight();
	inline void ShiftVXtoLeft();
	inline void SetIndexRegister();
	inline void SoundTimerEqualVX();
	inline void StoreBinaryCodedDecimal();
	inline void StoreV0toVX();
	
	inline void VXorVY();
	inline void VXandVY();
	inline void VXxorVY();
	inline void VXMinusVY();
	inline void VXNotEqualVY();
	inline void VYMinusVX();
	inline void VXEqualDelayTimer();

	unsigned char myMemory[4096];

	unsigned char V[16];

	unsigned short myIndexRegister;
	unsigned short myProgramCounter;


	unsigned char myDelayTimer;
	unsigned char mySoundTimer;

	unsigned short myStack[16];
	unsigned short myStackPointer;
	unsigned short myOpCode;

	unsigned char myKey[16];

	float myHertzTimer;
};

