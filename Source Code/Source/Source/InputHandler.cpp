#include "InputHandler.hpp"
#include <cassert>

namespace CommonUtilities
{
	InputHandler& InputHandler::GetInstance()
	{
		static InputHandler instance;
		return instance;
	}

	InputHandler::InputHandler() :
		myMouseDeltaX (0),
		myMouseDeltaY (0),
		myMouseWheelDelta (0)
	{
		myCurrentState.myKeys.insert({ Key::Escape, false });
		myLastState.myKeys.insert({ Key::Escape, false });
		myCurrentState.myKeys.insert({ Key::Enter, false });
		myLastState.myKeys.insert({ Key::Enter, false });
		myCurrentState.myKeys.insert({ Key::Tab, false });
		myLastState.myKeys.insert({ Key::Tab, false });
		myCurrentState.myKeys.insert({ Key::Backspace, false });
		myLastState.myKeys.insert({ Key::Backspace, false });

		myCurrentState.myKeys.insert({ Key::Up, false });
		myLastState.myKeys.insert({ Key::Up, false });
		myCurrentState.myKeys.insert({ Key::Down, false });
		myLastState.myKeys.insert({ Key::Down, false });
		myCurrentState.myKeys.insert({ Key::Left, false });
		myLastState.myKeys.insert({ Key::Left, false });
		myCurrentState.myKeys.insert({ Key::Right, false });
		myLastState.myKeys.insert({ Key::Right, false });

		myCurrentState.myKeys.insert({ Key::Zero, false });
		myLastState.myKeys.insert({ Key::Zero, false });
		myCurrentState.myKeys.insert({ Key::One, false });
		myLastState.myKeys.insert({ Key::One, false });
		myCurrentState.myKeys.insert({ Key::Two, false });
		myLastState.myKeys.insert({ Key::Two, false });
		myCurrentState.myKeys.insert({ Key::Three, false });
		myLastState.myKeys.insert({ Key::Three, false });
		myCurrentState.myKeys.insert({ Key::Four, false });
		myLastState.myKeys.insert({ Key::Four, false });
		myCurrentState.myKeys.insert({ Key::Five, false });
		myLastState.myKeys.insert({ Key::Five, false });
		myCurrentState.myKeys.insert({ Key::Six, false });
		myLastState.myKeys.insert({ Key::Six, false });
		myCurrentState.myKeys.insert({ Key::Seven, false });
		myLastState.myKeys.insert({ Key::Seven, false });
		myCurrentState.myKeys.insert({ Key::Eight, false });
		myLastState.myKeys.insert({ Key::Eight, false });
		myCurrentState.myKeys.insert({ Key::Nine, false });
		myLastState.myKeys.insert({ Key::Nine, false });

		myCurrentState.myKeys.insert({ Key::A, false });
		myLastState.myKeys.insert({ Key::A, false });
		myCurrentState.myKeys.insert({ Key::B, false });
		myLastState.myKeys.insert({ Key::B, false });
		myCurrentState.myKeys.insert({ Key::C, false });
		myLastState.myKeys.insert({ Key::C, false });
		myCurrentState.myKeys.insert({ Key::D, false });
		myLastState.myKeys.insert({ Key::D, false });
		myCurrentState.myKeys.insert({ Key::E, false });
		myLastState.myKeys.insert({ Key::E, false });
		myCurrentState.myKeys.insert({ Key::F, false });
		myLastState.myKeys.insert({ Key::F, false });
		myCurrentState.myKeys.insert({ Key::G, false });
		myLastState.myKeys.insert({ Key::G, false });
		myCurrentState.myKeys.insert({ Key::H, false });
		myLastState.myKeys.insert({ Key::H, false });
		myCurrentState.myKeys.insert({ Key::I, false });
		myLastState.myKeys.insert({ Key::I, false });
		myCurrentState.myKeys.insert({ Key::J, false });
		myLastState.myKeys.insert({ Key::J, false });
		myCurrentState.myKeys.insert({ Key::K, false });
		myLastState.myKeys.insert({ Key::K, false });
		myCurrentState.myKeys.insert({ Key::L, false });
		myLastState.myKeys.insert({ Key::L, false });
		myCurrentState.myKeys.insert({ Key::M, false });
		myLastState.myKeys.insert({ Key::M, false });
		myCurrentState.myKeys.insert({ Key::N, false });
		myLastState.myKeys.insert({ Key::N, false });
		myCurrentState.myKeys.insert({ Key::O, false });
		myLastState.myKeys.insert({ Key::O, false });
		myCurrentState.myKeys.insert({ Key::P, false });
		myLastState.myKeys.insert({ Key::P, false });
		myCurrentState.myKeys.insert({ Key::Q, false });
		myLastState.myKeys.insert({ Key::Q, false });
		myCurrentState.myKeys.insert({ Key::R, false });
		myLastState.myKeys.insert({ Key::R, false });
		myCurrentState.myKeys.insert({ Key::S, false });
		myLastState.myKeys.insert({ Key::S, false });
		myCurrentState.myKeys.insert({ Key::T, false });
		myLastState.myKeys.insert({ Key::T, false });
		myCurrentState.myKeys.insert({ Key::U, false });
		myLastState.myKeys.insert({ Key::U, false });
		myCurrentState.myKeys.insert({ Key::V, false });
		myLastState.myKeys.insert({ Key::V, false });
		myCurrentState.myKeys.insert({ Key::W, false });
		myLastState.myKeys.insert({ Key::W, false });
		myCurrentState.myKeys.insert({ Key::X, false });
		myLastState.myKeys.insert({ Key::X, false });
		myCurrentState.myKeys.insert({ Key::Z, false });
		myLastState.myKeys.insert({ Key::Z, false });

		myCurrentState.myCursorScreenPos.x = 0;
		myCurrentState.myCursorScreenPos.y = 0;
		myCurrentState.myLeftButtonDown = false;
		myCurrentState.myMiddleButtonDown = false;
		myCurrentState.myRightButtonDown = false;
		myCurrentState.myMouseInBounds = false;
		myCurrentState.myMouseLocalXPos = 0;
		myCurrentState.myMouseLocalYPos = 0;
		myCurrentState.myMouseWheelDelta = 0;

		myLastState.myCursorScreenPos.x = 0;
		myLastState.myCursorScreenPos.y = 0;
		myLastState.myLeftButtonDown = false;
		myLastState.myMiddleButtonDown = false;
		myLastState.myRightButtonDown = false;
		myLastState.myMouseInBounds = false;
		myLastState.myMouseLocalXPos = 0;
		myLastState.myMouseLocalYPos = 0;
		myLastState.myMouseWheelDelta = 0;

		GetCursorPos(&myCurrentState.myCursorScreenPos);
		myLastState.myCursorScreenPos = myCurrentState.myCursorScreenPos;
	}

