#pragma once
namespace Sampo
{
	enum class InputType
	{
		kUnknown = 0,
		kKeyboard,
		kMouse,
		kGamepad
	};

	enum class GamepadType
	{
		kNotGamepad = 0,
		kPS4,
		kPS5,
		kXBOX,
		kSwitch
	};
}