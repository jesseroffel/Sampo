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

		for (int i = 0; i <= GLFW_GAMEPAD_BUTTON_LAST; i++)
		{
			GamepadButton button = GetButtomFromPlatform(i);
			if (button != GamepadButton::kUnknownButton)
				SetButtonState(button, state.buttons[i]);
		}

		for (int i = 0; i <= GLFW_GAMEPAD_AXIS_LAST; i++)
		{
			GamepadAxis axis = GetAxisFromPlatform(i);
			if (axis != GamepadAxis::kUnknownAxis)
				SetAxisState(axis, state.axes[i]);
		}
	}

	GamepadButton Gamepad::GetButtomFromPlatform(int aGamepadButtonIndex)
	{
		GamepadButton button = GamepadButton::kUnknownButton;
		switch (aGamepadButtonIndex)
		{
		case GLFW_GAMEPAD_BUTTON_A: { button = GamepadButton::kActionDown; break; }
		case GLFW_GAMEPAD_BUTTON_B: { button = GamepadButton::kActionRight; break; }
		case GLFW_GAMEPAD_BUTTON_X: { button = GamepadButton::kActionLeft; break; }
		case GLFW_GAMEPAD_BUTTON_Y: { button = GamepadButton::kActionUp; break; }
		case GLFW_GAMEPAD_BUTTON_LEFT_BUMPER: { button = GamepadButton::kLeftBumper; break; }
		case GLFW_GAMEPAD_BUTTON_RIGHT_BUMPER: { button = GamepadButton::kRightBumper; break; }
		case GLFW_GAMEPAD_BUTTON_BACK: { button = GamepadButton::kSelect; break; }
		case GLFW_GAMEPAD_BUTTON_START: { button = GamepadButton::kStart; break; }
		case GLFW_GAMEPAD_BUTTON_GUIDE: { button = GamepadButton::kHome; break; }
		case GLFW_GAMEPAD_BUTTON_LEFT_THUMB: { button = GamepadButton::kLeftStick; break; }
		case GLFW_GAMEPAD_BUTTON_RIGHT_THUMB: { button = GamepadButton::kRightStick; break; }
		case GLFW_GAMEPAD_BUTTON_DPAD_UP: { button = GamepadButton::kDpadUp; break; }
		case GLFW_GAMEPAD_BUTTON_DPAD_RIGHT: { button = GamepadButton::kDpadRight; break; }
		case GLFW_GAMEPAD_BUTTON_DPAD_DOWN: { button = GamepadButton::kDpadDown; break; }
		case GLFW_GAMEPAD_BUTTON_DPAD_LEFT: { button = GamepadButton::kDpadLeft; break; }
		}
		return button;
	}

	GamepadAxis Gamepad::GetAxisFromPlatform(int aGamepadAxisIndex)
	{
		GamepadAxis axis = GamepadAxis::kUnknownAxis;
		switch (aGamepadAxisIndex)
		{
		case GLFW_GAMEPAD_AXIS_LEFT_X: { axis = GamepadAxis::kLeftX; break; }
		case GLFW_GAMEPAD_AXIS_LEFT_Y: { axis = GamepadAxis::kLeftY; break; }
		case GLFW_GAMEPAD_AXIS_RIGHT_X: { axis = GamepadAxis::kRightX; break; }
		case GLFW_GAMEPAD_AXIS_RIGHT_Y: { axis = GamepadAxis::kRightY; break; }
		case GLFW_GAMEPAD_AXIS_LEFT_TRIGGER: { axis = GamepadAxis::kLeftTrigger; break; }
		case GLFW_GAMEPAD_AXIS_RIGHT_TRIGGER: { axis = GamepadAxis::kRightTrigger; break; }
		}
		return axis;
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
			printButton(GamepadButton::kDpadRight, "Right");
			printButton(GamepadButton::kDpadDown, "Down");
			printButton(GamepadButton::kDpadLeft, "Left");
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