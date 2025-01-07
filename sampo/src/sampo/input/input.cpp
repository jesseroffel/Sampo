#include "sampo_pch.hpp"
#include "sampo/input/input.hpp"

#include "sampo/input/keyboard.hpp"
#include "sampo/input/mouse.hpp"

#include "sampo/events/event.hpp"

#include <imgui.h>

namespace Sampo
{
	Input::~Input()
	{
		for (int i = 0; i < myInputDevices.size(); i++)
			delete myInputDevices[i];
	}

	bool Input::Init()
	{
		InputDevice* mouse = AddInputDevice(new Mouse());
		m_Mouse = static_cast<Mouse*>(mouse);
		if (!m_Mouse)
			return false;

		InputDevice* keyboard = AddInputDevice(new Keyboard());
		m_Keyboard = static_cast<Keyboard*>(keyboard);
		if (!m_Keyboard)
			return false;

		return true;
	}

	InputDevice* Input::AddInputDevice(InputDevice* anInputDevice)
	{
		if (!anInputDevice->InitDevice())
		{
			delete anInputDevice;
			return nullptr;
		}
		
		return myInputDevices.emplace_back(anInputDevice);
	}

	int Input::GetFirstInputDeviceIndexByType(InputType anInputType) const
	{
		if (myInputDevices.empty())
			return -1;

		for (int i = 0; i < myInputDevices.size(); i++)
		{
			const InputDevice* inputDevice = myInputDevices[i];
			if (inputDevice->GetInputType() == anInputType)
				return i;
		}
		
		return -1;
	}

	const InputDevice* Input::GetInputDevice(uint32 anInputDeviceIndex) const
	{
		SAMPO_ASSERT(anInputDeviceIndex < myInputDevices.size());
		return myInputDevices[anInputDeviceIndex];
	}

	std::vector<const InputDevice*> Input::GetInputDevicesByUserIndex(int anUserIndex) const
	{
		std::vector<const InputDevice*> foundDevices;

		for (const InputDevice* device : myInputDevices)
		{
			if (device->GetUserIndex() != anUserIndex)
				continue;

			foundDevices.emplace_back(device);
		}
		return foundDevices;
	}

	std::vector<const InputDevice*> Input::GetAllInputDevicesOfTypeInputType(InputType anInputType) const
	{
		std::vector<const InputDevice*> foundDevices;

		for (const InputDevice* device : myInputDevices)
		{
			if (device->GetInputType() != anInputType)
				continue;

			foundDevices.emplace_back(device);
		}
		return foundDevices;
	}

	void Input::OnMouseEvent(Event& aMouseEvent)
	{
		SAMPO_ASSERT(m_Mouse);

		if (!aMouseEvent.IsInCategory(EventCategory::EventInput))
			return;

		m_Mouse->OnMouseEvent(aMouseEvent);
	}

	void Input::OnKeyboardEvent(Event& aKeyboardEvent)
	{
		SAMPO_ASSERT(m_Keyboard);

		if (!aKeyboardEvent.IsInCategory(EventCategory::EventInput))
			return;

		m_Keyboard->OnKeyboardEvent(aKeyboardEvent);
	}

