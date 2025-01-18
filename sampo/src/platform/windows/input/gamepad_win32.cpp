#include "sampo_pch.hpp"
#include "sampo/input/gamepad.hpp"

#include "sampo/events/gamepad_event.hpp"

#include <GLFW/glfw3.h>
#include <imgui.h>

namespace Sampo
{
	bool Gamepad::InitDevice()
	{
		m_RequiresPolling = true;

		m_DeviceInformation.m_DeviceName = glfwGetJoystickName(m_PlatformId);
		m_DeviceInformation.m_DeviceGUID = glfwGetJoystickGUID(m_PlatformId);
		m_GamepadName = glfwGetGamepadName(m_PlatformId);

		if (strcmp(m_GamepadName.c_str(), "PS5 Controller") == 0)
			m_GamepadType = GamepadType::kPS5;

		return true;
	}

	void Gamepad::PollDevice()
	{
		GLFWgamepadstate state;
		if (!glfwGetGamepadState(m_PlatformId, &state))
			return;

		for (int i = 0; i <= GLFW_GAMEPAD_BUTTON_LAST - 4; i++)
		{
			// Should translate based on detected type
			GamepadButton button = static_cast<GamepadButton>(i + 1);
			SetButtonState(button, state.buttons[i]);
		}

		for (int i = 0; i <= GLFW_GAMEPAD_AXIS_LAST; i++)
		{
			// Should translate based on detected type
			GamepadAxis axis = static_cast<GamepadAxis>(i + 1);
			SetAxisState(axis, state.axes[i]);
		}
	}

	void Gamepad::OnGamepadEvent(Event& aGamepadEvent)
	{
		SAMPO_UNUSED(aGamepadEvent);
	}

	void Gamepad::ImGuiDebug()
	{
		std::ostringstream stringStream;
		stringStream << m_PlatformId << " - " << GetDeviceName();

		if (ImGui::TreeNode(stringStream.str().c_str()))
		{
			ImGui::Text("Gamepad UID: %s", GetDeviceUID().data());
			ImGui::Text("Gamepad Slot: %d, type: %d", m_PlatformId, static_cast<int>(m_GamepadType));
			ImGui::Text("Gamepad Name: %s", m_GamepadName.c_str());

			ImGui::TreePop();

			constexpr ImVec2 buttonSize(30, 20);
			constexpr ImColor buttonPressedColor(1.0f, 0.4f, 0.4f);

			auto printButton = [&buttonSize, &buttonPressedColor, this](GamepadButton aKey, const char* label) {
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

			auto printAxis = [&buttonSize, &buttonPressedColor, this](GamepadAxis anAxis, const char* label) {
				float axisValue = GetGamepadAxis(anAxis);
				ImGui::PushID(static_cast<int>(anAxis));
				ImGui::SliderFloat(label, &axisValue, -1.0f, 1.0f, "%.2f");
				ImGui::PopID();
			};

			printButton(GamepadButton::kActionDown, "A");
			printButton(GamepadButton::kActionRight, "B");
			printButton(GamepadButton::kActionLeft, "X");
			printButton(GamepadButton::kActionUp, "Y");
			printButton(GamepadButton::kLeftBumper, "LB");
			printButton(GamepadButton::kRightBumper, "RB");
			printButton(GamepadButton::kSelect, "Select");
			printButton(GamepadButton::kStart, "Start");
			printButton(GamepadButton::kHome, "Home");
			printButton(GamepadButton::kLeftStick, "LS");
			printButton(GamepadButton::kRightStick, "RS");
			printButton(GamepadButton::kDpadUp, "Up");
			printButton(GamepadButton::kDpadLeft, "Left");
			printButton(GamepadButton::kDpadDown, "Down");
			printButton(GamepadButton::kDpadRight, "Right");
			ImGui::NewLine();

			printAxis(GamepadAxis::kLeftX, "Left X");
			printAxis(GamepadAxis::kLeftY, "Left Y");
			printAxis(GamepadAxis::kRightX, "Right X");
			printAxis(GamepadAxis::kRightY, "Right Y");
			printAxis(GamepadAxis::kLeftTrigger, "Left Trigger");
			printAxis(GamepadAxis::kRightTrigger, "Right Trigger");
		}
	}
}