	bool InputHandler::UpdateEvents(UINT aMessage, WPARAM aWParam, LPARAM aLParam)
	{
		assert(false);
		switch (aMessage)
		{
			case WM_LBUTTONDOWN:
			{
				myBufferState.myLeftButtonDown = true;
				if (myHandle)
				{
					SetCapture(myHandle);
				}
				return true;
				break;
			}
			case WM_LBUTTONUP:
			{
				myBufferState.myLeftButtonDown = false;
				ReleaseCapture();
				return true;
				break;
			}
			case WM_RBUTTONDOWN:
			{
				myBufferState.myRightButtonDown = true;
				if (myHandle)
				{
					SetCapture(myHandle);
				}
				return true;
				break;
			}
			case WM_RBUTTONUP:
			{
				myBufferState.myRightButtonDown = false;
				ReleaseCapture();
				return true;
				break;
			}
			case WM_MBUTTONDOWN:
			{
				myBufferState.myMiddleButtonDown = true;
				if (myHandle)
				{
					SetCapture(myHandle);
				}
				return true;
				break;
			}
			case WM_MBUTTONUP:
			{
				myBufferState.myMiddleButtonDown = false;
				ReleaseCapture();
				return true;
				break;
			}
			case WM_KEYDOWN:
			{
				Key result = Key::Count;
				switch (aWParam)
				{
					case VK_RETURN:
					{
						result = Key::Enter;
						break;
					}
					case VK_ESCAPE:
					{
						result = Key::Escape;
						break;
					}
					case VK_TAB:
					{
						result = Key::Tab;
						break;
					}
					case VK_BACK:
					{
						result = Key::Backspace;
						break;
					}
					case VK_SPACE:
					{
						result = Key::Space;
						break;
					}
					case VK_LEFT:
					{
						result = Key::Left;
						break;
					}
					case VK_RIGHT:
					{
						result = Key::Right;
						break;
					}
					case VK_UP:
					{
						result = Key::Up;
						break;
					}
					case VK_DOWN:
					{
						result = Key::Down;
						break;
					}
					case 0x30:
					{
						result = Key::Zero;
						break;
					}
					case 0x31:
					{
						result = Key::One;
						break;
					}
					case 0x32:
					{
						result = Key::Two;
						break;
					}
					case 0x33:
					{
						result = Key::Three;
						break;
					}
					case 0x34:
					{
						result = Key::Four;
						break;
					}
					case 0x35:
					{
						result = Key::Five;
						break;
					}
					case 0x36:
					{
						result = Key::Six;
						break;
					}
					case 0x37:
					{
						result = Key::Seven;
						break;
					}
					case 0x38:
					{
						result = Key::Eight;
						break;
					}
					case 0x39:
					{
						result = Key::Nine;
						break;
					}
					case 0x41:
					{
						result = Key::A;
						break;
					}
					case 0x42:
					{
						result = Key::B;
						break;
					}
					case 0x43:
					{
						result = Key::C;
						break;
					}
					case 0x44:
					{
						result = Key::D;
						break;
					}
					case 0x45:
					{
						result = Key::E;
						break;
					}
					case 0x46:
					{
						result = Key::F;
						break;
					}
					case 0x47:
					{
						result = Key::G;
						break;
					}
					case 0x48:
					{
						result = Key::H;
						break;
					}
					case 0x49:
					{
						result = Key::I;
						break;
					}
					case 0x4A:
					{
						result = Key::J;
						break;
					}
					case 0x4B:
					{
						result = Key::K;
						break;
					}
					case 0x4C:
					{
						result = Key::L;
						break;
					}
					case 0x4D:
					{
						result = Key::M;
						break;
					}
					case 0x4E:
					{
						result = Key::N;
						break;
					}
					case 0x4F:
					{
						result = Key::O;
						break;
					}
					case 0x50:
					{
						result = Key::P;
						break;
					}
					case 0x51:
					{
						result = Key::Q;
						break;
					}
					case 0x52:
					{
						result = Key::R;
						break;
					}
					case 0x53:
					{
						result = Key::S;
						break;
					}
					case 0x54:
					{
						result = Key::T;
						break;
					}
					case 0x55:
					{
						result = Key::U;
						break;
					}
					case 0x56:
					{
						result = Key::V;
						break;
					}
					case 0x57:
					{
						result = Key::W;
						break;
					}
					case 0x58:
					{
						result = Key::X;
						break;
					}
					case 0x59:
					{
						result = Key::Y;
						break;
					}
					case 0x5A:
					{
						result = Key::Z;
						break;
					}
					case 0xDD:
					{
						result = Key::Aoverring;
						break;
					}
					case 0xDE:
					{
						result = Key::Aumlaut;
						break;
					}
					case 0xC0:
					{
						result = Key::Oumlaut;
						break;
					}
					case VK_F1:
					{
						result = Key::F1;
						break;
					}
					case VK_F2:
					{
						result = Key::F2;
						break;
					}
					case VK_F3:
					{
						result = Key::F3;
						break;
					}
					case VK_F4:
					{
						result = Key::F4;
						break;
					}
					case VK_F5:
					{
						result = Key::F5;
						break;
					}
					case VK_F6:
					{
						result = Key::F6;
						break;
					}
					case VK_F7:
					{
						result = Key::F7;
						break;
					}
					case VK_F8:
					{
						result = Key::F8;
						break;
					}
					case VK_F9:
					{
						result = Key::F9;
						break;
					}
					case VK_F10:
					{
						result = Key::F10;
						break;
					}
					case VK_F11:
					{
						result = Key::F11;
						break;
					}
					case VK_F12:
					{
						result = Key::F12;
						break;
					}
					case 0xBE:
					{
						result = Key::Dot;
						break;
					}
					case 0xBD:
					{
						result = Key::Minus;
						break;
					}
					case 0xBC:
					{
						result = Key::Comma;
						break;
					}
					case 0xBB:
					{
						result = Key::Plus;
						break;
					}
					case 0xBA:
					{
						result = Key::Umlaut;
						break;
					}
					case 0xBF:
					{
						result = Key::SingleQuote;
						break;
					}
					case 0xDC:
					{
						result = Key::Paragraph;
						break;
					}
					case 0xDB:
					{
						result = Key::Accent;
						break;
					}
					case VK_PRIOR:
					{
						result = Key::PageUp;
						break;
					}
					case VK_NEXT:
					{
						result = Key::PageDown;
						break;
					}
					case VK_END:
					{
						result = Key::End;
						break;
					}
					case VK_HOME:
					{
						result = Key::Home;
						break;
					}
					case VK_INSERT:
					{
						result = Key::Insert;
						break;
					}
					case VK_DELETE:
					{
						result = Key::Delete;
						break;
					}
					case VK_SHIFT:
					{
						result = Key::Shift;
						break;
					}
					case VK_CONTROL:
					{
						result = Key::Control;
						break;
					}
					case VK_MENU:
					{
						result = Key::Alt;
						break;
					}
					case VK_CAPITAL:
					{
						result = Key::Caps;
						break;
					}
					case VK_NUMPAD0:
					{
						result = Key::NumZero;
						break;
					}
					case VK_NUMPAD1:
					{
						result = Key::NumOne;
						break;
					}
					case VK_NUMPAD2:
					{
						result = Key::NumTwo;
						break;
					}
					case VK_NUMPAD3:
					{
						result = Key::NumThree;
						break;
					}
					case VK_NUMPAD4:
					{
						result = Key::NumFour;
						break;
					}
					case VK_NUMPAD5:
					{
						result = Key::NumFive;
						break;
					}
					case VK_NUMPAD6:
					{
						result = Key::NumSix;
						break;
					}
					case VK_NUMPAD7:
					{
						result = Key::NumSeven;
						break;
					}
					case VK_NUMPAD8:
					{
						result = Key::NumEight;
						break;
					}
					case VK_NUMPAD9:
					{
						result = Key::NumNine;
						break;
					}
					case VK_ADD:
					{
						result = Key::NumAdd;
						break;
					}
					case VK_SUBTRACT:
					{
						result = Key::NumSubtract;
						break;
					}
					case VK_MULTIPLY:
					{
						result = Key::NumMultiply;
						break;
					}
					case VK_SEPARATOR:
					{
						result = Key::NumSeparator;
						break;
					}
					case VK_DECIMAL:
					{
						result = Key::NumDecimal;
						break;
					}
					case VK_DIVIDE:
					{
						result = Key::NumDivide;
						break;
					}
					case 0xE2:
					{
						result = Key::Bracket;
						break;
					}
				}

				if (result != Key::Count)
				{
					myBufferState.myKeys[result] = true;
				}

				return true;
				break;
			}
			case WM_KEYUP:
			{
				Key result = Key::Count;
				switch (aWParam)
				{
					case VK_RETURN:
					{
						result = Key::Enter;
						break;
					}
					case VK_ESCAPE:
					{
						result = Key::Escape;
						break;
					}
					case VK_TAB:
					{
						result = Key::Tab;
						break;
					}
					case VK_BACK:
					{
						result = Key::Backspace;
						break;
					}
					case VK_SPACE:
					{
						result = Key::Space;
						break;
					}
					case VK_LEFT:
					{
						result = Key::Left;
						break;
					}
					case VK_RIGHT:
					{
						result = Key::Right;
						break;
					}
					case VK_UP:
					{
						result = Key::Up;
						break;
					}
					case VK_DOWN:
					{
						result = Key::Down;
						break;
					}
					case 0x30:
					{
						result = Key::Zero;
						break;
					}
					case 0x31:
					{
						result = Key::One;
						break;
					}
					case 0x32:
					{
						result = Key::Two;
						break;
					}
					case 0x33:
					{
						result = Key::Three;
						break;
					}
					case 0x34:
					{
						result = Key::Four;
						break;
					}
					case 0x35:
					{
						result = Key::Five;
						break;
					}
					case 0x36:
					{
						result = Key::Six;
						break;
					}
					case 0x37:
					{
						result = Key::Seven;
						break;
					}
					case 0x38:
					{
						result = Key::Eight;
						break;
					}
					case 0x39:
					{
						result = Key::Nine;
						break;
					}
					case 0x41:
					{
						result = Key::A;
						break;
					}
					case 0x42:
					{
						result = Key::B;
						break;
					}
					case 0x43:
					{
						result = Key::C;
						break;
					}
					case 0x44:
					{
						result = Key::D;
						break;
					}
					case 0x45:
					{
						result = Key::E;
						break;
					}
					case 0x46:
					{
						result = Key::F;
						break;
					}
					case 0x47:
					{
						result = Key::G;
						break;
					}
					case 0x48:
					{
						result = Key::H;
						break;
					}
					case 0x49:
					{
						result = Key::I;
						break;
					}
					case 0x4A:
					{
						result = Key::J;
						break;
					}
					case 0x4B:
					{
						result = Key::K;
						break;
					}
					case 0x4C:
					{
						result = Key::L;
						break;
					}
					case 0x4D:
					{
						result = Key::M;
						break;
					}
					case 0x4E:
					{
						result = Key::N;
						break;
					}
					case 0x4F:
					{
						result = Key::O;
						break;
					}
					case 0x50:
					{
						result = Key::P;
						break;
					}
					case 0x51:
					{
						result = Key::Q;
						break;
					}
					case 0x52:
					{
						result = Key::R;
						break;
					}
					case 0x53:
					{
						result = Key::S;
						break;
					}
					case 0x54:
					{
						result = Key::T;
						break;
					}
					case 0x55:
					{
						result = Key::U;
						break;
					}
					case 0x56:
					{
						result = Key::V;
						break;
					}
					case 0x57:
					{
						result = Key::W;
						break;
					}
					case 0x58:
					{
						result = Key::X;
						break;
					}
					case 0x59:
					{
						result = Key::Y;
						break;
					}
					case 0x5A:
					{
						result = Key::Z;
						break;
					}
					case 0xDD:
					{
						result = Key::Aoverring;
						break;
					}
					case 0xDE:
					{
						result = Key::Aumlaut;
						break;
					}
					case 0xC0:
					{
						result = Key::Oumlaut;
						break;
					}
					case VK_F1:
					{
						result = Key::F1;
						break;
					}
					case VK_F2:
					{
						result = Key::F2;
						break;
					}
					case VK_F3:
					{
						result = Key::F3;
						break;
					}
					case VK_F4:
					{
						result = Key::F4;
						break;
					}
					case VK_F5:
					{
						result = Key::F5;
						break;
					}
					case VK_F6:
					{
						result = Key::F6;
						break;
					}
					case VK_F7:
					{
						result = Key::F7;
						break;
					}
					case VK_F8:
					{
						result = Key::F8;
						break;
					}
					case VK_F9:
					{
						result = Key::F9;
						break;
					}
					case VK_F10:
					{
						result = Key::F10;
						break;
					}
					case VK_F11:
					{
						result = Key::F11;
						break;
					}
					case VK_F12:
					{
						result = Key::F12;
						break;
					}
					case 0xBE:
					{
						result = Key::Dot;
						break;
					}
					case 0xBD:
					{
						result = Key::Minus;
						break;
					}
					case 0xBC:
					{
						result = Key::Comma;
						break;
					}
					case 0xBB:
					{
						result = Key::Plus;
						break;
					}
					case 0xBA:
					{
						result = Key::Umlaut;
						break;
					}
					case 0xBF:
					{
						result = Key::SingleQuote;
						break;
					}
					case 0xDC:
					{
						result = Key::Paragraph;
						break;
					}
					case 0xDB:
					{
						result = Key::Accent;
						break;
					}
					case VK_PRIOR:
					{
						result = Key::PageUp;
						break;
					}
					case VK_NEXT:
					{
						result = Key::PageDown;
						break;
					}
					case VK_END:
					{
						result = Key::End;
						break;
					}
					case VK_HOME:
					{
						result = Key::Home;
						break;
					}
					case VK_INSERT:
					{
						result = Key::Insert;
						break;
					}
					case VK_DELETE:
					{
						result = Key::Delete;
						break;
					}
					case VK_SHIFT:
					{
						result = Key::Shift;
						break;
					}
					case VK_CONTROL:
					{
						result = Key::Control;
						break;
					}
					case VK_MENU:
					{
						result = Key::Alt;
						break;
					}
					case VK_CAPITAL:
					{
						result = Key::Caps;
						break;
					}
					case VK_NUMPAD0:
					{
						result = Key::NumZero;
						break;
					}
					case VK_NUMPAD1:
					{
						result = Key::NumOne;
						break;
					}
					case VK_NUMPAD2:
					{
						result = Key::NumTwo;
						break;
					}
					case VK_NUMPAD3:
					{
						result = Key::NumThree;
						break;
					}
					case VK_NUMPAD4:
					{
						result = Key::NumFour;
						break;
					}
					case VK_NUMPAD5:
					{
						result = Key::NumFive;
						break;
					}
					case VK_NUMPAD6:
					{
						result = Key::NumSix;
						break;
					}
					case VK_NUMPAD7:
					{
						result = Key::NumSeven;
						break;
					}
					case VK_NUMPAD8:
					{
						result = Key::NumEight;
						break;
					}
					case VK_NUMPAD9:
					{
						result = Key::NumNine;
						break;
					}
					case VK_ADD:
					{
						result = Key::NumAdd;
						break;
					}
					case VK_SUBTRACT:
					{
						result = Key::NumSubtract;
						break;
					}
					case VK_MULTIPLY:
					{
						result = Key::NumMultiply;
						break;
					}
					case VK_SEPARATOR:
					{
						result = Key::NumSeparator;
						break;
					}
					case VK_DECIMAL:
					{
						result = Key::NumDecimal;
						break;
					}
					case VK_DIVIDE:
					{
						result = Key::NumDivide;
						break;
					}
					case 0xE2:
					{
						result = Key::Bracket;
						break;
					}
				}

				if (result != Key::Count)
				{
					myBufferState.myKeys[result] = false;
				}

				return true;
				break;
			}
			case WM_MOUSELEAVE:
			{
				myBufferState.myMouseInBounds = false;
				Clear();
				return true;
				break;
			}
			case WM_MOUSEMOVE:
			{
				myBufferState.myMouseInBounds = true;
				myBufferState.myMouseLocalXPos = GET_X_LPARAM(aLParam);
				myBufferState.myMouseLocalYPos = GET_Y_LPARAM(aLParam);

				return true;
				break;
			}
			case WM_MOUSEWHEEL:
			{
				myBufferState.myMouseWheelDelta = GET_WHEEL_DELTA_WPARAM(aWParam);
				return true;
				break;
			}
			case WM_ACTIVATE:
			{
				myBufferState.myMouseInBounds = false;
				Clear();
				return true;
				break;
			}
		}

		return false;
	}