	void Input::ImGuiDebug()
	{
		if (ImGui::TreeNode("Input"))
		{
			ImGui::Text("Connected devices: %d", myInputDevices.size());

			if (ImGui::CollapsingHeader("Mouse", ImGuiTreeNodeFlags_None))
			{
				const bool mousePresent = m_Mouse && m_Mouse->IsPresent();
				ImGui::Text("Present: [%s]", mousePresent ? "Enabled" : "Disconnected");
				if (mousePresent)
				{
					const MouseState& mouseState = m_Mouse->GetMouseState();
					if (mouseState.m_Enabled)
					{
						ImGui::Text("Position: %0.f, %0.f", mouseState.m_Position.x, mouseState.m_Position.y);
						ImGui::Text("Scroll: %0.f, %0.f", mouseState.m_ScrollOffset.x, mouseState.m_ScrollOffset.y);

						static ImGuiTableFlags flags = ImGuiTableFlags_SizingFixedFit | ImGuiTableFlags_RowBg | ImGuiTableFlags_Borders | ImGuiTableFlags_Hideable;

						if (ImGui::BeginTable("mousePressed", 5, flags))
						{
							ImGui::TableSetupColumn("Left", ImGuiTableColumnFlags_WidthFixed);
							ImGui::TableSetupColumn("Middle", ImGuiTableColumnFlags_WidthFixed);
							ImGui::TableSetupColumn("Right", ImGuiTableColumnFlags_WidthFixed);
							ImGui::TableSetupColumn("Mouse4", ImGuiTableColumnFlags_WidthFixed);
							ImGui::TableSetupColumn("Mouse5", ImGuiTableColumnFlags_WidthFixed);
							ImGui::TableHeadersRow();

							ImGui::TableNextRow();
							for (int i = 0; i < 5; i++)
							{
								ImGui::TableSetColumnIndex(i);
								ImGui::Text("%d", mouseState.m_Keys[i]);
							}

							ImGui::EndTable();
						}
					}
				}
			}

			if (ImGui::CollapsingHeader("Keyboard", ImGuiTreeNodeFlags_None))
			{
				const bool keyboardPresent = m_Keyboard;
				ImGui::Text("Present: [%s]", keyboardPresent ? "Enabled" : "Disconnected");
				if (keyboardPresent)
				{
					ImVec2 button_size(30, 20);
					Keyboard* currentKeyboard = m_Keyboard;
					auto printKey = [&button_size, &currentKeyboard](KeyboardButton aKey, const char* label) {
						bool isPressed = currentKeyboard->GetIsButtonPressed(aKey);
						if (isPressed)
							ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(7.0f, 0.6f, 0.6f));
						ImGui::PushID(static_cast<int>(aKey));
						ImGui::Button(label, button_size);
						if (isPressed)
							ImGui::PopStyleColor(1);
						ImGui::PopID();
						ImGui::SameLine();
					};

					printKey(KeyboardButton::kESCAPE, "ESC");
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
					printKey(KeyboardButton::kINSERT, "INS");
					printKey(KeyboardButton::kHOME, "HOM");
					printKey(KeyboardButton::kPAGE_UP, "PGU");
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
					printKey(KeyboardButton::kLEFT_BRACKET, "{");
					printKey(KeyboardButton::kRIGHT_BRACKET, "}");
					printKey(KeyboardButton::kBACKSLASH, "\\");
					printKey(KeyboardButton::kDELETE, "DEL");
					printKey(KeyboardButton::kEND, "END");
					printKey(KeyboardButton::kPAGE_DOWN, "PGD");
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
					printKey(KeyboardButton::kSLASH, "/");
					printKey(KeyboardButton::kENTER, "ENT");
					printKey(KeyboardButton::kKP_4, "4");
					printKey(KeyboardButton::kKP_5, "5");
					printKey(KeyboardButton::kKP_6, "6");

					ImGui::NewLine();
					printKey(KeyboardButton::kLEFT_SHIFT, "LSH");
					printKey(KeyboardButton::kWorld2, "|");
					printKey(KeyboardButton::kZ, "Z");
					printKey(KeyboardButton::kX, "X");
					printKey(KeyboardButton::kC, "C");
					printKey(KeyboardButton::kV, "V");
					printKey(KeyboardButton::kB, "B");
					printKey(KeyboardButton::kN, "N");
					printKey(KeyboardButton::kCOMMA, ",");
					printKey(KeyboardButton::kPERIOD, ".");
					printKey(KeyboardButton::kSLASH, "?");
					printKey(KeyboardButton::kRIGHT_SHIFT, "RSH");
					printKey(KeyboardButton::kUP, "UP");
					printKey(KeyboardButton::kKP_1, "1");
					printKey(KeyboardButton::kKP_2, "2");
					printKey(KeyboardButton::kKP_3, "3");
					printKey(KeyboardButton::kKP_ENTER, "ENT");

					ImGui::NewLine();
					printKey(KeyboardButton::kLEFT_CONTROL, "LCL");
					printKey(KeyboardButton::kLEFT_SUPER, "LSH");
					printKey(KeyboardButton::kLEFT_ALT, "LAL");
					printKey(KeyboardButton::kSPACE, "SPC");
					printKey(KeyboardButton::kRIGHT_ALT, "RAL");
					printKey(KeyboardButton::kMENU, "MEN");
					printKey(KeyboardButton::kRIGHT_CONTROL, "RCL");
					printKey(KeyboardButton::kLEFT, "LEF");
					printKey(KeyboardButton::kDOWN, "DWN");
					printKey(KeyboardButton::kRIGHT, "RIG");
					printKey(KeyboardButton::kKP_0, "0");
					printKey(KeyboardButton::kKP_DECIMAL, ".");
				}
			}
			ImGui::TreePop();
		}
	}
}