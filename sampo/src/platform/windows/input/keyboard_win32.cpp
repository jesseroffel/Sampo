#include "sampo_pch.hpp"
#include "sampo/input/keyboard.hpp"

#include "sampo/events/key_event.hpp"

#include <GLFW/glfw3.h>
#include <imgui.h>

namespace Sampo
{
	KeyboardButton Keyboard::GetKeyboardButtonFromPlatform(int aKeyboardCode)
	{
		KeyboardButton button = KeyboardButton::kUnknownButton;
		switch(aKeyboardCode)
		{
			case GLFW_KEY_SPACE: button = KeyboardButton::kSPACE; break;
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
				return;
			}
			case EventType::KeyReleased:
			{
				KeyReleasedEvent& keyReleasedEvent = static_cast<KeyReleasedEvent&>(aKeyboardEvent);
				SetButtonState(GetKeyboardButtonFromPlatform(keyReleasedEvent.GetKeyCode()), false);
				return;
			}
		}
		SAMPO_ASSERT_MSG(false, "Non keyboard event passed through keyboard event handler!");
	}

	void Keyboard::ImGuiDebug()
	{
		constexpr ImVec2 buttonSize(30, 20);
		constexpr ImColor buttonPressedColor(1.0f, 0.4f, 0.4f);

		auto printKey = [&buttonSize, &buttonPressedColor, this](KeyboardButton aKey, const char* label) {
			bool isPressed = GetIsButtonPressed(aKey);
			if (isPressed)
				ImGui::PushStyleColor(ImGuiCol_Button, static_cast<ImVec4>(buttonPressedColor));
			ImGui::PushID(static_cast<int>(aKey));
			ImGui::Button(label, buttonSize);
			if (isPressed)
				ImGui::PopStyleColor(1);
			ImGui::PopID();
			ImGui::SameLine();
		};

		auto printEmpty = [&buttonSize](const char* label) {
			ImGui::Button(label, buttonSize);
			ImGui::SameLine();
		};

		printKey(KeyboardButton::kESCAPE, "ESC");
		printEmpty("##row01");
		printKey(KeyboardButton::kF1, "F1");
		printKey(KeyboardButton::kF2, "F2");
		printKey(KeyboardButton::kF3, "F3");
		printKey(KeyboardButton::kF4, "F4");
		printKey(KeyboardButton::kF5, "F5");
		printKey(KeyboardButton::kF6, "F6");
		printKey(KeyboardButton::kF7, "F7");
		printKey(KeyboardButton::kF8, "F8");
		printKey(KeyboardButton::kF9, "F9");
		printKey(KeyboardButton::kF10, "F10");
		printKey(KeyboardButton::kF11, "F11");
		printKey(KeyboardButton::kF12, "F12");
		printEmpty("##row02");
		printKey(KeyboardButton::kPRINT_SCREEN, "PSC");
		printKey(KeyboardButton::kSCROLL_LOCK, "SLK");
		printKey(KeyboardButton::kPAUSE, "PAU");

		ImGui::NewLine();
		printKey(KeyboardButton::kGRAVE_ACCENT, "`");
		printKey(KeyboardButton::k1, "1");
		printKey(KeyboardButton::k2, "2");
		printKey(KeyboardButton::k3, "3");
		printKey(KeyboardButton::k4, "4");
		printKey(KeyboardButton::k5, "5");
		printKey(KeyboardButton::k6, "6");
		printKey(KeyboardButton::k7, "7");
		printKey(KeyboardButton::k8, "8");
		printKey(KeyboardButton::k9, "9");
		printKey(KeyboardButton::k0, "0");
		printKey(KeyboardButton::kMINUS, "-");
		printKey(KeyboardButton::kEQUAL, "=");
		printKey(KeyboardButton::kBACKSPACE, "BAC");
		printEmpty("##row11");
		printKey(KeyboardButton::kINSERT, "INS");
		printKey(KeyboardButton::kHOME, "HOM");
		printKey(KeyboardButton::kPAGE_UP, "PGU");
		printEmpty("##row12");
		printKey(KeyboardButton::kNUM_LOCK, "NLK");
		printKey(KeyboardButton::kKP_DIVIDE, "/");
		printKey(KeyboardButton::kKP_MULTIPLY, "*");
		printKey(KeyboardButton::kKP_SUBTRACT, "-");

		ImGui::NewLine();
		printKey(KeyboardButton::kTAB, "TAB");
		printKey(KeyboardButton::kQ, "Q");
		printKey(KeyboardButton::kW, "W");
		printKey(KeyboardButton::kE, "E");
		printKey(KeyboardButton::kR, "R");
		printKey(KeyboardButton::kT, "T");
		printKey(KeyboardButton::kY, "Y");
		printKey(KeyboardButton::kU, "U");
		printKey(KeyboardButton::kI, "I");
		printKey(KeyboardButton::kO, "O");
		printKey(KeyboardButton::kP, "P");
		printKey(KeyboardButton::kLEFT_BRACKET, "[");
		printKey(KeyboardButton::kRIGHT_BRACKET, "]");
		printKey(KeyboardButton::kBACKSLASH, "\\");
		printEmpty("##row21");
		printKey(KeyboardButton::kDELETE, "DEL");
		printKey(KeyboardButton::kEND, "END");
		printKey(KeyboardButton::kPAGE_DOWN, "PGD");
		printEmpty("##row22");
		printKey(KeyboardButton::kKP_7, "7");
		printKey(KeyboardButton::kKP_8, "8");
		printKey(KeyboardButton::kKP_9, "9");
		printKey(KeyboardButton::kKP_ADD, "+");

		ImGui::NewLine();
		printKey(KeyboardButton::kCAPS_LOCK, "CAP");
		printKey(KeyboardButton::kA, "A");
		printKey(KeyboardButton::kS, "S");
		printKey(KeyboardButton::kD, "D");
		printKey(KeyboardButton::kF, "F");
		printKey(KeyboardButton::kG, "G");
		printKey(KeyboardButton::kH, "H");
		printKey(KeyboardButton::kJ, "J");
		printKey(KeyboardButton::kK, "K");
		printKey(KeyboardButton::kL, "L");
		printKey(KeyboardButton::kSEMICOLON, ";");
		printKey(KeyboardButton::kAPOSTROPHE, "'");
		printKey(KeyboardButton::kENTER, "ENT");
		printEmpty("##row31");
		printEmpty("##row32");
		printEmpty("##row33");
		printEmpty("##row34");
		printEmpty("##row35");
		printEmpty("##row36");
		printKey(KeyboardButton::kKP_4, "4");
		printKey(KeyboardButton::kKP_5, "5");
		printKey(KeyboardButton::kKP_6, "6");
		printEmpty("##row37");

		ImGui::NewLine();
		printKey(KeyboardButton::kLEFT_SHIFT, "LSH");
		printKey(KeyboardButton::kZ, "Z");
		printKey(KeyboardButton::kX, "X");
		printKey(KeyboardButton::kC, "C");
		printKey(KeyboardButton::kV, "V");
		printKey(KeyboardButton::kB, "B");
		printKey(KeyboardButton::kN, "N");
		printKey(KeyboardButton::kM, "M");
		printKey(KeyboardButton::kCOMMA, ",");
		printKey(KeyboardButton::kPERIOD, ".");
		printKey(KeyboardButton::kSLASH, "/");
		printKey(KeyboardButton::kRIGHT_SHIFT, "RSH");
		printEmpty("##row41");
		printEmpty("##row42");
		printEmpty("##row43");
		printEmpty("##row44");
		printKey(KeyboardButton::kUP, "UP");
		printEmpty("##row45");
		printEmpty("##row46");
		printKey(KeyboardButton::kKP_1, "1");
		printKey(KeyboardButton::kKP_2,  "2");
		printKey(KeyboardButton::kKP_3, "3");
		printKey(KeyboardButton::kKP_ENTER, "ENT");

		ImGui::NewLine();
		printKey(KeyboardButton::kLEFT_CONTROL,  "LCL");
		printKey(KeyboardButton::kLEFT_SUPER, "LSH");
		printKey(KeyboardButton::kLEFT_ALT, "LAL");
		printEmpty("##row51");
		printKey(KeyboardButton::kWorld1, "WO1");
		printEmpty("##row52");
		printKey(KeyboardButton::kSPACE, "SPC");
		printEmpty("##row53");
		printKey(KeyboardButton::kWorld2, "WO2");
		printEmpty("##row54");
		printKey(KeyboardButton::kRIGHT_ALT, "RAL");
		printKey(KeyboardButton::kRIGHT_SUPER, "RSU");
		printKey(KeyboardButton::kMENU, "MEN");
		printKey(KeyboardButton::kRIGHT_CONTROL, "RCL");
		printEmpty("##row55");
		printKey(KeyboardButton::kLEFT, "LEF");
		printKey(KeyboardButton::kDOWN, "DWN");
		printKey(KeyboardButton::kRIGHT, "RIG");
		printEmpty("##row56");
		printKey(KeyboardButton::kKP_0, "0");
		printEmpty("##row57");
		printKey(KeyboardButton::kKP_DECIMAL, ".");
		printEmpty("##row58");

		ImGui::NewLine();
	}
}