	void InputHandler::Update()
	{
		//Update last:

		myLastState.myKeys = myCurrentState.myKeys;
		myLastState.myLeftButtonDown = myCurrentState.myLeftButtonDown;
		myLastState.myRightButtonDown = myCurrentState.myRightButtonDown;
		myLastState.myMiddleButtonDown = myCurrentState.myMiddleButtonDown;
		myLastState.myCursorScreenPos = myCurrentState.myCursorScreenPos;
		myLastState.myMouseLocalXPos = myCurrentState.myMouseLocalXPos;
		myLastState.myMouseLocalYPos = myCurrentState.myMouseLocalYPos;

		//myLastState.myMouseWheelDelta = myCurrentState.myMouseWheelDelta;

		//Update delta

		myMouseDeltaX = myBufferState.myMouseLocalXPos - myCurrentState.myMouseLocalXPos;
		myMouseDeltaY = myBufferState.myMouseLocalYPos - myCurrentState.myMouseLocalYPos;
		myCurrentState.myMouseWheelDelta = myBufferState.myMouseWheelDelta;

		//Update current:

		myCurrentState.myKeys = myBufferState.myKeys;
		myCurrentState.myLeftButtonDown = myBufferState.myLeftButtonDown;
		myCurrentState.myRightButtonDown = myBufferState.myRightButtonDown;
		myCurrentState.myMiddleButtonDown = myBufferState.myMiddleButtonDown;
		GetCursorPos(&myCurrentState.myCursorScreenPos);
		myCurrentState.myMouseLocalXPos = myBufferState.myMouseLocalXPos;
		myCurrentState.myMouseLocalYPos = myBufferState.myMouseLocalYPos;

		//Clear buffer
		myBufferState.myMouseWheelDelta = 0;

	}

