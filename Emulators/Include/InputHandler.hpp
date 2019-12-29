#pragma once
#include <Windows.h>
#include <windowsx.h>
#include <unordered_map>
#include <vector>

namespace CommonUtilities
{
	class InputHandler
	{
	public:
		enum class Key : int
		{ 
			Escape = VK_ESCAPE, 
			Enter = VK_RETURN,
			Tab = VK_TAB,
			Backspace = VK_BACK,
			Space = VK_SPACE,
			Up = VK_UP,
			Down = VK_DOWN,
			Left = VK_LEFT,
			Right = VK_RIGHT,
			Shift = VK_SHIFT,
			Control = VK_CONTROL,
			Alt = VK_MENU,
			Caps = VK_CAPITAL,
			NumZero = VK_NUMPAD0,
			NumOne = VK_NUMPAD1,
			NumTwo = VK_NUMPAD2,
			NumThree = VK_NUMPAD3,
			NumFour = VK_NUMPAD4,
			NumFive = VK_NUMPAD5,
			NumSix = VK_NUMPAD6,
			NumSeven = VK_NUMPAD7,
			NumEight = VK_NUMPAD8,
			NumNine = VK_NUMPAD9,
			NumAdd = VK_ADD,
			NumSubtract = VK_SUBTRACT,
			NumMultiply = VK_MULTIPLY,
			NumDecimal = VK_DECIMAL,
			NumSeparator = VK_SEPARATOR,
			NumDivide = VK_DIVIDE,
			Dot = 0xBE,
			Minus = 0xBD,
			Comma = 0xBC,
			Plus = 0xBB,
			Umlaut = 0xBA,
			SingleQuote = 0xBF,
			Paragraph = 0xDC,
			Accent = 0xDB,
			PageUp = VK_PRIOR,
			PageDown = VK_NEXT,
			End = VK_END,
			Home = VK_HOME,
			Insert = VK_INSERT,
			Delete = VK_DELETE,
			F1 = VK_F1,
			F2 = VK_F2,
			F3 = VK_F3,
			F4 = VK_F4,
			F5 = VK_F5,
			F6 = VK_F6,
			F7 = VK_F7,
			F8 = VK_F8,
			F9 = VK_F9,
			F10 = VK_F10,
			F11 = VK_F11,
			F12 = VK_F12,
			Zero = 0x30,
			One = 0x31,
			Two = 0x32,
			Three = 0x33,
			Four = 0x34,
			Five = 0x35,
			Six = 0x36,
			Seven = 0x37,
			Eight = 0x38,
			Nine = 0x39,
			A = 0x41,
			B = 0x42,
			C = 0x43,
			D = 0x44,
			E = 0x45,
			F = 0x46,
			G = 0x47,
			H = 0x48,
			I = 0x49,
			J = 0x4A,
			K = 0x4B,
			L = 0x4C,
			M = 0x4D,
			N = 0x4E,
			O = 0x4F,
			P = 0x50,
			Q = 0x51,
			R = 0x52,
			S = 0x53,
			T = 0x54,
			U = 0x55,
			V = 0x56,
			W = 0x57,
			X = 0x58,
			Y = 0x59,
			Z = 0x5A,
			Aoverring = 0xDD,
			Aumlaut = 0xDE,
			Oumlaut = 0xC0,
			Bracket = 0xE2,
			Count
		};

		enum class MouseButton {Left, Right, Middle};

		~InputHandler() = default;
		InputHandler(const InputHandler& aCopy) = delete;
		InputHandler& operator=(const InputHandler& aOther) = delete;

		static InputHandler& GetInstance();

		void AttachWindow(HWND aHandle);
		HWND GetWindowHandle() const;
		bool UpdateEvents(UINT aMessage, WPARAM aWParam, LPARAM aLParam);
		void Update();

		bool SetMouseCursor(int aX, int aY);

		bool ButtonIsDown(MouseButton aButton) const;
		bool ButtonWasPressed(MouseButton aButton) const;
		bool ButtonWasReleased(MouseButton aButton) const;
		bool KeyIsDown(Key aKey);
		bool KeyWasPressed(Key aKey);
		bool KeyWasReleased(Key aKey);

		bool GetMouseInBounds() const;
		int GetMouseLocalPosX() const;
		int GetMouseLocalPosY() const;
		long GetMouseScreenPosX() const;
		long GetMouseScreenPosY() const;
		int GetMouseDeltaX() const;
		int GetMouseDeltaY() const;
		int GetMouseWheelDelta() const;

	private:

		struct State
		{
			std::unordered_map<Key, bool> myKeys;
			POINT myCursorScreenPos;
			int myMouseLocalXPos;
			int myMouseLocalYPos;
			int myMouseWheelDelta;
			bool myLeftButtonDown;
			bool myMiddleButtonDown;
			bool myRightButtonDown;
			bool myMouseInBounds;
		};

		struct Message
		{
			UINT aMessage;
			WPARAM aWParam;
			LPARAM aLParam;
		};

		InputHandler();

		void Clear();

		State myBufferState;
		State myCurrentState;
		State myLastState;
		std::vector<Message> myMessageQueue;
		HWND myHandle;
		int myMouseDeltaX;
		int myMouseDeltaY;
		int myMouseWheelDelta;
		short myWindowWidth;
		short myWindowHeight;
	};
}