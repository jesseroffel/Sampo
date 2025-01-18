#include "sampo_pch.hpp"
#include "input_win32.hpp"

#include "sampo/input/gamepad.hpp"

#include <GLFW/glfw3.h>

namespace Sampo
{
	bool Win32Input::Init()
	{
		if (!Input::Init())
			return false;

		DiscoverConnectedGamepads();
		return true;
	}

	void Win32Input::DiscoverConnectedGamepads()
	{
		for (int gamepadId = GLFW_JOYSTICK_1; gamepadId <= GLFW_JOYSTICK_LAST; gamepadId++)
		{
			if (!glfwJoystickPresent(gamepadId))
				continue;

			const Gamepad* foundGamepad = GetGamepadByPlatformId(gamepadId);
			if (foundGamepad)
			{
				SAMPO_ASSERT_MSG(false, "Already have a gamepad with this id");
				continue;

			}

			AddInputDevice(new Gamepad(gamepadId));
		}
	}
}