	bool InputHandler::ButtonIsDown(MouseButton aButton) const
	{
		switch (aButton)
		{
			case MouseButton::Left:
			{
				return myCurrentState.myLeftButtonDown;
				break;
			}
			case MouseButton::Right:
			{
				return myCurrentState.myRightButtonDown;
				break;
			}
			case MouseButton::Middle:
			{
				return myCurrentState.myMiddleButtonDown;
				break;
			}
		}

		return false;
	}

	bool InputHandler::ButtonWasPressed(MouseButton aButton) const
	{
		switch (aButton)
		{
			case MouseButton::Left:
			{
				return myCurrentState.myLeftButtonDown && !myLastState.myLeftButtonDown;
				break;
			}
			case MouseButton::Middle:
			{
				return myCurrentState.myMiddleButtonDown && !myLastState.myMiddleButtonDown;
				break;
			}
			case MouseButton::Right:
			{
				return myCurrentState.myRightButtonDown && !myLastState.myRightButtonDown;
				break;
			}
		}
		return false;
	}

	bool InputHandler::ButtonWasReleased(MouseButton aButton) const
	{
		switch (aButton)
		{
			case MouseButton::Left:
			{
				return !myCurrentState.myLeftButtonDown && myLastState.myLeftButtonDown;
				break;
			}
			case MouseButton::Middle:
			{
				return !myCurrentState.myMiddleButtonDown && myLastState.myMiddleButtonDown;
				break;
			}
			case MouseButton::Right:
			{
				return !myCurrentState.myRightButtonDown && myLastState.myRightButtonDown;
				break;
			}

			default:
				break;
		}
		return false;
	}

