#include "sampo_pch.hpp"
#include "sampo/input/keyboard.hpp"

#include "sampo/events/key_event.hpp"

#include <GLFW/glfw3.h>

namespace Sampo
{
	KeyboardButton Keyboard::GetKeyboardButtonFromPlatform(int aKeyboardCode) const
	{
		KeyboardButton button = KeyboardButton::kUnknownButton;
		switch(aKeyboardCode)
		{
			case GLFW_KEY_SPACE: button = KeyboardButton::kBACKSPACE; break;
			case GLFW_KEY_APOSTROPHE: button = KeyboardButton::kAPOSTROPHE; break;
			case GLFW_KEY_COMMA: button = KeyboardButton::kCOMMA; break;
			case GLFW_KEY_MINUS: button = KeyboardButton::kMINUS; break;
			case GLFW_KEY_PERIOD: button = KeyboardButton::kPERIOD; break;
			case GLFW_KEY_SLASH: button = KeyboardButton::kSLASH; break;
			case GLFW_KEY_0: button = KeyboardButton::k0; break;
			case GLFW_KEY_1: button = KeyboardButton::k1; break;
			case GLFW_KEY_2: button = KeyboardButton::k2; break;
			case GLFW_KEY_3: button = KeyboardButton::k3; break;
			case GLFW_KEY_4: button = KeyboardButton::k4; break;
			case GLFW_KEY_5: button = KeyboardButton::k5; break;
			case GLFW_KEY_6: button = KeyboardButton::k6; break;
			case GLFW_KEY_7: button = KeyboardButton::k7; break;
			case GLFW_KEY_8: button = KeyboardButton::k8; break;
			case GLFW_KEY_9: button = KeyboardButton::k9; break;
			case GLFW_KEY_SEMICOLON: button = KeyboardButton::kSEMICOLON; break;
			case GLFW_KEY_EQUAL: button = KeyboardButton::kEQUAL; break;
			case GLFW_KEY_A: button = KeyboardButton::kA; break;
			case GLFW_KEY_B: button = KeyboardButton::kB; break;
			case GLFW_KEY_C: button = KeyboardButton::kC; break;
			case GLFW_KEY_D: button = KeyboardButton::kD; break;
			case GLFW_KEY_E: button = KeyboardButton::kE; break;
			case GLFW_KEY_F: button = KeyboardButton::kF; break;
			case GLFW_KEY_G: button = KeyboardButton::kG; break;
			case GLFW_KEY_H: button = KeyboardButton::kH; break;
			case GLFW_KEY_I: button = KeyboardButton::kI; break;
			case GLFW_KEY_J: button = KeyboardButton::kJ; break;
			case GLFW_KEY_K: button = KeyboardButton::kK; break;
			case GLFW_KEY_L: button = KeyboardButton::kL; break;
			case GLFW_KEY_M: button = KeyboardButton::kM; break;
			case GLFW_KEY_N: button = KeyboardButton::kN; break;
			case GLFW_KEY_O: button = KeyboardButton::kO; break;
			case GLFW_KEY_P: button = KeyboardButton::kP; break;
			case GLFW_KEY_Q: button = KeyboardButton::kQ; break;
			case GLFW_KEY_R: button = KeyboardButton::kR; break;
			case GLFW_KEY_S: button = KeyboardButton::kS; break;
			case GLFW_KEY_T: button = KeyboardButton::kT; break;
			case GLFW_KEY_U: button = KeyboardButton::kU; break;
			case GLFW_KEY_V: button = KeyboardButton::kV; break;
			case GLFW_KEY_W: button = KeyboardButton::kW; break;
			case GLFW_KEY_X: button = KeyboardButton::kX; break;
			case GLFW_KEY_Y: button = KeyboardButton::kY; break;
			case GLFW_KEY_Z: button = KeyboardButton::kZ; break;
			case GLFW_KEY_LEFT_BRACKET: button = KeyboardButton::kLEFT_BRACKET; break;
			case GLFW_KEY_BACKSLASH: button = KeyboardButton::kBACKSLASH; break;
			case GLFW_KEY_RIGHT_BRACKET: button = KeyboardButton::kRIGHT_BRACKET; break;
			case GLFW_KEY_GRAVE_ACCENT: button = KeyboardButton::kGRAVE_ACCENT; break;
			case GLFW_KEY_WORLD_1: button = KeyboardButton::kWorld1; break;
			case GLFW_KEY_WORLD_2: button = KeyboardButton::kWorld2; break;
			case GLFW_KEY_ESCAPE: button = KeyboardButton::kESCAPE; break;
			case GLFW_KEY_ENTER: button = KeyboardButton::kENTER; break;
			case GLFW_KEY_TAB: button = KeyboardButton::kTAB; break;
			case GLFW_KEY_BACKSPACE: button = KeyboardButton::kBACKSPACE; break;
			case GLFW_KEY_INSERT: button = KeyboardButton::kINSERT; break;
			case GLFW_KEY_DELETE: button = KeyboardButton::kDELETE; break;
			case GLFW_KEY_RIGHT: button = KeyboardButton::kRIGHT; break;
			case GLFW_KEY_LEFT: button = KeyboardButton::kLEFT; break;
			case GLFW_KEY_DOWN: button = KeyboardButton::kDOWN; break;
			case GLFW_KEY_UP: button = KeyboardButton::kUP; break;
			case GLFW_KEY_PAGE_UP: button = KeyboardButton::kPAGE_UP; break;
			case GLFW_KEY_PAGE_DOWN: button = KeyboardButton::kPAGE_DOWN; break;
			case GLFW_KEY_HOME: button = KeyboardButton::kHOME; break;
			case GLFW_KEY_END: button = KeyboardButton::kEND; break;
			case GLFW_KEY_CAPS_LOCK: button = KeyboardButton::kCAPS_LOCK; break;
			case GLFW_KEY_SCROLL_LOCK: button = KeyboardButton::kSCROLL_LOCK; break;
			case GLFW_KEY_NUM_LOCK: button = KeyboardButton::kNUM_LOCK; break;
			case GLFW_KEY_PRINT_SCREEN: button = KeyboardButton::kPRINT_SCREEN; break;
			case GLFW_KEY_PAUSE: button = KeyboardButton::kPAUSE; break;
			case GLFW_KEY_F1: button = KeyboardButton::kF1; break;
			case GLFW_KEY_F2: button = KeyboardButton::kF2; break;
			case GLFW_KEY_F3: button = KeyboardButton::kF3; break;
			case GLFW_KEY_F4: button = KeyboardButton::kF4; break;
			case GLFW_KEY_F5: button = KeyboardButton::kF5; break;
			case GLFW_KEY_F6: button = KeyboardButton::kF6; break;
			case GLFW_KEY_F7: button = KeyboardButton::kF7; break;
			case GLFW_KEY_F8: button = KeyboardButton::kF8; break;
			case GLFW_KEY_F9: button = KeyboardButton::kF9; break;
			case GLFW_KEY_F10: button = KeyboardButton::kF10; break;
			case GLFW_KEY_F11: button = KeyboardButton::kF11; break;
			case GLFW_KEY_F12: button = KeyboardButton::kF12; break;
			case GLFW_KEY_KP_0: button = KeyboardButton::kKP_0; break;
			case GLFW_KEY_KP_1: button = KeyboardButton::kKP_1; break;
			case GLFW_KEY_KP_2: button = KeyboardButton::kKP_2; break;
			case GLFW_KEY_KP_3: button = KeyboardButton::kKP_3; break;
			case GLFW_KEY_KP_4: button = KeyboardButton::kKP_4; break;
			case GLFW_KEY_KP_5: button = KeyboardButton::kKP_5; break;
			case GLFW_KEY_KP_6: button = KeyboardButton::kKP_6; break;
			case GLFW_KEY_KP_7: button = KeyboardButton::kKP_7; break;
			case GLFW_KEY_KP_8: button = KeyboardButton::kKP_8; break;
			case GLFW_KEY_KP_9: button = KeyboardButton::kKP_9; break;
			case GLFW_KEY_KP_DECIMAL: button = KeyboardButton::kKP_DECIMAL; break;
			case GLFW_KEY_KP_DIVIDE: button = KeyboardButton::kKP_DIVIDE; break;
			case GLFW_KEY_KP_MULTIPLY: button = KeyboardButton::kKP_MULTIPLY; break;
			case GLFW_KEY_KP_SUBTRACT: button = KeyboardButton::kKP_SUBTRACT; break;
			case GLFW_KEY_KP_ADD: button = KeyboardButton::kKP_ADD; break;
			case GLFW_KEY_KP_ENTER: button = KeyboardButton::kKP_ENTER; break;
			case GLFW_KEY_KP_EQUAL: button = KeyboardButton::kKP_EQUAL; break;
			case GLFW_KEY_LEFT_SHIFT: button = KeyboardButton::kLEFT_SHIFT; break;
			case GLFW_KEY_LEFT_CONTROL: button = KeyboardButton::kLEFT_CONTROL; break;
			case GLFW_KEY_LEFT_ALT: button = KeyboardButton::kLEFT_ALT; break;
			case GLFW_KEY_LEFT_SUPER: button = KeyboardButton::kLEFT_SUPER; break;
			case GLFW_KEY_RIGHT_SHIFT: button = KeyboardButton::kRIGHT_SHIFT; break;
			case GLFW_KEY_RIGHT_CONTROL: button = KeyboardButton::kRIGHT_CONTROL; break;
			case GLFW_KEY_RIGHT_ALT: button = KeyboardButton::kRIGHT_ALT; break;
			case GLFW_KEY_RIGHT_SUPER: button = KeyboardButton::kRIGHT_SUPER; break;
			case GLFW_KEY_MENU: button = KeyboardButton::kMENU; break;
		}
		return button;
	}

	void Keyboard::OnKeyboardEvent(Event& aKeyboardEvent)
	{
		switch (aKeyboardEvent.GetEventType())
		{
			case EventType::KeyPressed:
			{
				KeyPressedEvent& pressedEvent = static_cast<KeyPressedEvent&>(aKeyboardEvent);
				SetButtonState(GetKeyboardButtonFromPlatform(pressedEvent.GetKeyCode()), true);
				break;
			}
			case EventType::KeyReleased:
			{
				KeyReleasedEvent& keyReleasedEvent = static_cast<KeyReleasedEvent&>(aKeyboardEvent);
				SetButtonState(GetKeyboardButtonFromPlatform(keyReleasedEvent.GetKeyCode()), false);
				break;
			}

			default:
			{

				SAMPO_ASSERT_MSG(false, "Non keyboard event passed through keyboard event handler!");
				break;
			}
		}
	}
}