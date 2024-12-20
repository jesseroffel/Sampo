#pragma once

namespace Sampo
{
	enum class ButtonKeyState
	{
		kUp = 0,
		kFalling,
		kDown,
	};

	enum class MouseButton
	{
		kLeftMouse = 0,
		kMiddleMouse,
		kRightMouse,
		kMouseButton4,
		kMouseButton5,
		kUnknownMouseButton = 999
	};

	enum class Axes
	{
		kUnknownAxis = 0
	};

	enum class JoystickButton
	{
		kUnknownJoystickButton = 0
	};
}