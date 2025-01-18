#pragma once
#include "input_device.hpp"
#include "input_mapping.hpp"
#include "input_types.hpp"

namespace Sampo
{
	class Event;

	class Gamepad : public InputDevice
	{
	public:
		Gamepad(int aPlatformId);

		bool InitDevice() override;

		void PollDevice() override;

		bool IsValidButton(GamepadButton aGamepadButton) const;
		bool IsValidAxis(GamepadAxis aGamepadAxis) const;

		void SetButtonState(GamepadButton aGamepadButton, bool aIsDown);
		bool GetIsButtonPressed(GamepadButton aGamepadButton) const;

		void SetAxisState(GamepadAxis aGamepadAxis, float aValue);
		float GetGamepadAxis(GamepadAxis aGamepadAxis) const;

		virtual int GetPlatformId() const { return m_PlatformId; }
		GamepadType GetGamepadType() const { return m_GamepadType; }
		void SetGamepadType(GamepadType aType) { m_GamepadType = aType; }
		std::string_view GetGamepadName() const { return m_GamepadName; }

		void OnGamepadEvent(Event& aGamepadEvent);
		static int GetPlatformIdFromEvent(Event& aGamepadEvent);

		void ImGuiDebug() override;

	private:
		bool m_Buttons[15]{ false };
		float m_Axes[6]{ 0.0f };

		std::string m_GamepadName{ "Unknown" };
		int m_PlatformId{ -1 };
		GamepadType m_GamepadType { GamepadType::kUnknown };
	};
}