	bool InputHandler::KeyIsDown(Key aKey)
	{
		return myCurrentState.myKeys[aKey];
	}

	bool InputHandler::KeyWasPressed(Key aKey)
	{
		return myCurrentState.myKeys[aKey] && !myLastState.myKeys[aKey];
	}

	bool InputHandler::KeyWasReleased(Key aKey)
	{
		return !myCurrentState.myKeys[aKey] && myLastState.myKeys[aKey];
	}

	int InputHandler::GetMouseLocalPosX() const
	{
		return myCurrentState.myMouseLocalXPos;
	}

	int InputHandler::GetMouseLocalPosY() const
	{
		return myCurrentState.myMouseLocalYPos;
	}
	
	long InputHandler::GetMouseScreenPosX() const
	{
		return myCurrentState.myCursorScreenPos.x;
	}

	long InputHandler::GetMouseScreenPosY() const
	{
		return myCurrentState.myCursorScreenPos.y;
	}

	int InputHandler::GetMouseDeltaX() const
	{
		return myMouseDeltaX;
	}

	int InputHandler::GetMouseDeltaY() const
	{
		return myMouseDeltaY;
	}

	void InputHandler::AttachWindow(HWND aHandle)
	{
		myHandle = aHandle;
	}

	HWND InputHandler::GetWindowHandle() const
	{
		return myHandle;
	}

	void InputHandler::Clear()
	{
		myCurrentState.myLeftButtonDown = false;
		myCurrentState.myMiddleButtonDown = false;
		myCurrentState.myRightButtonDown = false;
		for (auto& iterator : myCurrentState.myKeys)
		{
			iterator.second = false;
		}
	}

	bool InputHandler::GetMouseInBounds() const
	{
		return myCurrentState.myMouseInBounds;
	}

	bool InputHandler::SetMouseCursor(int aX, int aY)
	{
		return SetCursorPos(aX, aY);
	}

	int InputHandler::GetMouseWheelDelta() const
	{
		return myCurrentState.myMouseWheelDelta;
	}

}
